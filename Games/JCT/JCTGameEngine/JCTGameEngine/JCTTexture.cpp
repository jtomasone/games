
#include "JCTTexture.h"

JCTTexture::JCTTexture(const string &name) : JCTObject(name)
{
};

JCTTexture::JCTTexture() : JCTObject("")
{

};

JCTTexture::~JCTTexture(void)
{
}
/*
JCTTexture::Init()
{

}

bool CTargaImage::Load(const char *filename)
{
	FILE *pFile = fopen(filename, "rb");

	if (!pFile)
		return false;

	tgaheader_t tgaHeader;

	// read the TGA header
	fread(&tgaHeader, 1, sizeof(tgaheader_t), pFile);

	// see if the image type is one that we support (RGB, RGB RLE, GRAYSCALE, GRAYSCALE RLE)
	if ( ((tgaHeader.imageTypeCode != TGA_RGB) && (tgaHeader.imageTypeCode != TGA_GRAYSCALE) && 
		 (tgaHeader.imageTypeCode != TGA_RGB_RLE) && (tgaHeader.imageTypeCode != TGA_GRAYSCALE_RLE)) ||
		 tgaHeader.colorMapType != 0)
	{
		fclose(pFile);
		return false;
	}

	// get image width and height
	m_width = tgaHeader.width;
	m_height = tgaHeader.height;

	// colormode -> 3 = BGR, 4 = BGRA
	int colorMode = tgaHeader.bpp / 8;

	// we don't handle less than 24 bit
	if (colorMode < 3)
	{
		fclose(pFile);
		return false;
	}

	m_imageSize = m_width * m_height * colorMode;

	// allocate memory for TGA image data
	m_pImageData = new unsigned char[m_imageSize];

	// skip past the id if there is one
	if (tgaHeader.idLength > 0)
		fseek(pFile, SEEK_CUR, tgaHeader.idLength);

	// read image data
	if (tgaHeader.imageTypeCode == TGA_RGB || tgaHeader.imageTypeCode == TGA_GRAYSCALE)
	{
		fread(m_pImageData, 1, m_imageSize, pFile);
	}
	else 
	{
		// this is an RLE compressed image
		unsigned char id;
		unsigned char length;
		rgba_t color = { 0, 0, 0, 0 };
		unsigned int i = 0;

		while (i < m_imageSize)
		{
			id = fgetc(pFile);

			// see if this is run length data
			if (id >= 128)// & 0x80)
			{
				// find the run length
				length = (unsigned char)(id - 127);

				// next 3 (or 4) bytes are the repeated values
				color.b = (unsigned char)fgetc(pFile);
				color.g = (unsigned char)fgetc(pFile);
				color.r = (unsigned char)fgetc(pFile);

				if (colorMode == 4)
					color.a = (unsigned char)fgetc(pFile);

				// save everything in this run
				while (length > 0)
				{
					m_pImageData[i++] = color.b;
					m_pImageData[i++] = color.g;
					m_pImageData[i++] = color.r;

					if (colorMode == 4)
						m_pImageData[i++] = color.a;

					--length;
				}
			}
			else
			{
				// the number of non RLE pixels
				length = unsigned char(id + 1);

				while (length > 0)
				{
					color.b = (unsigned char)fgetc(pFile);
					color.g = (unsigned char)fgetc(pFile);
					color.r = (unsigned char)fgetc(pFile);

					if (colorMode == 4)
						color.a = (unsigned char)fgetc(pFile);

					m_pImageData[i++] = color.b;
					m_pImageData[i++] = color.g;
					m_pImageData[i++] = color.r;

					if (colorMode == 4)
						m_pImageData[i++] = color.a;

					--length;
				}
			}
		}
	}

	fclose(pFile);

	switch(tgaHeader.imageTypeCode)
	{
	case TGA_RGB:
	case TGA_RGB_RLE:
		if (3 == colorMode)
		{
			m_imageDataFormat = IMAGE_RGB;
			m_imageDataType = IMAGE_DATA_UNSIGNED_BYTE;
			m_colorDepth = 24;
		}
		else
		{
			m_imageDataFormat = IMAGE_RGBA;
			m_imageDataType = IMAGE_DATA_UNSIGNED_BYTE;
			m_colorDepth = 32;
		}
		break;

	case TGA_GRAYSCALE:
	case TGA_GRAYSCALE_RLE:
		m_imageDataFormat = IMAGE_LUMINANCE;
		m_imageDataType = IMAGE_DATA_UNSIGNED_BYTE;
		m_colorDepth = 8;
		break;
	}

	if ((tgaHeader.imageDesc & TOP_LEFT) == TOP_LEFT)
		FlipVertical();

	// swap the red and blue components in the image data
	SwapRedBlue();

	return (m_pImageData != NULL);
}
*/