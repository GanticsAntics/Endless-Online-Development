#include "..\stdafx.h"

static LPDIRECT3DTEXTURE9 Blinker = NULL;
Textbox::Textbox(Game* p_game, sf::Vector2f m_position, sf::Vector2f m_size, int fontSize, sf::Color labelColor, sf::RenderWindow* m_Dev,unsigned char  _Phase,unsigned char  _Subphase)
{
	this->MaxLen = 20;
	this->TextBounds = RECT();
	this->focused = true;
	this->color = labelColor;
	this->keyMask = this->None;
	this->acceptsReturn = false;
	this->nonAcceptedKeyEntered = false;
	this->blinkhidden = false;
	this->position = m_position;
	this->size = m_size;
	this->hashkey = 0;
	this->Phase = _Phase;
	this->SubPhase = _Subphase;
	this->m_game = p_game;
	if(!Blinker)
	{
		CBitmapEx bmp;
		bmp.Create(1,14);
		for(int i = 0; i < bmp.GetHeight();i++)
		{
			bmp.SetPixel(0,i,_RGB(255, 255, 255));
		}
		LPBYTE cabuffer;
		DWORD cadwBufferSize = bmp.GetSize() + sizeof(BITMAPFILEHEADER) + sizeof(RGBQUAD) + sizeof(BITMAPINFOHEADER);
		cabuffer = (LPBYTE) malloc(cadwBufferSize);
		bmp.Save(cabuffer);
		LPDIRECT3DTEXTURE9 catxtbx = NULL;
		//D3DXIMAGE_INFO cainfo = D3DXIMAGE_INFO();
		//HRESULT caHr = D3DXCreateTextureFromFileInMemoryEx(m_Dev,cabuffer,cadwBufferSize,D3DX_DEFAULT_NONPOW2 ,D3DX_DEFAULT_NONPOW2,1,D3DUSAGE_DYNAMIC ,D3DFMT_A8R8G8B8,
			//													 D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, sf::Color::Color0,0,0,0),&cainfo,NULL,&Blinker);
	}
	//this->Font->AddRef();
}

Textbox::Textbox(Game* p_game, sf::Vector2f m_position, sf::Vector2f m_size, sf::Color labelColor,sf::Font* m_font,unsigned char  _Phase,unsigned char  _Subphase)
{
	this->MaxLen = 20;
	this->TextBounds = RECT();
	this->focused = true;
	this->color = labelColor;
	this->keyMask = this->LetterOrDigit;
	this->acceptsReturn = false;
	this->nonAcceptedKeyEntered = false;
	this->blinkhidden = false;
	this->Font = m_font;
	this->position = m_position;
	this->size = m_size;
	this->hashkey = 0;
	this->Phase = _Phase;
	this->SubPhase = _Subphase;
	this->m_game = p_game;
	if(!Blinker)
	{
		LPDIRECT3DDEVICE9 Dev;
		//m_font->GetDevice(&Dev);
		CBitmapEx bmp;
		bmp.Create(1,14);
		for(int i = 0; i < bmp.GetHeight();i++)
		{
			bmp.SetPixel(0,i,_RGB(255,255,255));
		}
		LPBYTE cabuffer;
		DWORD cadwBufferSize = bmp.GetSize() + sizeof(BITMAPFILEHEADER) + sizeof(RGBQUAD) + sizeof(BITMAPINFOHEADER);
		cabuffer = (LPBYTE) malloc(cadwBufferSize);
		bmp.Save(cabuffer);
		LPDIRECT3DTEXTURE9 catxtbx = NULL;
	//	D3DXIMAGE_INFO cainfo = D3DXIMAGE_INFO();
		//HRESULT caHr = D3DXCreateTextureFromFileInMemoryEx(Dev,cabuffer,cadwBufferSize,D3DX_DEFAULT_NONPOW2 ,D3DX_DEFAULT_NONPOW2,1,D3DUSAGE_DYNAMIC ,D3DFMT_A8R8G8B8,
															//	 D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, sf::Color::Color0,0,0,0),&cainfo,NULL,&Blinker);
	}
	//this->Font->AddRef();

}

void Textbox::OnKeyDown(WPARAM args)
{
}
void Textbox::UpdateBlinkerOffset()
{
	//this->Font->DrawText(NULL, this->Rendertext.c_str(), -1, &this->TextBounds, DT_CALCRECT, 0xffffffff);
}
void Textbox::OnKeyPress(WPARAM args)
{
	//char* your_wchar_in_char = to_string(argsz).c_str();
	switch(args)
	{
		
	case(8)://Backspace
		{
			if(this->text.length() > 0)
			{
				this->text.erase(text.length()-1,1);
				int StrIndex = 0;
				for (int i = 0; i < this->text.length() + 1; i++)
				{
					std::string Buildstr = this->text.substr(this->text.length() - i, i);
					this->TextBounds.right = m_game->GetFontSize(Buildstr, 9).x;
					this->TextBounds.top = m_game->GetFontSize(Buildstr, 9).y;
					//this->Font->DrawText(NULL, Buildstr.c_str(), -1, &this->TextBounds, DT_CALCRECT, 0xffffffff);
					this->Rendertext = Buildstr;
					if (this->TextBounds.right > this->size.x)
					{
						break;
					}

					StrIndex = i;
				}
				if(this->hashkey == 0)
				{
					this->TextBounds.right = m_game->GetFontSize(Rendertext, 9).x;
					this->TextBounds.top = m_game->GetFontSize(Rendertext, 9).y;
					//this->Font->DrawText(NULL, this->Rendertext.c_str(), -1, &this->TextBounds, DT_CALCRECT, 0xffffffff );
					break;
				}
				else
				{
					std::basic_string<char> str;
					for(int i = 0; i < this->text.length();i++)
					{
						str += this->hashkey;
					}
					this->TextBounds.right = m_game->GetFontSize(str, 9).x;
					this->TextBounds.top = m_game->GetFontSize(str, 9).y;
					//this->Font->DrawText(NULL, str.c_str(), -1, &this->TextBounds, DT_CALCRECT, 0xffffffff );
				}
			}
			break;
		}
		case(27)://Escape
		{
			this->text.clear();
			this->Rendertext.clear();
			int StrIndex = 0;
			for (int i = 0; i < this->text.length() + 1; i++)
			{
				std::string Buildstr = this->text.substr(this->text.length() - i, i);
				this->TextBounds.right = m_game->GetFontSize(Buildstr, 9).x;
				this->TextBounds.top = m_game->GetFontSize(Buildstr, 9).y;
				//this->Font->DrawText(NULL, Buildstr.c_str(), -1, &this->TextBounds, DT_CALCRECT, 0xffffffff);
				this->Rendertext = Buildstr;
				if (this->TextBounds.right > this->size.x)
				{
					break;
				}

				StrIndex = i;
			}
		
				if(this->hashkey == 0)
				{
					this->TextBounds.right = m_game->GetFontSize(Rendertext, 9).x;
					this->TextBounds.top = m_game->GetFontSize(Rendertext, 9).y;
					//this->Font->DrawText(NULL, this->Rendertext.c_str(), -1, &this->TextBounds, DT_CALCRECT, 0xffffffff );
					break;
				}
				else
				{
					std::basic_string<char> str;
					for(int i = 0; i < this->text.length();i++)
					{
						str += this->hashkey;
					}
					this->TextBounds.right = m_game->GetFontSize(str, 9).x;
					this->TextBounds.top = m_game->GetFontSize(str, 9).y;
					//this->Font->DrawText(NULL, str.c_str(), -1, &this->TextBounds, DT_CALCRECT, 0xffffffff );
				}
			break;
		}
		case(9)://tab
		{
				if(this->hashkey == 0)
				{
					//this->Font->DrawText(NULL, this->Rendertext.c_str(), -1, &this->TextBounds, DT_CALCRECT, 0xffffffff );
					break;
				}
				else
				{
					std::basic_string<char> str;
					for(int i = 0; i < this->text.length();i++)
					{
						str += this->hashkey;
					}
					this->TextBounds.right = m_game->GetFontSize(str, 9).x;
					this->TextBounds.top = m_game->GetFontSize(str, 9).y;
					//this->Font->DrawText(NULL, str.c_str(), -1, &this->TextBounds, DT_CALCRECT, 0xffffffff );
				}
			break;
		}
		case(32)://Space
		{
			if (!this->acceptspace  || (this->text.length() + 1 > this->MaxLen && this->MaxLen != 0))
			{
				return;
			}
			if (this->hashkey == 0)
			{
				std::string temptext = this->text + ',';
				this->text += (char)(args);
				//this->Font->DrawText(NULL, temptext.c_str(), -1, &this->TextBounds, DT_CALCRECT, 0xffffffff);
				this->TextBounds.right = m_game->GetFontSize(temptext, 9).x;
				this->TextBounds.top = m_game->GetFontSize(temptext, 9).y;
				if (this->text.length() < this->MaxLen)
				{
					int StrIndex = 0;
					for (int i = 0; i < this->text.length() + 1; i++)
					{
						std::string Buildstr = this->text.substr(this->text.length() - i, i);
						this->TextBounds.right = m_game->GetFontSize(Buildstr, 9).x;
						this->TextBounds.top = m_game->GetFontSize(Buildstr, 9).y;
						//this->Font->DrawText(NULL, Buildstr.c_str(), -1, &this->TextBounds, DT_CALCRECT, 0xffffffff);
						this->Rendertext = Buildstr;
						if (this->TextBounds.right > this->size.x)
						{
							break;
						}

						StrIndex = i;
					}
					this->TextBounds.right = m_game->GetFontSize(Rendertext, 9).x;
					this->TextBounds.top = m_game->GetFontSize(Rendertext, 9).y;
					//this->Font->DrawText(NULL, this->Rendertext.c_str(), -1, &this->TextBounds, DT_CALCRECT, 0xffffffff);
				}
				break;
			}
			else
			{
				this->text += (args);
				std::string str;
				for (int i = 0; i < this->text.length(); i++)
				{
					str += this->hashkey;
				}
				this->TextBounds.right = m_game->GetFontSize(str, 9).x;
				this->TextBounds.top = m_game->GetFontSize(str, 9).y;
				//this->Font->DrawText(NULL, str.c_str(), -1, &this->TextBounds, DT_CALCRECT, 0xffffffff);
			}
			break;
		}
	default:
		{
			switch(this->keyMask)
			{
			case(KeyType::None):
			{
				break;
			}
			case(KeyType::Letter):
				{
					if (!isalpha(args))
					{
						return;
					}
					break;
				}
			case(KeyType::LetterOrDigit):
				{
					if (!isalpha(args) && !isdigit(args))
					{
						return;
					}
					break;
				}
			case(KeyType::Digit):
				{
					if (!isdigit(args))
					{
						return;
					}
					break;
				}
			default:break;
			}
		
			if(this->text.length()+1 > this->MaxLen && this->MaxLen != 0)
			{
				return;
			}	
			
			if(this->hashkey == 0)
			{
				this->TextBounds.right = m_game->GetFontSize(this->text, 9).x;
				this->TextBounds.top = m_game->GetFontSize(this->text, 9).y;
				//this->Font->DrawText(NULL, this->text.c_str(), -1, &this->TextBounds, DT_CALCRECT, 0xffffffff );
				if (this->text.length() < this->MaxLen)
				{
					if ((args) == '`')
					{
						(args) = '~';
					}
					this->text += (args);

					int StrIndex = 0;
					for (int i = 0; i < this->text.length()+1; i++)
					{
						std::string Buildstr = this->text.substr(this->text.length() - i, i);
						this->TextBounds.right = m_game->GetFontSize(Buildstr, 9).x;
						this->TextBounds.top = m_game->GetFontSize(Buildstr, 9).y;
						//this->Font->DrawText(NULL, Buildstr.c_str(), -1, &this->TextBounds, DT_CALCRECT, 0xffffffff);
						this->Rendertext = Buildstr;
						if (this->TextBounds.right > this->size.x)
						{
							break;
						}
					
						StrIndex = i;
					}
					this->TextBounds.right = m_game->GetFontSize(Rendertext, 9).x;
					this->TextBounds.top = m_game->GetFontSize(Rendertext, 9).y;
					//this->Font->DrawText(NULL, this->Rendertext.c_str(), -1, &this->TextBounds, DT_CALCRECT, 0xffffffff);
				}


				break;
			}
			else
			{
				std::string str;
				for(int i = 0; i < this->text.length();i++)
				{
					str += this->hashkey;
				}
				this->TextBounds.right = m_game->GetFontSize(str, 9).x;
				this->TextBounds.top = m_game->GetFontSize(str, 9).y;
				//this->Font->DrawText(NULL, str.c_str(), -1, &this->TextBounds, DT_CALCRECT, 0xffffffff );

				if(this->TextBounds.right < this->size.x)
				{
					this->text += (wchar_t)(args);
					this->TextBounds.right = m_game->GetFontSize(str, 9).x;
					this->TextBounds.top = m_game->GetFontSize(str, 9).y;
					//this->Font->DrawText(NULL, str.c_str(), -1, &this->TextBounds, DT_CALCRECT, 0xffffffff );
					if(this->TextBounds.right > this->size.x)
					{	
						this->text.erase(text.length()-1,1);
					}
				str.clear();
				for(int i = 0; i < this->text.length();i++)
				{
					str += this->hashkey;
				}
				this->TextBounds.right = m_game->GetFontSize(str, 9).x;
				this->TextBounds.top = m_game->GetFontSize(str, 9).y;
				//this->Font->DrawText(NULL, str.c_str(), -1, &this->TextBounds, DT_CALCRECT, 0xffffffff );
				}
			}
		}
	}


}

void Textbox::SetKeyMask(KeyType newKeyMask)
{
	this->keyMask = newKeyMask;
}
void Textbox::Render(float _depth)
{
// Create a rectangle to indicate where on the screen it should be drawn
RECT rct;
rct.left= this->position.x;
rct.right= this->position.x + this->size.x;
rct.top= this->position.y + 3;
rct.bottom= this->position.y + this->size.y;

if(this->hashkey > 0)
{
	rct.top= this->position.y ;
	std::string str;
	for(int i = 0; i < this->text.length();i++)
	{
		str += this->hashkey;
	}
	this->m_game->DrawTextW(str.c_str(), rct.left, rct.top, this->color, 14, false, _depth);
	
	//this->Font->DrawText(m_Sprite, str.c_str(), -1, &rct, 0, this->color );
}
else
{
	//game->DrawTextW(this->Rendertext.c_str(), rct.left, rct.top, this->color, *game->DefaultFont);
	this->m_game->DrawTextW(this->Rendertext.c_str(), rct.left, rct.top, this->color, 14, false, _depth);
//this->Font->DrawText(m_Sprite, this->Rendertext.c_str(), -1, &rct, 0, this->color );
}

if(this->focused && !this->blinkhidden)
{
		//D3DXMATRIX mat;
		RECT SrcRect;
		//D3DXMatrixTransformation2D(&mat,NULL,NULL,NULL,NULL, NULL,NULL);
		////sf::Vector3f* Pos = new sf::Vector3f(this->position.x + this->TextBounds.right + 3,this->position.y + 3,0);
		//sf::Vector3f* Center = new sf::Vector3f(0,0,0);
		//m_Sprite->SetTransform(&mat);
		//m_Sprite->Draw(Blinker, NULL,Center, Pos, this->color);
		
		//delete Pos;
		//delete Center;

}

}

bool Textbox::CheckCollision(int X, int Y)
{
	if( X > this->position.x &&  X < this->position.x + this->size.x && 
	    Y > this->position.y &&  Y < this->position.y + this->size.y)
	{
		return true;
	}
	return false;
}

void Textbox::Reset()
{
	this->Rendertext.clear();
	this->text.clear();
	this->TextBounds.right = 0;
	this->TextBounds.left = 0;
	this->TextBounds.bottom = 0;
	this->TextBounds.top = 0;
}
void Textbox::Release()
{
	//if(this->Font)
	//{this->Font->Release();}
}