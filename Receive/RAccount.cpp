#include "Handler.h"
#include "..\Send\SCharacter.h"
#include "..\Send\SAccount.h"

std::string WCharToCharString(std::basic_string<wchar_t> str)
{
		char ch[260];
		char DefChar = ' ';
		WideCharToMultiByte(CP_ACP,0, str.c_str(),-1, ch,260,&DefChar, NULL);
		std::string ret(ch);
		return ret;
}

CLIENT_F_FUNC(Account)
{	
	switch(action)
	{	
	case(PACKET_REPLY): //reply to change pass request.
		{
			int ID = reader.GetShort(); 
			int val;
			if(reader.Length() > 6)
			{
				val = reader.GetByte();
			}
			std::string ret =  reader.GetEndString();
			if(ret == "OK")
			{
				if(ID == ACCOUNT_CHANGED)
				{
					game->SubStage = 0;
					World::ThrowMessage("Password changed", "Your password has changed, please use \nyour new password next time you login.");
				}
				else if(ID == ACCOUNT_CREATED)
				{
					game->SubStage = 0;
					World::ThrowMessage("Welcome", "Use your new account name and \npassword to login to the game.");
					game->SubStage=0;
					game->Stage = game->PMenu;
				}
				else
				{
					game->menu->SrvrCreateID = ID;
					SAccount::CreateAccount(game->world->connection->ClientStream,WCharToCharString(game->menu->TB_CAAccNme->text),WCharToCharString(game->menu->TB_CAPassWrdOne->text),WCharToCharString(game->menu->TB_CAPassWrdTwo->text),WCharToCharString(game->menu->TB_CAName->text),WCharToCharString(game->menu->TB_CACountry->text),WCharToCharString(game->menu->TB_CAEmail->text),game);
				}
			}
			else if(ret == "NO")
			{
				if(ID == ACCOUNT_CHANGE_FAILED)
				{
				World::ThrowMessage("Request denied", "The account name or old password you \nprovided do not match with our database.");
				}
				if(ID == ACCOUNT_EXISTS)
				{
				World::ThrowMessage("Already exists", "The account name you provided already \nexists in our database, use another.");
				}
				if(ID == ACCOUNT_NOT_APPROVED)
				{
				World::ThrowMessage("Request denied", "Sorry");
				}

			}
			else if(ret == "GO")
			{
				if(ID == ACCOUNT_CONTINUE || ID == ACCOUNT_CREATED)
				{
					World::ThrowMessage("Welcome", "Use your new account name and \npassword to login to the game.");
					game->SubStage=0;
					game->Stage = game->PMenu;

				}
			}
			break;
		}
		default :
			return false;
	}
	return true;
}