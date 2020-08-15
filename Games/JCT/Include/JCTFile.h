#pragma once
#include <windows.h>

//BMP, DDS, DXT1a, DXT1c, DXT3, DXT5, EXR, GIF, HRD, JP2, JPG, MTD, NRRD, PNG, PNM, PSD, SGI, TGA, TIF, 

enum{
   JCTFILE_SUCCESS=0,
   JCTFILE_ERROR_SEEKFAIL,
   JCTFILE_ERROR_INVALIDFILENAME,
   JCTFILE_ERROR_WRITEFAIL,
   JCTFILE_ERROR_READFAIL,
   JCTFILE_ERROR_INVALIDFILESIZE,
   JCTFILE_ERROR_CLOSEFAIL,
   JCTFILE_ERROR_COUNT
};
enum JCTFILE_CREATETYPE
{
   JCTFILE_READ=0,
   JCTFILE_WRITE
};

class JCTFile
{
public:
   JCTFile();
   ~JCTFile(void);
   
   const HANDLE Create(char* pFileName, DWORD &dwError, const DWORD &dwCreationDisposition, enum JCTFILE_CREATETYPE eType);
   HFILE Open(char* pFileName, DWORD &dwError);
   void Close(DWORD &dwError);
   void Read(unsigned char* outBuffer, const unsigned long &uiBytes, DWORD &dwError);
   void Write(char* inBuffer, const wint_t &uiBytes, DWORD &dwError);
   void SetFileName(char* pFileName, DWORD &dwError);
   void Seek(const long &lForward, DWORD &dwError);
   void Delete(const char *pFileName, DWORD &dwError);
   size_t GetSize(HANDLE hFile, DWORD &dwError);
   const HFILE getFileHandle();
   const HANDLE getHandle();
private:
   char* m_pFileName;
   HANDLE m_hFile;
   HFILE m_fhFile;
};
