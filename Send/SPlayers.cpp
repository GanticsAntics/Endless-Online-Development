#include "SPlayers.h"
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

void SPlayers::SendPlayerListRequest(pt::ipstream* ClientStream,LPVOID game)
{
	Game* gme = (Game*)game;
	PacketBuilder builder = PacketBuilder(PACKET_PLAYERS, PACKET_REQUEST);
	builder.AddByte(255);
	World::Send(gme,ClientStream,builder);
}
