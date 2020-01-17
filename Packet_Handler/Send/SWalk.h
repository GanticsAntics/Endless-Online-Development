#pragma once 
class SWalk
{
	public:
		static void SendWalk(pt::ipstream* ClientStream, int Direction, int x, int y, LPVOID game);
};