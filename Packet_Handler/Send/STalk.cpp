#include "..\stdafx.h"
#include "STalk.h"
#include "..\Game.h"

void STalk::SendTalk(pt::ipstream* ClientStream, std::string Message,LPVOID game)
{
	Game* gme = (Game*)game;
	PacketBuilder builder = PacketBuilder(PACKET_TALK, PACKET_REPORT);
	builder.AddString(Message);
	World::Send(gme, ClientStream, builder);
	D3DCOLOR bgcol = D3DCOLOR_ARGB(150, 255, 255, 255);
	D3DCOLOR TextCol = D3DCOLOR_ARGB(200, 0, 0, 0);
	if (Message.find("<3") != Message.npos)
	{
		bgcol = D3DCOLOR_ARGB(150, 200, 66, 66);
		TextCol = D3DCOLOR_ARGB(200, 255, 255, 255);
	}
	if (Message.find("Hotdog") != Message.npos)
	{
		bgcol = D3DCOLOR_ARGB(150, 66, 200, 66);
		TextCol = D3DCOLOR_ARGB(200, 255, 255, 255);
	}
	if (Message.find("Gantic") != Message.npos)
	{
		bgcol = D3DCOLOR_ARGB(150, 66, 66, 200);
		TextCol = D3DCOLOR_ARGB(200, 255, 255, 255);
	}
	if (Message.find("EODev") != Message.npos)
	{
		bgcol = D3DCOLOR_ARGB(150, 66, 200, 200);
		TextCol = D3DCOLOR_ARGB(200, 255, 255, 255);
	}
	gme->Map_UserInterface->map_ChatBubbleHandler->AddMapMessage(Message, World::WorldCharacterID , false, bgcol, TextCol);
}
void STalk::SendGlobal(pt::ipstream* ClientStream, std::string Message, LPVOID game)
{
	Game* gme = (Game*)game;
	PacketBuilder builder = PacketBuilder(PACKET_TALK, PACKET_MSG);
	builder.AddString(Message);
	World::Send(gme, ClientStream, builder);
}