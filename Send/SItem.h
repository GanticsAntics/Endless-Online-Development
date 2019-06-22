#include "..\include\Ptypes\pinet.h"
#include "..\include\Ptypes\ptypes.h"
#include "..\include\EOServ\packet.hpp"

class SItem
{
	public:
		static void SendPickup(pt::ipstream* ClientStream, int UID, LPVOID game);
		static void SendDrop(pt::ipstream* ClientStream, int ID, int amount , int x , int y, LPVOID game);
};