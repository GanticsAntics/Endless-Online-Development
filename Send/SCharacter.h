#include "..\include\Ptypes\pinet.h"
#include "..\include\Ptypes\ptypes.h"
#include "..\include\EOServ\packet.hpp"

class SCharacter
{
	public:
		static void DeletePlayer(pt::ipstream* ClientStream, int deleteId, LPVOID game);
		static void RequestDeletePlayer(pt::ipstream* ClientStream, int deleteId, LPVOID game);
		static void RequestCreatePlayer(pt::ipstream* ClientStream, LPVOID game);
		static void CreatePlayer(pt::ipstream* ClientStream, LPVOID game);
};