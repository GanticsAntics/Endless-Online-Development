#pragma once 
class SLogin
{
		public:
				static void SendLoginRequest(Game* _Game, pt::ipstream* ClientStream, std::string AccountName, std::string Password);
};