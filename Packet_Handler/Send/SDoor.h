#pragma once 
class SDoor
{
	public:
		static void SendDoorOpen(pt::ipstream* ClientStream, int x, int y, LPVOID game);
};