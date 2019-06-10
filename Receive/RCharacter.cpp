#include "Handler.h"
#include "..\Send\SCharacter.h"
#include "..\Send\SConnection.h"
CLIENT_F_FUNC(Character)
{	
	switch(action)
		{		
			case PACKET_PLAYER: 
				{
					int ID = reader.GetShort();//Delete ID - Used for confirmations.
					Menu::SrvrCharID = reader.GetInt();//CharacterID
					Menu::SrvrDeleteID = ID;
					break;
				}
			case PACKET_REPLY: 
				{
						int ID = reader.GetShort();
						switch(ID)
						{
						case (CHARACTER_EXISTS):
							{
								World::ThrowMessage("Already exists", "The character name you provided \nalready exists in our database, use \nanother.");
								return false;
							}
						case (CHARACTER_FULL):
							{
								World::ThrowMessage("Request Denied", "You can only have 3 characters. Please \ndelete a character and try again.");
								return false;
							}
						case (CHARACTER_NOT_APPROVED):
							{
								World::ThrowMessage("Not approved", "The character name you provided is not \napproved,try another name.");
								return false;
							}
						case (CHARACTER_OK):
							{	
								World::ThrowMessage("Character created", "Your new character has been created and \nis ready to explore a new world.");
								game->SubStage = 0;
								break;
							}
						case (CHARACTER_DELETED):
							{
								break;
							}
						default:
							{
									Menu::SrvrCreateID = ID;
									std::string str = reader.GetEndString();
									if(str != "OK")
									{
										World::ThrowMessage("Request denied","You can only have 3 characters. Please \ndelete a character and try again");
										return false;
									}
									game->SubStage = 1;
									return true;
							}
						}

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
							game->menu->CSModels[i].HatID = reader.GetShort() - 1;
							game->menu->CSModels[i].ShieldID = reader.GetShort() - 1;
							game->menu->CSModels[i].WeaponID = reader.GetShort() - 1;
							game->menu->CSModels[i].AlignCharacter();
							reader.GetByte();
						}
						game->AccountCharacterSize = CharacterSize;
						
					break;
				}
			default:
				{
					return false;
				}
		}
	return true;
}