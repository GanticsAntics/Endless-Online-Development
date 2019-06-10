#include "..\include\Ptypes\pinet.h"
#include "..\include\Ptypes\ptypes.h"
#include "..\include\EOServ\packet.hpp"

class SAttack
{
	public:
		static void SendAttack(pt::ipstream* ClientStream, int Direction, LPVOID game);
};