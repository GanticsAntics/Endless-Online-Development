#include "..\include\Ptypes\pinet.h"
#include "..\include\Ptypes\ptypes.h"
#include "..\include\EOServ\packet.hpp"

class SPaperdoll
{
	public:
		static void SendPaperdollRequest(pt::ipstream* ClientStream, int PlayerID, LPVOID game);
		static void SendPaperdollRemove(pt::ipstream* ClientStream, int RemoveID, int SubID, LPVOID game);
		static void SendPaperdollAdd(pt::ipstream* ClientStream, int AddID, int SubID, LPVOID game);
};