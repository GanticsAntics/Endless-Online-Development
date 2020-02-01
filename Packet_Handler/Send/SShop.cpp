#include "..\stdafx.h"
#include "SShop.h"
#include "..\Game.h"

void SShop::SendShopOpen(pt::ipstream* ClientStream, int ID, LPVOID game)
{
	Game* gme = (Game*)game;
	PacketBuilder builder = PacketBuilder(PACKET_SHOP, PACKET_OPEN);
	builder.AddShort(ID);
	World::Send(gme, ClientStream, builder);
}

void SShop::SendShopPurchase(pt::ipstream* ClientStream, int ID, int Amount, LPVOID game)
{
	Game* gme = (Game*)game;
	PacketBuilder builder = PacketBuilder(PACKET_SHOP, PACKET_BUY);
	builder.AddShort(ID);
	builder.AddInt(Amount);
	World::Send(gme, ClientStream, builder);
}

void SShop::SendShopSell(pt::ipstream* ClientStream, int ID, int Amount, LPVOID game)
{
	Game* gme = (Game*)game;
	PacketBuilder builder = PacketBuilder(PACKET_SHOP, PACKET_SELL);
	builder.AddShort(ID);
	builder.AddInt(Amount);
	World::Send(gme, ClientStream, builder);
}

void SShop::SendShopCraft(pt::ipstream* ClientStream, int ID, LPVOID game)
{
	Game* gme = (Game*)game;
	PacketBuilder builder = PacketBuilder(PACKET_SHOP, PACKET_CREATE);
	builder.AddShort(ID);
	World::Send(gme, ClientStream, builder);
}
