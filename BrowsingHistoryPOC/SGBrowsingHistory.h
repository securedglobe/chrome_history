/*
Fetch and search your Chrome history
A CodeProject article for explaining how to fetch the browsing history of the most popular browser, Chrome.

Author: Michael Haephrati 	haephrati@gmail.com
Secured Globe, Inc. 		www.securedglobe.net
©2019 Michael Haephrati, Secured Globe, Inc. 1501 Broadway Ave, STE 1200, New York 10036, NY


*/
#pragma once
#define URL_MAXSIZE 2048
#include <Windows.h>
#include <wincrypt.h>
#include <wincred.h>
#include <atlbase.h>
#include <atlstr.h>

#include "pstore.h"
#define CHROME_HISTORY_SQL_QUERY "SELECT last_visit_time, datetime(last_visit_time / 1000000 - 11644473600, 'unixepoch', 'localtime'),url,title FROM urls ORDER BY last_visit_time DESC"
#define CHROME_HISTORY_SQL_QUERY2_LEFT "SELECT last_visit_time, datetime(last_visit_time / 1000000 - 11644473600, 'unixepoch', 'localtime'),url,title FROM urls WHERE title like '"
#define CHROME_HISTORY_SQL_QUERY2_RIGHT "' ORDER BY last_visit_time DESC"

#define CHROMEHISTORY			_T("\\Google\\Chrome\\User Data\\Default\\history")

typedef struct _SGBrowserHistory
{
	int Browser;  // 1 = chrome, 2 = firefox, 3 = ie
	WCHAR SiteURL[URL_MAXSIZE];
	WCHAR SiteName[1024];
	WCHAR LastVisitDate[256];
} SGBrowserHistory;

typedef CSimpleArray<SGBrowserHistory> SGBrowserHistoryArray;

class SGBrowsingHistory
{
public:
	bool GetChromeHistory(SGBrowserHistoryArray *history,CString FileName = L"", CString SearchString= L"");


};

