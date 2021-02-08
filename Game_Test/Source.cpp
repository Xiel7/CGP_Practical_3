//	Ask the compiler to include minimal header files for our program.
#include "GameWindows.h"
#define BG_1 "bg1.png"

//	use int main if you want to have a console to print out message 
int main()
//hello
//	use WinMain if you don't want the console
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	GameWindows* gWin = gWin->getInstance();


	gWin->createWindow();
	//	Define Direct3D 9.
	IDirect3D9* direct3D9 = Direct3DCreate9(D3D_SDK_VERSION);

	//	Define how the screen presents.
	D3DPRESENT_PARAMETERS d3dPP;
	ZeroMemory(&d3dPP, sizeof(d3dPP));

	//	Refer to Direct3D 9 documentation for the meaning of the members.
	d3dPP.Windowed = true;
	d3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dPP.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dPP.BackBufferCount = 1;
	d3dPP.BackBufferWidth = 400;
	d3dPP.BackBufferHeight = 300;
	d3dPP.hDeviceWindow = gWin->getHWND();

	IDirect3DDevice9* d3dDevice;
	//	Create a Direct3D 9 device.
	HRESULT hr = direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, gWin->getHWND(), D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dPP, &d3dDevice);

	if (FAILED(hr))
		return 0;

	LPDIRECT3DTEXTURE9 texture = NULL;
	LPD3DXSPRITE sprite = NULL;

	//	Create sprite. Study the documentation. 
	D3DXCreateSprite(d3dDevice, &sprite);

	//	Create texture. Study the documentation.
	D3DXCreateTextureFromFile(d3dDevice, BG_1, &texture);
	//hr = D3DXCreateTextureFromFileEx(d3dDevice, "01.bmp", D3DX_DEFAULT, D3DX_DEFAULT, 
	//									D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, 
	//									D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 255, 255), 
	//									NULL, NULL, &texture);

	//	Specify the "	" rectangle.
	RECT spriteRect;
	spriteRect.left = 57;
	spriteRect.top = 262;
	spriteRect.right = 143;
	spriteRect.bottom = 348;

	int x = 0;
	int y = 0;

	bool executed = gWin->getIsFullscreen();
	while (gWin->gameLoop())//it just works
	{
		//	To Do:
		//	Update.

		//if (executed != gWin->getIsFullscreen())//this is so that it gets executed once per toggle and not infinitely
		//{
		//	if (gWin->getIsFullscreen())
		//	{
		//		d3dPP.BackBufferFormat = D3DFMT_X8R8G8B8;
		//		d3dPP.Windowed = false;
		//		d3dDevice->Reset(&d3dPP);
		//	}
		//	else if (!gWin->getIsFullscreen())
		//	{
		//		d3dPP.BackBufferFormat = D3DFMT_UNKNOWN;
		//		d3dPP.Windowed = true;
		//		d3dDevice->Reset(&d3dPP);
		//	}

		//	executed = gWin->getIsFullscreen();
		//}


		switch (gWin->keyPressed)
		{
		case VK_LEFT:
			x--;
			break;
		case VK_RIGHT:
			x++;
			break;
		case VK_UP:
			y--;
			break;
		case VK_DOWN:
			y++;
			break;
		default:
			break;
		}

		//	Clear the back buffer.
		d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(gWin->r, gWin->g, gWin->b), 1.0f, 0);

		//	Begin the scene
		d3dDevice->BeginScene();
		//	To Do:
		//	Drawing.
		//		//	Clear and begin scene

		//	Specify alpha blend will ensure that the sprite will render the background with alpha.
		sprite->Begin(D3DXSPRITE_ALPHABLEND);

		//	Sprite rendering. Study the documentation.
		//sprite->Draw(texture, NULL, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
		//sprite->Draw(texture, &spriteRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
		sprite->Draw(texture, &spriteRect, NULL, &D3DXVECTOR3(gWin->mouseX, gWin->mouseY, 0), D3DCOLOR_XRGB(255, 255, 255));

		//	End sprite drawing
		sprite->End();

		//	End and present scene

		//	End the scene
		d3dDevice->EndScene();

		//	Present the back buffer to screen
		d3dDevice->Present(NULL, NULL, NULL, NULL);

		
	}

	//	Release the device when exiting.
	d3dDevice->Release();
	//	Reset pointer to NULL, a good practice.
	d3dDevice = NULL;

	//	Release and clean up everything

	sprite->Release();
	sprite = NULL;

	texture->Release();
	texture = NULL;

	gWin->clearWindow();

	return 0;
}