/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector3.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 09:15:00 by acoezard          #+#    #+#             */
/*   Updated: 2023/03/02 08:35:59 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Public/Vector3.h"

Vector3 Vector3::Zero = Vector3(0.0f, 0.0f, 0.0f);
Vector3 Vector3::One = Vector3(1.0f, 1.0f, 1.0f);
Vector3 Vector3::Forward = Vector3(1.0f, 0.0f, -1.0f);
Vector3 Vector3::Backward = Vector3(0.0f, 0.0f, 1.0f);
Vector3 Vector3::Up = Vector3(0.0f, 1.0f, 0.0f);
Vector3 Vector3::Down = Vector3(0.0f, -1.0f, 0.0f);
Vector3 Vector3::Left = Vector3(-1.0f, 0.0f, 0.0f);
Vector3 Vector3::Right = Vector3(1.0f, 0.0f, 0.0f);

Vector3::Vector3(void): x(0.0f), y(0.0f), z(0.0f) {};
Vector3::Vector3(float value): x(value), y(value), z(value) {};
Vector3::Vector3(const Vector3& copy): x(copy.x), y(copy.y), z(copy.z) {};
Vector3::Vector3(float x, float y, float z): x(x), y(y), z(z) {};

Vector3& Vector3::operator=(const Vector3& copy) {
	this->x = copy.x;
	this->y = copy.y;
	this->z = copy.z;
	return *this;
}

Vector3 Vector3::Scale(float scale) {
	this->x *= scale;
	this->y *= scale;
	this->z *= scale;
	return *this;
}

Vector3 Vector3::Set(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
	return *this;
}

Vector3 Vector3::GetNormalized(void) {
	Vector3 destination(x, y, z);
	float invMagnitude = 1.0f / (float) Vector3::Magnitude(destination);
	destination.x *= invMagnitude;
	destination.y *= invMagnitude;
	destination.z *= invMagnitude;
	return destination;
}

bool Vector3::Equals(Vector3 vector) {
	return x == vector.x && y == vector.y && z == vector.z;
}

float Vector3::Dot(const Vector3& a, const Vector3& b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3 Vector3::Cross(const Vector3& a, const Vector3& b) {
	return Vector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

float Vector3::Angle(const Vector3& a, const Vector3& b) {
	float angle = Vector3::Dot(a, b);
	angle /= Vector3::Magnitude(a) * Vector3::Magnitude(b);
	return acosf(angle);
}

float Vector3::Magnitude(const Vector3& a) {
	return sqrtf(Vector3::Dot(a, a));
}

float Vector3::Distance(const Vector3& a, const Vector3& b) {
	return Magnitude(Sub(a, b));
}

Vector3 Vector3::Min(const Vector3& a, const Vector3& b) {
	Vector3 c;
	c.x = a.x > b.x ? b.x : a.x;
	c.y = a.y > b.y ? b.y : a.y;
	c.z = a.z > b.z ? b.z : a.z;
	return c;
}

Vector3 Vector3::Max(const Vector3& a, const Vector3& b) {
	Vector3 c;
	c.x = a.x < b.x ? b.x : a.x;
	c.y = a.y < b.y ? b.y : a.y;
	c.z = a.z < b.z ? b.z : a.z;
	return c;
}

Vector3 Vector3::Add(const Vector3& a, const Vector3& b) {
	return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
}

Vector3 Vector3::Sub(const Vector3& a, const Vector3& b) {
	return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
}


bool operator==(Vector3& lhs, const Vector3& rhs)
{
	return lhs.Equals(rhs);
}

bool operator!=(Vector3& lhs, const Vector3& rhs)
{
	return !lhs.Equals(rhs);
}

Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
{
	return Vector3::Add(lhs, rhs);
}

Vector3 operator+=(Vector3& lhs, const Vector3& rhs)
{
	lhs.x += rhs.x;
	lhs.y += rhs.y;
	lhs.z += rhs.z;
	return lhs;
}

Vector3 operator-(const Vector3& lhs, const Vector3& rhs)
{
	return Vector3::Sub(lhs, rhs);
}

Vector3 operator-=(Vector3& lhs, const Vector3& rhs)
{
	lhs.x -= rhs.x;
	lhs.y -= rhs.y;
	lhs.z -= rhs.z;
	return lhs;
}

Vector3 operator*(const Vector3& lhs, const float rhs)
{
	return Vector3(lhs).Scale(rhs);
}

Vector3 operator*=(Vector3& lhs, const float rhs)
{
	return lhs.Scale(rhs);
}

Vector3 operator^(const Vector3& lhs, const Vector3& rhs)
{
	return Vector3::Cross(lhs, rhs);
}

float operator&(const Vector3& lhs, const Vector3& rhs)
{
	return Vector3::Dot(lhs, rhs);
}

std::ostream& operator<<(std::ostream& os, const Vector3& v)
{
	os << std::fixed << std::setprecision(5);
	os << "[" << std::setw(10) << v.x << " " << std::setw(10) << v.y << " " << std::setw(10) << v.z  << "]\n";
	os << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
	return os;
}
