#include "..\include\Ptypes\pinet.h"
#include "..\include\Ptypes\ptypes.h"
#include "..\include\EOServ\packet.hpp"

class SLogin
{
		public:
				static void SendLoginRequest(LPVOID _Game, pt::ipstream* ClientStream, std::string AccountName, std::string Password);
};