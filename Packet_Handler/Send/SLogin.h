#pragma once 
class SLogin
{
		public:
				static void SendLoginRequest(LPVOID _Game, pt::ipstream* ClientStream, std::string AccountName, std::string Password);
};