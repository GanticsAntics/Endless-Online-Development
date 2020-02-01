#pragma once 
class SShop
{
	public:
		static void SendShopOpen(pt::ipstream* ClientStream, int ID, LPVOID game);
		static void SendShopPurchase(pt::ipstream* ClientStream, int ID, int Amount, LPVOID game);
		static void SendShopSell(pt::ipstream* ClientStream, int ID, int Amount, LPVOID game);
		static void SendShopCraft(pt::ipstream* ClientStream, int ID, LPVOID game);
};