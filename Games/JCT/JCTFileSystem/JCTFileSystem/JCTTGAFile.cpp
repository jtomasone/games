#include "JCTTGAFile.h"

JCTTGAFile::JCTTGAFile(void) : JCTImageFile()
{
}

JCTTGAFile::~JCTTGAFile(void)
{
}

STGA* JCTTGAFile::getTGAData()
{
   return &this->m_tgaData;
}

bool JCTTGAFile::Load(const char *filename, STGA* tgaFile, DWORD &dwError)
{
   tgaFile = this->getTGAData();
   //FILE *file;
   bool bSuccess=false;
   DWORD dwBytesRead = 0, dwPtr = 0;//, dwError = 0;
   //     file = fopen(filename, "rb");
   HANDLE hFile = Create((char*)filename, dwError, 0, JCTFILE_READ);//this->Create((char*)filename, dwError, OPEN_EXISTING);
   unsigned short nValue=0;

   if (dwError)
   {
      return false;
   }
   dwError = GetLastError();

   this->Read((unsigned char*)&tgaFile->header, sizeof(tgaFile->header), dwError);
   //bSuccess = ReadFile(hFile, &tgaFile->header, sizeof(tgaFile->header), &dwBytesRead, NULL);
   dwError = GetLastError();
   if (dwError)
   {
      return false;
   }

   if ( ((tgaFile->header.imageTypeCode != TGA_RGB) && (tgaFile->header.imageTypeCode != TGA_GRAYSCALE) && 
       (tgaFile->header.imageTypeCode != TGA_RGB_RLE) && (tgaFile->header.imageTypeCode != TGA_GRAYSCALE_RLE)) ||
       tgaFile->header.colorMapType != 0)
   {
      Close(dwError);
      return false;
   }

   // get image width and height
   this->setWidth(tgaFile->header.width);
   this->setHeight(tgaFile->header.height);

   tgaFile->width = this->getWidth();
   tgaFile->height = this->getHeight();;

   // colormode -> 3 = BGR, 4 = BGRA
   int colorMode = tgaFile->header.bpp / 8;

   // we don't handle less than 24 bit
   if (colorMode < 3)
   {
      CloseHandle(this->getHandle());
      return false;
   }

   this->setImageSize(this->getWidth() * this->getHeight() * colorMode);

   //allocate memory for image data
   tgaFile->data = new unsigned char[this->getImageSize()];

   // skip past the id if there is one
   if (tgaFile->header.idLength > 0)
   {
      this->Seek(tgaFile->header.idLength, dwError);
      if (dwError == JCTFILE_ERROR_SEEKFAIL) // Test for failure.
      { 
         return false;
      }
   }

   //read in image data
   if (tgaFile->header.imageTypeCode == TGA_RGB || tgaFile->header.imageTypeCode == TGA_GRAYSCALE)
   {
      Read((unsigned char*)tgaFile->data, this->getImageSize(), dwError);
      if (dwError == JCTFILE_ERROR_READFAIL)
      {
         return false;
      }
   }
   else
   {
      // this is an RLE compressed image
      unsigned char id;
      unsigned char length;
      rgba_t color = { 0, 0, 0, 0 };
      unsigned int i = 0;

      while (i < this->getImageSize())
      {
         this->Read((unsigned char*)&id, sizeof(unsigned char), dwError);

         // see if this is run length data
         if (id >= 128)// & 0x80)
         {
            // find the run length
            length = (unsigned char)(id - 127);

            // next 3 (or 4) bytes are the repeated values
            this->Read((unsigned char*)&color.b, sizeof(unsigned char), dwError);
            this->Read((unsigned char*)&color.g, sizeof(unsigned char), dwError);
            this->Read((unsigned char*)&color.r, sizeof(unsigned char), dwError);

            if (colorMode == 4)
            {
               Read((unsigned char*)&color.a, sizeof(unsigned char), dwError);
            }

            // save everything in this run
            while (length > 0)
            {
               this->m_pImageData[i++] = color.b;
               this->m_pImageData[i++] = color.g;
               this->m_pImageData[i++] = color.r;

               if (colorMode == 4)
                  this->m_pImageData[i++] = color.a;

               --length;
            }
         }
         else
         {
            // the number of non RLE pixels
            length = unsigned char(id + 1);

            while (length > 0)
            {
               this->Read((unsigned char*)&color.b, sizeof(unsigned char), dwError);
               this->Read((unsigned char*)&color.g, sizeof(unsigned char), dwError);
               this->Read((unsigned char*)&color.r, sizeof(unsigned char), dwError);

               if (colorMode == 4)
               {
                  this->Read((unsigned char*)&color.a, sizeof(unsigned char), dwError);
               }

               this->m_pImageData[i++] = color.b;
               this->m_pImageData[i++] = color.g;
               this->m_pImageData[i++] = color.r;

               if (colorMode == 4)
                  this->m_pImageData[i++] = color.a;

               --length;
            }
         }
      }
   }

   this->Close(dwError);

   switch(tgaFile->header.imageTypeCode)
   {
   case TGA_RGB:
   case TGA_RGB_RLE:
      if (3 == colorMode)
      {
         this->setImageDataFormat(IMAGE_RGB);
         this->setImageDataType(IMAGE_DATA_UNSIGNED_BYTE);
         this->setColorDepth(24);
      }
      else
      {
         this->setImageDataFormat(IMAGE_RGBA);
         this->setImageDataType(IMAGE_DATA_UNSIGNED_BYTE);
         this->setColorDepth(32);
      }
      break;

   case TGA_GRAYSCALE:
   case TGA_GRAYSCALE_RLE:
      this->setImageDataFormat(IMAGE_LUMINANCE);
      this->setImageDataType(IMAGE_DATA_UNSIGNED_BYTE);
      this->setColorDepth(8);
      break;
   }

   //if ((tgaFile->header.imageDesc & TOP_LEFT) == TOP_LEFT)
   //   FlipVertical();

   // swap the red and blue components in the image data
   //SwapRedBlue();

   //close file
   //CloseHandle(this->getHandle());
   return (NULL != tgaFile->data);
}
