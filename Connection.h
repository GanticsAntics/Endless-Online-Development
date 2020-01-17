#ifndef Connection_h
#define Connection_h

class Connection  : public pt::thread
{
public:
	LPVOID V_Game;
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
#endif //Connection_h