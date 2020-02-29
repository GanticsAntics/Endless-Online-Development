#include "..\stdafx.h"
#include "SLogin.h"
#include "..\World.h"
#include "..\game.h"
void SLogin::SendLoginRequest(Game* _Game, pt::ipstream* ClientStream, std::string AccountName, std::string Password)
{
			PacketBuilder builder = PacketBuilder(PACKET_LOGIN,PACKET_REQUEST);
			builder.AddBreakString(AccountName);
            builder.AddBreakString(Password);
			World::Send(_Game,ClientStream,builder);
}