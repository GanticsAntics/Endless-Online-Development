#pragma once
#include "..\stdafx.h"
class UI_Element
{
	boost::shared_ptr<IDirect3DTexture9> p_Texture;
	boost::shared_ptr<IDirect3DTexture9> p_Texture_MouseOver;
	std::pair<int, int> Position;
	std::pair<int, int> Size;

	int AnimID = 0;
	bool AnimNewTexture = false;
	bool MouseClicked;
	bool MouseOver;
	bool AnimDirectionTopDown;
public:
	UI_Element();
	std::pair<int, int> GetPosition() { return Position; }
	std::pair<int, int> GetSize() { return Size; }
	void SetPosition(std::pair<int, int> m_pos) { this->Position = m_pos; }
	void SetSize(std::pair<int, int> m_size) { this->Size = m_size; }
	int GetFrameID() { return this->AnimID; }
	bool MouseClickedOnElement() { return this->MouseClicked; }
	bool MouseOverElement() { return this->MouseOver; }
	bool IsAnimationSouthward() { return this->AnimDirectionTopDown; }
	void AssignAnimationDirectionSouthward(bool yesno) { this->AnimDirectionTopDown = yesno; }
	bool IsNewTextureForMouseOver() { return this->AnimNewTexture; }
	void AssignNewTextureForMouseOver(bool yesno) { this->AnimNewTexture = yesno; }
	void SetFrameID(int index) { this->AnimID = index; }
	void AssignTexture(boost::shared_ptr<IDirect3DTexture9> m_Texture) { this->p_Texture = m_Texture; }
	boost::shared_ptr<IDirect3DTexture9> GetTexture() { return this->p_Texture; }
	boost::shared_ptr<IDirect3DTexture9> GetMouseOverTexture() { return this->p_Texture_MouseOver; }

	void AssignMouseOverTexture(boost::shared_ptr<IDirect3DTexture9> m_Texture) { this->p_Texture_MouseOver = m_Texture; }

	void MouseClickProccessed(){ MouseClicked = false; }

	void Initialize(VOID* m_Game);
	void UpdateElement();
	~UI_Element();
};

