// JCTGame.cpp : Defines the entry point for the application.
//
#pragma once
#include "JCTGame.h"
#include "JCTGLControl.h"
#include "JCTCube.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                        // current instance
char szTitle[MAX_LOADSTRING];            	// The title bar text
char szWindowClass[MAX_LOADSTRING];      	// the main window class name

// Forward declarations of functions included in this code module:
ATOM            MyRegisterClass(HINSTANCE hInstance);
BOOL            InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
void OnMouseMove(int buttons, int x, int y);
void OnPaint();

void Draw();
JCTGLControl *Game;
JCTCube *pCube;
JCTCube *pCube2;
Vect pCenter;
Vect *pCubeSpot;
JCTSphere *pSphere;

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     char*    lpCmdLine,
                     int       nCmdShow)
{

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;
   
#ifdef _DEBUG
   Game = new JCTGLControl();
   
//   pCube = new JCTCube(5.0f, .5f, .5f);
   pCube = new JCTCube(2.0f);
   
   pCube2 = new JCTCube(2.0f);
   
   pCubeSpot = new Vect(0.0f, 0.0f, -7.0f);

   pSphere = new JCTSphere();

#else
   Game = new JCTGLControl();
   
   pCube = new JCTCube(1.0f);
   
   pCube2 = new JCTCube(2.0f);
   


   //pCube2 = new JCTCube(2.0f);
   

   pCubeSpot = new Vect(0.0f, 0.0f, -7.0f);
#endif
   pCube->m_vColor[0].set(0.0f, 0.0f, 1.0f);
   pCenter = Game->getCenter();

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_JCTGAME, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
      return FALSE;
	}
   Game->LoadStartup();
   Game->initTimer();

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_JCTGAME));
//   Test();
   
   while(Game->IsActive())
   {
      OnPaint();  

      while (PeekMessage (&msg, NULL, 0, 0, PM_NOREMOVE))
      {
         if (!GetMessage (&msg, NULL, 0, 0))
         {
            Game->SetActive(false);
            break;
         }

         TranslateMessage (&msg);
         DispatchMessage (&msg);
      }

   }

	return 0;//(int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style      	= CS_HREDRAW | CS_VREDRAW;
   wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra      = 0;
	wcex.cbWndExtra      = 0;
	wcex.hInstance      = hInstance;
	wcex.hIcon      	= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_JCTGAME));
	wcex.hCursor      = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_JCTGAME);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm      = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;
//   MSG      msg;          // message
   DWORD     dwExStyle;      // Window Extended Style
   DWORD     dwStyle;       // Window Style
   RECT      windowRect;
//	HACCEL hAccelTable;

   hInst = hInstance; // Store instance handle in our global variable

   windowRect.left=(long)0;                  // Set Left Value To 0
   windowRect.right=(long)JCTGLControl::m_windowWidth; // Set Right Value To Requested Width
   windowRect.top=(long)0;                   // Set Top Value To 0
   windowRect.bottom=(long)JCTGLControl::m_windowHeight;   // Set Bottom Value To Requested Height


   if (Game->fullscreen)                      // fullscreen?
   {
      DEVMODE dmScreenSettings;               // device mode
      memset(&dmScreenSettings,0,sizeof(dmScreenSettings));
      dmScreenSettings.dmSize = sizeof(dmScreenSettings); 
      dmScreenSettings.dmPelsWidth = JCTGLControl::m_windowWidth;       // screen width
      dmScreenSettings.dmPelsHeight = JCTGLControl::m_windowHeight;         // screen height
      dmScreenSettings.dmBitsPerPel = Game->windowBits;          // bits per pixel
      dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

      // 
      if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
      {
         // setting display mode failed, switch to windowed
         MessageBox(NULL, (char*)"Display mode failed", NULL, MB_OK);
         Game->fullscreen = FALSE; 
      }
   }

   if (Game->fullscreen)                      // Are We Still In Fullscreen Mode?
   {
      dwExStyle=WS_EX_APPWINDOW;              // Window Extended Style
      dwStyle=WS_POPUP;                  // Windows Style
      ShowCursor(FALSE);                 // Hide Mouse Pointer
   }
   else
   {
      dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;   // Window Extended Style
      dwStyle=WS_OVERLAPPEDWINDOW;               // Windows Style
   }

   AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);    // Adjust Window To True Requested Size

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   GetDC(hWnd);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}
//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//

void OnPaint()
{
   Game->SetupCamera();
   Draw();
   Game->Render();

///	SwapBuffers(hDC);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;

	switch (message)
	{
	case WM_COMMAND:
      wmId    = LOWORD(wParam);
      wmEvent = HIWORD(wParam);
      // Parse the menu selections:
      switch (wmId)
      {
      case IDM_ABOUT:
      	DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
      	break;
      case IDM_EXIT:
      	DestroyWindow(hWnd);
      	break;
      default:
      	return DefWindowProc(hWnd, message, wParam, lParam);
      }
      break;

   case WM_CREATE:       // window creation
      Game->SetDrawingContext(GetDC(hWnd));
      Game->SetupPixelFormat();
      break;
   case WM_SIZE:
      Game->SetupProjection(LOWORD(lParam), HIWORD(lParam));
      break;
	case WM_PAINT:
      BeginPaint(hWnd, &ps);
//       OnPaint();  
         
      // TODO: Add any drawing code here...
      EndPaint(hWnd, &ps);
      break;
	case WM_DESTROY:
      Game->DestryDrawingContext();
      PostQuitMessage(0);
      break;
   case WM_KEYUP:
         break;

   case WM_KEYDOWN:
      int fwKeys;
      LPARAM keyData;
      fwKeys = (int)wParam;   // virtual-key code 
      keyData = lParam;        // key data 
      Game->HandleKeys(fwKeys);
      break;

   case WM_MOUSEMOVE:
		OnMouseMove(wParam,LOWORD(lParam),HIWORD(lParam));
		break;

	default:
      return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


void OnMouseMove(int flags, int x, int y){
	static int mouseX, mouseY;

	if (flags & VK_LBUTTON){
		Game->m_vRotate.set(Game->m_vRotate.getElement(1)-(mouseY - y),Game->m_vRotate.getElement(0)-(mouseX - x), Game->m_vRotate.getElement(2));
		//Game->m_vRotate.set(0,);
	}
	if (flags & VK_RBUTTON){
		Game->m_fZvalue += (float)((mouseX - x)*0.1);
		if (Game->m_fZvalue>200) Game->m_fZvalue=200.0;
		if (Game->m_fZvalue<5) Game->m_fZvalue=5.0;
	}     
	mouseX = x;
	mouseY = y;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
      return (INT_PTR)TRUE;

	case WM_COMMAND:
      if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
      {
      	EndDialog(hDlg, LOWORD(wParam));
      	return (INT_PTR)TRUE;
      }
      break;
	}
	return (INT_PTR)FALSE;
}

void Draw()
{

   pCenter = Game->getCenter();

   Game->SetupCamera();
   float fTemp = (pCenter.getElement(2)-5.0f);
   pCenter.setElement(2, fTemp);

   if(pCube->Collide(pCube2->getAABB(pCenter), *pCubeSpot))
   {
      pCube->m_vColor[0].set(1.0f, 0.0f, 0.0f);
      pCube2->m_vColor[0].set(.6f, 0.0f, 0.0f);
   }
   else
   {
      pCube->m_vColor[0].set(0.0f, 0.0f, 1.0f);
      pCube2->m_vColor[0].set(0.0f, 0.6f, 0.0f);
   }
	Game->DrawColorCube(0.0f, 0.0f, -7.0f, *pCube);//);centerX-1.0f, centerY, centerZ+1.0f, 1.0f);
   Game->DrawColorCube(pCenter.getElement(0), pCenter.getElement(1), pCenter.getElement(2), *pCube2, true);
}

