#include "..\stdafx.h"
#include <WinBase.h>
#include <map>
#include <iostream>
#include <conio.h>
//#include "..\include/CBitmapEx/BitmapEx.h"
#include "Resource_Manager.h"

#define D3D_DEBUG_INFO
using namespace std;
static sf::RenderWindow* Device;

void padTo(std::wstring &str, const size_t num, const char paddingChar = ' ')
{     
	if(num > str.size()) 
		str.insert(0, num - str.size(), paddingChar);
} 

Resource_Manager::Module Resource_Manager::LoadModule(int id)
{
	Module module = Module();
	try
	{
		wchar_t* st = new wchar_t[8];
		_itow(id, st, 10);

		wchar_t* buffer = new wchar_t[1024];
		GetCurrentDirectory(1024, buffer);

		std::wstring Path = L"";
		Path += buffer;
		Path+=L"\\gfx\\gfx";
		wstring NumberPath = st;
		padTo(NumberPath,3,'0');
		Path+=NumberPath += L".egf";

		module.loadfailed = false;
		module.failid = 0;
     	module.module = LoadLibrary(Path.c_str());

		if(!module.module)
		{
			module.loadfailed = true;
			module.failid = id;
		}
		Path += L" loaded\n";
	}
	catch(exception)
	{
		module.loadfailed = true;
		module.failid = id;
	}
	return module;
}
HRESULT Resource_Manager::Initialize(sf::RenderWindow*m_Device)
{
	Device = m_Device;
	sf::Image newimg;
	newimg.create(1, 1);
	newimg.createMaskFromColor(sf::Color::Black);
	this->CacheTexture = new Resource_Manager::TextureData();
	sf::Texture* newtex = new sf::Texture();
	newtex->loadFromImage(newimg);
	CacheTexture->_height = 1;
	CacheTexture->_width = 1;
	CacheTexture->_GfxID = 0;
	CacheTexture->_Texture = std::shared_ptr<sf::Texture>(newtex);
	CacheTexture->_Sprite = std::shared_ptr<sf::Sprite>(new sf::Sprite());
	CacheTexture->_Sprite->setTexture(*CacheTexture->_Texture);
	for(int i = 1; i < 26; i++)
	{
	Resource_Manager::Module module = LoadModule(i);
	Resource_Manager::Modules[i] = module;
	}
	return 0;
}

Resource_Manager::TextureData* Resource_Manager::GetResource(DWORD ModuleID, int GFXID, bool BlackIsTransparent)
{

	if(!BlackIsTransparent)
	{
		if(!this->Modules[ModuleID].data[GFXID].Data)
		{
			sf::Texture* text = new sf::Texture();
			CBitmapEx bitmapEx;
			HBITMAP BmpHndle = (HBITMAP)LoadImage(this->Modules[ModuleID].module, MAKEINTRESOURCE(GFXID + 100),0,0,0,0);
			if (BmpHndle == NULL)
			{
				return CacheTexture;
			}
			else
			{
				bitmapEx.Load(BmpHndle);
				DWORD dwBufferSize = bitmapEx.GetSize() + sizeof(BITMAPFILEHEADER) + sizeof(RGBQUAD) + sizeof(BITMAPINFOHEADER);
				LPBYTE buffer;
				buffer = (LPBYTE)malloc(dwBufferSize);
				bitmapEx.Save(buffer);
				bool loadsuccesss = text->loadFromMemory(buffer, dwBufferSize);
				text->generateMipmap();
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				//text->setSmooth(true);
				//if (ModuleID == 3)
				{
					//text->setSmooth(false);
				}
				free(buffer);

				if (loadsuccesss)
				{
					Module::TXData dat;
					Resource_Manager::TextureData* texturedat = new Resource_Manager::TextureData();
					sf::Sprite* m_sprite = new sf::Sprite();
					texturedat->_GfxID = ModuleID;
					texturedat->_TextureID = GFXID;
					texturedat->_Texture = std::shared_ptr<sf::Texture>(text);
					texturedat->_height = bitmapEx.GetHeight();
					texturedat->_width = bitmapEx.GetWidth();
					m_sprite->setTexture(*text);
					texturedat->_Sprite = std::shared_ptr<sf::Sprite>(m_sprite);
					dat.Data = texturedat;

					this->Modules[ModuleID].data[GFXID] = dat;
					return dat.Data;
				}
				else
				{
					delete text;
					return CacheTexture;
				}
			}
		}
		else
		{
			return this->Modules[ModuleID].data[GFXID].Data;
		}
	}
	else
	{
		
		if(!this->Modules[ModuleID].data[GFXID + 1000000].Data)
		{
			sf::Image resimage;
			sf::Texture* text = new sf::Texture();
			CBitmapEx bitmapEx;
			HBITMAP BmpHndle = (HBITMAP)LoadImage(this->Modules[ModuleID].module, MAKEINTRESOURCE(GFXID + 100),0,0,0,0);
			if (BmpHndle == NULL)
			{
				return CacheTexture;
			}
			else
			{
				bitmapEx.Load(BmpHndle);
				DWORD dwBufferSize = bitmapEx.GetSize() + sizeof(BITMAPFILEHEADER) + sizeof(RGBQUAD) + sizeof(BITMAPINFOHEADER);
				LPBYTE buffer;
				buffer = (LPBYTE)malloc(dwBufferSize);
				bitmapEx.Save(buffer);
				resimage.loadFromMemory(buffer, dwBufferSize);
				resimage.createMaskFromColor(sf::Color::Black, 0);
				bool loadsuccesss = text->loadFromImage(resimage);
				text->generateMipmap();

				//text->setSmooth(true);
				//if (ModuleID == 3)
				{
				//	text->setSmooth(false);
				}
				free(buffer);
				if (loadsuccesss)
				{
					Module::TXData dat;
					Resource_Manager::TextureData* texturedat = new Resource_Manager::TextureData();
					sf::Sprite* m_sprite = new sf::Sprite();
					texturedat->_GfxID = ModuleID;
					texturedat->_TextureID = GFXID + 1000000;
					texturedat->_Texture = std::shared_ptr<sf::Texture>(text);
					texturedat->_height = bitmapEx.GetHeight();
					texturedat->_width = bitmapEx.GetWidth();
					m_sprite->setTexture(*text);
					texturedat->_Sprite = std::shared_ptr<sf::Sprite>(m_sprite);
					dat.Data = texturedat;
					this->Modules[ModuleID].data[GFXID + 1000000] = dat;
					return dat.Data;
				}
				else
				{
					delete text;
					return CacheTexture;
				}
			}
		}
		else
		{
			return  this->Modules[ModuleID].data[GFXID + 1000000].Data;
		}
	}	
};

void Resource_Manager::Release()
{
	//map<int, Module>::iterator iter;
   //  for (iter = this->Modules.begin(); iter != this->Modules.end(); iter++) 
	 {
	//	/ map<int, Module::TXData>::iterator d_iter;
		/// for (d_iter = iter->second.data.begin(); d_iter != iter->second.data.end(); d_iter++) 
		 {
			// if(this->Modules[iter->first].data[d_iter->first].Data._Texture) 
			 {
			//	this->Modules[iter->first].data[d_iter->first].Data._Texture.reset();
			 }
		 }
	 }

}

void Resource_Manager::DestroyTexture(int FileID, int GFXID)
{
	
	if(this->Modules[FileID].data[GFXID].Data->_Texture)
		{
			ZeroMemory(&this->Modules[FileID].data[GFXID],sizeof(this->Modules[FileID].data[GFXID]));
		}
}
