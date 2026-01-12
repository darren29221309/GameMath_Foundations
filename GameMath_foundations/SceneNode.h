#pragma once
#include "MathLib.h"
#include <vector>
#include <algorithm>


class SceneNode {
private:
	Vector3 localPosition;
	Vector3 localScale;
	float localRotationZ;

	//¶¥¼h
	SceneNode* parent = nullptr;
	std::vector<SceneNode*> children;


	//Dirty Flag
	mutable bool bIsDirty;
	mutable Matrix4x4 worldTransform;

protected:
	void UpdateTransform() const;

	void SetDirty();

public:
	SceneNode();

	void SetParent(SceneNode* newParent);
	void SetLocalPosition(const Vector3& pos);
	void SetLocalScale(const Vector3& scale);
	void SetRotationZ(float rot);

	Vector3 GetWorldPosition() const;
	const Matrix4x4& GetWorldTransform() const;
	Vector3 GetLocalPosition() const { return localPosition; }

	void AddChild(SceneNode* child);
	void RemoveChild(SceneNode* child);

};