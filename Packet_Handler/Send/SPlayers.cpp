#include "..\stdafx.h"
#include "SPlayers.h"
#include "..\Game.h"

void SPlayers::SendPlayerListRequest(pt::ipstream* ClientStream,LPVOID game)
{
	Game* gme = (Game*)game;
	PacketBuilder builder = PacketBuilder(PACKET_PLAYERS, PACKET_REQUEST);
	builder.AddByte(255);
	World::Send(gme,ClientStream,builder);
}
