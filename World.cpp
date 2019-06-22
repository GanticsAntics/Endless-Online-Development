#include "stdafx.h"
#include "World.h"
#include "Game.h"
#include <list>
using namespace std;

Game* Wgame;
bool World::Connected = false;
bool World::Connecting = false;
std::string World::MBMessage = "";
std::string World::MBTitle = "";
PacketProcessor World::PProcessor = PacketProcessor();
bool World::MBHidden = true;
unsigned int World::PacketCount = 0;
unsigned char World::RawPacketCount = 0;
int World::WorldCharacterID = -1;
ENF* World::ENF_File;
EIF* World::EIF_File;
ESF* World::ESF_File;
ECF* World::ECF_File;
World::World(LPVOID _Game)
{
	Wgame = (Game*)_Game;
	//File_ENF = new ENF("\\pub\\dtn001.enf");
	ENF_File = new ENF("\pub\\dtn001.enf");
	EIF_File = new EIF("\pub\\dat001.eif");
	ESF_File = new ESF("\pub\\dsl001.esf");
	ECF_File = new ECF("\pub\\dat001.ecf");
};
pt::thread* ListenThread;
void World::HandleTextInput(WPARAM Param, byte phase, byte subphase)
{
	TextType::iterator i;
	for(i = this->TextBoxLst.begin(); i != this->TextBoxLst.end();i++)
	{
		if(i->focused && i->Phase == phase && i->SubPhase == subphase)
		{
			i->OnKeyPress(Param);
			return;
		}
	}
};
void World::HandleKeyInput(WPARAM Param, byte phase, byte subphase)
{
	if (Wgame->Stage == Game::PInGame)
	{
		Wgame->map->OnKeyPress(Param);
	}
};
Textbox* World::RegisterTextBox(Textbox textbox)
{
	TextType::iterator i;
	int count = 0;
	for(i = this->TextBoxLst.begin(); i != this->TextBoxLst.end();i++)
	{
		if(i->WorldID == -1)
		{
			Textbox & s( *i );
			s =  textbox;
			return &s;
		}
		count++;
	}

	int ret = TextBoxLst.size();
	textbox.WorldID = ret;
	TextBoxLst.insert(TextBoxLst.end(),textbox);

	for(i = this->TextBoxLst.begin(); i != this->TextBoxLst.end();i++)
	{

		if(i->WorldID == ret)
		{
			Textbox & s( *i );
			return &s;
		}
	}
	return NULL;
};

void World::UnregisterTextBox(Textbox* textbox)
{
	TextType::iterator i;
	for(i = this->TextBoxLst.begin(); i != this->TextBoxLst.end();i++)
	{
		Textbox & s( *i );
		if(i->WorldID == textbox->WorldID)
		{
			s.WorldID = -1;
		}
	}
};

void World::CreateConnection()
{
		if(Connecting)
		{ 
			World::DebugPrint("A connection attempt has alreeady been established!");
			fflush( stdout );
			return;
		}
		this->connection = new Connection();
		this->connection->V_Game = (LPVOID)Wgame;
		Connecting = true;
		if(this->connection->Initialize(IniConfiguration::Host.c_str(), IniConfiguration::Port))
		{
			World::Connected = false;
			this->connection->start();	
		}
}
void World::DropConnection()
{
	if(this->Connected)
	{
		World::DebugPrint("Connection closed.\n");
		Connection::ConnectionDropped = true;
		this->connection->ClientStream->close();
		this->Connected = false;
	}
}
void World::MassTextBoxReset()
{
	TextType::iterator i;
	for(i = this->TextBoxLst.begin(); i != this->TextBoxLst.end();i++)
	{
		i->Reset();
	}
	
}
void World::RenderTextBoxes(ID3DXSprite* m_Sprite, byte phase, byte subphase)
{

	TextType::iterator i;
	for(i = this->TextBoxLst.begin(); i != this->TextBoxLst.end();i++)
	{
		if(i->Phase == phase && i->SubPhase == subphase && i->Phase < Game::GameStage::PInGame)
		{
			i->Render(m_Sprite);
		}
	}

}

void World::SetFocusedTextbox(Textbox* TxtBox)
{
	TextType::iterator i;
	for(i = this->TextBoxLst.begin(); i != this->TextBoxLst.end();i++)
	{
		if(i->WorldID == TxtBox->WorldID)
		{
			i->focused = true;
		}
		else
		{
			i->focused = false;
		}
	}
}

Textbox* World::GetFocusedTextbox()
{
	TextType::iterator i;
	for(i = this->TextBoxLst.begin(); i != this->TextBoxLst.end();i++)
	{
		if(i->focused)
		{
			Textbox & s( *i );
			return &s;
		}
	}
	return NULL;
}

void World::Send(LPVOID game, pt::ipstream* stream, PacketBuilder builder)
{	
	Game* gme = (Game*)game;
	try
	{
		gme->world->RawPacketCount = (gme->world->RawPacketCount + 1) % 10;

		std::string str = builder.Get();

		if ((gme->world->RawPacketCount + gme->world->PacketCount) >= 253)
		{
			int seqval = ((gme->world->RawPacketCount + gme->world->PacketCount));
			unsigned char* seqdat = new unsigned char[2];
			seqdat = gme->world->PProcessor.ENumber(seqval).data();
			builder.InsertByte(0, seqdat[1]);
			builder.InsertByte(0, seqdat[0]);
		}
		else
		{
			unsigned char seqval = gme->world->PProcessor.Number((gme->world->RawPacketCount + gme->world->PacketCount + 2));
			builder.InsertByte(0, seqval);
		}
		str = gme->world->PProcessor.Encode(builder.Get());
		std::string reportstr = "Sending : ";

		for (int i = 0; i < str.length(); i++)
		{
			char* st = new char[8];
			_itoa(str[i], st, 10);
			if (i == 2)
			{
				reportstr += "[" + PacketProcessor::GetActionName(PacketAction(str[i] + 128)) + "]";
			}
			else if (i == 3)
			{
				reportstr += "[" + PacketProcessor::GetFamilyName(PacketFamily(str[i] + 131)) + "]";
			}
			else
			{
				reportstr += "[";
				reportstr += st;
				reportstr += "]";
			}
		}
		World::DebugPrint(reportstr.c_str());

		int Sent = stream->write(str.c_str(), str.length());
		stream->flush();
	}
	catch (...)
	{
		World::ThrowMessage("Could not find server", "The game server could not be found,\nplease try again at a later time.");
		stream->close();
		World::Connected = false;
	}
}

std::string World::Receive(LPVOID game, std::string builder)
{
	Game* gme = (Game*)game;
	std::string str = gme->world->PProcessor.Decode(builder);
	return str;
}