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
	auto vec(*this);
	vec += rhs;
	return vec;
}

Vector Vector::operator-(const Vector& rhs)const
{
	auto vec(*this);
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
	auto vec(*this);
	vec *= rhs;
	return vec;
}

Vector Vector::operator/(const float& rhs)const
{
	auto vec(*this);
	vec /= rhs;
	return vec;
}

float Vector::magnitude()
{
	return sqrt(x*x + y*y);
}

void Vector::normalize() {
	auto m = magnitude();
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

void Vector::rotate(const float& angle)
{
	auto _angle = angle * M_PI / 180;
	auto _cos = cos(_angle);
	auto _sin = sin(_angle);
	auto px = this->x * _cos - this->y * _sin;
	auto py = this->x * _sin + this->y * _cos;
	this->x = px;
	this->y = py;
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

	auto angle = atan2(-y, x) * 57.2957795131f;
	if (angle < 0)
	{
		angle *= -1;
	}
	else
	{
		angle = 360 - angle;
	}
	return angle;
}

void Vector::random()
{
	x = rand() % 100 - 50;
	y = rand() % 100 - 50;
}
