#include "..\include\Ptypes\pinet.h"
#include "..\include\Ptypes\ptypes.h"
#include "..\include\EOServ\packet.hpp"
#include "..\stdafx.h"
class SWelcome
{
	public:
		static void LoginCharacter(pt::ipstream* ClientStream, int PlayerID, LPVOID game);
		static void RequestFile(pt::ipstream* ClientStream, char FileType, LPVOID game);
		static void LoginWelcome(pt::ipstream* ClientStream, int charID, LPVOID game);
};