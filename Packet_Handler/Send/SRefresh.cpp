#include "..\stdafx.h"
#include "SRefresh.h"
#include "..\game.h"

void SRefresh::RequestRefresh(pt::ipstream* ClientStream, LPVOID game)
{
	Game* gme = (Game*)game;
	PacketBuilder builder = PacketBuilder(PACKET_REFRESH, PACKET_REQUEST);
	builder.Addbyte(0);
	World::Send(gme,ClientStream,builder);
}
