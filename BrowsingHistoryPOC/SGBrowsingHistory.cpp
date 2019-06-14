/*
Fetch and search your Chrome history
A CodeProject article for explaining how to fetch the browsing history of the most popular browser, Chrome.

Author: Michael Haephrati 	haephrati@gmail.com
Secured Globe, Inc. 		www.securedglobe.net
©2019 Michael Haephrati, Secured Globe, Inc. 1501 Broadway Ave, STE 1200, New York 10036, NY


*/
#include "SGBrowsingHistory.h"
#include "utils.h"
#include "SG_Database.h"

CSGDatabase * db;		// Database for captured data

bool SGBrowsingHistory::GetChromeHistory(SGBrowserHistoryArray *history, CString FileName,CString SearchString)
{
	bool result = false;
	WCHAR szPath[MAX_PATH];
	utils::SG_GetSpecialFolderPath(szPath, CSIDL_LOCAL_APPDATA);
	StrCat(szPath, CHROMEHISTORY);

	WCHAR filename[MAX_PATH + 1] = { TEMP_DB_NAME };

	if (CopyFile(szPath, filename, FALSE))
	{
		if (GetFileAttributes(filename) != 0xFFFFFFFF)
		{
		}
		else
		{
			wprintf(L"Error: Cannot find login data for Google Chrome browser\r\n");
		}
		bool result = db->GetChromeHistoryRecords(filename, history, SearchString);
	}

	return result;
}
