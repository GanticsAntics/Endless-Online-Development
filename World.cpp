#include "stdafx.h"
#include "Connection.h"
#include "World.h"

using namespace std;
bool World::Connected = false;
bool World::Connecting = false;


std::string World::MBMessage = "";
std::string World::MBTitle = "";
PacketProcessor World::PProcessor = PacketProcessor();
bool World::MBHidden = true;
bool World::UIBox_Hidden = true;
unsigned int World::PacketCount = 0;
unsigned char World::RawPacketCount = 0;
int World::WorldCharacterID = -1;
int World::ChestX = -1;
int World::ChestY = -1;
ENF* World::ENF_File;
EIF* World::EIF_File;
ESF* World::ESF_File;
ECF* World::ECF_File;
std::vector<World::OnlinePlayerContainer> World::OnlinePlayers;
World::World(Game* _Game)
{
	this->m_game = _Game;
	//File_ENF = new ENF("\\pub\\dtn001.enf");
	ENF_File = new ENF("\pub\\dtn001.enf");
	EIF_File = new EIF("\pub\\dat001.eif");
	ESF_File = new ESF("\pub\\dsl001.esf");
	ECF_File = new ECF("\pub\\dat001.ecf");
	
};
pt::thread* ListenThread;
void World::HandleTextInput(WPARAM Param, int  phase, int  subphase)
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
void World::HandleKeyInput(WPARAM Param, int  phase,int subphase)
{
	if (this->m_game->Stage == Game::PInGame)
	{
		this->m_game->map->OnKeyPress(Param);
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
		this->connection->V_Game = this->m_game;
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

int BlinkCount = 0;
bool ShowBlinker = false;
void World::RenderTextBoxes(int  phase,int  subphase)
{

	BlinkCount++;
	if (BlinkCount > this->m_game->FPS / 2)
	{
		Textbox* box = this->GetFocusedTextbox();

		if (ShowBlinker)
		{
			ShowBlinker = false;
			box->blinkhidden = true;
		}
		else
		{
			ShowBlinker = true;
			box->blinkhidden = false;
		}

		BlinkCount = 0;
	}
	TextType::iterator i;
	for(i = this->TextBoxLst.begin(); i != this->TextBoxLst.end();i++)
	{
		if(i->Phase == phase && i->SubPhase == subphase && i->Phase < Game::GameStage::PInGame)
		{
			i->Render();
		}
	}

}
void World::SetFocusedTextbox(Textbox* TxtBox)
{
	if (TxtBox == NULL) { return; }
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

void World::Send(Game* t_game, pt::ipstream* stream, PacketBuilder builder)
{	
	try
	{
		t_game->world->RawPacketCount = (t_game->world->RawPacketCount + 1) % 10;

		std::string str = builder.Get();

		if ((t_game->world->RawPacketCount + t_game->world->PacketCount) >= 253)
		{
			int seqval = ((t_game->world->RawPacketCount + t_game->world->PacketCount));
			unsigned char* seqdat = new unsigned char[2];
			seqdat = t_game->world->PProcessor.ENumber(seqval).data();
			builder.Insertbyte(0, seqdat[1]);
			builder.Insertbyte(0, seqdat[0]);
		}
		else
		{
			unsigned char seqval = t_game->world->PProcessor.Number((t_game->world->RawPacketCount + t_game->world->PacketCount + 2));
			builder.Insertbyte(0, seqval);
		}
		str = t_game->world->PProcessor.Encode(builder.Get());
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
std::string World::Receive(Game* t_game, std::string builder)
{
	std::string str = t_game->world->PProcessor.Decode(builder);
	return str;
}