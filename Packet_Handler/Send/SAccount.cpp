#include "..\stdafx.h"
#include "SAccount.h"
#include "..\game.h"

void SAccount::ChangePass(pt::ipstream* ClientStream, std::string AccountName, std::string OldPassword,  std::string NewPassword, LPVOID game)
{
	Game* gme = (Game*)game;
	PacketBuilder builder = PacketBuilder(PACKET_ACCOUNT, PACKET_AGREE);
	builder.AddBreakString(AccountName);
	builder.AddBreakString(OldPassword);
	builder.AddBreakString(NewPassword);
	World::Send(gme,ClientStream,builder);
}

void SAccount::RequestAccountCreate(pt::ipstream* ClientStream, std::string AccountName ,LPVOID game)
{
	Game* gme = (Game*)game;
	PacketBuilder builder = PacketBuilder(PACKET_ACCOUNT, PACKET_REQUEST);
	builder.AddString(AccountName);
	World::Send(gme,ClientStream,builder);
}
void SAccount::CreateAccount(pt::ipstream* ClientStream, std::string AccountName, std::string Password, std::string fullname, std::string location, std::string email, std::string computer, LPVOID game)
{
	
	std::string notice = "Create account " + AccountName + ". \nNOTE: The account creation process takes approximately three seconds otherwise the game server disconnects you.\n";
	World::DebugPrint(notice.c_str());
	CHAR volumeName[MAX_PATH + 1] = { 0 };
	CHAR fileSystemName[MAX_PATH + 1] = { 0 };
	DWORD serialNumber = 0;
	DWORD maxComponentLen = 0;
	DWORD fileSystemFlags = 0;
	
	GetVolumeInformationA(
	("C:\\"),
	volumeName,
	ARRAYSIZE(volumeName),
	&serialNumber,
	&maxComponentLen,
	&fileSystemFlags,
	fileSystemName,
	ARRAYSIZE(fileSystemName));

	std::string str = std::to_string(serialNumber);
	Game* gme = (Game*)game;
	char nameBuf[MAX_COMPUTERNAME_LENGTH + 2];
	DWORD nameBufSize;

	nameBufSize = sizeof nameBuf - 1;
	GetComputerNameA(nameBuf, &nameBufSize);
	std::string ComputerName = nameBuf;
	
	Sleep(4000);
	PacketBuilder builder = PacketBuilder(PACKET_ACCOUNT, PACKET_CREATE);
	builder.AddShort(gme->menu->SrvrCreateID);
	builder.Addbyte(255);
	builder.AddBreakString(AccountName);
	builder.AddBreakString(Password);
	builder.AddBreakString(fullname);
	builder.AddBreakString(location);
	builder.AddBreakString(email);
	builder.AddBreakString(ComputerName);
	builder.AddBreakString(str);
	World::Send(gme,ClientStream,builder);
}