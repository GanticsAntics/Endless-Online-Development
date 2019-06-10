#include "STalk.h"
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

void STalk::SendTalk(pt::ipstream* ClientStream, std::string Message,LPVOID game)
{
	Game* gme = (Game*)game;
	PacketBuilder builder = PacketBuilder(PACKET_TALK, PACKET_REPORT);
	builder.AddString(Message);
	World::Send(gme, ClientStream, builder);
}
