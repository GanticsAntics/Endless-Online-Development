#pragma once 
class SChest
{
	public:
		static void SendOpenChest(pt::ipstream* ClientStream, int x, int y, LPVOID game);
		static void SendAddChest(pt::ipstream* ClientStream, int ItemID, int Amount, LPVOID game);
		static void SendRemoveChest(pt::ipstream* ClientStream, int ItemID, LPVOID game);
};