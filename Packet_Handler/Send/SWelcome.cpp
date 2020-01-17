#include "..\stdafx.h"
#include "SWelcome.h"
#include "..\Game.h"
#include "..\World.h"

void SWelcome::LoginCharacter(pt::ipstream* ClientStream, int ID, LPVOID game)
{
	Game* gme = (Game*)game;
	PacketBuilder builder = PacketBuilder(PACKET_WELCOME, PACKET_REQUEST);
	builder.AddInt(ID);
	World::Send(gme, ClientStream, builder);
}
void SWelcome::LoginWelcome(pt::ipstream* ClientStream, int Char_ID, LPVOID game)
{
	Game* gme = (Game*)game;
	PacketBuilder builder = PacketBuilder(PACKET_WELCOME, PACKET_MSG);
	builder.AddThree(0);//Unknown
	builder.AddInt(Char_ID);
	World::Send(gme, ClientStream, builder);
}

void SWelcome::RequestFile(pt::ipstream* ClientStream, char FileType, LPVOID game)
{
	Game* gme = (Game*)game;
	PacketBuilder builder = PacketBuilder(PACKET_WELCOME, PACKET_AGREE);
	builder.AddChar(FileType);
	if (FileType > 1)
	{
		builder.AddShort(2);
		builder.AddByte(2);
	}
	else
	{
		builder.AddShort(4);
		builder.AddShort(gme->map->MapID);
	}
	World::Send(gme, ClientStream, builder);
}
