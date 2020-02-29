#include "..\stdafx.h"
#include "SChest.h"
#include "..\game.h"

void SChest::SendOpenChest(pt::ipstream* ClientStream, int x, int y,LPVOID game)
{
	Game* gme = (Game*)game;
	PacketBuilder builder = PacketBuilder(PACKET_CHEST, PACKET_OPEN);
	builder.AddChar(x);
	builder.AddChar(y);
	World::Send(gme,ClientStream,builder);
}
void SChest::SendAddChest(pt::ipstream* ClientStream, int ItemID, int Amount, LPVOID game)
{
	Game* gme = (Game*)game;
	PacketBuilder builder = PacketBuilder(PACKET_CHEST, PACKET_ADD);
	builder.AddChar(World::ChestX);
	builder.AddChar(World::ChestY);
	builder.AddShort(ItemID);
	builder.AddThree(Amount);
	World::Send(gme, ClientStream, builder);
}

void SChest::SendRemoveChest(pt::ipstream* ClientStream, int ItemID, LPVOID game)
{
	Game* gme = (Game*)game;
	PacketBuilder builder = PacketBuilder(PACKET_CHEST, PACKET_TAKE);
	builder.AddChar(World::ChestX);
	builder.AddChar(World::ChestY);
	builder.AddShort(ItemID);
	World::Send(gme, ClientStream, builder);
}