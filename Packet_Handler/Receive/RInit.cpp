#include "..\stdafx.h"
#include "Handler.h"
#include "..\Send\SConnection.h"
CLIENT_F_FUNC(Init)
{
	int id = reader.Getbyte();
    char emulti_e;
    char emulti_d;
	short PlayerID;

	switch (id)
    {
        case (1):
        {
			break;
		}
		case (2):
        {
			World::DebugPrint("Connection established!\n");
			World::Connecting = false;
			game->world->connection->ConnectionAccepted = true;
			if(game->menu->SelectID == 1)
			{
				game->Stage = Game::GameStage::PLogin;
			}
			else if(game->menu->SelectID == 2)
			{
				game->Stage = Game::GameStage::PCreateAccount;
			}
            int EIFVAL1 = reader.Getbyte();
            int EIFVAL2 = reader.Getbyte();

			int PCVal = EIFVAL1 * 7 - 13 + EIFVAL2;
			bool FindFlag = false;

			game->world->PacketCount = PCVal;
			game->world->RawPacketCount = 0;
            emulti_d = reader.Getbyte();
            emulti_e = reader.Getbyte();
			PlayerID = reader.GetShort();
			game->SendMulti = (unsigned char)emulti_e;
			game->RecvMulti = (unsigned char)emulti_d;
			game->world->PProcessor.SetEMulti(emulti_e,emulti_d);
			game->GameID = PlayerID;
			int response = reader.GetThree();
			game->menu->SelectID = 0;
			World::Connected = true;
			//Connection::ConnectionDropped = true;
			SConnection::SendPlayer(clientstream,response,game);
			break;
		}
		case (3):
        {
            int bid = reader.Getbyte();
            int banlength = reader.Getbyte();
            if (bid == 0)
            {
			 std::string message = "";
			 message += "The server dropped the connection,\nreason: temporary ip ban. ";
			 char* st = new char[8];
			 _itoa(banlength, st, 10);
			 message += st;
			 message +=  " minutes.";
             World::ThrowMessage("Connection is blocked", message);
            }
            else if (bid == 2)
            {
             World::ThrowMessage("Connection is blocked", "The server dropped the connection,\nreason: permanent ip ban.");
            }
            break;
         }
		 default:
         {
	     }
	}

	return true;
}
