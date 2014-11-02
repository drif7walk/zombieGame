#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

class Vector {

public:
	float x;
	float y;

	Vector(float x_, float y_) {
		x = x_;
		y = y_;
	}

	Vector(const Vector& vec)
	{
		x = vec.x;
		y = vec.y;
	}

	Vector()
	{
		x = 0;
		y = 0;
	}

	~Vector()
	{
	}

	Vector operator+(const Vector& rhs);
	
	Vector operator-(const Vector& rhs);
	
	Vector operator*(float rhs);

	Vector operator/(float rhs);

	float magnitude();

	void normalize();

	void limit(float n);
};

#endif