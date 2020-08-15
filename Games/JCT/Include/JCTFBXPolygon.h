#pragma once
#include "jctfbxobject.h"
#include "Vect.h"
#include "math3d.h"

typedef std::vector<Vect*>JCTPolyComponents;

class JCTFBXPolygon :
   public JCTFBXObject
{

   unsigned int m_iVertCount;

public:
   JCTFBXPolygon(const unsigned int &iCount);

   void setVertCount(const unsigned int &iCount);
   unsigned int getVertCount();

   JCTPolyComponents m_pPoints;
   JCTPolyComponents m_pUVs;
   JCTPolyComponents m_pNormals;
   JCTFBXPolygon(void);
   ~JCTFBXPolygon(void);
   virtual void Render();
};


/*
Polygon 0
            Coordinates: 8.565114, -39.962467, 39.303127
            Texture UV (on layer 0): 0.942071, 0.494969
            Normal (on layer 0): 0.163138, -0.622738, -0.765234
            
            Coordinates: 0.000000, -39.962467, 36.634930
            Texture UV (on layer 0): 0.993623, 0.494969
            Normal (on layer 0): -0.000000, -0.337715, -0.941249
            Coordinates: 0.000000, -15.710989, 30.479607
            Texture UV (on layer 0): 0.993623, 0.359694
            Normal (on layer 0): -0.000000, -0.273864, -0.961769
            Coordinates: 14.052543, -14.077739, 37.557323
            Texture UV (on layer 0): 0.942071, 0.359694
            Normal (on layer 0): 0.515776, 0.419959, -0.746733
*/
