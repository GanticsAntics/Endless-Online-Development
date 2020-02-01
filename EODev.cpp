
// include the basic windows header file
#include "stdafx.h"
#include <windows.h>
#include <windowsx.h>

#include <time.h>

#include "game.h"


IDirect3D9Ptr d3d;
IDirect3DDevice9Ptr  d3ddev;    // the pointer to the device class
static int ResX, ResY; 
Game game;
World* world;
// function prototypes
void initD3D(HWND hWnd);    // sets up and initializes Direct3D
void cleanD3D(void);    // closes Direct3D and releases memory

// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd,
                         UINT message,
                         WPARAM wParam,
                         LPARAM lParam);

// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
#ifdef DEBUG
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	World::DebugPrint("EODEV 3.0 Debug");
#endif
	
	std::srand(time(0));
	ResX = 640;
	ResY = 480;
    // the handle for the window, filled by a function
    HWND hWnd;
    // this struct holds information for the window class
    WNDCLASSEX wc;

    // clear out the window class for use
    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    // fill in the struct with the needed information
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = L"WindowClass1";

    // register the window class
    RegisterClassEx(&wc);

    // create the window and use the result as the handle
    hWnd = CreateWindowEx(NULL,
                          L"WindowClass1",    // name of the window class
                          L"EoDEV++",   // title of the window
                          WS_OVERLAPPEDWINDOW,    // window style
                          386,    // x-position of the window
                          142,    // y-position of the window
                          689,    // width of the window
                          488,    // height of the window
                          NULL,    // we have no parent window, NULL
                          NULL,    // we aren't using menus, NULL
                          hInstance,    // application handle
                          NULL);    // used with multiple windows, NULL

    // display the window on the screen
    ShowWindow(hWnd, nCmdShow);
	world = new World(&game);
	game.Config = new IniConfiguration();
	game.Config->Init();
	initD3D(hWnd);
	game.Initialize(d3ddev, world);

    // enter the main loop:

    // this struct holds Windows event messages
    MSG msg;

// Enter the infinite message loop
while(TRUE)
{
	if (GetForegroundWindow() == hWnd)
	{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			world->HandleKeyInput(VK_LEFT, game.Stage, game.SubStage);
		}
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			world->HandleKeyInput(VK_UP, game.Stage, game.SubStage);
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			world->HandleKeyInput(VK_DOWN, game.Stage, game.SubStage);
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			world->HandleKeyInput(VK_RIGHT, game.Stage, game.SubStage);
		}
		if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
		{
			world->HandleKeyInput(VK_CONTROL, game.Stage, game.SubStage);
		}
		if (GetAsyncKeyState(VK_F3) & 0x8000)
		{
			world->HandleKeyInput(VK_F3, game.Stage, game.SubStage);
		}
	}
	
    // Check to see if any messages are waiting in the queue
    while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        // Translate the message and dispatch it to WindowProc()
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // If the message is WM_QUIT, exit the while loop
    if(msg.message == WM_QUIT)
        break;

	game.Update();
	game.Render();
	if (game.MousePressed)
	{
		game.MousePressed = false;
	}
	if (game.MouseRightPressed)
	{
		game.MouseRightPressed = false;
	}
    // Run game code here
    // ...
    // ...
}
	//cleanD3D();
    // return this part of the WM_QUIT message to Windows
    return msg.wParam;
}

// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	


    // sort through and find what code to run for the message given
    switch(message)
    {
        // this message is read when the window is closed   
		case WM_DESTROY :
			{
				PostQuitMessage(0);       // Send WM_QUIT
				std::exit(0);
				break;
			}
		case WM_KEYDOWN:
		{
			if (wParam < 0x25 && wParam > 0x28)
			{
				world->HandleKeyInput(wParam, game.Stage, game.SubStage);
			}
			break;
		}
		case WM_CHAR :
            {
                // close the application entirely
				world->HandleTextInput(wParam, game.Stage, game.SubStage);
				switch(wParam)
				{
					case(VK_TAB):
					{
						if(game.Stage == game.PLogin || game.Stage == game.PCharacterChoose|| game.Stage == game.PCreateAccount)
						{
							game.menu->TabPressed();
						}
						break;
					}
					case(VK_RETURN):
					{
						if(game.Stage == game.PLogin)
						{
							game.menu->Login();
						}
						if (game.Stage == game.PInGame)
						{	
							game.Map_UserInterface->UI_SendMessage();
							//game.menu->Login();
						}
						break;
					}
				}
                return 0;
            }
     
		case WM_MOUSEMOVE:
			{
				int i = wParam;
				//MessageBox(0,L"",L"LOL",0);
				POINTS pt = MAKEPOINTS(lParam);
				
				RECT rect;
				GetClientRect(hWnd,&rect);
				float multix = (float)((float)rect.right - rect.left) / (float)ResX;
				float multiy =  (float)((float)rect.bottom - rect.top) / (float)ResY;
				float mousex = pt.x / multix;
				float mousey = pt.y / multiy;

				game.MouseX = mousex;
				game.MouseY = mousey;
				
			
				 return 0;
			}
		case WM_LBUTTONDOWN:
			{
				game.MousePressed = true;
				game.RAWMousePressed = true;
				return 0;
				
			}	
		case WM_MOUSEWHEEL:
			{
			if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
			{
				game.MouseWheelVal -= 1;
			}
			else if (GET_WHEEL_DELTA_WPARAM(wParam) < 0) {
				game.MouseWheelVal += 1;
			}
				return 0;
				
			}
		case WM_RBUTTONDOWN:
		{
			game.MouseRightPressed = true;
			return 0;

		}
		case WM_LBUTTONUP:
			{
				game.MousePressed = false;
				game.RAWMousePressed = false;
				 return 0;
			}
			
			break;
    }

    // Handle any messages the switch statement didn't
    return DefWindowProc (hWnd, message, wParam, lParam);
} 

// this function initializes and prepares Direct3D for use
void initD3D(HWND hWnd)
{
    d3d = Direct3DCreate9(D3D_SDK_VERSION);    // create the Direct3D interface
	//_CrtSetBreakAlloc(605);
    D3DPRESENT_PARAMETERS d3dpp;    // create a struct to hold various device information
    ZeroMemory(&d3dpp, sizeof(d3dpp));    // clear out the struct for use
	d3dpp.Windowed = IniConfiguration::FullScreen;    // program windowed, not fullscreen
   // d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;    // discard old frames
	//d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD	;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	//d3dpp.AutoDepthStencilFormat = D3DFMT_A8R8G8B8;
    d3dpp.hDeviceWindow = hWnd;    // set the window to be used by Direct3D
	d3dpp.BackBufferHeight = ResY;
	d3dpp.BackBufferWidth = ResX;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
    // create a device class using this information and information from the d3dpp stuct
    d3d->CreateDevice(D3DADAPTER_DEFAULT,
                      D3DDEVTYPE_HAL,
                      hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
                      &d3dpp,
                      &d3ddev);
	d3ddev->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	d3ddev->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	d3ddev->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, TRUE);
	d3ddev->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	d3ddev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_INVSRCALPHA);
	d3ddev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCALPHA);

}

void cleanD3D(void)
{
	game.Unload();
	d3ddev.Release();
	d3d.Release();
}