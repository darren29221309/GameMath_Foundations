#include <iostream>
#include <cmath>
#include <iomanip>
#include "MathLib.h"
#include "AABB.h"

const float PI = 3.14159265359f;

int main() {
	AABB playerBox;
	playerBox.LocalHalfSize = { 1.0f, 1.0f, 1.0f }; // 玩家半徑為 1

	AABB wallBox;
	wallBox.Update(Vector3(5, 0, 0), Vector3(1, 1, 1)); // 牆在 X=5 的位置

	for (float s = 1.0f; s <= 5.0f; s += 0.5f) {
		//玩家不動
		playerBox.Update(Vector3(0, 0, 0), Vector3(s, 1, 1));

		bool hit = playerBox.Intersects(wallBox);

		printf("Scale: %.f | Player Max X: %.1f | Wall Min X: %.1f | Collision: %s\n",
			s, playerBox.Max.X, wallBox.Min.X, hit ? "BOOM!" : "Safe");
	}


	std::system("pause");
	return 0;
}