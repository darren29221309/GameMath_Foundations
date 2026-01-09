#include "AABB.h"
#include <cmath>

AABB::AABB() :Min(0, 0, 0), Max(0, 0, 0) {}
AABB::AABB(Vector3 min,Vector3 max):Min(min),Max(max){}

bool AABB::Intersects(const AABB& Other)const {

	//檢查X軸是否分開
	if (Max.X < Other.Min.X || Min.X > Other.Max.X) return false;
	//檢查Y軸是否分開
	if (Max.Y < Other.Min.Y || Min.Y > Other.Max.Y) return false;
	//檢查Z軸是否分開
	if (Max.Z < Other.Min.Z || Min.Z > Other.Max.Z) return false;


	//三軸都沒分開->重疊
	return true;
}

void AABB::Update(const Vector3& WorldPos, const Vector3& Scale) {
	Min.X = WorldPos.X - (LocalHalfSize.X * Scale.X);
	Max.X = WorldPos.X + (LocalHalfSize.X * Scale.X);

	Min.Y = WorldPos.Y - (LocalHalfSize.Y * Scale.Y);
	Max.Y = WorldPos.Y + (LocalHalfSize.Y * Scale.Y);

	Min.Z = WorldPos.Z - (LocalHalfSize.Z * Scale.Z);
	Max.Z = WorldPos.Z + (LocalHalfSize.Z * Scale.Z);
}


float CalculationAxisOverlap(float minA, float maxA, float minB, float maxB) {
	float radiusA = (maxA - minA) * 0.5f;
	float radiusB = (maxB - minB) * 0.5f;
	float centerA = (minA + maxA) * 0.5f;
	float centerB = (minB + maxB) * 0.5f;
	return (radiusA + radiusB) - std::abs(centerA - centerB);
}

CollisionInfo AABB::GetCollisionInfo(const AABB& Other) const {
	CollisionInfo info = { false,0,0,0 };
	

	//如果沒撞到
	if (!Intersects(Other)) return info;

	info.bIsHit = true;

	//計算各軸重疊深度

	info.OverlapX = CalculationAxisOverlap(Min.X, Max.X, Other.Min.X, Other.Max.X);
	info.OverlapY = CalculationAxisOverlap(Min.Y, Max.Y, Other.Min.Y, Other.Max.Y);
	info.OverlapZ = CalculationAxisOverlap(Min.Z, Max.Z, Other.Min.Z, Other.Max.Z);

	return info;


}



