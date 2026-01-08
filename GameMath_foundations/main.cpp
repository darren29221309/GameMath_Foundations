#include <iostream>
#include <cmath>
#include <iomanip>
#include "MathLib.h"
#include "AABB.h"

const float PI = 3.14159265359f;

int main() {
	AABB playerBox;


	Vector3 minCorner(-1, -1, -1);
	Vector3 maxCorner(1, 1, 1);
	AABB enemyBox(minCorner, maxCorner);



	std::cout<<enemyBox.Intersects(playerBox)<< std::endl;
	std::system("pause");
	return 0;
}