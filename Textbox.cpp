#include "stdafx.h"
#include "Utilities\Textbox.h"
#include "include\CBitmapEx\BitmapEx.h"
static LPDIRECT3DTEXTURE9 Blinker = NULL;

Textbox::Textbox(D3DXVECTOR2 m_position, D3DXVECTOR2 m_size, int fontSize, D3DXCOLOR labelColor, IDirect3DDevice9* m_Dev, byte _Phase, byte _Subphase)
{
	this->MaxLen = 0;
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
	if(!Blinker)
	{
		CBitmapEx bmp;
		bmp.Create(1,14);
		for(int i = 0; i < bmp.GetHeight();i++)
		{
			bmp.SetPixel(0,i,_RGB(0,0,0));
		}
		LPBYTE cabuffer;
		DWORD cadwBufferSize = bmp.GetSize() + sizeof(BITMAPFILEHEADER) + sizeof(RGBQUAD) + sizeof(BITMAPINFOHEADER);
		cabuffer = (LPBYTE) malloc(cadwBufferSize);
		bmp.Save(cabuffer);
		LPDIRECT3DTEXTURE9 catxtbx = NULL;
		D3DXIMAGE_INFO cainfo = D3DXIMAGE_INFO();
		HRESULT caHr = D3DXCreateTextureFromFileInMemoryEx(m_Dev,cabuffer,cadwBufferSize,D3DX_DEFAULT_NONPOW2 ,D3DX_DEFAULT_NONPOW2,1,D3DUSAGE_DYNAMIC ,D3DFMT_A8R8G8B8,
																 D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_ARGB(0,0,0,0),&cainfo,NULL,&Blinker);
	}
	this->Font->AddRef();
}

Textbox::Textbox(D3DXVECTOR2 m_position, D3DXVECTOR2 m_size, D3DXCOLOR labelColor, ID3DXFont* m_font, byte _Phase, byte _Subphase)
{
	this->MaxLen = 0;
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
	this->position = m_position;
	this->size = m_size;
	this->hashkey = 0;
	this->Phase = _Phase;
	this->SubPhase = _Subphase;
	if(!Blinker)
	{
		LPDIRECT3DDEVICE9 Dev;
		m_font->GetDevice(&Dev);
		CBitmapEx bmp;
		bmp.Create(1,14);
		for(int i = 0; i < bmp.GetHeight();i++)
		{
			bmp.SetPixel(0,i,_RGB(0,0,0));
		}
		LPBYTE cabuffer;
		DWORD cadwBufferSize = bmp.GetSize() + sizeof(BITMAPFILEHEADER) + sizeof(RGBQUAD) + sizeof(BITMAPINFOHEADER);
		cabuffer = (LPBYTE) malloc(cadwBufferSize);
		bmp.Save(cabuffer);
		LPDIRECT3DTEXTURE9 catxtbx = NULL;
		D3DXIMAGE_INFO cainfo = D3DXIMAGE_INFO();
		HRESULT caHr = D3DXCreateTextureFromFileInMemoryEx(Dev,cabuffer,cadwBufferSize,D3DX_DEFAULT_NONPOW2 ,D3DX_DEFAULT_NONPOW2,1,D3DUSAGE_DYNAMIC ,D3DFMT_A8R8G8B8,
																 D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_ARGB(0,0,0,0),&cainfo,NULL,&Blinker);
	}
	this->Font->AddRef();

}

void Textbox::OnKeyDown(WPARAM args)
{
}

void Textbox::OnKeyPress(WPARAM args)
{
	switch(args)
	{
	case(VK_BACK):
		{
			if(this->text.length() > 0)
			{
				this->text.erase(text.length()-1,1);

				if(this->hashkey == 0)
				{
					this->Font->DrawText(NULL, this->text.c_str(), -1, &this->TextBounds, DT_CALCRECT, 0xffffffff );
					break;
				}
				else
				{
					std::basic_string<wchar_t> str;
					for(int i = 0; i < this->text.length();i++)
					{
						str += this->hashkey;
					}
					this->Font->DrawText(NULL, str.c_str(), -1, &this->TextBounds, DT_CALCRECT, 0xffffffff );
				}
			}
			break;
		}
	case(VK_ESCAPE):
		{
			this->text.erase(0,text.length());
				if(this->hashkey == 0)
				{
					this->Font->DrawText(NULL, this->text.c_str(), -1, &this->TextBounds, DT_CALCRECT, 0xffffffff );
					break;
				}
				else
				{
					std::basic_string<wchar_t> str;
					for(int i = 0; i < this->text.length();i++)
					{
						str += this->hashkey;
					}
					this->Font->DrawText(NULL, str.c_str(), -1, &this->TextBounds, DT_CALCRECT, 0xffffffff );
				}
			break;
		}
		case(VK_TAB):
		{
				if(this->hashkey == 0)
				{
					this->Font->DrawText(NULL, this->text.c_str(), -1, &this->TextBounds, DT_CALCRECT, 0xffffffff );
					break;
				}
				else
				{
					std::basic_string<wchar_t> str;
					for(int i = 0; i < this->text.length();i++)
					{
						str += this->hashkey;
					}
					this->Font->DrawText(NULL, str.c_str(), -1, &this->TextBounds, DT_CALCRECT, 0xffffffff );
				}
			break;
		}
		case(VK_SPACE):
		{
			if (!this->acceptspace  || (this->text.length() + 1 > this->MaxLen && this->MaxLen != 0))
			{
				return;
			}
			if (this->hashkey == 0)
			{
				std::wstring temptext = this->text + L',';
				this->text += (wchar_t)(args);
				this->Font->DrawText(NULL, temptext.c_str(), -1, &this->TextBounds, DT_CALCRECT, 0xffffffff);
				break;
			}
			else
			{
				this->text += (wchar_t)(args);
				std::basic_string<wchar_t> str;
				for (int i = 0; i < this->text.length(); i++)
				{
					str += this->hashkey;
				}
				this->Font->DrawText(NULL, str.c_str(), -1, &this->TextBounds, DT_CALCRECT, 0xffffffff);
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
			//else if(this->keyMask == this->LetterOrDigit && (args < 47 || args > 123) && (args < 64 || args > 58) && (args < 96 || args > 91))
			{
			//	return;
			}
			if(this->text.length()+1 > this->MaxLen && this->MaxLen != 0)
			{
				return;
			}
			if(this->hashkey == 0)
			{
				this->Font->DrawText(NULL, this->text.c_str(), -1, &this->TextBounds, DT_CALCRECT, 0xffffffff );

				if(this->TextBounds.right < this->size.x)
				{
					this->text += (wchar_t)(args);
					this->Font->DrawText(NULL, this->text.c_str(), -1, &this->TextBounds, DT_CALCRECT, 0xffffffff );
					if(this->TextBounds.right > this->size.x)
					{	
						this->text.erase(text.length()-1,1);
					}
				this->Font->DrawText(NULL, this->text.c_str(), -1, &this->TextBounds, DT_CALCRECT, 0xffffffff );
				}
				break;
			}
			else
			{
				std::basic_string<wchar_t> str;
				for(int i = 0; i < this->text.length();i++)
				{
					str += this->hashkey;
				}

				this->Font->DrawText(NULL, str.c_str(), -1, &this->TextBounds, DT_CALCRECT, 0xffffffff );

				if(this->TextBounds.right < this->size.x)
				{
					this->text += (wchar_t)(args);
					this->Font->DrawText(NULL, str.c_str(), -1, &this->TextBounds, DT_CALCRECT, 0xffffffff );
					if(this->TextBounds.right > this->size.x)
					{	
						this->text.erase(text.length()-1,1);
					}
				str.clear();
				for(int i = 0; i < this->text.length();i++)
				{
					str += this->hashkey;
				}

				this->Font->DrawText(NULL, str.c_str(), -1, &this->TextBounds, DT_CALCRECT, 0xffffffff );
				}
			}
		}
	}


}

void Textbox::SetKeyMask(KeyType newKeyMask)
{
	this->keyMask = newKeyMask;
}
void Textbox::Render(ID3DXSprite* m_Sprite)
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
	std::basic_string<wchar_t> str;
	for(int i = 0; i < this->text.length();i++)
	{
		str += this->hashkey;
	}
	this->Font->DrawText(m_Sprite, str.c_str(), -1, &rct, 0, this->color );
}
else
{
// Draw some text 
this->Font->DrawText(m_Sprite, this->text.c_str(), -1, &rct, 0, this->color );
}

if(this->focused && !this->blinkhidden)
{
		D3DXMATRIX mat;
		RECT SrcRect;
		D3DXMatrixTransformation2D(&mat,NULL,NULL,NULL,NULL, NULL,NULL);
		D3DXVECTOR3* Pos = new D3DXVECTOR3(this->position.x + this->TextBounds.right + 3,this->position.y + 3,0);
		D3DXVECTOR3* Center = new D3DXVECTOR3(0,0,0);
		m_Sprite->SetTransform(&mat);
		m_Sprite->Draw(Blinker, NULL,Center, Pos, this->color);
		
		delete Pos;
		delete Center;

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
	this->text.clear();
	this->TextBounds.right = 0;
	this->TextBounds.left = 0;
	this->TextBounds.bottom = 0;
	this->TextBounds.top = 0;
}
void Textbox::Release()
{
	if(this->Font)
	{this->Font->Release();}
}