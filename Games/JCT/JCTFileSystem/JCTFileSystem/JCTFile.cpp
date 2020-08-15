
#include "JCTFile.h"

JCTFile::JCTFile()
{
   this->m_pFileName = "";
   this->m_fhFile = 0;
   this->m_hFile = 0;

   //this->Open(pFileName);
};

JCTFile::~JCTFile(void)
{
};

/*
CreateFile
DeleteFile
CloseHandle
ReadFile
WriteFile
File Information
*/

const HFILE JCTFile::getFileHandle()
{
   return this->m_fhFile;
};

const HANDLE JCTFile::getHandle()
{
   return this->m_hFile;
};

const HANDLE JCTFile::Create(char* pFileName, DWORD &dwError, const DWORD &dwCreationDisposition, enum JCTFILE_CREATETYPE eType)
{
   if(pFileName)
   {
      HANDLE hTemp=0;
      this->SetFileName(pFileName, dwError);
      //strcpy_s(this->m_pFileName, 255, pFileName);
      //this->m_hFile = CreateFile(pFileName,GENERIC_READ|GENERIC_WRITE,1, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
      //hTemp = CreateFile(pFileName,GENERIC_READ, FILE_ATTRIBUTE_READONLY, NULL, dwCreationDisposition, FILE_ATTRIBUTE_NORMAL, NULL);
      //this->m_hFile = CreateFile(pFileName,GENERIC_READ|GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
//      this->m_hFile = CreateFile(pFileName,GENERIC_READ, FILE_SHARE_READ, NULL, dwCreationDisposition, FILE_ATTRIBUTE_NORMAL, NULL);


      /*
      hFile = CreateFile( TEXT("testfile"),
                        GENERIC_WRITE,
                        FILE_SHARE_WRITE,
                        NULL,
                        OPEN_ALWAYS,
                        0,
                        NULL );
    if( hFile == INVALID_HANDLE_VALUE )
    {
       printf( "Cannot open testfile\n" );
       return;
    }
    else
       WriteFile( hFile, "This is testfile", 16, &dwRet, NULL );

    hStream = CreateFile( TEXT("testfile:stream"),
                          GENERIC_WRITE,
                          FILE_SHARE_WRITE,
                          NULL,
                          OPEN_ALWAYS,
                          0,
                          NULL );
    if( hStream == INVALID_HANDLE_VALUE )
        printf( "Cannot open testfile:stream\n" );
    else
        WriteFile(hStream, 
                  "This is testfile:stream", 23, &dwRet, NULL);

                  */
      if(eType == JCTFILE_READ)
      {
         this->m_hFile = CreateFile(pFileName,GENERIC_READ, FILE_ATTRIBUTE_READONLY, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
      }
      else
      {
         this->m_hFile = CreateFile(pFileName,GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
      }



      if (this->m_hFile == (HANDLE)0xFFFFFFFF)
      {
         dwError = JCTFILE_ERROR_INVALIDFILESIZE;
         //printf("GetLastError() = %d", GetLastError());
      }
   }
   else
   {
      dwError = JCTFILE_ERROR_INVALIDFILENAME;
   }
   /*LPCTSTR lpFileName,   // pointer to name of the file 
       DWORD dwDesiredAccess,   // access (read-write) mode 
       DWORD dwShareMode,   // share mode 
       LPSECURITY_ATTRIBUTES lpSecurityAttributes,   // pointer to security descriptor 
       DWORD dwCreationDistribution,   // how to create 
       DWORD dwFlagsAndAttributes,   // file attributes 
       HANDLE hTemplateFile    // handle to file with attributes to copy  
   );   
FILE_ATTRIBUTE_ARCHIVE
FILE_ATTRIBUTE_COMPRESSED
FILE_ATTRIBUTE_HIDDEN
FILE_ATTRIBUTE_NORMAL
FILE_ATTRIBUTE_OFFLINE
FILE_ATTRIBUTE_READONLY
FILE_ATTRIBUTE_SYSTEM
FILE_ATTRIBUTE_TEMPORARY
FILE_FLAG_WRITE_THROUGH   
FILE_FLAG_OVERLAPPED
FILE_FLAG_NO_BUFFERING
FILE_FLAG_RANDOM_ACCESS
FILE_FLAG_SEQUENTIAL_SCA
FILE_FLAG_DELETE_ON_CLOSE
FILE_FLAG_BACKUP_SEMANTICS
FILE_FLAG_POSIX_SEMANTICS
   
   */
   return this->m_hFile;
};


void JCTFile::SetFileName(char* pFileName, DWORD &dwError)
{
   dwError = JCTFILE_SUCCESS;
   if(pFileName)
   {
      this->m_pFileName = pFileName;//new wchar_t[100000];
   }
   else
   {
      dwError = JCTFILE_ERROR_INVALIDFILENAME;
   }
   //errno_t ctmp = wcscpy_s(m_pFileName2, sizeof(&pFileName), pFileName);
};

HFILE JCTFile::Open(char* pFileName, DWORD &dwError)
{
   dwError = JCTFILE_SUCCESS;
   if(pFileName)
   {
      this->SetFileName(pFileName, dwError);
      OFSTRUCT ofInfo;
      //strcpy_s(m_pFileName, sizeof(&pFileName), pFileName);
      this->m_fhFile = OpenFile((LPCSTR)this->m_pFileName, &ofInfo, NULL);
   }
   else
   {
      dwError = JCTFILE_ERROR_INVALIDFILENAME;
   }
   return this->m_fhFile;
   
};

void JCTFile::Close(DWORD &dwError)
{
   dwError = JCTFILE_SUCCESS;
   if(!CloseHandle(this->m_hFile))
   {
      dwError = JCTFILE_ERROR_CLOSEFAIL;
   }
};

void JCTFile::Read(unsigned char* outBuffer, const unsigned long &uiBytes, DWORD &dwError)
{
   dwError = JCTFILE_SUCCESS;
   DWORD iBytesRead = 0;
   BOOL bReturn;
   OVERLAPPED ovr;
   memset(&ovr,0,sizeof(ovr));
   ovr.Offset=0;
   /*if(outBuffer && uiBytes > 0)
   {*/
    bReturn = ReadFile(this->m_hFile, outBuffer, uiBytes, &iBytesRead, NULL);//, &ovr);
/*
    if( FALSE == ReadFile(hFile, ReadBuffer, BUFFERSIZE-1, &dwBytesRead, NULL) )
    {
        DisplayError(TEXT("ReadFile"));
        printf("Terminal failure: Unable to read from file.\n");
        CloseHandle(hFile);
        return;
    }

    // This is the section of code that assumes the file is ANSI text. 
    // Modify this block for other data types if needed.

    if (dwBytesRead > 0 || dwBytesRead <= BUFFERSIZE)
    {
        ReadBuffer[dwBytesRead]='\0'; // NULL character

        _tprintf(TEXT("Data read from %s (%d bytes): \n"), argv[1], dwBytesRead);
        printf("%s\n", ReadBuffer);
    }
    else if (dwBytesRead == 0)
    {
        _tprintf(TEXT("No data read from file %s\n"), argv[1]);
    }
    else
    {
        printf("\n ** Unexpected value for dwBytesRead ** \n");
    }

    // It is always good practice to close the open file handles even though
    // the app will exit here and clean up open handles anyway.
    
   /* do

    {
          bReturn = ReadFile(this->m_hFile, (LPVOID)&outBuffer, 43, &iBytesRead, NULL);
        //ReadFile(hSrc, pBuffer, sizeof(pBuffer), &dwRead, NULL);

    } while (iBytesRead != 0);
*/
    if(!bReturn || iBytesRead <= 0)
      {
         DWORD dwTemp = GetLastError();
         dwError = JCTFILE_ERROR_READFAIL;
         //printf("Read Failed with error %d\n", GetLastError());
      }
   //}
   /*else
   {
      return false;
   }*/
   /*
   BOOL WINAPI ReadFile(
  __in         HANDLE hFile,
  __out        LPVOID lpBuffer,
  __in         DWORD nNumberOfBytesToRead,
  __out_opt    LPDWORD lpNumberOfBytesRead,
  __inout_opt  LPOVERLAPPED lpOverlapped
);
*/

    //CloseHandle(this->m_hFile);

}
#include <algorithm> //required for std::swap


#define ByteSwap5(x) ByteSwap((unsigned char *) &x,sizeof(x))

void ByteSwap(unsigned char * b, int n)
{
   register int i = 0;
   register int j = n-1;
   while (i<j)
   {
      std::swap(b[i], b[j]);
      i++, j--;
   }
}

void JCTFile::Write(char* inBuffer, const wint_t &uiBytes, DWORD &dwError)
{
   BOOL bResult;
   DWORD dwBytesWritten = 0;

   if(strcmp(inBuffer, ""))
   {
   
      bResult = WriteFile(this->m_hFile,inBuffer,uiBytes, &dwBytesWritten,NULL);

      if(bResult && dwBytesWritten > 0)
      {
         dwError = 0;
      }
      else
      {
         dwError = JCTFILE_ERROR_WRITEFAIL;
         printf("Write Failed with error %d", GetLastError());
         int iError = GetLastError();
         bool bTemp = 0;
      }
   }
   
};

void JCTFile::Seek(const long &lForward, DWORD &dwError)
{
   long dwBytesDistance = 0;
   dwError = SetFilePointer(this->getHandle(), lForward, &dwBytesDistance, FILE_CURRENT);

   if((!dwError && !dwBytesDistance) || (dwError) || (dwError == 0xFFFFFFFF))
   {
      dwError = JCTFILE_ERROR_SEEKFAIL;
   }
   else
   {
      dwError = JCTFILE_SUCCESS;
   }
};

size_t JCTFile::GetSize(HANDLE hFile, DWORD &dwError)
{
   dwError = JCTFILE_SUCCESS;
   DWORD dwHighSize = 0;
   DWORD dwReturn;
   size_t iReturn = 0;
   dwReturn = GetFileSize(hFile, &dwHighSize);
   if(INVALID_FILE_SIZE == dwError)
   {
      dwError = JCTFILE_ERROR_INVALIDFILESIZE;
   }

   return dwReturn;
};

void JCTFile::Delete(const char *pFileName, DWORD &dwError)
{
   if(pFileName)
   {
      if(!DeleteFile((char*)pFileName))
      {
         dwError = JCTFILE_ERROR_INVALIDFILENAME;
      }
      else
      {
         dwError = JCTFILE_SUCCESS;
      }
   }
   else 
   {
      dwError = JCTFILE_ERROR_INVALIDFILENAME;
   }
};

/*
int Application::InitWavData()
{

   infile.open(m_sFileName, ios::binary);

    //cout << "sizeof(short) = " << sizeof(short) << endl;
   
   short x[2];
   //short x2[12];
   int *iA;
   if (!infile) 
   {
      cout << "Couldn't open file " << m_sFileName << " for reading." << endl;
      return EXIT_FAILURE;
   }
   cout << "Opened file " << m_sFileName << " for reading." << endl;
   
   char buf[44];
   char buf2[2];
   char buf4[4];
   unsigned short iTemp=0;
   unsigned int frequency = 0;
   iLimit = 0, 
   iCount = 0;

   //ChunkID
   infile.read(reinterpret_cast<char *>(&buf4), 4);

   //Chunk Size
   infile.read(reinterpret_cast<char *>(&buf4), 4);

   //Format
   infile.read(reinterpret_cast<char *>(&buf4), 4);
   cout << "Format" << buf4 << endl;

   //SubChunk 1 ID
   infile.read(reinterpret_cast<char *>(&buf4), 4);

   //SubChunk 1 Size
   infile.read(reinterpret_cast<char *>(&buf4), 4);

   //Audio Format
   infile.read(reinterpret_cast<char *>(&buf2), 2);
   bits = 0;
   bits  = buf2[1]<<8;
   bits |= buf2[0];
   m_pcmWaveFormat.wf.wFormatTag = bits;
   cout << "Audio Format(PCM - 1)==>>" << m_pcmWaveFormat.wf.wFormatTag << endl;

   //Number of Channels
   infile.read(reinterpret_cast<char *>(&buf2), 2); 
   bits = 0;
   bits  = buf2[1]<<8;
   bits |= buf2[0];
   m_pcmWaveFormat.wf.nChannels = bits;
   cout << "Number of Channels (Mono = 1, Stereo = 2)==>>" << m_pcmWaveFormat.wf.nChannels << endl;

   //Sample Rate
   infile.read(reinterpret_cast<char *>(&buf4), 4);
   iTemp = buf4[0] + (buf4[1] << 8) + (buf4[2] << 16) + (buf4[3] << 24);
   cout << "Sample Rate" << iTemp << endl;
   m_pcmWaveFormat.wf.nSamplesPerSec = iTemp;
   iTemp=0;

   //Byte Rate
   infile.read(reinterpret_cast<char *>(&buf4), 4);

   //Block Align
   infile.read(reinterpret_cast<char *>(&buf2), 2);

   //Bits Per Sample
   infile.read(reinterpret_cast<char *>(&buf2), 2);
   bits = 0;
   bits  = buf2[1]<<8;
   bits |= buf2[0];
   m_pcmWaveFormat.wBitsPerSample = bits;
   cout << "Bits Per Sample==>>" << m_pcmWaveFormat.wBitsPerSample << endl;

   //SubChunk 2 ID
   infile.read(reinterpret_cast<char *>(&buf4), 4);

   //SubChunk 2 Size
   infile.read(reinterpret_cast<char *>(&buf4), 4);
   m_iFreq = (int)m_pcmWaveFormat.wf.nSamplesPerSec*.1;
   
   if(m_pcmWaveFormat.wBitsPerSample == 8)
   {
      m_iArrayIndex = 0;
      m_cArray = new unsigned char*[10];
      for(int x=0; x<10; x++)
      {
         m_cArray[x] = new unsigned char[m_iFreq];
      }
   }
   else
   {
      m_iArrayIndex = 0;
      m_fArray = new double*[10];
      for(int x=0; x<10; x++)
      {
         m_fArray[x] = new double[m_iFreq];
      }
   }

   Win.SetTimer(1, (float)m_iSeconds*1000);
   Win.SetTimerEvent(this, &Application::TimerEvent);
   
}
int Application::LoadWavData()
{
   
   yMin = 0.0;
   yMax = 0.0;
   //float fInc = (float)1/441;
//(iLimit < 4410 ) &&
//   (iLimit < fIntervals ) &&
   unsigned bytes_read = 0;
   int iSize = 2*m_pcmWaveFormat.wf.nChannels;
   char *x = new char[iSize];
   int iTemp = 0;
   iLimit = 0;
   if(m_pcmWaveFormat.wBitsPerSample == 8)
   {
      unsigned char fY = 0;
      while ((iLimit < (float)m_iFreq ) && infile.read(reinterpret_cast<char *>(x), iSize) && !infile.eof()) 
      {
        bits  = x[1]<<8;
        bits |= x[0];

       //if(bits != 0.0)
      // {
           //vs.push_back(bits);

           bytes_read += infile.gcount();
            //fX += fInc;
            fY = (unsigned char)((unsigned char)bits/(unsigned char)32768);//vs[iLimit];
            //cout << "Scalar (unsigned char)==>> " << fY << endl;
            
            unsigned char *scalar = (unsigned char *)(data->GetScalarPointer(iLimit, 0, 0));
            
            scalar[0] = (unsigned char)fY;
            m_cArray[0][iLimit] = bits;

            //yMin = min(cyMin, fY);
            //yMax = max(cyMax, fY);
            iLimit++;
        //}
        //else
         // iCount+= 1;
         
      }
   }
   else
   {
      double fY = 0.0;

      while ((iLimit < (float)m_iFreq ) && infile.read(reinterpret_cast<char *>(x), iSize) && !infile.eof()) 
      {
        bits  = x[1]<<8;
        bits |= x[0];
/*
        bits  = x[1]<<8;
        bits |= x[0];

/*        iLimit = 0;
        iTemp = x[0] + (x[1] << 8) + (x[2] << 16) + (x[3] << 24);

       if(bits != 0.0)
       {
           //vs.push_back(bits);

           bytes_read += infile.gcount();
            //int iH = bits;
            fY = (double)((double)bits/(double)32768);
           //fX += fInc;
            //fY = (double)bits;
            //cout << "Scalar (double)==>> " << fY << endl;
            double *scalar = (double *)(data->GetScalarPointer(iLimit, 0, 0));
            scalar[0] = fY;//(double)((double)bits/(double)32767);//vs[iLimit];
            m_fArray[0][iLimit] = fY;
            
                //= (double)fY;
            
            //yMin = min(yMin, scalar[0]);
            //yMax = max(yMax, scalar[0]);
            iLimit++;
        }
        //else
        //   iCount+= 1;
           
      }
   }
   if(infile.eof())
   {
    Win.StopTimer(1);
      infile.close();
   }
   delete []x;
    return EXIT_SUCCESS;
}
*/