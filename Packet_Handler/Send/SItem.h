#pragma once 
class SItem
{
	public:
		static void SendPickup(pt::ipstream* ClientStream, int UID, LPVOID game);
		static void SendDrop(pt::ipstream* ClientStream, int ID, int amount, int x, int y, LPVOID game);
		static void SendJunk(pt::ipstream* ClientStream, int ID, int amount, LPVOID game);
};