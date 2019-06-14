/*
Fetch and search your Chrome history
A CodeProject article for explaining how to fetch the browsing history of the most popular browser, Chrome.

Author: Michael Haephrati 	haephrati@gmail.com
Secured Globe, Inc. 		www.securedglobe.net
©2019 Michael Haephrati, Secured Globe, Inc. 1501 Broadway Ave, STE 1200, New York 10036, NY


*/
#include "stdafx.h"
#include "SG_Database.h"
#include "utils.h"
#include "SGBrowsingHistory.h"

#define createTableChromeHistory L"CREATE TABLE IF NOT EXISTS ChromeHistory(\
id INTEGER PRIMARY KEY AUTOINCREMENT,\
created TIMESTAMP not null default CURRENT_TIMESTAMP,\
date_last_visited TEXT not null default '',\
site_name TEXT not null default '',\
size_url TEXT not null default '',\
);"


// 

#define STR_ERROR_RUNNING_QEURY L"Error running query: %s. Error message: %s. Function = %s\n"


void CSGDatabase::LogSqlError(CppSQLite3Exception &e, CString Function, CString sql)
{
	wprintf(STR_ERROR_RUNNING_QEURY, sql.GetBuffer(), e.errorMessage(), Function.GetBuffer());
}

CSGDatabase::CSGDatabase(LPCTSTR fileName)
{
	OpenDB(fileName);
}


CSGDatabase::~CSGDatabase()
{
	CloseDB();
}


void CSGDatabase::OpenDB(LPCTSTR fileName)
{
	db.close();
	db.open(fileName);

	try
	{
		if (!db.tableExists(L"ChromeHistory")) db.execDML(createTableChromeHistory);
	}
	catch (CppSQLite3Exception & e)
	{
		wprintf(L"Can't create the ChromeHistory table in the database.\n Error #1 - %s\n", e.errorMessage());
	}
}


void CSGDatabase::CloseDB()
{ 
	db.close(); 
}


bool CSGDatabase::GetChromeHistoryRecords(LPWSTR DbFileName, SGBrowserHistoryArray *history, CString SearchString)
{
	bool result = false;
	int rc = 0;
	WCHAR *szURL, *szURLName, *szURLLastDate;
	CppSQLite3DB HistoryDB;
	try
	{
		HistoryDB.open(DbFileName);
		HistoryDB.execQuery(L"PRAGMA locking_mode = EXCLUSIVE");
	}
	catch (CppSQLite3Exception &e)
	{
		return false;
	}
	CppSQLite3Query SqlQuery;
	CString sql;
	if (SearchString != "")
	{
		sql = (CString)CHROME_HISTORY_SQL_QUERY2_LEFT + SearchString + (CString)CHROME_HISTORY_SQL_QUERY2_RIGHT;
	}
	else
	{
		sql = CHROME_HISTORY_SQL_QUERY;
	}
	try
	{
		SqlQuery = HistoryDB.execQuery(sql);
	}
	catch (CppSQLite3Exception &e)
	{
		LOGSQLERROR(e,sql);
		return 0;
	}
	// Prepare data structure
	SGBrowserHistory SingleBrowserHistoryEntry;
	// Empty the array
	history->RemoveAll();
	result = true;
	int count = 0;
	
	while (!SqlQuery.eof())	// we assume there is always one file with one code
	{
		szURLLastDate = (WCHAR *)SqlQuery.fieldValue(1);
		szURLName = (WCHAR *)SqlQuery.fieldValue(3);
		szURL = (WCHAR *)SqlQuery.fieldValue(2);
		CString UTC_Date = utils::SG_Date_Format_2_UTC(szURLLastDate);
		if (UTC_Date == DEFAULT_EARLIEST_DATE)
		{
			wprintf(L"Web site %s (%s) has an error in its visited date\n", szURLName, szURL);
		}
		wcsncpy(SingleBrowserHistoryEntry.SiteName, szURLName, 256);
		wcsncpy(SingleBrowserHistoryEntry.SiteURL, szURL, URL_MAXSIZE);
		// Convert last visit date/time to GMT / UTC
		wcscpy(SingleBrowserHistoryEntry.LastVisitDate, UTC_Date);

		history->Add(SingleBrowserHistoryEntry);
		SqlQuery.nextRow();
	}
	wprintf(L"Found %d history records\n",history->GetSize());
	// Now we calculate the mex visit date time
	try
	{
		sql = L"SELECT MAX(last_visit_time) as max_visit_time FROM urls";
		SqlQuery = HistoryDB.execQuery(sql);
	}
	catch (CppSQLite3Exception &e)
	{
		
		return 0;
	}
	return true;
}
