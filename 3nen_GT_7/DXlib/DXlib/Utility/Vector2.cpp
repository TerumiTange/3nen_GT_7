#include "Vector2.h"
#include <cmath>

Vector2::Vector2():
	x(0),y(0)
{
}

Vector2::Vector2(float x, float y):
	x(x),y(y)
{
}

float Vector2::length()
{
	return std::sqrtf(dot(Vector2(x, y)));
}

Vector2 & Vector2::normalize()
{
	float l = length();
	if (l != 0)
	{
		this->x /= l;
		this->y /= l;
	}
	return *this;
}

float Vector2::dot(const Vector2 & v) const
{
	return (this->x*v.x) + (this->y*v.y);
}

Vector2 & Vector2::Vec()
{
	return *this;
}

Vector2 Vector2::operator+() const
{
	return Vector2(x, y);
}

Vector2 Vector2::operator-() const
{
	return Vector2(-x, -y);
}

Vector2 & Vector2::operator+=(const Vector2 & v)
{
	this->x += v.x;
	this->y += v.y;
	return *this;
}

Vector2 & Vector2::operator-=(const Vector2 & v)
{
	this->x -= v.x;
	this->y -= v.y;
	return *this;

}

Vector2 & Vector2::operator*=(float s)
{
	this->x *= s;
	this->y *= s;

	return *this;
}

Vector2 & Vector2::operator/=(float s)
{
	if (s == 0) { s = 0.00000001f; }//ŒÀ‚è‚È‚­0‚É‹ß‚¢”Žš‚ÅŒvŽZ
	this->x /= s;
	this->y /= s;

	return *this;
}

const Vector2 operator+(const Vector2 & v1, const Vector2 & v2)
{
	Vector2 temp(v1);
	temp += v2;
	return temp;
}

const Vector2 operator-(const Vector2 & v1, const Vector2 & v2)
{
	Vector2 temp(v1);
	temp -= v2;
	return temp;
}

const Vector2 operator*(const Vector2 & v, float s)
{
	Vector2 temp(v);
	temp *= s;
	return temp;
}

const Vector2 operator*(float s, const Vector2 & v)
{
	Vector2 temp(v);
	temp *= s;
	return temp;
}

const Vector2 operator/(const Vector2 & v, float s)
{
	Vector2 temp(v);
	if (s == 0) { s = 0.00000001f; }
	temp /= s;
	return temp;
}
