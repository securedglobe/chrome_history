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
#include "CppSQLite3U.h"
#include "SGBrowsingHistory.h"

#define LOGSQLERROR(e,sql) LogSqlError(e, (CString)__FUNCTION__, sql);
#define TEMP_DB_NAME	L"temp.db"

class CSGDatabase
{
public:
	CSGDatabase(LPCTSTR fileName);
	~CSGDatabase();
	void OpenDB(LPCTSTR fileName);
	void CloseDB();
	bool CSGDatabase::GetChromeHistoryRecords(LPWSTR DbFileName, SGBrowserHistoryArray *history, CString SearchString);
	void LogSqlError(CppSQLite3Exception &e, CString Function, CString sql);
private:
	CppSQLite3DB db;
};
extern CSGDatabase * db;		// Database for captured data

