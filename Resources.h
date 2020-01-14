
using namespace std;

#ifndef Resource_h
#define Resource_h
class Resource
{
	public:

		/*
		Texture Data struct - for referencing textures when destroyed.
		*/
		struct TextureData
		{
		public:
			int TextureID;
			int GfxID;
			std::shared_ptr<IDirect3DTexture9> Texture;
		};

		/*
		Module - A Module for each Gfx file. Credits go to Addison for this one!
		*/
		struct Module
		{
		public:
	    
			struct TXData
			{
			public: 
				D3DXIMAGE_INFO BitmapInfo;
				TextureData Data;
			};

			bool loadfailed;
            int failid;
            HMODULE module;
			map<int, TXData> data;		
		};

		Module LoadModule(int file);
		HRESULT CreateSprite(IDirect3DDevice9Ptr Device, ID3DXSprite* Sprite);
		HRESULT Initialize(IDirect3DDevice9Ptr Device);
		typedef std::map<int,Module> ModuleType;
		ModuleType Modules;
		TextureData CreateTexture(DWORD ModuleID, int GFXID, bool BlackIsTransparent);
		D3DXIMAGE_INFO GetImageInfo(DWORD ModuleID, int GFXID, bool Transparent);
		static struct Resources
		{
				enum ResourceIDs
				{
					Gfx001 = 1,
					Gfx002 = 2,
					Gfx003 = 3,
					Gfx004 = 4,
					Gfx005 = 5,
					Gfx006 = 6,
					Gfx007 = 7,
					Gfx008 = 8,
					Gfx009 = 9,
					Gfx010 = 10,
					Gfx011 = 11,
					Gfx012 = 12,
					Gfx013 = 13,
					Gfx014 = 14,
					Gfx015 = 15,
					Gfx016 = 16,
					Gfx017 = 17,
					Gfx018 = 18,
					Gfx019 = 19,
					Gfx020 = 20,
					Gfx021 = 21,
					Gfx022 = 22,
					Gfx023 = 23,
					Gfx024 = 24,
					Gfx025 = 25
				 };
		};
		LPDIRECT3DTEXTURE9 CacheTexture;
		void Release();
		void DumpGFX(Resources ResourceID);
		void DestroyTexture(int FileID, int GfxID);
		BITMAP CacheBitmap;
};
#endif //Resource_h