#pragma once
#include "mathLib.h"

struct AABB {
	Vector3 Min;
	Vector3 Max;

	AABB();
	AABB(Vector3 min, Vector3 max);

	//§PÂ_¨Ï§_¸I¼²
	bool Intersects(const AABB& Other)const;


	//®Ú¾Ú¥@¬É¯x°}§ó·s¸I¼²²°
	void Update(const Vector3& WorldPos, const Vector3& Scale);

};
