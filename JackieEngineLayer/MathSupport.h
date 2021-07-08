#ifndef __JKEG_MathSupport__
#define __JKEG_MathSupport__

#include "../CrossBufferLayer/BasicDataTypeDeclarations.h"


/*
** Define Some Calculating Functions
*/




/*
** Vector4D
*/

class Vector4D {
public:
	float x;
	float y;
	float z;
	float w;

	Vector4D(float x_, float y_, float z_, float w_);
	Vector4D();
	string    str()                        const;
	float     length()                     const;
	Vector4D  normalized()                 const;
	void      Normalize();
	void      DevideByW();
	Vector4D  operator+(const Vector4D& b) const;
	Vector4D  operator-(const Vector4D& b) const;
	float     operator*(const Vector4D& b) const;  // Dot   Product
	Vector4D  operator%(const Vector4D& b) const;  // Cross Product
};


/*
** Matrix4D
*/

class Matrix4D {
public:
	float m11, m12, m13, m14;
	float m21, m22, m23, m24;
	float m31, m32, m33, m34;
	float m41, m42, m43, m44;

	Matrix4D(
		float m11, float m12, float m13, float m14,
		float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34,
		float m41, float m42, float m43, float m44
	);
	Matrix4D();

	string str() const;
	friend Vector4D operator*(Vector4D& v, Matrix4D& m);
	friend Matrix4D operator*(Matrix4D& a, Matrix4D& b);
};
#endif
