using namespace std;
#include <list>
#include "include/Ptypes/ptypes.h"
#include "include/Ptypes/pport.h"
#include "include\EOServ\packet.hpp"
#include "Utilities\Button.h"
#include "Utilities\Textbox.h"
#include "Resources.h"
#include "Connection.h"
#include "Utilities\ConfigFile.h"
#include "Utilities\UI_MessageBox.h"
#include "include/EOServ/eodata.hpp"

#ifndef World_h
#define World_h
class World
{
public:
	World(LPVOID _Game);
	typedef std::list<Textbox> TextType;
	UI_MessageBox* W_UI_Messagebox;
	static int WorldCharacterID;
	TextType TextBoxLst;
	Connection* connection;
	static std::string MBMessage;
	static std::string MBTitle;
	static PacketProcessor PProcessor;
	static bool MBHidden;
	static unsigned int World::PacketCount;
	static unsigned char World::RawPacketCount;
	static ENF* ENF_File;
	static EIF* EIF_File;
	static ESF* ESF_File;
	static ECF* ECF_File;

	void HandleTextInput(WPARAM Parameter, byte phase, byte subphase);
	void HandleKeyInput(WPARAM Parameter, byte phase, byte subphase);
    Textbox* RegisterTextBox(Textbox TxtBox);
    void UnregisterTextBox(Textbox* TxtBox);
	void MassTextBoxReset();
	void RenderTextBoxes(ID3DXSprite* m_Sprite, byte phase, byte subphase);
	void SetFocusedTextbox(Textbox* TxtBox);

	
	static void DebugPrint(pt::string Message);
	static void ThrowMessage(std::string Title, std::string Message);
	static void ThrowMessage(std::string Title, std::string Message, bool Okay);
	Textbox* GetFocusedTextbox();

	void CreateConnection();
	void DropConnection();
	static bool Connected;
	static bool Connecting;
	static void Send(LPVOID game, pt::ipstream* Stream, PacketBuilder Builder);
	static std::string Receive(LPVOID game, std::string Builder);
};
#endif //World_h