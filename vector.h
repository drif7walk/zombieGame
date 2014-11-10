#ifndef VECTOR_H
#define VECTOR_H

#include <SDL.h>

#include <math.h>
#include <stdlib.h>

class Vector {

public:
	float x;
	float y;

	Vector(const float& x_, const float& y_) {
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

	Vector& operator=(const Vector& rhs);

	Vector& operator+=(const Vector& rhs);

	Vector& operator-=(const Vector& rhs);

	Vector operator+(const Vector& rhs) const;

	Vector operator-(const Vector& rhs) const;

	Vector& operator*=(const float& rhs);

	Vector& operator/=(const float& rhs);

	Vector operator*(const float& rhs) const;

	Vector operator/(const float& rhs) const;

	float magnitude();

	void normalize();

	void limit(const float& n);

	float angle();
	//returns an angle a particular vector is pointing towards, getting the correct angle requires
	//a vector that begins at 0,
	//0 - 360, 0 is (1, 0) and increases clockwise
	//            270 degrees
	//
	//180 degrees  0     0 degrees
	//
	//             90 degrees
	//same with rotate() it rotates clockwise 
	void rotate(const float& angle);

	void random();
};

#endif
