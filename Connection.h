#pragma once
#include <Ptypes/pinet.h>
#include <Ptypes/ptypes.h>
#include <Ptypes/pstreams.h>
#include <Ptypes/ptime.h>
#include <Ptypes/pasync.h>
#include <Ptypes/pport.h>
class Connection  : public pt::thread
{
public:
	Game* V_Game;
	bool Initialize(pt::string _IPAddress, int _port);
	void execute();

	enum FileType
	{
		Map = 5,
		EIF = 6,
		ENF,
		ESF,
		PlayerList = 11,
		ECF = 12
	};
	struct FileContainer
	{
		FileType File_Type;
		int ID;
	};
	bool ConnectionAccepted = false;
	std::list<FileContainer> FileQueue;
	//void ProcessFile(const char* m_Buffer, Connection::FileContainer m_filecontainer);
	Connection () : pt::thread(false){}
	pt::ipstream* ClientStream;
	static bool ConnectionDropped;

};
