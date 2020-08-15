#include "JCTShader.h"

#include <iostream>
using namespace std;

//#include "mesh.h"
//#include "scene.h"


JCTShader::JCTShader()
{
	glProgramObj = 0;
	glVertShader = 0;
	glFragShader = 0;
	vertexShaderName[0] = '\0';
	fragmentShaderName[0] = '\0';
	nUniforms = 0;
	time = 0;
	LoadGlobalGLSLFunctions();
	lightingGLSLVertFunctions = NULL;
	lightingGLSLFragFunctions = NULL;

}

JCTShader::~JCTShader()
{
	// To Do
	//
	// clean up by detaching and deleting the shaders and the program object it is attached to.
   glDetachShader(glProgramObj, glVertShader);
   glDetachShader(glProgramObj, glFragShader);
   glDeleteShader(glVertShader);
   glDeleteShader(glFragShader);
   glDeleteProgram(glProgramObj);

}


void JCTShader::BeginShading(void)
{
	LoadShaders();

	for (int j=0; j < nTextures; j++)
   {
//		textures[j]->BeginShading();
   }
}
/*
void JCTShader::DrawPolygon(int n, Vect p[], Vect vn[], Vect pn[], Vect uv[])
{
	// To Do
	// 
	// Same as for the multitexture shader
}

void JCTShader::DrawTriangles(int nVerts, int nPolys, Vect vertexData[], int vertexBuffer, Vect faceData[], int faceIndexBuffer, Vect triangleNormals[])
{
	float *texCoords = NULL;
	int paramLoc;

	InitializeProgramConstants();

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	// To Do
	//
	// Enable the client's active texture, and enable the client state for a texture coord array.
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
   glClientActiveTexture(GL_TEXTURE0);

//	glVertexPointer(3, GL_FLOAT, sizeof(vert), &(vertexData[0].position));
//	glNormalPointer(GL_FLOAT, sizeof(vert), &(vertexData[0].normal));

	// To Do
	//
	// If the entity in the "tEntity" member is equal to UV, then set the glTexCoord pointer.
	// Note though that if there is a vertex buffer you should use the buffer offset instead of 
	// the address of the uv memeber of vert.
	//
	// If the entity is not UV, then create an array of floats in the "texCoords" local variable
	// defined above and fill it with the values returned from the "CalculateTexCoords" method.
	// Then unbind the array buffer, send the tex coord pointer, and then rebind the array buffer.

   if(vertexBuffer != 0 && faceIndexBuffer != 0)
   {
      glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, faceIndexBuffer);

      glVertexPointer(3, GL_FLOAT, sizeof(Vect),BUFFER_OFFSET(vertexData[0].p);
      glNormalPointer(GL_FLOAT, sizeof(Vect),BUFFER_OFFSET(vertexData[0].normal));
	   //glDrawElements(GL_TRIANGLES, 3*nPolys, GL_UNSIGNED_INT, 0);
      
//         glBindBuffer(GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING, textureBuffer);
         glTexCoordPointer(3, GL_FLOAT, sizeof(Vect),BUFFER_OFFSET(vertexData[0].uv));
   	   glDrawElements(GL_TRIANGLES, 3*nPolys, GL_UNSIGNED_INT, 0);
         glBindBuffer(GL_ARRAY_BUFFER, 0);
         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//         glBindBuffer(GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING, 0);
      
   }
   else
   {
	   glVertexPointer(3, GL_FLOAT, sizeof(vert), &(vertexData[0].position));
	   glNormalPointer(GL_FLOAT, sizeof(vert), &(vertexData[0].normal));
      glDrawElements(GL_TRIANGLES, 3 * nPolys, GL_UNSIGNED_INT, faceData);
   }


	// To Do
	// 
	// Disable the texture coordinate array in the client state and the
	// vertex and Vect index buffers

   glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	// To Do
	// 
	// Same as for the multitexture shader, except that you should also
	// send a uniform variable "time" with the current value of the "time"
	// member of the shader base class. 
}
*/
char* JCTShader::LoadShader(const char *fileName)
{
	int size;
	char *buffer;
	FILE *shaderFile = fopen(fileName, "rb");
	if (shaderFile == NULL)
	{
		cout << "Unable to open shader file " << fileName << endl;
		return NULL;
	}

	fseek(shaderFile, 0, SEEK_END);
	size = ftell(shaderFile);
	rewind(shaderFile);

	buffer = new char[size + 1];
	int num = fread(buffer, 1, size, shaderFile);
	buffer[num] = '\0';

	fclose(shaderFile);
	return buffer;
}

void JCTShader::printShaderInfoLog(GLuint obj)
{
	int infologLength = 0;
	int charsWritten = 0;
	GLchar *infoLog;
	glGetObjectParameterivARB(obj, GL_OBJECT_INFO_LOG_LENGTH_ARB, &infologLength);

	if (infologLength > 0)
	{
		infoLog = new GLchar[infologLength];
		if (infoLog == NULL)
		{
			cout << "Error: Could not allocate buffer for error log in JCTShader\n";
			return;
		}
		glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
		cout << "-------------------------------------------------------------------\n";
		cout << infoLog << endl;
		cout << "-------------------------------------------------------------------\n\n";
		delete [] infoLog;
	}
}

void JCTShader::printProgramInfoLog(GLuint obj)
{
	int infologLength = 0;
	int charsWritten = 0;
	GLchar *infoLog;
	glGetObjectParameterivARB(obj, GL_OBJECT_INFO_LOG_LENGTH_ARB, &infologLength);

	if (infologLength > 0)
	{
		infoLog = new GLchar[infologLength];
		if (infoLog == NULL)
		{
			cout << "Error: Could not allocate buffer for error log in JCTShader\n";
			return;
		}
		glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
		cout << "-------------------------------------------------------------------\n";
		cout << infoLog << endl;
		cout << "-------------------------------------------------------------------\n\n";
		delete [] infoLog;
	}
}

void JCTShader::LoadShaders(void)
{
	GLint good;

	if (!glProgramObj)
	{
		char *vertCode[3];
		char *fragCode[3];

		vertCode[0] = LoadShader(vertexShaderName);
		fragCode[0] = LoadShader(fragmentShaderName);
		vertCode[1] = GlobalVertFunctions();
		fragCode[1] = GlobalFragFunctions();
		vertCode[2] = LightingVertFunctions();
		fragCode[2] = LightingFragFunctions();

		if (vertCode[0])
		{
			// To Do
			// 
			// Create a vertex shader, send the source code and compile it.  Make sure that
			// it compiled properly and if not, print the shader log
         glVertShader = glCreateShader(GL_VERTEX_SHADER);
         glShaderSource(glVertShader,2, (const GLchar **)&vertCode[0], NULL);
         glCompileShader(glVertShader);
         glGetShaderiv(glVertShader, GL_COMPILE_STATUS, &good);
         if(!good)
         {
            printShaderInfoLog(glVertShader);
            return;
         }
                   
		}

		if (fragCode[0])
		{
			// To Do
			// 
			// Create a fragment shader, send the source code and compile it.  Make sure that
			// it compiled properly and if not, print the shader log
         glFragShader = glCreateShader(GL_FRAGMENT_SHADER);
         glShaderSource(glFragShader,2, (const GLchar **)&fragCode[0], NULL);
         glCompileShader(glFragShader);
         glGetShaderiv(glFragShader, GL_COMPILE_STATUS, &good);
         if(!good)
         {
            printShaderInfoLog(glFragShader);
            return;
         }
          
		}

		// To Do
		//
		// Create the glsl program.  Attach the two shaders and initialize the vertex attributes.  
		// Then link the program and if there was an error, print the program log
		
         glProgramObj = glCreateProgram();
         glAttachShader(glProgramObj, glVertShader);
         glAttachShader(glProgramObj, glFragShader);
         InitializeVertexAttributes();
         glLinkProgram(glProgramObj);
         glGetProgramiv(glProgramObj, GL_LINK_STATUS, &good);
         if(!good)
         {
            printProgramInfoLog(glProgramObj);
            return;
         }

		if (vertCode[0])
			delete [] vertCode[0];
		if (fragCode[0])
			delete [] fragCode[0];
	}
	// To Do
	// 
	// Tell OpenGL to use the program, and initialize the program constants
   glUseProgram(glProgramObj);
   InitializeProgramConstants();
}

void JCTShader::InitializeVertexAttributes(void)
{
	// To Do
	//
	// Bind attribute locations for the "uv", "dPdu" and "dPdv" vertex attributes
}

void JCTShader::InitializeProgramConstants(void)
{
	// To Do
	// 
	// For each of "texture0", "texture1", etc.  Find the location of the uniform in GLSL
	// and set the value of that uniform to the appropriate texture unit.  Then set the 
	// time uniform as well. 
	//
	// Then go through the stored uniform values in this class and set them as well.
	// Use the nUniformComponents member, to determine which function you should use
	// to set these in OpenGL
   GLuint iLocation;

   for(int x=0; x<8; x++)
   {
      glUniform1i(glGetUniformLocation(glProgramObj, "texture"+x), x);
      
   }
   glUniform1i(glGetUniformLocation(glProgramObj, "time"), time);
   for(int x=0; x<nUniforms; x++)
   {
         cout << "nUniformComponents[x]==" << nUniformComponents[x] << endl;
         //   glUniform1i(uniformParamNames[x][(x+50)], uniformParamValues[x]);
   }
}

void JCTShader::EndShading(void)
{
/*	for (int i = 0; i < nTextures; i++)
		textures[i]->EndShading();
*/	
	// To Do
	// 
	// Stop using a program by telling OpenGL to use program "0"
   glUseProgram(0);
}


void JCTShader::LoadGlobalGLSLFunctions(void)
{
	int size;
	char *buffer;
	FILE *shaderFile = fopen("ShaderFunctions.vert", "rb");
	if (shaderFile == NULL)
	{
		cout << "Unable to open file with global vertex shader functions: ShaderFunctions.vert" << endl;
		buffer = NULL;
	}
	else
	{
		fseek(shaderFile, 0, SEEK_END);
		size = ftell(shaderFile);
		rewind(shaderFile);

		buffer = new char[size + 1];
		int num = fread(buffer, 1, size, shaderFile);
		buffer[num] = '\0';

		fclose(shaderFile);
		globalGLSLVertFunctions = buffer;
	}

	shaderFile = fopen("ShaderFunctions.frag", "rb");
	if (shaderFile == NULL)
	{
		cout << "Unable to open file with global fragment shader functions: ShaderFunctions.frag" << endl;
		buffer = NULL;
	}
	else
	{
		fseek(shaderFile, 0, SEEK_END);
		size = ftell(shaderFile);
		rewind(shaderFile);

		buffer = new char[size + 1];
		int num = fread(buffer, 1, size, shaderFile);
		buffer[num] = '\0';

		fclose(shaderFile);
		globalGLSLFragFunctions = buffer;
	}
}

/*
#include "miscIO.h"

void JCTShader::Load(Loader &input)
{
	char token[MAX_INPUT_LENGTH];

	if (!input.ReadInt(nTextures))
		input.Error("Missing texture count after JCTShader command");

	for (int i = 0; i < nTextures; i++)
	{
		if (i < maxTextures)
		{
			shader *tmpShader = shader::LoadShader(input);

			if (tmpShader == NULL)
				input.Error("Expected a texture shader in multitexture.");

			// Warning, this will cause an error if the shader loaded is not 
			// a derived class of textureShader.  Need to use RTTI here.
			textures[i] = (textureShader *)tmpShader;
			textures[i]->SetTextureUnit(i);
			textures[i]->SetUsedByProgrammable(true);
		}
		else
		{
			input.Warning("Graphics card supports %d textures.  Ignoring texture %d", maxTextures, i);
			textureShader *tex = new textureShader;
			tex->Load(input);
			delete tex; // Delete it because we can't use it
		}
	}

	do
	{
		input.ReadToken(token);
		if (strncmp(token, "vertexshader", 12) == 0)
			input.ReadToken(vertexShaderName);
		else if (strncmp(token, "fragmentshader", 13) == 0)
			input.ReadToken(fragmentShaderName);
		else if (strcmp(token, "uniform") == 0)
		{
			input.ReadToken(uniformParamNames[nUniforms]);
			nUniformComponents[nUniforms] = 0;
			for (int i = 0; i < 4; i++)
			{
				if (!input.ReadFloat(uniformParamValues[nUniforms][i]))
				{
					if (i == 0)	
						input.Error("Incomplete uniform parameter %s\n", uniformParamNames[nUniforms]);
					break;
				}
				else
					nUniformComponents[nUniforms]++;
			}
			nUniforms++;
		}
		else if (strncmp(token, "end", 3) != 0)
		{
			// Load a uniform constant
			input.Error(token, "Unrecognized multitexture command: %s", token);
		}
	} while (strncmp(token, "end", 3) != 0);
}


char* JCTShader::LoadShader(const char *fileName)
{
	int fsize;
	char *buffer;
	FILE *shaderFile = fopen(fileName, "rb");
	if (shaderFile == NULL)
	{
		cout << "Unable to open shader file " << fileName << endl;
		return NULL;
	}

	fseek(shaderFile, 0, SEEK_END);
	fsize = ftell(shaderFile);
	rewind(shaderFile);

	buffer = new char[fsize + 1];
	int num = fread(buffer, 1, fsize, shaderFile);
	buffer[num] = '\0';

	fclose(shaderFile);
	return buffer;
}

void JCTShader::printShaderInfoLog(GLuint obj)
{
	int infologLength = 0;
	int charsWritten = 0;
	GLchar *infoLog;
	glGetObjectParameterivARB(obj, GL_OBJECT_INFO_LOG_LENGTH_ARB, &infologLength);

	if (infologLength > 0)
	{
		infoLog = new GLchar[infologLength];
		if (infoLog == NULL)
		{
			cout << "Error: Could not allocate buffer for error log in JCTShader\n";
			return;
		}
		glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
		cout << "-------------------------------------------------------------------\n";
		cout << infoLog << endl;
		cout << "-------------------------------------------------------------------\n\n";
		delete [] infoLog;
	}
}

void JCTShader::printProgramInfoLog(GLuint obj)
{
	int infologLength = 0;
	int charsWritten = 0;
	GLchar *infoLog;
	glGetObjectParameterivARB(obj, GL_OBJECT_INFO_LOG_LENGTH_ARB, &infologLength);

	if (infologLength > 0)
	{
		infoLog = new GLchar[infologLength];
		if (infoLog == NULL)
		{
			cout << "Error: Could not allocate buffer for error log in JCTShader\n";
			return;
		}
		glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
		cout << "-------------------------------------------------------------------\n";
		cout << infoLog << endl;
		cout << "-------------------------------------------------------------------\n\n";
		delete [] infoLog;
	}
}

void JCTShader::LoadShaders(void)
{
	GLint good;

	if (!glProgramObj)
	{
		char *vertCode;
		char *fragCode;

		int index = 0;

		vertCode = LoadShader("TestShader2.vert");
		fragCode = LoadShader("TestShader2.frag");

		if (vertCode)
		{
			glVertShader = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(glVertShader, 1, (const char **)(&vertCode), NULL);
			glCompileShader(glVertShader);

			glGetObjectParameterivARB(glVertShader, GL_OBJECT_COMPILE_STATUS_ARB, &good);
			if (good == false)
			{
				cout << "Vertex Shader 'TestShader.vert' failed to compile" << endl;
				printShaderInfoLog(glVertShader);
			}
		}

		if (fragCode)
		{
			glFragShader = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(glFragShader, 1, (const char **)&fragCode, NULL);
			glCompileShader(glFragShader);

			glGetObjectParameterivARB(glFragShader, GL_OBJECT_COMPILE_STATUS_ARB, &good);
			if (good == false)
			{
				cout << "Fragment Shader 'TestShader.frag' failed to compile" << endl;
				printShaderInfoLog(glFragShader);
			}
		}

		glProgramObj = glCreateProgram();
		glAttachShader(glProgramObj, glVertShader);
		glAttachShader(glProgramObj, glFragShader);

		glLinkProgram(glProgramObj);
		glGetObjectParameterivARB(glProgramObj, GL_OBJECT_LINK_STATUS_ARB, &good);
		if (good == false)
		{
			cout << "Program and Shaders objects failed to link." << endl;
			printProgramInfoLog(glProgramObj);
		}
		
		delete [] vertCode;
		delete [] fragCode;
	}
	glUseProgram(glProgramObj);
}
*/