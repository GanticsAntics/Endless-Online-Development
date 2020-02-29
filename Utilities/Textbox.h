#include "..\stdafx.h"
#pragma once
class Textbox
{
public:
		Game* m_game;
		enum KeyType
		{
			None = 0,
			Letter = 1,
			Digit = 2,
			LetterOrDigit = Letter | Digit,
			Punctuation = 4,
			Separator = 8,
			Control = 16
		};

		RECT TextBounds;
		int Phase;
		int SubPhase;
		sf::Sprite* Sprite;
		int WorldID;
        KeyType keyMask;
        bool nonAcceptedKeyEntered;
		int MaxLen;
		bool focused;
		bool blinkhidden;
        bool acceptsReturn;
		bool acceptspace = false;
		wchar_t hashkey;
        int textBoxInnerWidth;
		sf::Color color;
		std::string Rendertext;
		std::string text;
		sf::Vector2f position, size;
		Textbox(Game* p_game, sf::Vector2f m_position, sf::Vector2f m_size, int fontSize, sf::Color labelColor, sf::RenderWindow*m_Dev,unsigned char  _Phase,unsigned char  _Subphase);
		Textbox(Game* p_game, sf::Vector2f m_position, sf::Vector2f m_size, sf::Color labelColor, sf::Font* m_font,unsigned char  _Phase, unsigned char _Subphase);
		sf::Font* Font;
		KeyType GetKeyType(char c);
		void UpdateBlinkerOffset();
		void OnKeyDown(WPARAM args);
		void OnKeyPress(WPARAM args);
		void Render(float _depth = 0.0f);
		void Reset();
		void SetKeyMask(KeyType newKeyMask);
		bool CheckCollision(int X, int Y);
		void Release();

};
