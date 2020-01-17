#pragma once 
class SAttack
{
	public:
		static void SendAttack(pt::ipstream* ClientStream, int Direction, LPVOID game);
};