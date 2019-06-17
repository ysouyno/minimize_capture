// minimize_capture.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <Windows.h>
#include <log4cxx/logger.h>

log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("minimize_capture"));

int main()
{
	LOG4CXX_DEBUG(logger, "main");

	HWND hwnd = FindWindow(NULL, L"mfc_application_test");
	if (!hwnd)
	{
		LOG4CXX_ERROR(logger, L"no window named mfc_application_test");
		return -1;
	}

	BOOL is_iconic = IsIconic(hwnd);
	if (is_iconic)
	{
		LOG4CXX_DEBUG(logger, "hwnd is invisible");
	}
	else
	{
		LOG4CXX_DEBUG(logger, "hwnd is visible");
	}

	long old_style = 0;
	ANIMATIONINFO ai;
	ai.cbSize = sizeof(ai);

	if (is_iconic)
	{
		ai.iMinAnimate = 0;
		SystemParametersInfo(SPI_SETANIMATION, ai.cbSize, &ai, SPIF_SENDCHANGE);

		old_style = GetWindowLong(hwnd, GWL_EXSTYLE);
		SetWindowLong(hwnd, GWL_EXSTYLE, old_style | WS_EX_LAYERED);
		SetLayeredWindowAttributes(hwnd, 0, 1, LWA_ALPHA);
		ShowWindow(hwnd, SW_RESTORE);
	}

	RECT rect;
	GetWindowRect(hwnd, &rect);

	HDC hdc_hwnd = GetDC(NULL);
	HDC hdc = CreateCompatibleDC(hdc_hwnd);
	HBITMAP hbmp = CreateCompatibleBitmap(hdc_hwnd,
		rect.right - rect.left,
		rect.bottom - rect.top);
	SelectObject(hdc, hbmp);

	PrintWindow(hwnd, hdc, 0);

	OpenClipboard(NULL);
	EmptyClipboard();
	SetClipboardData(CF_BITMAP, hbmp);
	CloseClipboard();

	DeleteObject(hbmp);
	DeleteDC(hdc);
	ReleaseDC(NULL, hdc_hwnd);

	if (is_iconic)
	{
		ShowWindow(hwnd, SW_MINIMIZE);
		SetWindowLong(hwnd, GWL_EXSTYLE, old_style);

		ai.iMinAnimate = 1;
		SystemParametersInfo(SPI_SETANIMATION, ai.cbSize, &ai, SPIF_SENDCHANGE);
	}

	return 0;
}
