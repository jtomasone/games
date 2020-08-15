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
   this->m_bRotate = false;
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
   this->hRC = wglCreateContext(this->hDC);
   wglMakeCurrent(this->hDC, this->hRC);

};

void JCTGLControl::LoadStartup()
{
   GLint iWidth=0, iHeight=0, iComponents=0;
   centerX = centerY = centerZ = 0.0f;//cameraX = cameraY = cameraZ = 
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
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

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

   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, sTGAFile->width, sTGAFile->height,
     0, GL_RGB, GL_UNSIGNED_BYTE, sTGAFile->data);
#endif
}

void JCTGLControl::DrawColorCube(float xPos, float yPos, float zPos, const JCTCube &pCube, bool bRotate)
{


	// load the identity matrix (clear to default position and orientation)
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
      
	   glRotatef(m_fRotate, 0.0f, 0.0f, 1.0f);
   }
   glTranslatef(xPos, yPos, zPos);

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

void renderSphere(Vect vPosition, float radius, int subdivisions, GLUquadricObj *quadric)
{
   glPushMatrix();
   glTranslatef(vPosition.getElement(x), vPosition.getElement(y), vPosition.getElement(z));
   gluSphere(quadric, radius, subdivisions,subdivisions);
   glPopMatrix();
}

		

void JCTGLControl::SetupCamera()
{
#ifdef __JCTFBX__
	cameraX = sin(DEG2RAD(m_angle))*TERRAIN_SIZE*(float).2;
	cameraY = m_height;
	cameraZ = cos(DEG2RAD(m_angle))*TERRAIN_SIZE*(float).2;
#endif
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
