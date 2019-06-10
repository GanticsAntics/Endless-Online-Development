#include <array>
#include <stdexcept>
#include "include\EOServ\packet.hpp"

namespace Handler
{
	class Handler
	{
	void HandlePacket(PacketAction action, PacketFamily family);
	void SendPacket(PacketAction action, PacketFamily family);
	};
}