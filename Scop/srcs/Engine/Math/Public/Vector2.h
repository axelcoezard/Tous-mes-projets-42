/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector2.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 09:27:19 by acoezard          #+#    #+#             */
/*   Updated: 2023/03/05 00:17:36 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <iomanip>
#include <cmath>

struct Vector2 {
	float x, y;

	Vector2(void);
	Vector2(float value);
	Vector2(const Vector2& copy);
	Vector2(float x, float y);
	Vector2& operator=(const Vector2& copy);

	bool Equals(Vector2 vector);

	Vector2 Scale(float scale);
	Vector2 Set(float x, float y);
	Vector2 GetNormalized(void);

	static float Dot(const Vector2& a, const Vector2& b);
	static float Angle(const Vector2& a, const Vector2& b);
	static float Magnitude(const Vector2& a);
	static float Distance(const Vector2& a, const Vector2& b);
	static Vector2 Min(const Vector2& a, const Vector2& b);
	static Vector2 Max(const Vector2& a, const Vector2& b);
	static Vector2 Add(const Vector2& a, const Vector2& b);
	static Vector2 Sub(const Vector2& a, const Vector2& b);

	friend bool operator==(Vector2& lhs, const Vector2& rhs);
	friend bool operator!=(Vector2& lhs, const Vector2& rhs);
	friend Vector2 operator+(const Vector2& lhs, const Vector2& rhs);
	friend Vector2 operator+=(Vector2& lhs, const Vector2& rhs);
	friend Vector2 operator-(const Vector2& lhs, const Vector2& rhs);
	friend Vector2 operator-=(Vector2& lhs, const Vector2& rhs);
	friend Vector2 operator*(const Vector2& lhs, const float& rhs);
	friend Vector2 operator*=(Vector2& lhs, const float& rhs);
	friend Vector2 operator^(const Vector2& lhs, const Vector2& rhs);
	friend float operator&(const Vector2& lhs, const Vector2& rhs);

	friend std::ostream& operator<<(std::ostream& os, const Vector2& v);
};
