#include "..\stdafx.h"
#include "SFace.h"
#include "..\game.h"

void SFace::SendFace(pt::ipstream* ClientStream, int Direction,LPVOID game)
{
	Game* gme = (Game*)game;
	PacketBuilder builder = PacketBuilder(PACKET_FACE, PACKET_PLAYER);
	int procDirection = Direction;
	if (Direction == 1)
	{
		procDirection = 2;
	}
	if (Direction == 2)
	{
		procDirection = 3;
	}
	if (Direction == 3)
	{
		procDirection = 1;
	}
	

	builder.AddChar(procDirection);
	World::Send(gme,ClientStream,builder);
}
