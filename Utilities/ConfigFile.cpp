#include "..\stdafx.h"
#include "ConfigFile.h"
#include <iostream>
#include <Windows.h>

CIniReader::CIniReader(char* szFileName)
{
 memset(m_szFileName, 0x00, 255);
 memcpy(m_szFileName, szFileName, strlen(szFileName));
}
int CIniReader::ReadInteger(char* szSection, char* szKey, int iDefaultValue)
{
 int iResult = GetPrivateProfileIntA(szSection,  szKey, iDefaultValue, m_szFileName); 
 return iResult;
}
float CIniReader::ReadFloat(char* szSection, char* szKey, float fltDefaultValue)
{
 char szResult[255];
 char szDefault[255];
 float fltResult;
 sprintf(szDefault, "%f",fltDefaultValue);
 GetPrivateProfileStringA(szSection,  szKey, szDefault, szResult, 255, m_szFileName); 
 fltResult =  atof(szResult);
 return fltResult;
}
bool CIniReader::ReadBoolean(char* szSection, char* szKey, bool bolDefaultValue)
{
 char szResult[255];
 char szDefault[255];
 bool bolResult;
 sprintf(szDefault, "%s", bolDefaultValue? "True" : "False");
 GetPrivateProfileStringA(szSection, szKey, szDefault, szResult, 255, m_szFileName); 
 bolResult =  (strcmp(szResult, "True") == 0 || 
		strcmp(szResult, "true") == 0) ? true : false;
 return bolResult;
}
char* CIniReader::ReadString(char* szSection, char* szKey, const char* szDefaultValue)
{
 char* szResult = new char[255];
 memset(szResult, 0x00, 255);
 GetPrivateProfileStringA(szSection,  szKey, 
		szDefaultValue, szResult, 255, m_szFileName); 
 return szResult;
}

CIniWriter::CIniWriter(char* szFileName)
{
 memset(m_szFileName, 0x00, 255);
 memcpy(m_szFileName, szFileName, strlen(szFileName));
}
void CIniWriter::WriteInteger(char* szSection, char* szKey, int iValue)
{
 char szValue[255];
 sprintf(szValue, "%d", iValue);
 WritePrivateProfileStringA(szSection,  szKey, szValue, m_szFileName); 
}
void CIniWriter::WriteFloat(char* szSection, char* szKey, float fltValue)
{
 char szValue[255];
 sprintf(szValue, "%f", fltValue);
 WritePrivateProfileStringA(szSection,  szKey, szValue, m_szFileName); 
}
void CIniWriter::WriteBoolean(char* szSection, char* szKey, bool bolValue)
{
 char szValue[255];
 sprintf(szValue, "%s", bolValue ? "on" : "off");
 WritePrivateProfileStringA(szSection,  szKey, szValue, m_szFileName); 
}
void CIniWriter::WriteString(char* szSection, char* szKey, char* szValue)
{
 WritePrivateProfileStringA(szSection,  szKey, szValue, m_szFileName);
}
std::string IniConfiguration::Host = "";
int IniConfiguration::Port = 0;
bool IniConfiguration::FullScreen = false;

void IniConfiguration::Init()
{
	DWORD cchCurDir = MAX_PATH;
	char szCurDir[MAX_PATH];
		
	int cnt = GetCurrentDirectoryA(cchCurDir, szCurDir);
	std::string str = "\\config\\setup.ini";
	for(int i = 0; i <str.length();i++)
	{
		szCurDir[cnt + i] = str[i];
	}
	szCurDir[cnt + str.length()] = '\0';
	reader = new CIniReader(szCurDir);
	this->Host = reader->ReadString("CONNECTION","Host","game.endless-online.com");
	this->Port = reader->ReadInteger("CONNECTION","Port",8078);
	std::string Fullscreen = reader->ReadString("CONFIGURATION","Fullscreen","off");
	this->FullScreen = false;
		if(Fullscreen == "off")
		{this->FullScreen = true;}
}