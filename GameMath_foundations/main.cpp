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


int main() {
	float degree = 330.0f;
	float radian = degree * (PI / 180.0f);

	Vector3 EnemyForward = { 1.0, 0.0f, 0.0f };
	
	Vector3 DirToPlayer = {
		std::cos(radian),
		std::sin(radian),
		0.0f
	};

	Vector3 crossResult = EnemyForward.Cross(DirToPlayer);

	std::cout <<"cross result(z-axis): " << crossResult.Z << std::endl;

	
	std::system("pause");
	return 0;
}