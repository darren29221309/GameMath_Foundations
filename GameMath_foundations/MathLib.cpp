#include "MathLib.h" 
#include <cmath>    
#include <iostream> 
// 構造函式的實作
Vector3::Vector3(float InX, float InY, float InZ)
    : X(InX), Y(InY), Z(InZ) {
}

// 內積實作
float Vector3::Dot(const Vector3& Other) const {
    return (X * Other.X) + (Y * Other.Y) + (Z * Other.Z);
}

// 外積實作
Vector3 Vector3::Cross(const Vector3& Other) const {
    return Vector3(
        Y * Other.Z - Z * Other.Y,
        Z * Other.X - X * Other.Z,
        X * Other.Y - Y * Other.X
    );
}

// 長度平方實作
float Vector3::SizeSquared() const {
    return X * X + Y * Y + Z * Z;
}

// 正規化實作
void Vector3::Normalize() {
    float Length = std::sqrt(SizeSquared());
    if (Length > 0.00001f) {
        X /= Length;
        Y /= Length;
        Z /= Length;
    }
}

Matrix4x4::Matrix4x4() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            m[i][j] = (i == j) ? 1.0f : 0.0f;
        }
    }
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& other) const {
    Matrix4x4 result;
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            float sum = 0.0f;
            for (int k = 0; k < 4; k++) {
                sum += m[row][k] * other.m[k][col];
            }
            result.m[row][col] = sum;
        }
    }
    return result;
}

Matrix4x4 Matrix4x4::CreateRotationZ(float degree) {
    Matrix4x4 res; 
    float rad = degree * (3.14159265f / 180.0f);
    float c = std::cos(rad);
    float s = std::sin(rad);

    res.m[0][0] = c;  res.m[0][1] = s;
    res.m[1][0] = -s; res.m[1][1] = c;

    return res;
}

Vector3 Matrix4x4::TransformVector(const Vector3& v) const {
    Vector3 res;
    res.X = v.X * m[0][0] + v.Y * m[1][0] + v.Z * m[2][0] + m[3][0];
    res.Y = v.X * m[0][1] + v.Y * m[1][1] + v.Z * m[2][1] + m[3][1];
    res.Z = v.X * m[0][2] + v.Y * m[1][2] + v.Z * m[2][2] + m[3][2];
    return res;
}