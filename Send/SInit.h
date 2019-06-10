#include "..\include\Ptypes\pinet.h"
#include "..\include\Ptypes\ptypes.h"
#include "..\include\EOServ\packet.hpp"

class SInit
{
	public:
			static byte DickWinderA;
			static byte DickWinderB;
			static void SendInit(pt::ipstream* ClientStream);
};