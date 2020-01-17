#include "..\stdafx.h"
#include "SAttack.h"
#include "..\Game.h"


void SAttack::SendAttack(pt::ipstream* ClientStream, int Direction,LPVOID game)
{
	Game* gme = (Game*)game;
	PacketBuilder builder = PacketBuilder(PACKET_ATTACK, PACKET_USE);
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
	
	std::time_t t = std::time(0);   // get time now
	std::tm* now = std::localtime(&t);


	SYSTEMTIME time;
	GetSystemTime(&time);
	LONG time_ms = (time.wSecond * 1000) + time.wMilliseconds;

	builder.AddChar(procDirection);
	builder.AddThree((now->tm_hour * 3600) + (now->tm_min*60) + (now->tm_sec*100) + (time_ms/ 10));
	World::Send(gme,ClientStream,builder);
}
