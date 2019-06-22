#include "..\include\Ptypes\pinet.h"
#include "..\include\Ptypes\ptypes.h"
#include "..\include\EOServ\packet.hpp"

class STalk
{
	public:
		static void SendTalk(pt::ipstream* ClientStream, std::string Message, LPVOID game);
		static void SendGlobal(pt::ipstream* ClientStream, std::string Message, LPVOID game);
};