/*
Fetch and search your Chrome history
A CodeProject article for explaining how to fetch the browsing history of the most popular browser, Chrome.

Author: Michael Haephrati 	haephrati@gmail.com
Secured Globe, Inc. 		www.securedglobe.net
©2019 Michael Haephrati, Secured Globe, Inc. 1501 Broadway Ave, STE 1200, New York 10036, NY


*/
#include <iostream>
#include <stdio.h>
#include "utils.h"
#include "SGBrowsingHistory.h"
#include "SG_Database.h"
using namespace std;

/*
	USAGE:
	BrowsingHistoryPOC - fetches all history records
	BrowsingHistoryPOC <Database file name> -	fetches all history records from a given
												database file
	BrowsingHistoryPOC <Database file name>, <search string>
											-	fetches all history records based on 
												a given search term.
*/
int main(int argc,      // Number of strings in array argv
	char *argv[])		// Array of command-line argument strings
{
	CString DbFileName = L"";
	CString SearchString = L"";
	char *argument = NULL;
	if (argc > 1)
	{
		argument = &argv[1][0];
		std::wstring temp;
		temp = (LPWSTR)utils::ConvertA2W(argument).c_str();
		DbFileName = temp.c_str();
		wprintf(L"Loading history from file '%s'\n", DbFileName.GetBuffer());
		if (argc > 2)
		{
			argument = &argv[2][0];
			std::wstring temp;
			temp = (LPWSTR)utils::ConvertA2W(argument).c_str();
			SearchString = temp.c_str();
			SearchString.Replace(L"*", L"%");
			wprintf(L"Filtering history to '%s'\n", SearchString.GetBuffer());
		}
	}

	// Get the date and time of last query
	CString LastBrowserQueryDateTime = L"", NewBrowserQueryDateTime = L"";
	utils::SetRed();
	wprintf(L"Browsing History POC\n");
	utils::SetGreen();
	wprintf(L"\nFetch and search your Chrome history\n");
	utils::SetYellow();
	wprintf(L"A CodeProject article for explaining how to fetch the browsing history of the most popular browser, Chrome.\n");
	utils::SetGreen();
	wprintf(L"Author: Michael Haephrati 	haephrati@gmail.com, Secured Globe, Inc.\n");
	wprintf(L"www.securedglobe.net(c)2019 Michael Haephrati, Secured Globe, Inc. 1501 Broadway Ave, STE 1200, New York 10036, NY\n\n");
	utils::SetWhite();

	SGBrowsingHistory Chrome;
	SGBrowserHistoryArray ChromeResults;
	Chrome.GetChromeHistory(&ChromeResults,DbFileName,SearchString);
	wprintf(L"Chrome history has collected\nPress any key to view\n");
	for (int i = 0; i < ChromeResults.GetSize(); i++)
	{
		utils::SetRed();
		wprintf(L"%d", i);
		utils::SetGreen();
		wprintf(L"\t%s ",ChromeResults[i].LastVisitDate);
		utils::SetWhite();
		wprintf(L"%s \n\n", ChromeResults[i].SiteName);
		utils::SetYellow();
		wprintf(L"%s\n\n", ChromeResults[i].SiteURL);

	}
	system("pause");

}
