#include "..\include\Ptypes\pinet.h"
#include "..\include\Ptypes\ptypes.h"
#include "..\include\EOServ\packet.hpp"

class SWarp
{
	public:
		static void AcceptWarp(pt::ipstream* ClientStream, int MapID, int x, int y, LPVOID game);
		static void AcceptFile(pt::ipstream* ClientStream, LPVOID game);
};