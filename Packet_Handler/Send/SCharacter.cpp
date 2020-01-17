#include "..\stdafx.h"
#include "SCharacter.h"
#include "..\Game.h"

void SCharacter::DeletePlayer(pt::ipstream* ClientStream, int deleteId, LPVOID game)
{
	Game* gme = (Game*)game;
	if(Menu::SrvrCharID > 0)
	{
		PacketBuilder builder = PacketBuilder(PACKET_CHARACTER, PACKET_REMOVE);
		builder.AddShort(Menu::SrvrDeleteID ); 
		builder.AddInt(Menu::SrvrCharID);
		World::Send(gme,ClientStream,builder);
	}
}

void SCharacter::RequestDeletePlayer(pt::ipstream* ClientStream, int deleteId, LPVOID game)
{
	Game* gme = (Game*)game;
	PacketBuilder builder = PacketBuilder(PACKET_CHARACTER, PACKET_TAKE);
	builder.AddInt(gme->menu->CSModels[deleteId].Game_ID);
	World::Send(gme,ClientStream,builder);
}
void SCharacter::RequestCreatePlayer(pt::ipstream* ClientStream, LPVOID game)
{
	Game* gme = (Game*)game;
	PacketBuilder builder = PacketBuilder(PACKET_CHARACTER, PACKET_REQUEST);
	builder.AddBreakString("NEW");
	World::Send(gme,ClientStream,builder);
}
void SCharacter::CreatePlayer(pt::ipstream* ClientStream, LPVOID game)
{
	Game* gme = (Game*)game;
	PacketBuilder builder = PacketBuilder(PACKET_CHARACTER, PACKET_CREATE);
	builder.AddShort(gme->menu->SrvrCreateID);
	builder.AddShort(gme->menu->CCModel->Gender);
	builder.AddShort(gme->menu->CCModel->HairStyle + 1);
	builder.AddShort(gme->menu->CCModel->HairCol);
	builder.AddShort(gme->menu->CCModel->SkinCol);
	builder.AddByte(255);//breakID
	builder.AddBreakString(gme->menu->CCModel->name);
	//builder.AddBreakString(gme->menu->CCModel->name);
	World::Send(gme,ClientStream,builder);
}