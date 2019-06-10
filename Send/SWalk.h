#include "..\include\Ptypes\pinet.h"
#include "..\include\Ptypes\ptypes.h"
#include "..\include\EOServ\packet.hpp"

class SWalk
{
	public:
		static void SendWalk(pt::ipstream* ClientStream, int Direction, int x, int y, LPVOID game);
};