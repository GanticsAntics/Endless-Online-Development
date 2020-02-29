#pragma once
class Game;
class UI_Element
{
	std::pair<int, int> Position;
	std::pair<int, int> Size;

	int AnimID = 0;
	bool AnimNewTexture = false;
	bool MouseClicked;
	bool MouseOver;
	bool AnimDirectionTopDown;
	bool HighlightOnMouseDown = false;
	bool IsActive = true;
protected:
	Game* m_game;
	Resource_Manager::TextureData* p_Texture;
	Resource_Manager::TextureData* p_Texture_MouseOver;
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
	void AssignTexture(Resource_Manager::TextureData* m_Texture) { this->p_Texture = m_Texture; }
	std::shared_ptr<sf::Texture> GetTexture() { return this->p_Texture->_Texture; }
	std::shared_ptr<sf::Texture> GetMouseOverTexture() { return this->p_Texture_MouseOver->_Texture; }

	void AssignMouseOverTexture(Resource_Manager::TextureData* m_Texture) { this->p_Texture_MouseOver = m_Texture; }

	void MouseClickProccessed(){ MouseClicked = false; }

	void Initialize(Game* m_Game);
	void UpdateElement();
	~UI_Element();
};
