#include <iostream>
#include <cmath>
#include <iomanip>
#include "MathLib.h"
#include "AABB.h"

const float PI = 3.14159265359f;

int main() {
	Vector3 playerPos(0.5f, 0.0f, 0.0f);
	Vector3 playerScale(1, 1, 1);

	Vector3 WallPos(2.0f, 0.0f, 0.0f);
	Vector3 WallScale(1, 1, 1);


	AABB playerBox;
	playerBox.Update(playerPos, playerScale); // 玩家半徑為 1

	AABB wallBox;
	wallBox.Update(WallPos, WallScale); // 牆在 X=2 的位置

	CollisionInfo info =  playerBox.GetCollisionInfo(wallBox);

	printf("碰到:%s\nX:%f Y:%f Z:%f\n",info.bIsHit?"true":"false",info.OverlapX,info.OverlapY,info.OverlapZ);

	if (info.bIsHit) {
		float overlaps[3] = { info.OverlapX,info.OverlapY ,info.OverlapZ };

		//找出最小距離軸
		int minAxis = 0;
		if (overlaps[1] < overlaps[minAxis])minAxis = 1;
		if (overlaps[2] < overlaps[minAxis])minAxis = 2;


	}

	std::system("pause");
	return 0;
}