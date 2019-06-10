#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include <string>
#include <vector>
using namespace std;

#define ADDR_CONSOLE    0x4393E0    // MW2 v1.2.208

class MW2_Console
{
    public:
        void Render(int x, int y, int width, LPDIRECT3DDEVICE9 pDevice);
        void takeInput(WPARAM wParam);
        void Init();
        void Send(string cmd);

        string command;
        vector<string> prevCommands;
        int caretPos,caretTick,cmdCount,currCmd;
        bool showCaret,handled;
}Console;

#endif