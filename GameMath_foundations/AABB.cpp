#include "AABB.h"
#include <cmath>

AABB::AABB(Vector3 min,Vector3 max)
	:LocalMin(min),LocalMax(max)
{
	Min = min;
	Max = max;
}

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

void AABB::Update(const Matrix4x4& transform) {
	Vector3 corners[8];
	corners[0] = Vector3(LocalMin.X, LocalMin.Y, LocalMin.Z);
	corners[1] = Vector3(LocalMax.X, LocalMin.Y, LocalMin.Z);
	corners[2] = Vector3(LocalMin.X, LocalMax.Y, LocalMin.Z);
	corners[3] = Vector3(LocalMin.X, LocalMin.Y, LocalMax.Z);
	corners[4] = Vector3(LocalMax.X, LocalMax.Y, LocalMin.Z);
	corners[5] = Vector3(LocalMax.X, LocalMin.Y, LocalMax.Z);
	corners[6] = Vector3(LocalMin.X, LocalMax.Y, LocalMax.Z);
	corners[7] = Vector3(LocalMax.X, LocalMax.Y, LocalMax.Z);

	corners[0] = transform.TransformVector(corners[0]);
	Min.X = corners[0].X;
	Max.X = corners[0].X;
	Min.Y = corners[0].Y;
	Max.Y = corners[0].Y;
	Min.Z = corners[0].Z;
	Max.Z = corners[0].Z;

	for (int i = 1; i < 8; i++) {
		corners[i] = transform.TransformVector(corners[i]);
		if (corners[i].X < Min.X)Min.X = corners[i].X;
		else if (corners[i].X > Max.X)Max.X = corners[i].X;

		if (corners[i].Y < Min.Y)Min.Y = corners[i].Y;
		else if (corners[i].Y > Max.Y)Max.Y = corners[i].Y;

		if (corners[i].Z < Min.Z)Min.Z = corners[i].Z;
		else if (corners[i].Z > Max.Z)Max.Z = corners[i].Z;
	}
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



