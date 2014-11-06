#include "vector.h"


Vector& Vector::operator=(const Vector& rhs)
{
	if (this != &rhs)
	{
		this->x = rhs.x;
		this->y = rhs.y;
	}
	return *this;
}

Vector& Vector::operator+=(const Vector& rhs)
{
	this->x += rhs.x;
	this->y += rhs.y;
	return (*this);
}

Vector& Vector::operator-=(const Vector& rhs)
{
	this->x -= rhs.x;
	this->y -= rhs.y;
	return (*this);
}

Vector Vector::operator+(const Vector& rhs)const
{
	Vector vec(*this);
	vec += rhs;
	return vec;
}

Vector Vector::operator-(const Vector& rhs)const
{
	Vector vec(*this);
	vec -= rhs;
	return vec;
}

Vector& Vector::operator*=(const float& rhs)
{
	this->x *= rhs;
	this->y *= rhs;
	return (*this);
}

Vector& Vector::operator/=(const float& rhs)
{
	this->x /= rhs;
	this->y /= rhs;
	return (*this);
}

Vector Vector::operator*(const float& rhs)const
{
	Vector vec(*this);
	vec *= rhs;
	return vec;
}

Vector Vector::operator/(const float& rhs)const
{
	Vector vec(*this);
	vec /= rhs;
	return vec;
}

float Vector::magnitude()
{
	return sqrt(x*x + y*y);
}

void Vector::normalize() {
	float m = magnitude();
	if (m != 0) {
		(*this) = (*this) / m;
	}
}

void Vector::limit(const float& n)
{
	if (magnitude() > n)
	{
		normalize();
		(*this) = (*this) * n;
	}
}

float Vector::angle()
{
	//Vector U(1, 0);
	//float dot = x*U.x + y*U.y;
	//float det = x*U.y - y*U.x;
	//float angle = atan2(det, dot) * 180 / M_PI;
	//if (angle < 0)
	//{
	//	angle = angle + 360;
	//}
	//return 360-angle;
	return 360 - atan2(-y, x) * 57.2957795131f;//checkmate math
}

void Vector::random()
{
	x = rand() % 100 - 50;
	y = rand() % 100 - 50;
}
