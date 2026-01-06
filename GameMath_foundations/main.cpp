#include <iostream>
#include <cmath>
#include <iomanip>

const float PI = 3.14159265359f;

struct Vector3 {
	float X,Y,Z;



	float Dot(const Vector3& Other) const {
		return (X * Other.X) + (Y * Other.Y) + (Z * Other.Z);
	}

	Vector3 Cross(const Vector3& Other) const {
		return Vector3{
			Y * Other.Z - Z * Other.Y,
			Z * Other.X - X * Other.Z,
			X * Other.Y - Y * Other.X
		};
	}

	float SizeSquared() const {
		return X * X + Y * Y + Z * Z;
	}

	void Normalize() {
		float Length = std::sqrt(SizeSquared());
		if (Length > 0.00001f) {
			X /= Length; Y /= Length; Z /= Length;
		}
	}


};

struct Matrix4x4 {
	float m[4][4];

	Matrix4x4() {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				m[i][j] = (i == j) ? 1.0f : 0.0f;
			}
		}
	}

	Matrix4x4 operator*(const Matrix4x4& other) const {
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

};

int main() {
	Matrix4x4 translationMatrix;

	translationMatrix.m[3][0] = 10.0f;
	translationMatrix.m[3][1] = 0.0f;
	translationMatrix.m[3][2] = 0.0f;

	Matrix4x4 translationMatrix2;

	translationMatrix2.m[3][1] = 5.0f;

	Matrix4x4 combineMatrix = translationMatrix * translationMatrix2;

	std::cout << "combined Translation: ("
		<< combineMatrix.m[3][0] << ", "
		<< combineMatrix.m[3][1] << ", "
		<< combineMatrix.m[3][2] << ")" << std::endl;

	
	std::system("pause");
	return 0;
}