#pragma once

#ifndef __GLSLSHADER_H__
#define __GLSLSHADER_H__

//#include "shader.h"
//#include "mesh.h"
#include "glew.h"
#include "wglew.h"
#include "Math3D.h"
#include "MathEngine.h"

//#include <glu.h>
//#include "string.h"

//#include "OpenGLWin.h"

class JCTShader
{
public:
   JCTShader(void);
   ~JCTShader(void);
	virtual void BeginShading(void);
	/*virtual void DrawPolygon(int n, Vect p[], Vect vn[], Vect pn[], Vect uv[]);
	virtual void DrawTriangles(int nVerts, int nPolys, Vect vertexData[], int vertexBuffer, Vect faceData[], int faceIndexBuffer, Vect triangleNormals[]);
	*/virtual void EndShading(void);
	virtual char* LoadShader(const char* filename);
	virtual void LoadShaders(void);
//	virtual void Load(Loader &input); 
	virtual void UpdateState(void) { }

	virtual void SetTime(float newTime) { time = newTime; }
	char *GlobalVertFunctions(void) { return globalGLSLVertFunctions; }
	char *GlobalFragFunctions(void) { return globalGLSLFragFunctions; }
	char *LightingVertFunctions(void) { return lightingGLSLVertFunctions; }
	char *LightingFragFunctions(void) { return lightingGLSLFragFunctions; }
   void LoadGlobalGLSLFunctions(void);

protected:

	//textureShader **textures;  // An array of pointers to textures
	int nTextures;
	int maxTextures;
	bool disableLight;
	bool disableDiffuse;
	bool disableAmbient;
	bool disableSpecular;

	void InitializeGLSL(void);
	void InitializeProgramConstants(void);
	void InitializeVertexAttributes(void);
	void printShaderInfoLog(GLuint obj);
	void printProgramInfoLog(GLuint obj);

	char *lightingGLSLVertFunctions;
	char *lightingGLSLFragFunctions;
	char *globalGLSLVertFunctions;
	char *globalGLSLFragFunctions;



	GLuint glProgramObj;
	GLuint glVertShader;
	GLuint glFragShader;
	float time;				// For animated procedural shaders

	char uniformParamNames[50][50]; // Fifty uniform parameters, at 50 characters per name
   M3DVector3d uniformParamValues[50];
	int nUniformComponents[50];
	int nUniforms;

	char vertexShaderName[MAX_PATH], fragmentShaderName[MAX_PATH];

	Vect v_ViewVec;
};

/*
class glslShader : public multiTexture
{
public:

	glslShader();
	~glslShader();

	virtual void BeginShading(void);
	virtual void DrawPolygon(int n, point p[], vector vn[], vector pn[], vector uv[]);
	virtual void DrawTriangles(int nVerts, int nPolys, vert vertexData[], int vertexBuffer, face faceData[], int faceIndexBuffer, vector triangleNormals[]);
	virtual void EndShading(void);
	virtual char* LoadShader(const char* filename);
	virtual void LoadShaders(void);
	virtual void Load(Loader &input); 
	virtual void UpdateState(void) { }

	virtual void SetTime(float newTime) { time = newTime; }

protected:

	void InitializeGLSL(void);
	void InitializeProgramConstants(void);
	void InitializeVertexAttributes(void);
	void printShaderInfoLog(GLuint obj);
	void printProgramInfoLog(GLuint obj);

	GLuint glProgramObj;
	GLuint glVertShader;
	GLuint glFragShader;
	float time;				// For animated procedural shaders

	char uniformParamNames[50][50]; // Fifty uniform parameters, at 50 characters per name
	point uniformParamValues[50];
	int nUniformComponents[50];
	int nUniforms;

	char vertexShaderName[MAX_PATH], fragmentShaderName[MAX_PATH];

	vector v_ViewVec;
};
*/
#endif