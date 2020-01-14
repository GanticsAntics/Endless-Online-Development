#include "SInit.h"
#include "..\Game.h"
static int stupid_hash(int i)
{
++i;
return 110905 + (i % 9 + 1) * ((11092004 - i) % ((i % 11 + 1) * 119)) * 119 + i % 2004;
}

//using lexical_cast;
 void SInit::SendInit(pt::ipstream* ClientStream)
{
	
	PacketBuilder builder;
	int DickWinderA = 6 + (std::rand() % 6);
	builder.AddThree(stupid_hash(DickWinderA));
    builder.AddChar(0);
    builder.AddChar(0);
    builder.AddChar(28);
    builder.AddChar(112);
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

	std::string serial = std::to_string(serialNumber);
	builder.AddChar(serial.length());
	builder.AddString(serial);
	std::string strr = builder.Get();
	ClientStream->write(strr.c_str(),strr.length());
	try
	{
	ClientStream->flush();
	}
	catch(...)
	{
		World::ThrowMessage("Could not find server","The game server could not be found,\nplease try again at a later time."); 
		ClientStream->close();
		World::Connected = false;
		World::Connecting = false;
		return;
	}
}