#pragma once
#include "jctimagefile.h"

enum TGATypes
{
	TGA_NODATA = 0,
	TGA_INDEXED = 1,
	TGA_RGB = 2,
	TGA_GRAYSCALE = 3,
	TGA_INDEXED_RLE = 9,
	TGA_RGB_RLE = 10,
	TGA_GRAYSCALE_RLE = 11
};

struct rgba_t
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	unsigned char a;
};

// Image Data Formats
#define	IMAGE_RGB       0
#define IMAGE_RGBA      1
#define IMAGE_LUMINANCE 2

// Image data types
#define	IMAGE_DATA_UNSIGNED_BYTE 0
// TGA header
// TGA header
struct tgaheader_tb
{
	unsigned char  idLength;		
	unsigned char  colorMapType;	
	unsigned char  imageTypeCode;	
	unsigned char  colorMapSpec[5];	
	unsigned short xOrigin;			
	unsigned short yOrigin;			
	unsigned short width;			
	unsigned short height;			
	unsigned char  bpp;				
	unsigned char  imageDesc;		
};

struct STGA
{
        STGA()
        {
                data = (unsigned char*)0;
                width = 0;
                height = 0;
                byteCount = 0;
        }

	~STGA() { delete[] data; data = 0; }

	void destroy() { delete[] data; data = 0; }
   tgaheader_tb header;
   int width;
	int height;
   unsigned char byteCount;
   unsigned char* data;
};



class JCTTGAFile :
   public JCTImageFile
{
   STGA m_tgaData;
public:
   JCTTGAFile(void);
   ~JCTTGAFile(void);
	STGA* getTGAData();

   bool Load(const char *filename, STGA* tgaFile, DWORD &dwError);
};
