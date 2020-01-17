#include "..\stdafx.h"
#include "SRefresh.h"
#include "..\Game.h"

void SRefresh::RequestRefresh(pt::ipstream* ClientStream, LPVOID game)
{
	Game* gme = (Game*)game;
	PacketBuilder builder = PacketBuilder(PACKET_REFRESH, PACKET_REQUEST);
	builder.AddByte(0);
	World::Send(gme,ClientStream,builder);
}
