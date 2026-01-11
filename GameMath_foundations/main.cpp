#include <iostream>
#include <cmath>
#include <iomanip>
#include "MathLib.h"
#include "AABB.h"

const float PI = 3.14159265359f;

int main() {
	Vector3 playerPos(0.5f, 0.0f, 0.0f);
	Vector3 playerScale(1, 1, 1);

	Vector3 WallPos(3.0f, 0.0f, 0.0f);
	Vector3 WallScale(1, 1, 1);


	AABB playerBox;
	playerBox.Update(playerPos, playerScale); // 玩家半徑為 1

	AABB wallBox;
	wallBox.Update(WallPos, WallScale); // 牆在 X=2 的位置


	//假設這是玩家這一個影格想要移動的方向
	Vector3 velocity(1.0f, 1.0f, 0.0f);

	CollisionInfo info =  playerBox.GetCollisionInfo(wallBox);


	
	if (info.bIsHit) {
		float overlaps[3] = { info.OverlapX,info.OverlapY ,info.OverlapZ };

		//找出最小距離軸
		int minAxis = 0;
		if (overlaps[1] < overlaps[minAxis])minAxis = 1;
		if (overlaps[2] < overlaps[minAxis])minAxis = 2;

		if (minAxis == 0) {
			if (playerPos.X < WallPos.X) playerPos.X -= info.OverlapX;
			else playerPos.X += info.OverlapX;

			velocity.X = 0;
			printf(">>> 撞擊 X 軸: 位置已修正，現改為沿 Y 軸滑動\n");
		}
		else if (minAxis == 1) {
			if (playerPos.Y < WallPos.Y) playerPos.Y -= info.OverlapY;
			else playerPos.Y += info.OverlapY;

			velocity.Y = 0;
			printf(">>> 撞擊 Y 軸: 位置已修正，現改為沿 X 軸滑動\n");
		}
		else {
			if (playerPos.Z < WallPos.Z) playerPos.Z -= info.OverlapZ;
			else playerPos.Z += info.OverlapZ;

			velocity.Z = 0;
			printf(">>> 撞擊 Z 軸：位置已修正\n");
		}

		playerBox.Update(playerPos, playerScale);

	}

	playerPos.X += velocity.X;
	playerPos.Y += velocity.Y;
	playerPos.Z += velocity.Z;

	printf("最終玩家位置: (%.2f, %.2f, %.2f)\n", playerPos.X, playerPos.Y, playerPos.Z);
	std::system("pause");
	return 0;
}