#pragma once
#include "JCTGLBase.h"

#if __JCTFBX__
#include "JCTFBXFile.h"
#endif
#include "JCTCube.h"
#include "timer.h"
#include <gl\glu.h>

#define PI 3.14159f
#define DEG2RAD(x) (x*PI)/180.0f

class JCTGLControl
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

   static size_t  m_windowWidth;
   static size_t  m_windowHeight;
   long windowBits;
   bool fullscreen;
   float m_fZvalue;
   float m_fRotate;
   Vect m_vRotate;

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
   void Render();
   void SetupProjection(const int &width, const int &height);
   void DrawHUD();
   void SetupPixelFormat();
   void LoadStartup();
   void SetupCamera();
   void initTimer();
   void SetDrawingContext(const HDC &hDC);
   const HDC getDrawingContext();
   void DestryDrawingContext();
   void HandleKeys(const int &iKeys);
   
};

