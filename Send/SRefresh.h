#include "..\include\Ptypes\pinet.h"
#include "..\include\Ptypes\ptypes.h"
#include "..\include\EOServ\packet.hpp"

class SRefresh
{
	public:
		static void RequestRefresh(pt::ipstream* ClientStream, LPVOID game);
};