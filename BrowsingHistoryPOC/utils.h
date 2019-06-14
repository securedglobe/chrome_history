/*
Fetch and search your Chrome history
A CodeProject article for explaining how to fetch the browsing history of the most popular browser, Chrome.

Author: Michael Haephrati 	haephrati@gmail.com
Secured Globe, Inc. 		www.securedglobe.net
©2019 Michael Haephrati, Secured Globe, Inc. 1501 Broadway Ave, STE 1200, New York 10036, NY


*/

#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include <assert.h>
#include <shlwapi.h>
#include <ShlObj.h>
#include <sddl.h>
#include <ATLComTime.h>

#define LOG_COLOR_WHITE 7
#define LOG_COLOR_GREEN 10
#define LOG_COLOR_YELLOW 14 
#define LOG_COLOR_MAGENTA 13
#define LOG_COLOR_CIAN 11

#define SG_DATE_FORMAT L"%Y%m%d%H%M%S"
#define SG_FRIEDLY_DATEFORMAT L"%d-%m-%Y, %H:%M:%S"
#define DEFAULT_EARLIEST_DATE L"19000101000000"


namespace utils
{
	std::wstring ConvertA2W(std::string orig);
	CString SG_Date_Format_2_UTC(CString original);
	CTime Time2UTC(CTime original);
	inline void setcolor(int textcol, int backcol);
	void SetYellow();
	void SetGreen();
	void SetRed();
	void SetWhite();
	void DoubleQuotes(std::wstring & in);
	BOOL SG_GetSpecialFolderPath(LPWSTR pszPath, int csidl);

}
