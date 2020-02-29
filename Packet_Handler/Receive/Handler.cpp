#include "..\stdafx.h"
#include "Handler.h"

#define CLIENT_F_HANDLE(ID,FUNC) \
case ID: \
	result = this->Handle_##FUNC(family, action, reader, false, H_game, clientstream);\
	break

void PacketHandler::HandlePacket(PacketReader reader, Game* H_game, pt::ipstream* clientstream)
	{
		bool result = false;

		PacketFamily family = reader.Family();
		PacketAction action = reader.Action();

		switch(family)
		{
		CLIENT_F_HANDLE(PACKET_F_INIT,Init);
		CLIENT_F_HANDLE(PACKET_LOGIN,Login);
		CLIENT_F_HANDLE(PACKET_CHARACTER,Character);
		CLIENT_F_HANDLE(PACKET_CONNECTION,Connection);
		CLIENT_F_HANDLE(PACKET_ACCOUNT,Account);
		CLIENT_F_HANDLE(PACKET_WELCOME, Welcome);
		//CLIENT_F_HANDLE(PACKET_CHAIR, Chair);
		CLIENT_F_HANDLE(PACKET_CHEST, Chest);
		CLIENT_F_HANDLE(PACKET_WALK, Walk);
		CLIENT_F_HANDLE(PACKET_FACE, Face);
		CLIENT_F_HANDLE(PACKET_ATTACK, Attack);
		CLIENT_F_HANDLE(PACKET_PLAYERS, Players);
		CLIENT_F_HANDLE(PACKET_AVATAR, Avatar);
		CLIENT_F_HANDLE(PACKET_REFRESH, Refresh);
		CLIENT_F_HANDLE(PACKET_WARP, Warp);
		CLIENT_F_HANDLE(PACKET_NPC, NPC);
		CLIENT_F_HANDLE(PACKET_SHOP, Shop);
		CLIENT_F_HANDLE(PACKET_APPEAR, Appear);
		CLIENT_F_HANDLE(PACKET_TALK, Talk);
		CLIENT_F_HANDLE(PACKET_ITEM, Item);
		CLIENT_F_HANDLE(PACKET_PAPERDOLL, Paperdoll);
		default:;
		}

		#ifdef DEBUG
		//if (family != PACKET_CONNECTION || action != PACKET_NET)
		{
			//Console::Dbg("Packet %s[%i]_%s[%i] from %s", PacketProcessor::GetFamilyName(family).c_str(), family, PacketProcessor::GetActionName(action).c_str(), action, static_cast<std::string>(this->GetRemoteAddr()).c_str());
		}
		#endif
		//CLIENT_F_HANDLE(PacketAction::PACKET_A_INIT,PACKET_F_INIT);
	}

