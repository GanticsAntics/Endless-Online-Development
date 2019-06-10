#include "stdafx.h"
#include "Game.h"
#include "Send\SInit.h"
#include "Receive\Handler.h"
#include <iostream>
#include <fstream>
#include "include/EOServ/eodata.hpp"
USING_PTYPES
pt::ipstream* ClientStream;
PacketHandler* Packethandler;
const int maxtoken = 4090;
pt::string IP;
int Conport;
bool Connection::ConnectionDropped;
bool Connection::Initialize(pt::string _IPAddress, int _port)
{
	IP = _IPAddress;
	Conport = _port;
	ConnectionDropped = false;
	return true;
}
char* PacketSize;
char* buffer;
bool Initialized;
unsigned int BufferBytesRecieved;
unsigned int LengthOfBuffer = 0;
PacketProcessor proc;
clock_t Tinit, timer;

void ConnectionTextPadTo(std::wstring& str, const size_t num, const char paddingChar = ' ')
{
	if (num > str.size())
		str.insert(0, num - str.size(), paddingChar);
}
void ProcessFile(const char* m_Buffer, Connection::FileContainer m_filecontainer)
{
	switch (m_filecontainer.File_Type)
	{
	case(Connection::FileType::Map):
		{
			std::ofstream output;

			wchar_t* dir_buffer = new wchar_t[1024];
			GetCurrentDirectory(1024, dir_buffer);
			std::wstring Path = L"";
			Path += dir_buffer;
			Path += L"\\Maps\\";
			wstring NumberPath = std::to_wstring(m_filecontainer.ID);
			ConnectionTextPadTo(NumberPath, 5, '0');
			Path += NumberPath += L".emf";

			output.open(Path, ios::out | ios::binary);
			output.write(m_Buffer, strlen(m_Buffer));
			std::string strMapID = "Map File " + std::to_string(m_filecontainer.ID) + " Recieved!";
			World::DebugPrint(strMapID.c_str());
			delete [] dir_buffer;
			output.close();

			break;
		}
	case(Connection::FileType::EIF):
		{
			std::ofstream output;

			wchar_t* dir_buffer = new wchar_t[1024];
			GetCurrentDirectory(1024, dir_buffer);
			std::wstring Path = L"";
			Path += dir_buffer;
			Path += L"\\pub\\dat";
			wstring NumberPath = std::to_wstring(m_filecontainer.ID);
			ConnectionTextPadTo(NumberPath, 3, '0');
			Path += NumberPath += L".eif";

			output.open(Path, ios::out | ios::binary);
			output.write(m_Buffer, strlen(m_Buffer));

			std::string strMapID = "Item File " + std::to_string(m_filecontainer.ID) + " Recieved!";
			World::DebugPrint(strMapID.c_str());
			delete [] dir_buffer;
			output.close();
			std::string str(Path.begin(), Path.end());
			World::EIF_File = new EIF("\pub\\dat001.eif");
			break;
		}
		case(Connection::FileType::ENF):
		{
			std::ofstream output;

			wchar_t* dir_buffer = new wchar_t[1024];
			GetCurrentDirectory(1024, dir_buffer);
			std::wstring Path = L"";
			Path += dir_buffer;
			Path += L"\\pub\\dtn";
			wstring NumberPath = std::to_wstring(m_filecontainer.ID);
			ConnectionTextPadTo(NumberPath, 3, '0');
			Path += NumberPath += L".enf";

			output.open(Path, ios::out | ios::binary);
			output.write(m_Buffer, strlen(m_Buffer));
			
			std::string strMapID = "NPC File " + std::to_string(m_filecontainer.ID) + " Recieved!";
			World::DebugPrint(strMapID.c_str());
			delete [] dir_buffer;
			output.close();
			std::string str(Path.begin(), Path.end());
			World::ENF_File = new ENF("\pub\\dtn001.enf");
			break;
		}
		case(Connection::FileType::ESF):
		{
			std::ofstream output;

			wchar_t* dir_buffer = new wchar_t[1024];
			GetCurrentDirectory(1024, dir_buffer);
			std::wstring Path = L"";
			Path += dir_buffer;
			Path += L"\\pub\\dsl";
			wstring NumberPath = std::to_wstring(m_filecontainer.ID);
			ConnectionTextPadTo(NumberPath, 3, '0');
			Path += NumberPath += L".esf";

			output.open(Path, ios::out | ios::binary);
			output.write(m_Buffer, strlen(m_Buffer));
			std::string strMapID = "Spell File " + std::to_string(m_filecontainer.ID) + " Recieved!";
			World::DebugPrint(strMapID.c_str());
			delete[] dir_buffer;
			output.close();
			std::string str(Path.begin(), Path.end());
			World::ESF_File = new ESF("\pub\\dsl001.esf");
			break;
		}
		case(Connection::FileType::ECF):
		{
			std::ofstream output;

			wchar_t* dir_buffer = new wchar_t[1024];
			GetCurrentDirectory(1024, dir_buffer);
			std::wstring Path = L"";
			Path += dir_buffer;
			Path += L"\\pub\\dat";
			wstring NumberPath = std::to_wstring(m_filecontainer.ID);
			ConnectionTextPadTo(NumberPath, 3, '0');
			Path += NumberPath += L".ecf";

			output.open(Path, ios::out | ios::binary);
			output.write(m_Buffer, strlen(m_Buffer));

			std::string strMapID = "Class File" + std::to_string(m_filecontainer.ID) + " Recieved!";
			World::DebugPrint(strMapID.c_str());
			delete[] dir_buffer;
			output.close();
			std::string str(Path.begin(), Path.end());
			World::ECF_File = new ECF("\pub\\dat001.ecf");;
			break;
		}
	}
}
void Connection::execute()
{
	try
	{
	Packethandler = new PacketHandler();
	Initialized = false;

	World::DebugPrint("Connecting to " + IP);
	Tinit = clock();
	this->ClientStream = new ipstream(IP,Conport);
	this->ClientStream->open();
	SInit::SendInit(this->ClientStream);
	ConnectionAccepted = false;

	} catch(...)
	{ 
		World::DebugPrint("Couldn't connect to the login server.");
		World::ThrowMessage("Could not find server","The game server could not be found,\nplease try again at a later time."); 
		World::Connected = false; 
		World::Connecting = false;
		
		return;
	}
	while(true)
	{		
		unsigned int streambufferlength = 0;
			try
			{
				if(World::Connecting)
				{
					timer = clock();
					if(timer - Tinit > 2500)
					{
						World::DebugPrint("Couldn't connect to the login server.");
						this->ConnectionDropped = false;
						World::ThrowMessage("Could not find server","The game server could not be found,\nplease try again at a later time.");
						World::Connected = false;
						World::Connecting = false;
						return;
					}
				}
				int val= ClientStream->get_dataavail();

				if(val > 0)
				{
					if(PacketSize == nullptr)
					{
						PacketSize = new char[2];
						ClientStream->read(PacketSize,2);
						LengthOfBuffer = proc.Number(PacketSize[0], PacketSize[1]);
						buffer = new char[LengthOfBuffer];

						val += 2;
					}

					if (val + BufferBytesRecieved <= LengthOfBuffer)
					{
						BufferBytesRecieved += val;
					}
					else if (val + BufferBytesRecieved > LengthOfBuffer)
					{
						BufferBytesRecieved = LengthOfBuffer;
					}

					if (BufferBytesRecieved >= LengthOfBuffer)
					{
						ClientStream->read(buffer, LengthOfBuffer);

						std::string newbuf = "";

						for (int i = 0; i < LengthOfBuffer; i++)
						{
							newbuf += buffer[i];
						}

						newbuf = World::Receive(V_Game, newbuf);
						PacketReader* reader = new PacketReader(newbuf);

						int familyID = reader->Family();
						int ActionID = reader->Action();
						if (familyID == 255 && ActionID == 255 && ConnectionAccepted)
						{
							int ID = reader->GetByte();
							if (ID == FileType::Map)
							{
								Connection::FileContainer filecont;
								filecont.File_Type = (FileType)ID;
								Game* gme = (Game*)V_Game;
								filecont.ID = gme->map->MapID;
								std::string str = reader->GetEndString();
								ProcessFile(str.c_str(), filecont);
								gme->map->LoadMap(filecont.ID);
							}
							else
							{
								Connection::FileContainer filecont;
								filecont.File_Type = (FileType)ID;
								filecont.ID = reader->GetChar();
								std::string str = reader->GetEndString();
								ProcessFile(str.c_str(), filecont);
							}
							
							
							FileQueue.pop_front();
						}
						else
						{
							std::string reportstr = "";
							reportstr += "[" + PacketProcessor::GetFamilyName(reader->Family()) + "]";
							reportstr += "[" + PacketProcessor::GetActionName(reader->Action()) + "]";

							for (int i = 0; i < reader->Length(); i++)
							{
								char* st = new char[8];
								_itoa(newbuf[i], st, 10);
								//reportstr += "[";
								//reportstr += st;
								//reportstr += "]";
								delete st;
							}
							World::DebugPrint(reportstr.c_str());
							Packethandler->HandlePacket(*reader, (Game*)V_Game, ClientStream);
						}

						delete reader;
						delete [] PacketSize;
						PacketSize = nullptr;
						delete [] buffer;
						BufferBytesRecieved = 0;
						LengthOfBuffer = 0;
					}
					else
					{
						//World::DebugPrint("Waiting On Data, , , ,");
					}
				}
			}
			catch(...)
			{
				if(!World::Connected && !this->ConnectionDropped)
				{
					World::DebugPrint("connection lost\n");
					this->ConnectionDropped = false;
					World::ThrowMessage("Could not find server","The game server could not be found,\nplease try again at a later time.");
				}
				ConnectionAccepted = false;
				World::Connected = false;
				World::Connecting = false;
				Game* gme = (Game*)V_Game;
				World::WorldCharacterID = -1;				
				return;
			}
	}
	World::DebugPrint("connection cut\n");
	World::Connected = false;
	World::Connecting = false;
}