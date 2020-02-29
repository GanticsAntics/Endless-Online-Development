#include "..\stdafx.h"
#include "STalk.h"
#include "..\game.h"

void STalk::SendTalk(pt::ipstream* ClientStream, std::string Message,LPVOID game)
{
	Game* gme = (Game*)game;
	PacketBuilder builder = PacketBuilder(PACKET_TALK, PACKET_REPORT);
	builder.AddString(Message);
	World::Send(gme, ClientStream, builder);
	sf::Color bgcol = sf::Color::Color(255, 255, 255, 150);
	sf::Color TextCol = sf::Color::Color(0, 0, 0, 200);
	if (Message.find("<3") != Message.npos)
	{
		bgcol = sf::Color::Color(66, 200, 66, 150);
		TextCol = sf::Color::Color(255, 255, 255, 200);
	}
	if (Message.find("Hotdog") != Message.npos)
	{
		bgcol = sf::Color::Color(66, 66, 200, 150);
		TextCol = sf::Color::Color(255, 255, 255, 200);
	}
	if (Message.find("Gantic") != Message.npos)
	{
		bgcol = sf::Color::Color(200, 66, 66, 150);
		TextCol = sf::Color::Color(255, 255, 255, 200);
	}
	if (Message.find("EODev") != Message.npos)
	{
		bgcol = sf::Color::Color(200, 66, 200, 150);
		TextCol = sf::Color::Color(255, 255, 255, 200);
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