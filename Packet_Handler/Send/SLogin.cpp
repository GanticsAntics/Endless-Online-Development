#include "..\stdafx.h"
#include "SLogin.h"
#include "..\World.h"
#include "..\Game.h"
void SLogin::SendLoginRequest(LPVOID _Game, pt::ipstream* ClientStream, std::string AccountName, std::string Password)
{
			Game* gme = (Game*)_Game;
			PacketBuilder builder = PacketBuilder(PACKET_LOGIN,PACKET_REQUEST);
			builder.AddBreakString(AccountName);
            builder.AddBreakString(Password);
			World::Send((LPVOID)gme,ClientStream,builder);
}