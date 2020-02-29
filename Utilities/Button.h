#pragma once
#include "..\Utilities\UI_Element.h"
class Button : public UI_Element
{
public:
	Button(Game* m_game, int _X, int _Y, int _ImgX, int _ImgY, int _ImgWidth, int _ImgHeight, bool _ClipDown, Resource_Manager::TextureData* _Texture);
	Button(Game* m_game, int _X, int _Y, int _ImgWidth, int _ImgHeight, Resource_Manager::TextureData* _Texture, Resource_Manager::TextureData* _Texture_2);
	int ImgX,ImgY;

	void Update(int MouseX, int MouseY, bool MousePressed);
	void Draw(float depth = 0);
	void Deactivate();
	void Release();
};
