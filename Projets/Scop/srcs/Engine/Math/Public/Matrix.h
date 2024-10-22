/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 12:30:22 by acoezard          #+#    #+#             */
/*   Updated: 2023/02/28 13:29:53 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Inspiration from UE5 https://docs.unrealengine.com/4.27/en-US/API/Runtime/Core/Math/FMatrix/
// Inpisration from https://github.com/glfw/glfw/blob/master/deps/linmath.h

#pragma once

#include <iostream>
#include <iomanip>
#include <cmath>

#include "Vector3.h"

struct Matrix {
	float values[16];

	Matrix(void);
	Matrix(const float copy[16]);
	Matrix(float m00, float m01, float m02, float m03,
			float m04, float m05, float m06, float m07,
			float m08, float m09, float m10, float m11,
			float m12, float m13, float m14, float m15);
	Matrix(const Matrix& copy);
	Matrix& operator=(const Matrix& copy);

	void Set(const float copy[16]);
	void Set(float m00, float m01, float m02, float m03,
			float m04, float m05, float m06, float m07,
			float m08, float m09, float m10, float m11,
			float m12, float m13, float m14, float m15);
	void Set(unsigned int i, float value);
	void Set(unsigned int x, unsigned int y, float value);
	void SetColumn(unsigned int i, const Vector3& column);

	float Get(unsigned int i) const;
	float Get(unsigned int i, unsigned int j) const;

	void Scale(float scale);

	bool Equals(const Matrix& other) const;

	Matrix GetTransposed(void) const;
	Matrix GetCopy(void) const;

	static void Identity(Matrix& matrix);
	static Matrix Add(const Matrix& a, const Matrix& b);
	static Matrix Sub(const Matrix& a, const Matrix& b);
	static Matrix Mul(const Matrix& a, const Matrix& b);
	//static void Rotate(Matrix& matrix, const float angle, const Vector3& axis);
	static void RotateX(Matrix& matrix, const float angle);
	static void RotateY(Matrix& matrix, const float angle);
	static void RotateZ(Matrix& matrix, const float angle);
	static void Scale(Matrix& matrix, float s);
	static void Scale(Matrix& matrix, float x, float y, float z);
	static void Translate(Matrix& matrix, float x, float y, float z);
	static Matrix LookAt(Vector3& position, Vector3& target, Vector3& up);

	static Matrix GetFrustrum(float left, float right, float bottom, float top, float near, float far);
	static Matrix GetPerspective(float fov, float aspect, float near, float far);
	static Matrix GetOrtho(float left, float right, float bottom, float top, float near, float far);

	float operator[](unsigned int i) const;
	float& operator[](unsigned int i);

	friend bool operator==(const Matrix& lhs, const Matrix& rhs);
	friend bool operator!=(const Matrix& lhs, const Matrix& rhs);
	friend Matrix operator+(const Matrix& lhs, const Matrix& rhs);
	friend Matrix operator-(const Matrix& lhs, const Matrix& rhs);
	friend Matrix operator*(const Matrix& lhs, const Matrix& rhs);

	friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
};
