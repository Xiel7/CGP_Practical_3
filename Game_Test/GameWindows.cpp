#include "GameWindows.h"

GameWindows* GameWindows::instance = 0;
int GameWindows::keyPressed = 0;
int GameWindows::mouseX = 0;
int GameWindows::mouseY = 0;

GameWindows* GameWindows::getInstance()
{
	if (!instance)
	{
		instance = new GameWindows;
	}

	return instance;
}

GameWindows::GameWindows()
{
	std::cout << "created" << std::endl;
	this->r = 0;
	this->g = 128;
	this->b = 128;
	this->isFullscreen = false;
	this->hInstance = GetModuleHandle(NULL);
	this->g_hWnd = NULL;
}


//	Window Procedure, for event handling
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	GameWindows* gWin = gWin->getInstance();

	switch (message)
	{
		//	The message is post when we destroy the window.
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		//std::cout << wParam << std::endl;
		if (wParam == VK_ESCAPE)
		{
			PostQuitMessage(0);
			break;
		}

		gWin->keyPressed = wParam;
		//else if (wParam == 70)
		//{
		break;
	case WM_KEYUP:
		gWin->keyPressed = 0;
		break;
	case WM_MOUSEMOVE:
		gWin->mouseX = LOWORD(lParam);
		gWin->mouseY = HIWORD(lParam);
		break;
		//	if (!gWin->getIsFullscreen())
		//	{
		//		gWin->setIsFullscreen(true);
		//	}
		//	else if (gWin->getIsFullscreen())
		//	{
		//		gWin->setIsFullscreen(false);
		//	}
		//}



		//	Default handling for other messages.
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

void GameWindows::createWindow()
{
	/*
	Step 1
	Define and Register a Window.
*/

//	Sset all members in wndClass to 0.
	ZeroMemory(&wndClass, sizeof(wndClass));

	//	Filling wndClass. You are to refer to MSDN for each of the members details.
	//	These are the fundamental structure members to be specify, in order to create your window.
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACKONWHITE);
	wndClass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(BLAZE_CURSOR));
	//wndClass.hCursor = LoadCursorFromFile(AOT);
	wndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(GAME_ICON));
	wndClass.hInstance = hInstance;	//	GetModuleHandle(NULL);
	wndClass.lpfnWndProc = WindowProcedure;
	wndClass.lpszClassName = "My Window";
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	//	Register the window.
	RegisterClass(&wndClass);

	/*
		Step 2
		Create the Window.
	*/
	//	You are to refer to MSDN for each of the parameters details.
	g_hWnd = CreateWindowEx(0, wndClass.lpszClassName, "My Window's Name", WS_OVERLAPPEDWINDOW, 0, 0, 418, 347, NULL, NULL, hInstance, NULL);
	ShowWindow(g_hWnd, 1);

	//	Some interesting function to try out.
	//ShowCursor(false);

	RECT rcClient, rcWind;
	GetClientRect(g_hWnd, &rcClient);
	GetWindowRect(g_hWnd, &rcWind);

	int x = (rcWind.right - rcWind.left) - rcClient.right;
	int y = (rcWind.bottom - rcWind.top) - rcClient.bottom;

	std::cout << x << std::endl;
	std::cout << y << std::endl;

}



void GameWindows::clearWindow()
{
	//	Free up the memory.
	UnregisterClass(wndClass.lpszClassName, hInstance);
}

bool GameWindows::gameLoop()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	/*
		Step 3
		Handling window messages
		NOTE! There are several ways of writing the message loop.
		You have to based on which kind of application your are writing.
	*/

	/*
		The if- version process one message per one iteration loop
		The while- version will clear the message queue before dealing with your own code.
		Another function is GetMessage.
		This function is not suitable for game, because it will block your program until it recieves a message.
		your code will only executed when you have messages, otherwies your pogram will be waiting... (similar to cin)
		Suitable for event based program, such as bussiness app.
	*/
	//	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		//	Receive a quit message
		if (msg.message == WM_QUIT)
		{

		}

		//	Translate the message 
		TranslateMessage(&msg);
		//	Send message to your window procedure
		DispatchMessage(&msg);

	}

	/*
		Write your code here...
	*/


	return msg.message != WM_QUIT;
}

HWND GameWindows::getHWND()
{
	return this->g_hWnd;
}


void GameWindows::setIsFullscreen(bool con)
{
	isFullscreen = con;
}

bool GameWindows::getIsFullscreen()
{
	return this->isFullscreen;
}