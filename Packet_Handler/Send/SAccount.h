#pragma once 
class SAccount
{
	public:
		static void ChangePass(pt::ipstream* ClientStream, std::string AccountName, std::string OldPassword,  std::string NewPassword, LPVOID game);
		static void RequestAccountCreate(pt::ipstream* ClientStream, std::string AccountName, LPVOID game);
		static void CreateAccount(pt::ipstream* ClientStream, std::string AccountName, std::string Password, std::string fullname, std::string location, std::string email, std::string computer, LPVOID game);

};