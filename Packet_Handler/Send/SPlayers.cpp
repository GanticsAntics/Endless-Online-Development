#include "..\stdafx.h"
#include "SPlayers.h"
#include "..\game.h"

void SPlayers::SendPlayerListRequest(pt::ipstream* ClientStream,LPVOID game)
{
	Game* gme = (Game*)game;
	PacketBuilder builder = PacketBuilder(PACKET_PLAYERS, PACKET_REQUEST);
	builder.Addbyte(255);
	World::Send(gme,ClientStream,builder);
}
