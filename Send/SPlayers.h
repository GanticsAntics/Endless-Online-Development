#include "..\include\Ptypes\pinet.h"
#include "..\include\Ptypes\ptypes.h"
#include "..\include\EOServ\packet.hpp"

class SPlayers
{
	public:
		static void SendPlayerListRequest(pt::ipstream* ClientStream, LPVOID game);
};