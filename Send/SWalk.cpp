#include "SWalk.h"
#include "..\Game.h"
#include <iostream>
#include <ctime>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys\utime.h>
#include <iostream>
#include <chrono>
#include <ctime>

void SWalk::SendWalk(pt::ipstream* ClientStream, int Direction, int x, int y, LPVOID game)
{
	Game* gme = (Game*)game;
	PacketBuilder builder = PacketBuilder(PACKET_WALK, PACKET_PLAYER);
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

	SYSTEMTIME time;
	GetSystemTime(&time);
	
	builder.AddChar(procDirection);
	builder.AddThree((time.wHour * 3600) + (time.wMinute*60) + (time.wSecond*100) + (time.wMilliseconds / 10));
	builder.AddChar(x);
	builder.AddChar(y);
	World::Send(gme,ClientStream,builder);
}
