#ifndef _UI_Element_
#define _UI_Element_
class UI_Element
{
	std::shared_ptr<IDirect3DTexture9> p_Texture;
	std::shared_ptr<IDirect3DTexture9> p_Texture_MouseOver;
	std::pair<int, int> Position;
	std::pair<int, int> Size;

	int AnimID = 0;
	bool AnimNewTexture = false;
	bool MouseClicked;
	bool MouseOver;
	bool AnimDirectionTopDown;
	bool HighlightOnMouseDown = false;
	bool IsActive = true;
	
public:
	UI_Element();
	bool GetIsActive() { return this->IsActive; }
	void SetIsActive(bool val) { this->IsActive = val; }
	std::pair<int, int> GetPosition() { return Position; }
	std::pair<int, int> GetSize() { return Size; }
	void Element_Deactivate() { this->AnimID = (int)0; this->MouseClicked = false; this->MouseOver = false; }
	void Deactivate() { this->AnimID = (int)0; this->MouseClicked = false; this->MouseOver = false; }
	void SetPosition(std::pair<int, int> m_pos) { this->Position = m_pos; }
	void SetSize(std::pair<int, int> m_size) { this->Size = m_size; }
	int GetFrameID() { return this->AnimID; }
	bool MouseClickedOnElement() { return this->MouseClicked; }
	bool MouseOverElement() { return this->MouseOver; }
	void SetHighlightOnMouseDown(bool val) { this->HighlightOnMouseDown = val; }
	bool GetHighlightOnMouseDown() { return this->HighlightOnMouseDown; }
	bool IsAnimationSouthward() { return this->AnimDirectionTopDown; }
	void AssignAnimationDirectionSouthward(bool yesno) { this->AnimDirectionTopDown = yesno; }
	bool IsNewTextureForMouseOver() { return this->AnimNewTexture; }
	void AssignNewTextureForMouseOver(bool yesno) { this->AnimNewTexture = yesno; }
	void SetFrameID(int index) { this->AnimID = index; }
	void AssignTexture(std::shared_ptr<IDirect3DTexture9> m_Texture) { this->p_Texture = m_Texture; }
	std::shared_ptr<IDirect3DTexture9> GetTexture() { return this->p_Texture; }
	std::shared_ptr<IDirect3DTexture9> GetMouseOverTexture() { return this->p_Texture_MouseOver; }

	void AssignMouseOverTexture(std::shared_ptr<IDirect3DTexture9> m_Texture) { this->p_Texture_MouseOver = m_Texture; }

	void MouseClickProccessed(){ MouseClicked = false; }

	void Initialize(VOID* m_Game);
	void UpdateElement();
	~UI_Element();
};
#endif
