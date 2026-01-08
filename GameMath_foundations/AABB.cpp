#include "AABB.h"

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
	Vector3 halfSize = Vector3(1.0f, 1.0f, 1.0f);
	Min.X = WorldPos.X - (halfSize.X * Scale.X);
	Max.X = WorldPos.X + (halfSize.X * Scale.X);

	Min.Y = WorldPos.Y - (halfSize.Y * Scale.Y);
	Max.Y = WorldPos.Y + (halfSize.Y * Scale.Y);

	Min.Z = WorldPos.Z - (halfSize.Z * Scale.Z);
	Max.Z = WorldPos.Z + (halfSize.Z * Scale.Z);
}



