#include "..\stdafx.h"

Button::Button(Game* m_Game, int _X, int _Y, int _ImgX, int _ImgY, int _ImgWidth, int _ImgHeight, bool _ClipDown, Resource_Manager::TextureData* _Texture)
{
	this->SetPosition(std::pair<int, int>(_X + 1, _Y + 1));
	this->ImgX = _ImgX;
	this->ImgY = _ImgY;
	this->SetSize(std::pair<int, int>(_ImgWidth, _ImgHeight));
	this->AssignAnimationDirectionSouthward(_ClipDown);
	this->SetFrameID(0);
	this->AssignTexture(_Texture);
	this->Initialize(m_Game);
};
Button::Button(Game* m_Game, int _X, int _Y, int _ImgWidth, int _ImgHeight, Resource_Manager::TextureData* _Texture, Resource_Manager::TextureData* _Texture_2)
{
	this->SetPosition(std::pair<int, int>(_X + 1, _Y + 1));
	this->ImgX = 0;
	this->ImgY = 0;
	this->SetSize(std::pair<int, int>(_ImgWidth, _ImgHeight));
	this->AssignAnimationDirectionSouthward(false);
	this->AssignNewTextureForMouseOver(true);
	this->SetFrameID(0);
	this->AssignTexture(_Texture);
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

void Button::Draw(float depth)
{
	if (this->GetIsActive())
	{
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


		if (this->IsNewTextureForMouseOver())
		{
			if (this->MouseOverElement())
			{
				this->m_game->Draw(this->p_Texture_MouseOver, this->GetPosition().first, this->GetPosition().second, sf::Color::Color(255, 255, 255, 255), 0, 0, -1, -1, sf::Vector2f(1, 1), depth);
			}
			else
			{
				this->m_game->Draw(this->p_Texture, this->GetPosition().first, this->GetPosition().second, sf::Color::Color(255, 255, 255, 255), 0, 0, -1, -1, sf::Vector2f(1, 1), depth);
			}
		}
		else
		{
			this->m_game->Draw(this->p_Texture, this->GetPosition().first - 1, this->GetPosition().second - 1, sf::Color::White, SrcRect.left , SrcRect.top , SrcRect.right, SrcRect.bottom, sf::Vector2f(1, 1), depth);		}
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