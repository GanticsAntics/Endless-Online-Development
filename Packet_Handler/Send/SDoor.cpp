#include "..\stdafx.h"
#include "SDoor.h"
#include "..\Game.h"

void SDoor::SendDoorOpen(pt::ipstream* ClientStream, int x, int y,LPVOID game)
{
	Game* gme = (Game*)game;
	PacketBuilder builder = PacketBuilder(PACKET_DOOR, PACKET_OPEN);
	builder.AddChar(x);
	builder.AddChar(y);
	World::Send(gme,ClientStream,builder);
}
