#pragma once 
class SConnection
{
	public:
		static void SendPlayer(pt::ipstream* ClientStream, int response, LPVOID game);
		static void Ping(pt::ipstream* ClientStream, LPVOID game);
};