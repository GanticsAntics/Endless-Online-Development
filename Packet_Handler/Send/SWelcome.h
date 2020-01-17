#pragma once 
class SWelcome
{
	public:
		static void LoginCharacter(pt::ipstream* ClientStream, int PlayerID, LPVOID game);
		static void RequestFile(pt::ipstream* ClientStream, char FileType, LPVOID game);
		static void LoginWelcome(pt::ipstream* ClientStream, int charID, LPVOID game);
};