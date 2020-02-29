
// include the basic windows header file
#include "stdafx.h"
#include <windows.h>
#include <windowsx.h>
#include <cstdint>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <random>
#include <time.h>

#include "game.h"


static int ResX, ResY; 
Game game;
World* world;
// function prototypes

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
	World::DebugPrint("EODEV 3.0 Debug");
#endif

	std::srand(time(0));
	ResX = 640;
	ResY = 480;
	// the handle for the window, filled by a function
	HWND hWnd;
	sf::ContextSettings settings;
	settings.depthBits = 0;
	settings.stencilBits = 0;
	settings.antialiasingLevel = 0;
	settings.majorVersion = 3;
	settings.minorVersion = 0;

	sf::RenderWindow window(sf::VideoMode(ResX, ResY), "Endless Online Developmental", sf::Style::Default, settings);
	//window.setVerticalSyncEnabled(true);

	window.setFramerateLimit(120);
	hWnd = window.getSystemHandle();

	world = new World(&game);
	game.Config = new IniConfiguration();
	game.Config->Init();

	game.Initialize(&window, world);
	// this struct holds Windows event messages
	MSG msg;

	// Enter the infinite message loop
	while (window.isOpen())
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
		sf::Event event;
		while (window.pollEvent(event))
		{
			// catch the resize events
			switch (event.type)
			{
			case(sf::Event::MouseButtonPressed):
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					game.MousePressed = true;
					game.RAWMousePressed = true;
				}
				else if (event.mouseButton.button == sf::Mouse::Right)
				{
					game.MouseRightPressed = true;
				}
				break;
			}
			case(sf::Event::MouseButtonReleased):
			{
				game.MousePressed = false;
				game.RAWMousePressed = false;
				game.MouseRightPressed = false;
				break;
			}
			case(sf::Event::Resized):
			{
				// update the view to the new size of the window
				sf::FloatRect visibleArea(0.0f, 0.0f, 640.0f, 480.0f);
				window.setView(sf::View(visibleArea));
				
				break;
			}
			case(sf::Event::Closed):
			{
				window.close();
				break;
			}
			case(sf::Event::MouseWheelMoved):
			{		
				if (event.mouseWheel.delta > 0)
				{
					game.MouseWheelVal -= 1;
				}
				else if (event.mouseWheel.delta < 0) {
					game.MouseWheelVal += 1;
				}
				break;
			}
			
			case(sf::Event::KeyPressed):
			{
				if (event.key.code < 0x25 && event.key.code > 0x28)
				{
					world->HandleKeyInput(event.key.code, game.Stage, game.SubStage);
				}
				else
				{
					//world->HandleTextInput(event.text.unicode, game.Stage, game.SubStage);
				}

				switch (event.key.code)
				{
				case(sf::Keyboard::Tab):
					{
						if (game.Stage == game.PLogin || game.Stage == game.PCharacterChoose || game.Stage == game.PCreateAccount)
						{
							game.menu->TabPressed();
						}
						break;
					}
				case(sf::Keyboard::Return):
					{
						if (game.Stage == game.PLogin)
						{
							game.menu->Login();
						}
						if (game.Stage == game.PInGame)
						{
							game.Map_UserInterface->UI_SendMessage();
						}
						break;
					}
				}
				break;
			}
			case(sf::Event::TextEntered):
			{
				world->HandleTextInput((event.text.unicode), game.Stage, game.SubStage);
			}
			default: break;
			}
		}
		// Check to see if any messages are waiting in the queue
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// Translate the message and dispatch it to WindowProc()
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// If the message is WM_QUIT, exit the while loop
		if (msg.message == WM_QUIT)
			break;
		sf::Vector2i mousepos = sf::Mouse::getPosition(window);
		sf::Vector2f newmouspos = window.mapPixelToCoords(mousepos);
		game.MouseX = std::clamp((int)newmouspos.x, 0, 640);
		game.MouseY = std::clamp((int)newmouspos.y, 0, 480);
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
	
	}
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
						}
						break;
					}
				}
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
