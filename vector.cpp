#include "vector.h"

Vector Vector::operator+(const Vector& rhs)
{
	Vector vec;
	vec.x = this->x + rhs.x;
	vec.y = this->y + rhs.y;
	return vec;
}

Vector Vector::operator-(const Vector& rhs)
{
	Vector vec;
	vec.x = this->x - rhs.x;
	vec.y = this->y - rhs.y;
	return vec;
}

Vector Vector::operator*(const float& rhs)
{
	Vector vec;
	vec.x = this->x * rhs;
	vec.y = this->y * rhs;
	return vec;
}

Vector Vector::operator/(const float& rhs)
{
	Vector vec;
	vec.x = this->x / rhs;
	vec.y = this->y / rhs;
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