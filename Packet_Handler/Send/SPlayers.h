#pragma once 
class SPlayers
{
	public:
		static void SendPlayerListRequest(pt::ipstream* ClientStream, LPVOID game);
};