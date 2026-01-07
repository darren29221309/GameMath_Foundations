#include <iostream>
#include <cmath>
#include <iomanip>
#include "MathLib.h"

const float PI = 3.14159265359f;

int main() {
	/*Matrix4x4 translationMatrix;

	translationMatrix.m[3][0] = 10.0f;
	translationMatrix.m[3][1] = 0.0f;
	translationMatrix.m[3][2] = 0.0f;

	Matrix4x4 translationMatrix2;

	translationMatrix2.m[3][1] = 5.0f;

	Matrix4x4 combineMatrix = translationMatrix * translationMatrix2;

	std::cout << "combined Translation: ("
		<< combineMatrix.m[3][0] << ", "
		<< combineMatrix.m[3][1] << ", "
		<< combineMatrix.m[3][2] << ")" << std::endl;*/

	Vector3 playerPos = {1.0f, 0.0f, 0.0f};

	Matrix4x4 rot = Matrix4x4::CreateRotationZ(90.0f);

	Vector3 newPos = rot.TransformVector(playerPos);


	std::cout << "Original: (1, 0, 0)" << std::endl;
	std::cout << "After 90 deg rotation: ("
		<< newPos.X << ", " << newPos.Y << ", " << newPos.Z << ")" << std::endl;

	Matrix4x4 rot90 = Matrix4x4::CreateRotationZ(90.0f);
	Matrix4x4 trans10; trans10.m[3][0] = 10.0f;


	Matrix4x4 finalMatrixA = rot90 * trans10;
	Matrix4x4 finalMatrixB = trans10 * rot90;

	Vector3 resA = finalMatrixA.TransformVector({ 1, 0, 0 });
	Vector3 resB = finalMatrixB.TransformVector({ 1, 0, 0 });
	std::cout << "Original: (1, 0, 0)" << std::endl;
	std::cout << "After 90 deg rotation + 10 translation: ("
		<< resA.X << ", " << resA.Y << ", " << resA.Z << ")" << std::endl;
	std::cout << "After 10 translation + 90 deg rotation: ("
		<< resB.X << ", " << resB.Y << ", " << resB.Z << ")" << std::endl;



	
	std::system("pause");
	return 0;
}