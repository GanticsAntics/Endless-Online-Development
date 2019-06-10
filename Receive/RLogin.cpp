#include "Handler.h"

CLIENT_F_FUNC(Login)
{
		switch(action)
		{
			case PACKET_REPLY: 
				{
					int ID = reader.GetShort();
         
					switch(ID)
					{
					case(1):
						{
						World::ThrowMessage("Login refused", "The account name you provided does not\nexist in our database.");
						break;
						}
					case(2):
						{
							World::ThrowMessage( "Login refused", "The account or passsword you provided\ncould not be found in our database.");
							break;
						}
					case(3):
						{
							BYTE CharacterSize = reader.GetChar();
							reader.GetByte();
							reader.GetByte();
							for(int i = 0; i < 3;i++)
							{
								game->menu->CSModels[i] = CharacterModel(); 
								game->menu->CSModels[i].Initialize((LPVOID*)game); 
							}
	
							for (int i = 0; i < CharacterSize; i++)
							{
							
								//Character Character = new Character();
								 game->menu->CSModels[i].name = reader.GetBreakString();
								 if ( game->menu->CSModels[i].name[0] > 'a' &&  game->menu->CSModels[i].name[0] < 'z')
								 {
										 game->menu->CSModels[i].name[0] += 'A' - 'a';
								 }
								 game->menu->CSModels[i].ID = i;
								 int Gameid = reader.GetInt();
								 game->menu->CSModels[i].Game_ID = Gameid;
								 if(i ==0)
								 {
									 game->PlayerID = game->menu->CSModels[i].Game_ID;
								 }
								 game->menu->CSModels[i].level = reader.GetChar();
								 game->menu->CSModels[i].Gender = reader.GetChar();
								 game->menu->CSModels[i].HairStyle = reader.GetChar() - 1;
								 game->menu->CSModels[i].HairCol = reader.GetChar();
								 game->menu->CSModels[i].SkinCol = reader.GetChar();
								 game->menu->CSModels[i].admin = reader.GetChar();
								 game->menu->CSModels[i].ShoeID = reader.GetShort() - 1;
								 game->menu->CSModels[i].ArmorID = reader.GetShort() - 1;
								 game->menu->CSModels[i].HatID = reader.GetShort() - 1 + 5;
								 game->menu->CSModels[i].ShieldID = reader.GetShort() - 1;
								 game->menu->CSModels[i].WeaponID = reader.GetShort() - 1;
								 reader.GetByte();
							     game->menu->CSModels[i].AlignCharacter();
							}
							game->AccountCharacterSize = CharacterSize;
							game->Stage = game->PCharacterChoose;
							break;
						}
					case(5):
						{
							World::ThrowMessage( "Login refused", "This account is already logged on. Please\ntry again in a few minutes.");
							break;
						}
					case(6):
						{
							World::ThrowMessage( "Login refused", "The server is currently full.\nPlease try again in a few minutes.");
							break;
						}
					}
				}
			default:
					return false;
		}	
		return true;
}