#ifndef ENGINE_MATH_UTIL_H
#define ENGINE_MATH_UTIL_H
static float DEF_TOLERANCE = (float)0.001;
#include "MathEngine.h"

class Util
{
public:
	static bool isEqual( const float a, const float b, const float epsilon );
	static bool isNotEqual( const float a, const float b, const float epsilon );
	static bool isOne( const float a, const float epsilon );
	static bool isNonZero( const float a, const float epsilon );
	static bool isZero( const float a, const float epsilon );

};

#endif