#include "Handler.h"
#include "..\Send\SConnection.h"
CLIENT_F_FUNC(Init)
{
	int id = reader.GetByte();
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
            int EIFVAL1 = reader.GetByte();
            int EIFVAL2 = reader.GetByte();

			int PCVal = EIFVAL1 * 7 - 13 + EIFVAL2;
			bool FindFlag = false;
			/*for (int i = 0; i <= 1757; i++)
			{
				int imax = (i + 13) / 7;
				int imin = std::max<int>(0, (i - 252 + 13 + 6) / 7);

				for (int ii = imin; ii < imax; ii++)
				{
					unsigned char s1 = ii;
					unsigned char s2 = i - ii * 7 + 13;
					if (s1 == EIFVAL1 && s2 == EIFVAL2)
					{
						PCVal = i;
						FindFlag = true;
						break;
					}
					if (FindFlag) { break; }
				}
			}*/
			//pt::string strs = "PCVAL = " + PCVal;
			//World::DebugPrint(strs);
			game->world->PacketCount = PCVal;
			game->world->RawPacketCount = 0;
            emulti_d = reader.GetByte();
            emulti_e = reader.GetByte();
			PlayerID = reader.GetShort();
			game->SendMulti = emulti_e;
			game->RecvMulti = emulti_d;
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
            int bid = reader.GetByte();
            int banlength = reader.GetByte();
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
