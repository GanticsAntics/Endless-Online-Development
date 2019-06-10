#include <string>
#ifndef INIREADER_H
#define INIREADER_H
class CIniReader
{
public:
 CIniReader(char* szFileName); 
 int ReadInteger(char* szSection, char* szKey, int iDefaultValue);
 float ReadFloat(char* szSection, char* szKey, float fltDefaultValue);
 bool ReadBoolean(char* szSection, char* szKey, bool bolDefaultValue);
 char* ReadString(char* szSection, char* szKey, const char* szDefaultValue);
private:
  char m_szFileName[255];
};
#endif//INIREADER_H

#ifndef INIWRITER_H
#define INIWRITER_H
class CIniWriter
{
public:
 CIniWriter(char* szFileName); 
 void WriteInteger(char* szSection, char* szKey, int iValue);
 void WriteFloat(char* szSection, char* szKey, float fltValue);
 void WriteBoolean(char* szSection, char* szKey, bool bolValue);
 void WriteString(char* szSection, char* szKey, char* szValue);
private:
 char m_szFileName[255];
};
#endif //INIWRITER_H

#ifndef Config_H
#define Config_H
class IniConfiguration
{
public:
	CIniReader* reader;
	CIniWriter* writer;
	static std::string Host;
	static int Port;
	static bool FullScreen;
	static bool Sizeable;
	static bool StayOnTop;
	static bool Music;
	static bool Sound;
	static bool Shadows;
	static bool ChatBalloons;
	static bool Filter;
	static bool FilterAll;
	void Init();
};
#endif //Config_H