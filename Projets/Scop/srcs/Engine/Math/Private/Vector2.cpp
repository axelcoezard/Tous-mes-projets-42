/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector2.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 09:15:00 by acoezard          #+#    #+#             */
/*   Updated: 2023/03/04 17:51:42 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Public/Vector2.h"

Vector2::Vector2(void): x(0.0f), y(0.0f) {};
Vector2::Vector2(float value): x(value), y(value) {};
Vector2::Vector2(const Vector2& copy): x(copy.x), y(copy.y) {};
Vector2::Vector2(float x, float y): x(x), y(y) {};

Vector2& Vector2::operator=(const Vector2& copy) {
	this->x = copy.x;
	this->y = copy.y;
	return *this;
}

Vector2 Vector2::Scale(float scale) {
	this->x *= scale;
	this->y *= scale;
	return *this;
}

Vector2 Vector2::Set(float x, float y) {
	this->x = x;
	this->y = y;
	return *this;
}

Vector2 Vector2::GetNormalized(void) {
	Vector2 destination(x, y);
	float invMagnitude = 1.0f / (float) Vector2::Magnitude(destination);
	destination.x *= invMagnitude;
	destination.y *= invMagnitude;
	return destination;
}

bool Vector2::Equals(Vector2 vector) {
	return x == vector.x && y == vector.y;
}

float Vector2::Dot(const Vector2& a, const Vector2& b) {
	return a.x * b.x + a.y * b.y;
}

float Vector2::Angle(const Vector2& a, const Vector2& b) {
	float angle = Vector2::Dot(a, b);
	angle /= Vector2::Magnitude(a) * Vector2::Magnitude(b);
	return acosf(angle);
}

float Vector2::Magnitude(const Vector2& a) {
	return sqrtf(Vector2::Dot(a, a));
}

float Vector2::Distance(const Vector2& a, const Vector2& b) {
	return Magnitude(Sub(a, b));
}

Vector2 Vector2::Min(const Vector2& a, const Vector2& b) {
	Vector2 c;
	c.x = a.x > b.x ? b.x : a.x;
	c.y = a.y > b.y ? b.y : a.y;
	return c;
}

Vector2 Vector2::Max(const Vector2& a, const Vector2& b) {
	Vector2 c;
	c.x = a.x < b.x ? b.x : a.x;
	c.y = a.y < b.y ? b.y : a.y;
	return c;
}

Vector2 Vector2::Add(const Vector2& a, const Vector2& b) {
	return Vector2(a.x + b.x, a.y + b.y);
}

Vector2 Vector2::Sub(const Vector2& a, const Vector2& b) {
	return Vector2(a.x - b.x, a.y - b.y);
}


bool operator==(Vector2& lhs, const Vector2& rhs)
{
	return lhs.Equals(rhs);
}

bool operator!=(Vector2& lhs, const Vector2& rhs)
{
	return !lhs.Equals(rhs);
}

Vector2 operator+(const Vector2& lhs, const Vector2& rhs)
{
	return Vector2::Add(lhs, rhs);
}

Vector2 operator+=(Vector2& lhs, const Vector2& rhs)
{
	lhs.x += rhs.x;
	lhs.y += rhs.y;
	return lhs;
}

Vector2 operator-(const Vector2& lhs, const Vector2& rhs)
{
	return Vector2::Sub(lhs, rhs);
}

Vector2 operator-=(Vector2& lhs, const Vector2& rhs)
{
	lhs.x -= rhs.x;
	lhs.y -= rhs.y;
	return lhs;
}

Vector2 operator*(const Vector2& lhs, const float rhs)
{
	return Vector2(lhs).Scale(rhs);
}

Vector2 operator*=(Vector2& lhs, const float rhs)
{
	return lhs.Scale(rhs);
}

float operator&(const Vector2& lhs, const Vector2& rhs)
{
	return Vector2::Dot(lhs, rhs);
}

std::ostream& operator<<(std::ostream& os, const Vector2& v)
{
	os << std::fixed << std::setprecision(5);
	os << "[" << std::setw(10) << v.x << " " << std::setw(10) << v.y << "]\n";
	os << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
	return os;
}
