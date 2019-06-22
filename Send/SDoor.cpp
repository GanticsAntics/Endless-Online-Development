#include "SDoor.h"
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

void SDoor::SendDoorOpen(pt::ipstream* ClientStream, int x, int y,LPVOID game)
{
	Game* gme = (Game*)game;
	PacketBuilder builder = PacketBuilder(PACKET_DOOR, PACKET_OPEN);
	builder.AddChar(x);
	builder.AddChar(y);
	World::Send(gme,ClientStream,builder);
}
