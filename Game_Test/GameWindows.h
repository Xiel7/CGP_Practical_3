#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <iostream>
#include "resource.h"
#include <d3d9.h>
#include <d3dx9.h>


class GameWindows
{
private:
	//	Window handle
	static GameWindows* instance;
	HWND g_hWnd;
	HINSTANCE hInstance;
	//	Window's structure
	WNDCLASS wndClass;
	bool isFullscreen;

	GameWindows();
public:
	static int keyPressed;
	static int mouseX;
	static int mouseY;
	int r;
	int g;
	int b;
	static GameWindows* getInstance();
	void createWindow();
	void clearWindow();
	bool gameLoop();
	HWND getHWND();
	void setIsFullscreen(bool isFullScreen);
	bool getIsFullscreen();


};