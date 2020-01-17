#pragma once 
class STalk
{
	public:
		static void SendTalk(pt::ipstream* ClientStream, std::string Message, LPVOID game);
		static void SendGlobal(pt::ipstream* ClientStream, std::string Message, LPVOID game);
};