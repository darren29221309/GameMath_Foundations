#include <iostream>
#include <cmath>
#include <iomanip>
#include "MathLib.h"
#include "AABB.h"

const float PI = 3.14159265359f;

int main() {
	AABB playerBox;
	playerBox.Update(Vector3(0.5f,0.0f,0.0f),Vector3(1,1,1)); // 玩家半徑為 1

	AABB wallBox;
	wallBox.Update(Vector3(2, 0, 0), Vector3(1, 1, 1)); // 牆在 X=2 的位置

	CollisionInfo info =  playerBox.GetCollisionInfo(wallBox);

	printf("碰到:%s\nX:%f Y:%f Z:%f\n",info.bIsHit?"true":"false",info.OverlapX,info.OverlapY,info.OverlapZ);

	std::system("pause");
	return 0;
}