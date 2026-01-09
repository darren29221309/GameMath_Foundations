#pragma once
#include "MathLib.h"

//計算兩個AABB 重疊的深度(OverLapping Depth)
struct CollisionInfo {
	bool bIsHit;
	float OverlapX;
	float OverlapY;
	float OverlapZ;
};


struct AABB {
	Vector3 Min;
	Vector3 Max;
	Vector3 LocalHalfSize = { 1.0f,1.0f,1.0f };//default 1

	AABB();
	AABB(Vector3 min, Vector3 max);

	//判斷使否碰撞
	bool Intersects(const AABB& Other)const;


	//根據世界矩陣更新碰撞盒
	void Update(const Vector3& WorldPos, const Vector3& Scale);

	CollisionInfo GetCollisionInfo(const AABB& Other) const;

};
