#include "..\include\Ptypes\pinet.h"
#include "..\include\Ptypes\ptypes.h"
#include "..\include\EOServ\packet.hpp"

class SFace
{
	public:
		static void SendFace(pt::ipstream* ClientStream, int Direction, LPVOID game);
};