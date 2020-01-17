#include "..\stdafx.h"

Button::Button(VOID* m_Game, int _X, int _Y, int _ImgX, int _ImgY, int _ImgWidth, int _ImgHeight, bool _ClipDown, std::shared_ptr<IDirect3DTexture9> _Texture)
{
	this->SetPosition(std::pair<int, int>(_X, _Y));
	this->ImgX = _ImgX;
	this->ImgY = _ImgY;
	this->SetSize(std::pair<int, int>(_ImgWidth, _ImgHeight));
	this->AssignAnimationDirectionSouthward(_ClipDown);
	this->SetFrameID(0);
	this->AssignTexture(_Texture);
	this->Initialize(m_Game);
};
Button::Button(VOID* m_Game, int _X, int _Y, int _ImgWidth, int _ImgHeight, std::shared_ptr<IDirect3DTexture9> _Texture_1, std::shared_ptr<IDirect3DTexture9> _Texture_2)
{
	this->SetPosition(std::pair<int, int>(_X, _Y));
	this->ImgX = 0;
	this->ImgY = 0;
	this->SetSize(std::pair<int, int>(_ImgWidth, _ImgHeight));
	this->AssignAnimationDirectionSouthward(false);
	this->AssignNewTextureForMouseOver(true);
	this->SetFrameID(0);
	this->AssignTexture(_Texture_1);
	this->AssignMouseOverTexture(_Texture_2);
	this->Initialize(m_Game);
};
void Button::Update(int MouseX, int MouseY, bool MousePressed)
{
	if (this->GetIsActive())
	{
		this->UpdateElement();
	}
};

void Button::Draw(ID3DXSprite* _Sprite)
{
	if (this->GetIsActive())
	{
		D3DXMATRIX mat;
		RECT SrcRect;
		SrcRect.left = this->ImgX;
		SrcRect.top = this->ImgY;
		SrcRect.bottom = this->ImgY + this->GetSize().second;
		SrcRect.right = this->ImgX + this->GetSize().first;
		if (this->IsAnimationSouthward())
		{
			SrcRect.top = this->ImgY + (this->GetFrameID() * this->GetSize().second);
			SrcRect.bottom = this->ImgY + (this->GetFrameID() + 1) * (this->GetSize().second);
		}
		else
		{
			SrcRect.left = this->ImgX + (this->GetFrameID() * this->GetSize().first);
			SrcRect.right = this->ImgX + ((this->GetFrameID() + 1) * (this->GetSize().first));
		}

		D3DXMatrixTransformation2D(&mat, NULL, NULL, NULL, NULL, NULL, NULL);
		D3DXVECTOR3* Pos = new D3DXVECTOR3(this->GetPosition().first, this->GetPosition().second, 0.05);
		D3DXVECTOR3* Center = new D3DXVECTOR3(0, 0, 0);
		_Sprite->SetTransform(&mat);

		if (this->IsNewTextureForMouseOver())
		{
			if (this->MouseOverElement())
			{
				_Sprite->Draw(this->GetMouseOverTexture().get(), NULL, Center, Pos, D3DCOLOR_ARGB(255, 255, 255, 255));
			}
			else
			{
				_Sprite->Draw(this->GetTexture().get(), NULL, Center, Pos, D3DCOLOR_ARGB(255, 255, 255, 255));
			}
		}
		else
		{

			_Sprite->Draw(this->GetTexture().get(), &SrcRect, Center, Pos, D3DCOLOR_ARGB(255, 255, 255, 255));
		}


		delete Pos;
		delete Center;
	}
};

void Button::Deactivate()
{
	this->MouseClickProccessed();

}

void Button::Release()
{
	if(this->GetTexture())
	{
		this->GetTexture().reset();
		
	}
}