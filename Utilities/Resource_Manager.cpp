#include "..\stdafx.h"
#include <WinBase.h>
#include <map>
#include <iostream>
#include <conio.h>
#include "..\include/CBitmapEx/BitmapEx.h"
#include "Resource_Manager.h"

#define D3D_DEBUG_INFO
using namespace std;
static IDirect3DDevice9* Device;

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
HRESULT Resource_Manager::Initialize(IDirect3DDevice9Ptr m_Device)
{
	Device = m_Device;
	CBitmapEx Bmp;
	
	for(int i = 1; i < 26; i++)
	{
	Resource_Manager::Module module = LoadModule(i);
	Resource_Manager::Modules[i] = module;
	}
	return 0;
}

HRESULT Resource_Manager::CreateSprite(IDirect3DDevice9Ptr Device, ID3DXSprite* Sprite)
{
	HRESULT hr = D3DXCreateSprite(Device,&Sprite);
	return hr;

}

Resource_Manager::TextureData Resource_Manager::CreateTexture(DWORD ModuleID, int GFXID, bool BlackIsTransparent)
{

	if(!BlackIsTransparent)
	{
		if(!this->Modules[ModuleID].data[GFXID].Data.Texture)
		{
			D3DXIMAGE_INFO info = D3DXIMAGE_INFO();
			LPDIRECT3DTEXTURE9 text = NULL;
			CBitmapEx bitmapEx;
			HBITMAP BmpHndle = (HBITMAP)LoadImage(this->Modules[ModuleID].module, MAKEINTRESOURCE(GFXID + 100),0,0,0,0);
			bitmapEx.Load(BmpHndle);

			DWORD dwBufferSize = bitmapEx.GetSize() + sizeof(BITMAPFILEHEADER) + sizeof(RGBQUAD) + sizeof(BITMAPINFOHEADER);
			LPBYTE buffer;
			buffer = (LPBYTE) malloc(dwBufferSize);
			bitmapEx.Save(buffer);

			HRESULT Hr = D3DXCreateTextureFromFileInMemoryEx(Device,buffer,dwBufferSize,D3DX_DEFAULT_NONPOW2 ,D3DX_DEFAULT_NONPOW2,1,D3DUSAGE_DYNAMIC ,D3DFMT_A8R8G8B8,
																 D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_ARGB(0,0,0,0) | D3DCOLOR_ARGB(0,222,0,0),&info,NULL,&text);
			free(buffer);

			if(text)
			{
				Module::TXData dat;
				Resource_Manager::TextureData texturedat;
				texturedat.GfxID = ModuleID;
				texturedat.TextureID = GFXID;
				texturedat.Texture = std::shared_ptr<IDirect3DTexture9>(text);
				dat.Data =  texturedat;
				dat.BitmapInfo = info;
				this->Modules[ModuleID].data[GFXID] = dat;
				return dat.Data;
			}
			else
			{
				return this->Modules[ModuleID].data[GFXID].Data;
			}
		}
		else
		{
			return this->Modules[ModuleID].data[GFXID].Data;
		}
	}
	else
	{
		
		if(!this->Modules[ModuleID].data[GFXID + 1000000].Data.Texture)
		{
			D3DXIMAGE_INFO info = D3DXIMAGE_INFO();
			LPDIRECT3DTEXTURE9 text = NULL;
			CBitmapEx bitmapEx;
			HBITMAP BmpHndle = (HBITMAP)LoadImage(this->Modules[ModuleID].module, MAKEINTRESOURCE(GFXID + 100),0,0,0,0);
			bitmapEx.Load(BmpHndle);
			bitmapEx.MakeTransparent(_RGB(8,0,0));
			//bitmapEx.
			DWORD dwBufferSize = bitmapEx.GetSize() + sizeof(BITMAPFILEHEADER) + sizeof(RGBQUAD) + sizeof(BITMAPINFOHEADER);
			LPBYTE buffer;
			buffer = (LPBYTE) malloc(dwBufferSize);
			bitmapEx.Save(buffer);

			HRESULT Hr = D3DXCreateTextureFromFileInMemoryEx(Device,buffer,dwBufferSize,D3DX_DEFAULT_NONPOW2 ,D3DX_DEFAULT_NONPOW2,1,D3DUSAGE_DYNAMIC ,D3DFMT_A8R8G8B8,
															 D3DPOOL_DEFAULT, D3DX_FILTER_NONE, D3DX_FILTER_NONE, D3DCOLOR_ARGB(1,0,0,0),&info,NULL,&text);
			free(buffer);
	
			if(SUCCEEDED(Hr))
			{
				Module::TXData dat;
				Resource_Manager::TextureData texturedat;
				texturedat.GfxID = ModuleID;
				texturedat.TextureID = GFXID + 1000000;
				texturedat.Texture = std::shared_ptr<IDirect3DTexture9>(text);
				dat.Data = texturedat;
				dat.BitmapInfo = info;
				this->Modules[ModuleID].data[GFXID + 1000000] = dat;
				return dat.Data;
			}
			else
			{
				return this->Modules[ModuleID].data[GFXID + 1000000].Data;
			}
		}
		else
		{
			return  this->Modules[ModuleID].data[GFXID + 1000000].Data;
		}
	}	
};

D3DXIMAGE_INFO Resource_Manager::GetImageInfo(DWORD ModuleID, int GFXID, bool Transparent)
{
	if(Transparent)
	{
	return this->Modules[ModuleID].data[GFXID + 1000000].BitmapInfo;
	}
	else
	{
	return this->Modules[ModuleID].data[GFXID].BitmapInfo;
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
			// if(this->Modules[iter->first].data[d_iter->first].Data.Texture) 
			 {
			//	this->Modules[iter->first].data[d_iter->first].Data.Texture.reset();
			 }
		 }
	 }

}

void Resource_Manager::DestroyTexture(int FileID, int GFXID)
{
	
	if(this->Modules[FileID].data[GFXID].Data.Texture)
		{
			ZeroMemory(&this->Modules[FileID].data[GFXID],sizeof(this->Modules[FileID].data[GFXID]));
		}
}
