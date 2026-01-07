#pragma once

struct Vector3 {
	float X, Y, Z;

	Vector3(float InX = 0.0f, float InY = 0.0f, float InZ = 0.0f);

	float Dot(const Vector3& Other) const;
	Vector3 Cross(const Vector3& Other) const;
	float SizeSquared() const;
	void Normalize();
};

struct Matrix4x4 {
	float m[4][4];

	Matrix4x4();

	//旋轉矩陣
	static Matrix4x4 CreateRotationZ(float degree);
	//變換向量
	Vector3 TransformVector(const Vector3& v)const;
	//矩陣乘法
	Matrix4x4 operator*(const Matrix4x4& other) const;

};