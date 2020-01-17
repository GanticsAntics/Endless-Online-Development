#include "..\stdafx.h"
#include "SItem.h"
#include "..\Game.h"

void SItem::SendPickup(pt::ipstream* ClientStream, int UID,LPVOID game)
{
	Game* gme = (Game*)game;
	PacketBuilder builder = PacketBuilder(PACKET_ITEM, PACKET_GET);
	builder.AddShort(UID);
	World::Send(gme,ClientStream,builder);
}

void SItem::SendDrop(pt::ipstream* ClientStream, int ID, int amount, int x, int y, LPVOID game)
{
	Game* gme = (Game*)game;
	PacketBuilder builder = PacketBuilder(PACKET_ITEM, PACKET_DROP);
	builder.AddShort(ID);
	builder.AddInt(amount);
	builder.AddChar(x);
	builder.AddChar(y);
	World::Send(gme, ClientStream, builder);
}

void SItem::SendJunk(pt::ipstream* ClientStream, int ID, int amount, LPVOID game)
{
	Game* gme = (Game*)game;
	PacketBuilder builder = PacketBuilder(PACKET_ITEM, PACKET_JUNK);
	builder.AddShort(ID);
	builder.AddInt(amount);
	World::Send(gme, ClientStream, builder);
}