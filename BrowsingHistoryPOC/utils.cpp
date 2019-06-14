/*
Fetch and search your Chrome history
A CodeProject article for explaining how to fetch the browsing history of the most popular browser, Chrome.

Author: Michael Haephrati 	haephrati@gmail.com
Secured Globe, Inc. 		www.securedglobe.net
©2019 Michael Haephrati, Secured Globe, Inc. 1501 Broadway Ave, STE 1200, New York 10036, NY


*/
#include "stdafx.h"
#include "utils.h"

namespace utils
{
	std::wstring ConvertA2W(std::string orig)
	{
		std::wstring result(orig.begin(), orig.end());
		return result;
	}

	CString SG_Date_Format_2_UTC(CString original)
	{
		// Should also address dates such as: L"2016-03-01 12:29:37"
		CString converted = L"";
		int Year, Month, Day, Hour, Minute;
		original.Remove('-');
		original.Remove(' ');
		original.Remove(':');


		if (original != L"" && original.GetLength() >= 12)
		{
			Year = _wtol(original.Left(4));
			if (Year <= 1900)
			{
#if _LOG
				wprintf(L"Internal error: Year of %s is %d", original, Year);
#endif
				return (CString)DEFAULT_EARLIEST_DATE;
			}
			Month = _wtol(original.Mid(4, 2));
			Day = _wtol(original.Mid(6, 2));
			Hour = _wtol(original.Mid(8, 2));
			Minute = _wtol(original.Mid(10, 2));
			CTime result(Year, Month, Day, Hour, Minute, 0);
			converted = Time2UTC(result).Format(SG_FRIEDLY_DATEFORMAT);
		}
		return converted;
	}
	CTime Time2UTC(CTime original)
	{
		CString Formatted = original.FormatGmt(SG_DATE_FORMAT);
		int Year, Month, Day, Hour, Minute;

		if (Formatted != L"" && Formatted.GetLength() >= 12)
		{
			Year = _wtol(Formatted.Left(4));
			Month = _wtol(Formatted.Mid(4, 2));
			Day = _wtol(Formatted.Mid(6, 2));
			Hour = _wtol(Formatted.Mid(8, 2));
			Minute = _wtol(Formatted.Mid(10, 2));
			CTime result(Year, Month, Day, Hour, Minute, 0);
			return result;
		}
		else
		{
			return (CTime)NULL;
		}
	}



	inline void setcolor(int textcol, int backcol)
	{
		if ((textcol % 16) == (backcol % 16))textcol++;
		textcol %= 16; backcol %= 16;
		unsigned short wAttributes = ((unsigned)backcol << 4) | (unsigned)textcol;
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hStdOut, wAttributes);
	}
	void SetYellow()
	{
		setcolor(LOG_COLOR_YELLOW, 0);
	}

	void SetGreen()
	{
		setcolor(LOG_COLOR_GREEN, 0);
	}

	void SetRed()
	{
		setcolor(LOG_COLOR_MAGENTA, 0);
	}
	void SetWhite()
	{
		setcolor(LOG_COLOR_WHITE, 0);

	}
	void DoubleQuotes(std::wstring & in)
	{
		if (in == L"") in = L"0";
		size_t pos = 0;
		while ((pos = in.find(L"\'", pos)) != std::wstring::npos)
		{
			in.replace(pos, 1, L"\'\'");
			pos += 2;
		}
	}

	BOOL SG_GetSpecialFolderPath(LPWSTR pszPath, int csidl)
	{
		bool result = FALSE;
		result = SHGetSpecialFolderPath(0, pszPath, csidl, 0);
		wprintf(L"Special folder found %d %s\n", csidl, pszPath);
		return result;
	}

}

