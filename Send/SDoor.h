#include "..\include\Ptypes\pinet.h"
#include "..\include\Ptypes\ptypes.h"
#include "..\include\EOServ\packet.hpp"

class SDoor
{
	public:
		static void SendDoorOpen(pt::ipstream* ClientStream, int x, int y, LPVOID game);
};