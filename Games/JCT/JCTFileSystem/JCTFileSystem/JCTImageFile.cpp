#include "JCTImageFile.h"

JCTImageFile::JCTImageFile(void) : JCTFile()
{
}

JCTImageFile::~JCTImageFile(void)
{
}

const unsigned char  JCTImageFile::getColorDepth()
{
   return this->m_colorDepth;
};
const unsigned char  JCTImageFile::getImageDataType()
{
   return this->m_imageDataType;
};
const unsigned char  JCTImageFile::getImageDataFormat()
{
   return this->m_imageDataFormat;
};
const unsigned char* JCTImageFile::getPImageData()
{
   return this->m_pImageData;
};
const unsigned short JCTImageFile::getWidth()
{
   return this->m_width;
};
const unsigned short JCTImageFile::getHeight()
{
   return this->m_height;
};
const unsigned long  JCTImageFile::getImageSize()
{
   return this->m_imageSize;
};

void JCTImageFile::setColorDepth      (const unsigned char &ucIcolorDepth)
{
   m_colorDepth = ucIcolorDepth;
};
void JCTImageFile::setImageDataType   (const unsigned char  &ucImageDataType)
{
   m_imageDataType = ucImageDataType;
};
void JCTImageFile::setImageDataFormat (const unsigned char  &ucImageDataFormat)
{
   m_imageDataFormat = ucImageDataFormat;
};
void JCTImageFile::setPImageData      (const unsigned char &pImageData)
{
   m_pImageData = (unsigned char*)pImageData;
};
void JCTImageFile::setWidth           (const unsigned short &usWidth)
{
   m_width = usWidth;
};
void JCTImageFile::setHeight          (const unsigned short &usHeight)
{
   m_height = usHeight;
};
void JCTImageFile::setImageSize       (const unsigned long &lImageSize)
{
   m_imageSize = lImageSize;
};