#include "..\include\Ptypes\pinet.h"
#include "..\include\Ptypes\ptypes.h"
#include "..\include\EOServ\packet.hpp"

class SConnection
{
	public:
		static void SendPlayer(pt::ipstream* ClientStream, int response, LPVOID game);
		static void Ping(pt::ipstream* ClientStream, LPVOID game);
};