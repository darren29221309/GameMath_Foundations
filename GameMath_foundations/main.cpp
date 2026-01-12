#include <iostream>
#include <cmath>
#include <iomanip>
#include <chrono>
#include <thread>
#include <Windows.h>
#include "MathLib.h"
#include "AABB.h"
#include "SceneNode.h"

const float PI = 3.14159265359f;

int main() {

	SceneNode sun;
	sun.SetLocalPosition(Vector3(0, 0, 0));

	SceneNode earth;
	earth.SetLocalPosition(Vector3(10, 0, 0));
	earth.SetParent(&sun);

	AABB earthBox(Vector3(-1, -1, -1), Vector3(1, 1, 1));

	std::cout << "--Rotation Test--" << std::endl;

	for (int i = 0; i <= 4; i++) {
		float angle = i * 45.0f;
		sun.SetRotationZ(angle);

		Matrix4x4 earthMatrix = earth.GetWorldTransform();

		earthBox.Update(earthMatrix);

		printf("Angle: %.0f | Box Min: (%.1f, %.1f) | Box Max: (%.1f, %.1f)\n",
			angle,
			earthBox.Min.X,
			earthBox.Min.Y,
			earthBox.Max.X,
			earthBox.Max.Y);

	}


	std::system("pause");
	return 0;
}