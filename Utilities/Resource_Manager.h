using namespace std;

#ifndef Resource_Manager_h
#define Resource_Manager_h
class Resource_Manager
{
	public:

		/*
		Texture Data struct - for referencing textures when destroyed.
		*/
		struct TextureData
		{
		public:
			int _TextureID;
			int _GfxID;
			std::shared_ptr<sf::Texture> _Texture;
			std::shared_ptr<sf::Sprite>_Sprite;
			int _width;
			int _height;
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
				TextureData* Data;
			};

			bool loadfailed;
            int failid;
            HMODULE module;
			map<int, TXData> data;		
		};
		
		Module LoadModule(int file);
		HRESULT Initialize(sf::RenderWindow*Device);
		typedef std::map<int,Module> ModuleType;
		ModuleType Modules;
		TextureData* GetResource(DWORD ModuleID, int GFXID, bool BlackIsTransparent);
		TextureData CreateTexture(DWORD ModuleID, int GFXID, bool BlackIsTransparent) { return TextureData(); }
		static struct Resource_Managers
		{
				enum Resource_ManagerIDs
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
		TextureData* CacheTexture;
		void Release();
		void DumpGFX(Resource_Managers Resource_ManagerID);
		void DestroyTexture(int FileID, int GfxID);
		BITMAP CacheBitmap;
};
#endif //Resource_Manager_h