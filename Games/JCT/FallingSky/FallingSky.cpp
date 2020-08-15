// FallingSky.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "FallingSky.h"
#include "JCTGLControl.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

void Draw();
JCTGLControl *Game;
JCTCube *pCube;
JCTCube *pCube2;
Vect pCenter;
Vect *pCubeSpot;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_FALLINGSKY, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FALLINGSKY));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
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

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FALLINGSKY));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_FALLINGSKY);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   /*HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}*/
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
   /*	hWnd = CreateWindow( 
	"Win32Example", "Realtime 3D Character Animation - Win32 OpenGL Example", 
	WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_SIZEBOX,
	100, 100, 500, 400,
	NULL, NULL, hInstance, NULL );
      */
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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

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
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
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



/*


#pragma once
#include "JCTGLBase.h"
#include "JCTCube.h"
#include "timer.h"
#include <gl\glu.h>

#define PI 3.14159f
#define DEG2RAD(x) (x*PI)/180.0f

class JCTGLControl : public JCTGLBase
{

   unsigned int m_textureObjectOne;
   unsigned int m_textureObjectTwo;

   static float m_angle;
   static float m_height;
   static float cameraX;
   static float cameraY;
   static float cameraZ;
   static float centerX;
   static float centerY;
   static float centerZ;

   static GLfloat xRot;
   static GLfloat yRot;
   bool exiting;
   const int TERRAIN_SIZE;


   #define MAX_LOADSTRING 100
   float fMovement;
   CHiResTimer *g_hiResTimer;

   static HDC hDC;
   static HGLRC hRC;
public:
#ifdef __JCTFBX__
   JCTFBXFile *pScene;
#endif
   static size_t  m_windowWidth;
   static size_t  m_windowHeight;
   long windowBits;
   bool fullscreen;
   Vect m_vRotate;
   float m_fZvalue;
   float m_fRotate;

   bool m_bRotate;
   JCTGLControl(void);
   ~JCTGLControl(void);
   bool IsActive();
   void SetActive(const bool &bActive);

   void DrawColorCube(float xPos, float yPos, float zPos, const JCTCube &pCub, bool bRotate = false);
   

   Vect& getCenter(){return Vect(JCTGLControl::centerX, JCTGLControl::centerY, JCTGLControl::centerZ);}
   void MoveCameraRight() { m_angle += 50.0f; }
   void MoveCameraLeft() { m_angle -= 50.0f; }
   void MoveCameraUp() { m_height += 50.0f;	}
   void MoveCameraDown() { m_height -= 50.0f;}
   virtual void Render();
   virtual void SetupProjection(const int &width, const int &height);
   virtual void SetupPixelFormat();
   virtual void LoadStartup();
   virtual void SetupCamera();
   void initTimer();
   void SetDrawingContext(const HDC &hDC);
   const HDC getDrawingContext();
   void DestryDrawingContext();
   void HandleKeys(const int &iKeys);
   
};





#include "JCTGLControl.h"

size_t JCTGLControl::m_windowWidth = 800;
size_t JCTGLControl::m_windowHeight = 600;
GLfloat JCTGLControl::xRot = 0.0f;
GLfloat JCTGLControl::yRot = 0.0f;
float JCTGLControl::m_angle = 0.0f;
float JCTGLControl::m_height = 10.0f;
float JCTGLControl::cameraX = 0.0f;
float JCTGLControl::cameraY = 0.0f;
float JCTGLControl::cameraZ = 0.0f;
float JCTGLControl::centerX = 0.0f;
float JCTGLControl::centerY = 0.0f;
float JCTGLControl::centerZ = 0.0f;
HDC   JCTGLControl::hDC  = 0;
HGLRC JCTGLControl::hRC = 0;
float fSize = 2.0f;




JCTGLControl::JCTGLControl(void):TERRAIN_SIZE(1),exiting(false)
{
   this->windowBits   = 32;
   this->fullscreen   = false;
   this->g_hiResTimer = NULL;
   this->g_hiResTimer = new CHiResTimer;
   this->m_fZvalue = 50.0;
   this->m_fRotate = .1f;
#ifdef __JCTFBX__
   pScene = new JCTFBXFile();
#endif
}

JCTGLControl::~JCTGLControl(void)
{
}

bool JCTGLControl::IsActive()
{
   return this->exiting;
};

void JCTGLControl::SetActive(const bool &bActive)
{
   this->exiting = bActive;
};

void JCTGLControl::Render()
{

   /*M3DVector3f vCorners[5] = { { 0.0f, .80f, 0.0f },    // Top         0
                       { -0.5f, 0.0f, -.50f },   // Back left    1
                       { 0.5f, 0.0f, -0.50f },   // Back right   2
                       { 0.5f, 0.0f, 0.5f },     // Front right   3
                       { -0.5f, 0.0f, 0.5f }};   // Front left   4

   M3DVector3f vBoxCorners[8] = { 
                       { -5.5f,  0.5f,  -0.5f },  //FF UL   0
                       { -5.5f, -0.5f,  -0.5f },  //FF LL   1
                       { -4.5f,  0.5f,  -0.5f },  //FF UR   2
                       { -4.5f, -0.5f,  -0.5f },  //FF LR   3 
                       { -4.5f,  0.5f,  -1.5f },  //BF UR   4
                       { -4.5f, -0.5f,  -1.5f },  //BF LR   5
                       { -5.5f,  0.5f,  -1.5f },  //BF UL   6
                       { -5.5f, -0.5f,  -1.5f }}; //BF LL}; 7 
                       
                       */

   // clear screen and depth buffer

	// load the identity matrix (clear to default position and orientation)

	// position and size the cube
	/*glTranslatef(0.4, 0.0, -1.5);
	glRotatef(15.0, 1.0, 0.0, 0.0);
	*/
	/*glScalef(0.75, 0.75, 0.75);*/
   //glRotatef(-15.0f, 0.0, 1.0, 0.0);

/*   JCTCube *pCube = new JCTCube(1.0f);

//   glLoadIdentity();
//   glPushMatrix();
   //glRotatef(45.0f, 0.0, 1.0, 0.0);

   //glRotatef(15.0f, 1.0, 0.0, 0.0);
   glRotatef(15.0f, 0.0, 1.0, 0.0);
	glTranslatef(0.4, 0.0, -1.5);
	DrawColorCube(-2.0f, -2.0f,-6.0f, pCube);//);centerX-1.0f, centerY, centerZ+1.0f, 1.0f);
*/
/*	DrawColorCube(-2.0f, -2.0f,-6.0f,2.0f);//);centerX-1.0f, centerY, centerZ+1.0f, 1.0f);
//   glPopMatrix();

   glLoadIdentity();
   glPushMatrix();
   glRotatef(15.0f, 0.0, 0.0, 1.0);
   DrawColorCube(centerX, centerY, centerZ-1.0f, pCube2);
   glPopMatrix();
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	DrawColorCube(0.0f,0.0f,-5.0f,10.0f);
   
#if __JCTFBX__

   // Clear the window with current clearing color
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// load the identity matrix (clear to default position and orientation)

	glLoadIdentity();//
	gluLookAt( 0.0, 175.0, 150.0, 0.0, 100.0, 0.0, 0.0, 1.0, 0.0);
	// bind the texture
	//glBindTexture(GL_TEXTURE_2D, m_textureObjectOne);

   // Save the matrix state and do the rotations
   glPushMatrix();
   // Move object back and do in place rotation
   glTranslatef(0.0f+centerX, -0.25f+centerY, -4.0f+centerZ);
   glRotatef(xRot, 1.0f, 0.0f, 0.0f);
   glRotatef(yRot, 0.0f, 1.0f, 0.0f);

   // Draw the Pyramid
   glColor3f(1.0f, 1.0f, 1.0f);
   
	glBindTexture(GL_TEXTURE_2D, m_textureObjectOne);

   for(size_t x=0; x<this->pScene->m_pFBXObjs.size(); x++)
   {
      switch(this->pScene->m_pFBXObjs[x]->getType())
      {
      case JCTFBX_MESH:
            this->pScene->m_pFBXObjs[x]->Render();
         break;
      case JCTFBX_MATERIAL:
         break;
      case JCTFBX_POLYGON:
         break;
      }; 
   }
   
   glPopMatrix();
#endif

   SwapBuffers(this->hDC);
};

void JCTGLControl::SetupProjection(const int &width, const int &height)
{

   glViewport(0, 0, width, height);      // reset the viewport to new dimensions
   glMatrixMode(GL_PROJECTION);         // set projection matrix current matrix
   glLoadIdentity();                  // reset projection matrix
/*
		pFieldOfViewY	40.000000000000000	double
		pAspect	1.3333333333333333	double
		pNearPlane	10.000000000000000	double
		pFarPlane	4000.0000000000000	double
-		
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();  
    gluPerspective(pFieldOfViewY, 
        pAspect, 
        pNearPlane, 
        pFarPlane);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(pEye[0], pEye[1], pEye[2],
        pCenter[0], pCenter[1], pCenter[2],
        pUp[0], pUp[1], pUp[2]);

   // calculate aspect ratio of window //
   gluPerspective(52.0f,(GLfloat)width/(GLfloat)height,1.0f,4000.0f);

//   gluPerspective(40.0f,1.3333,10.0f,4000.0f);

   glMatrixMode(GL_MODELVIEW);          // set modelview matrix
   glLoadIdentity();                  // reset modelview matrix

   m_windowWidth = width;
   m_windowHeight = height;
};

void JCTGLControl::SetupPixelFormat()
{
   int pixelFormat;

   PIXELFORMATDESCRIPTOR pfd =
   {   
      sizeof(PIXELFORMATDESCRIPTOR),  // size
         1,                    // version
         PFD_SUPPORT_OPENGL |      // OpenGL window
         PFD_DRAW_TO_WINDOW |      // render to window
         PFD_DOUBLEBUFFER,         // support double-buffering
         PFD_TYPE_RGBA,           // color type
         32,                   // prefered color depth
         0, 0, 0, 0, 0, 0,         // color bits (ignored)
         0,                    // no alpha buffer
         0,                    // alpha bits (ignored)
         0,                    // no accumulation buffer
         0, 0, 0, 0,             // accum bits (ignored)
         16,                   // depth buffer
         0,                    // no stencil buffer
         0,                    // no auxiliary buffers
         PFD_MAIN_PLANE,          // main layer
         0,                    // reserved
         0, 0, 0,               // no layer, visible, damage masks
   };

   pixelFormat = ChoosePixelFormat(this->hDC, &pfd);
   SetPixelFormat(this->hDC, pixelFormat, &pfd);
//SetupPalette();
   this->hRC = wglCreateContext(this->hDC);
   wglMakeCurrent(this->hDC, this->hRC);

};

void JCTGLControl::LoadStartup()
{
   GLint iWidth=0, iHeight=0, iComponents=0;
   centerX = centerY = centerZ = 0.0f;//cameraX = cameraY = cameraZ = 
   /*centerZ = -5.0f;
   centerY = -1.0f;
   fMovement = (float).2;
   m_angle = 0.0;
   m_height = 10.0;
   DWORD dwError = 0;

   // Light values and coordinates
   GLfloat  whiteLight[] = { 0.05f, 0.05f, 0.05f, 1.0f };
   GLfloat  sourceLight[] = { 0.25f, 0.25f, 0.25f, 1.0f };
   GLfloat	 lightPos[] = { -10.f, 5.0f, 5.0f, 1.0f };

   glEnable(GL_DEPTH_TEST);	// Hidden surface removal
   glFrontFace(GL_CCW);		// Counter clock-wise polygons face out
   glEnable(GL_CULL_FACE);		// Do not calculate inside of jet

   // Enable lighting
   glEnable(GL_LIGHTING);

   // Setup and enable light 0
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT,whiteLight);
   glLightfv(GL_LIGHT0,GL_AMBIENT,sourceLight);
   glLightfv(GL_LIGHT0,GL_DIFFUSE,sourceLight);
   glLightfv(GL_LIGHT0,GL_POSITION,lightPos);
   glEnable(GL_LIGHT0);

   glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

   //this->pScene->Load("humanoid.fbx", dwError);//Mixamo-Soldier_8k_poly.fbx", dwError);
   //this->pScene->LoadBones("humanoid.txt", dwError);//"Mixamo-Soldier_8k_poly.fbx"

//   this->pScene->LoadFBXTxt("humanoid_JCT.TXT", dwError);
   //this->pScene->LoadFBXTxt("warbearTriangulated.txt", dwError);
   // Enable color tracking
   glEnable(GL_COLOR_MATERIAL);

   // Set Material properties to follow glColor values
   glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
   #ifdef __JCTFBX__
   this->pScene->LoadFBXTxt("Mixamo-Soldier_8k_poly.txt", dwError);

   //this->pScene->LoadFBXTxt("GENERIC_RUN.txt", dwError);

   JCTTGAFile *pTga = new JCTTGAFile();
   STGA *sTGAFile = pTga->getTGAData();//new STGA;
   
   pTga->Load(this->pScene->m_cTGAFile, NULL, dwError);
//this->pScene->m_cTGAFile
	glClearColor(0.0, 0.0, 0.0, 0.0);

	// enable 2D texturing
	glEnable(GL_TEXTURE_2D);

	// retrieve "unused" texture object
	glGenTextures(1, &m_textureObjectOne);

	// bind the texture object
	glBindTexture(GL_TEXTURE_2D, (GLuint)m_textureObjectOne);

	// minimum required to set the min and mag texture filters

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
   glEnable(GL_TEXTURE_2D);

	// now that the texture object is bound, specify a texture for it
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_tgaUncompress->GetWidth(), m_tgaUncompress->GetHeight(),
//				 0, GL_RGB, GL_UNSIGNED_BYTE, m_tgaUncompress->GetImage());

   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, sTGAFile->width, sTGAFile->height,
     0, GL_RGB, GL_UNSIGNED_BYTE, sTGAFile->data);
#endif
}

void JCTGLControl::DrawColorCube(float xPos, float yPos, float zPos, const JCTCube &pCube, bool bRotate)
{


	// load the identity matrix (clear to default position and orientation)

	// bind the texture
	//glBindTexture(GL_TEXTURE_2D, m_textureObjectOne);

   // Save the matrix state and do the rotations
   //glPushMatrix();
   // Move object back and do in place rotation
   // Draw the Pyramid
//	glPushMatrix();

   glPushMatrix();
  	glLoadIdentity();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   
   if(bRotate && m_bRotate)
   {
      if(m_fRotate <= 360.0f)
      {
         m_fRotate += .1f;
      }
      else
      {
         m_fRotate = .1f;
      }

      //glRotatef(this->m_vRotate.getElement(0), 1.0f, 0.0f, 0.0f);
      
	   glRotatef(m_fRotate, 0.0f, 0.0f, 1.0f);
	   //glRotatef(this->m_vRotate.getElement(2), 0.0f, 0.0f, 1.0f);
   }
   else
   {
      //m_fRotate = 8.0f;
   }
   glTranslatef(xPos, yPos, zPos);

//   glRotatef(35.0f, 0.0, 0.0, 1.0);
//   glRotatef(15.0f, 1.0, 0.0, 1.0);

	glBegin(GL_QUADS);
   
   for(int x=0; x<JCTCUBE_SIDECOUNT; x++)
   {

		glColor3fv((GLfloat*)&pCube.m_vColor[0]);
      for(int y=0; y<JCTCUBE_POINTCOUNT; y++)
      {
         glVertex3fv((GLfloat*)&pCube.m_vCube[x][y]);
      }
   }
	glEnd();
   glPopMatrix();
}


		

void JCTGLControl::SetupCamera()
{
#ifdef __JCTFBX__
	cameraX = sin(DEG2RAD(m_angle))*TERRAIN_SIZE*(float).2;
	cameraY = m_height;
	cameraZ = cos(DEG2RAD(m_angle))*TERRAIN_SIZE*(float).2;
#endif
   	//glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


};

void JCTGLControl::SetDrawingContext(const HDC &hDC)
{
   this->hDC = hDC;
};

const HDC JCTGLControl::getDrawingContext()
{
   return this->hDC;
};

void JCTGLControl::DestryDrawingContext()
{
      // deselect rendering context and delete it
      wglMakeCurrent(hDC, NULL);
      wglDeleteContext(hRC);

      // send WM_QUIT to message queue
}

void JCTGLControl::HandleKeys(const int &iKeys)
{
   switch(iKeys)
      {
      case VK_LEFT :
         centerX -= fMovement;
         break;

      case 'A'   :
         centerZ -= fMovement;
         break;

      case 'S'   :
         centerZ += fMovement;
         break;

      case VK_UP   :
         centerY += fMovement;
         break;

      case VK_RIGHT:
         centerX += fMovement;
         break;
      
      case VK_DOWN :
         centerY -= fMovement;
         break;

      case VK_ESCAPE:
         PostQuitMessage(0);
         break;
      case 'R':
         if(this->m_bRotate)
         {
            this->m_bRotate = false;
         }
         else
         {
            this->m_bRotate = true;
         }
         break;

      default:
         break;
      }
};

void JCTGLControl::initTimer()
{
   this->g_hiResTimer->Init();
   this->SetActive(true);
}

*/