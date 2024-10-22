/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Matrix.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acoezard <acoezard@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:16:04 by acoezard          #+#    #+#             */
/*   Updated: 2023/03/01 13:37:52 by acoezard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Public/Matrix.h"

Matrix::Matrix(void) {
	Matrix::Identity(*this);
}


Matrix::Matrix(const float copy[16]) {
	Set(copy);
}

Matrix::Matrix(float m00, float m01, float m02, float m03,
				float m04, float m05, float m06, float m07,
				float m08, float m09, float m10, float m11,
				float m12, float m13, float m14, float m15) {
	Set(m00, m01, m02, m03, m04, m05, m06, m07, m08, m09, m10, m11, m12, m13, m14, m15);
}

Matrix::Matrix(const Matrix& copy) {
	*this = copy;
}

Matrix& Matrix::operator=(const Matrix& copy) {
	for (unsigned int i = 0; i < 16; i++) {
		this->values[i] = copy.values[i];
	}
	return *this;
}

void Matrix::Set(const float copy[16]) {
	values[0] = copy[0]; values[1] = copy[1]; values[2] = copy[2]; values[3] = copy[3];
	values[4] = copy[4]; values[5] = copy[5]; values[6] = copy[6]; values[7] = copy[7];
	values[8] = copy[8]; values[9] = copy[9]; values[10] = copy[10]; values[11] = copy[11];
	values[12] = copy[12]; values[13] = copy[13]; values[14] = copy[14]; values[15] = copy[15];
}

void Matrix::Set(float m00, float m01, float m02, float m03,
				float m04, float m05, float m06, float m07,
				float m08, float m09, float m10, float m11,
				float m12, float m13, float m14, float m15) {
	values[0] = m00; values[1] = m01; values[2] = m02; values[3] = m03;
	values[4] = m04; values[5] = m05; values[6] = m06; values[7] = m07;
	values[8] = m08; values[9] = m09; values[10] = m10; values[11] = m11;
	values[12] = m12; values[13] = m13; values[14] = m14; values[15] = m15;
}


void Matrix::Set(unsigned int i, float value) {
	values[i] = value;
}

void Matrix::Set(unsigned int x, unsigned int y, float value) {
	Set(x + 4 * y, value);
}

void Matrix::SetColumn(unsigned int i, const Vector3& column) {
	values[i * 4] = column.x;
	values[i * 4 + 1] = column.y;
	values[i * 4 + 2] = column.z;
}

float Matrix::Get(unsigned int i) const {
	return values[i];
}

float Matrix::Get(unsigned int x, unsigned int y) const {
	return Get(x + 4 * y);
}

void Matrix::Scale(float scale) {
	for (unsigned int i = 0; i < 16; i++) {
		values[i] *= scale;
	}
}

bool Matrix::Equals(const Matrix& other) const {
	for (unsigned int i = 0; i < 16; i++) {
		if (values[i] != other.values[i]) {
			return false;
		}
	}
	return true;
}

Matrix Matrix::GetTransposed(void) const {
	Matrix destination;
	for (unsigned int x = 0; x < 4; x++) {
		for (unsigned int y = 0; y < 4; y++) {
			destination.values[y + 4 * x] = values[x + 4 * y];
		}
	}
	return destination;
}

Matrix Matrix::GetCopy(void) const {
	return Matrix(*this);
}

void Matrix::Identity(Matrix& matrix) {
	for (unsigned int i = 0; i < 16; i++) {
		matrix.values[i] = 0.0f;
	}
	matrix.values[0] = 1.0f;
	matrix.values[5] = 1.0f;
	matrix.values[10] = 1.0f;
	matrix.values[15] = 1.0f;
}

Matrix Matrix::Add(const Matrix& a, const Matrix& b) {
	Matrix destination;
	for (unsigned int i = 0; i < 16; i++) {
		destination.values[i] = a.values[i] + b.values[i];
	}
	return destination;
}

Matrix Matrix::Sub(const Matrix& a, const Matrix& b) {
	Matrix destination;
	for (unsigned int i = 0; i < 16; i++) {
		destination.values[i] = a.values[i] - b.values[i];
	}
	return destination;
}

Matrix Matrix::Mul(const Matrix& a, const Matrix& b) {
	return Matrix(a[0] * b[0]  + a[4] * b[1]  + a[8] * b[2]  + a[12] * b[3],
				a[1] * b[0]  + a[5] * b[1]  + a[9] * b[2]  + a[13] * b[3],
				a[2] * b[0]  + a[6] * b[1]  + a[10] * b[2]  + a[14] * b[3],
				a[3] * b[0]  + a[7] * b[1]  + a[11] * b[2]  + a[15] * b[3],
				a[0] * b[4]  + a[4] * b[5]  + a[8] * b[6]  + a[12] * b[7],
				a[1] * b[4]  + a[5] * b[5]  + a[9] * b[6]  + a[13] * b[7],
				a[2] * b[4]  + a[6] * b[5]  + a[10] * b[6]  + a[14] * b[7],
				a[3] * b[4]  + a[7] * b[5]  + a[11] * b[6]  + a[15] * b[7],
				a[0] * b[8]  + a[4] * b[9]  + a[8] * b[10] + a[12] * b[11],
				a[1] * b[8]  + a[5] * b[9]  + a[9] * b[10] + a[13] * b[11],
				a[2] * b[8]  + a[6] * b[9]  + a[10] * b[10] + a[14] * b[11],
				a[3] * b[8]  + a[7] * b[9]  + a[11] * b[10] + a[15] * b[11],
				a[0] * b[12] + a[4] * b[13] + a[8] * b[14] + a[12] * b[15],
				a[1] * b[12] + a[5] * b[13] + a[9] * b[14] + a[13] * b[15],
				a[2] * b[12] + a[6] * b[13] + a[10] * b[14] + a[14] * b[15],
				a[3] * b[12] + a[7] * b[13] + a[11] * b[14] + a[15] * b[15]);
}

void Matrix::RotateX(Matrix& matrix, const float angle) {
	float s = sinf(angle);
	float c = cosf(angle);

	float m1 = matrix.values[1],  m2 = matrix.values[2],
		m5 = matrix.values[5], m6 = matrix.values[6],
		m9 = matrix.values[9], m10 = matrix.values[10],
		m13 = matrix.values[13], m14 = matrix.values[14];

	matrix.values[1] = m1 * c + m2 * -s;
	matrix.values[2] = m1 * s + m2 * c;
	matrix.values[5] = m5 * c + m6 * -s;
	matrix.values[6] = m5 * s + m6 * c;
	matrix.values[9] = m9 * c + m10 * -s;
	matrix.values[10] = m9 * s + m10 * c;
	matrix.values[13] = m13 * c + m14 * -s;
	matrix.values[14] = m13 * s + m14 * c;
}

void Matrix::RotateY(Matrix& matrix, const float angle) {
	float s = sinf(angle);
	float c = cosf(angle);
	float m0 = matrix.values[0],  m2 = matrix.values[2],
		m4 = matrix.values[4],  m6 = matrix.values[6],
		m8 = matrix.values[8],  m10 = matrix.values[10],
		m12 = matrix.values[12], m14 = matrix.values[14];

	matrix.values[0] = m0 * c + m2 * s;
	matrix.values[2] = m0 * -s + m2 * c;
	matrix.values[4] = m4 * c + m6 * s;
	matrix.values[6] = m4 * -s + m6 * c;
	matrix.values[8] = m8 * c + m10 * s;
	matrix.values[10] = m8 * -s + m10 * c;
	matrix.values[12] = m12 * c + m14 * s;
	matrix.values[14] = m12 * -s + m14 * c;
}

void Matrix::RotateZ(Matrix& matrix, const float angle) {
	float s = sinf(angle);
	float c = cosf(angle);

	float m0 = matrix.values[0],  m1 = matrix.values[1],
			m4 = matrix.values[4],  m5 = matrix.values[5],
			m8 = matrix.values[8],  m9 = matrix.values[9],
			m12 = matrix.values[12], m13 = matrix.values[13];

	matrix.values[0] = m0 * c + m1 * -s;
	matrix.values[1] = m0 * s + m1 * c;
	matrix.values[4] = m4 * c + m5 * -s;
	matrix.values[5] = m4 * s + m5 * c;
	matrix.values[8] = m8 * c + m9 * -s;
	matrix.values[9] = m8 * s + m9 * c;
	matrix.values[12] = m12 * c + m13 * -s;
	matrix.values[13] = m12 * s + m13 * c;
}

void Matrix::Scale(Matrix& matrix, float s)
{
    return Matrix::Scale(matrix, s, s, s);
}

void Matrix::Scale(Matrix& matrix, float x, float y, float z)
{
	matrix.values[0] *= x;
	matrix.values[4] *= x;
	matrix.values[8] *= x;
	matrix.values[12] *= x;
	matrix.values[1] *= y;
	matrix.values[5] *= y;
	matrix.values[9] *= y;
	matrix.values[13] *= y;
	matrix.values[2] *= z;
	matrix.values[6] *= z;
	matrix.values[10] *= z;
	matrix.values[14] *= z;
}

void Matrix::Translate(Matrix& matrix, float x, float y, float z) {
	matrix.values[0] += matrix.values[3] * x;
	matrix.values[4] += matrix.values[7] * x;
	matrix.values[8] += matrix.values[11] * x;
	matrix.values[12] += matrix.values[15] * x;
    matrix.values[1] += matrix.values[3] * y;
	matrix.values[5] += matrix.values[7] * y;
	matrix.values[9] += matrix.values[11] * y;
	matrix.values[13] += matrix.values[15] * y;
    matrix.values[2] += matrix.values[3] * z;
	matrix.values[6] += matrix.values[7] * z;
	matrix.values[10] += matrix.values[11] * z;
	matrix.values[14] += matrix.values[15] * z;
}

Matrix Matrix::LookAt(Vector3& position, Vector3& target, Vector3& up) {
	Vector3 eyeDirection = (target - position).GetNormalized();
	Vector3 leftDirection = Vector3::Cross(up, eyeDirection).GetNormalized();
	Vector3 upDirection = Vector3::Cross(eyeDirection, leftDirection).GetNormalized();

	Matrix lookAt;
	lookAt.SetColumn(0, leftDirection);
	lookAt.SetColumn(1, upDirection);
	lookAt.SetColumn(2, eyeDirection);
	lookAt.SetColumn(3, position);
	return lookAt;
}

Matrix Matrix::GetFrustrum(float l, float r, float b, float t, float n, float f) {
	Matrix matrix;
	matrix.values[0] = 2.0f * n / (r - l);
	matrix.values[5] = 2.0f * n / (t - b);
	matrix.values[8] = (r + l) / (r - l);
	matrix.values[9] = (t + b) / (t - b);
	matrix.values[10] = -(f + n) / (f - n);
	matrix.values[11] = -1.0f;
	matrix.values[14] = -(2.0f * f * n) / (f - n);
	matrix.values[15] = 0.0f;
	return matrix;
}

Matrix Matrix::GetPerspective(float fov, float aspect, float near, float far) {
	float tangent = tanf(fov / 2.0f);
	float height = near * tangent;
	float width = height * aspect;
	return GetFrustrum(-width, width, -height, height, near, far);
}

Matrix Matrix::GetOrtho(float l, float r, float b, float t, float n, float f) {
	Matrix matrix;
	matrix.values[0] = 2.0f / (r - l);
	matrix.values[5] = 2.0f / (t - b);
	matrix.values[10] = -2.0f / (f - n);
	matrix.values[12] = -(r + l) / (r - l);
	matrix.values[13] = -(t + b) / (t - b);
	matrix.values[14] = -(f + n) / (f - n);
	return matrix;
}

float Matrix::operator[](unsigned int i) const
{
	return values[i];
}

float& Matrix::operator[](unsigned int  i)
{
	return values[i];
}


bool operator==(const Matrix& lhs, const Matrix& rhs)
{
	return lhs.Equals(rhs);
}

bool operator!=(const Matrix& lhs, const Matrix& rhs)
{
	return !lhs.Equals(rhs);
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs)
{
	return Matrix::Add(lhs, rhs);
}

Matrix operator-(const Matrix& lhs, const Matrix& rhs)
{
	return Matrix::Sub(lhs, rhs);
}

Matrix operator*(const Matrix& lhs, const Matrix& rhs)
{
	return Matrix::Mul(lhs, rhs);
}

std::ostream& operator<<(std::ostream& os, const Matrix& m)
{
	os << std::fixed << std::setprecision(5);
	os << "[" << std::setw(10) << m[0] << " " << std::setw(10) << m[4] << " " << std::setw(10) << m[8]  <<  " " << std::setw(10) << m[12] << "]\n"
		<< "[" << std::setw(10) << m[1] << " " << std::setw(10) << m[5] << " " << std::setw(10) << m[9]  <<  " " << std::setw(10) << m[13] << "]\n"
		<< "[" << std::setw(10) << m[2] << " " << std::setw(10) << m[6] << " " << std::setw(10) << m[10] <<  " " << std::setw(10) << m[14] << "]\n"
		<< "[" << std::setw(10) << m[3] << " " << std::setw(10) << m[7] << " " << std::setw(10) << m[11] <<  " " << std::setw(10) << m[15] << "]\n";
	os << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
	return os;
}
