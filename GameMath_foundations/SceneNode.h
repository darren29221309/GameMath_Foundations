#pragma once
#include "MathLib.h"
#include <vector>
#include <algorithm>
#include <memory>


class SceneNode {
private:
	Vector3 localPosition;
	Vector3 localScale;
	float localRotationZ;

	//¶¥¼h
	SceneNode* m_Parent = nullptr;
	std::vector<std::unique_ptr<SceneNode>> m_Children;


	//Dirty Flag
	mutable bool bIsDirty;
	mutable Matrix4x4 worldTransform;

protected:
	void UpdateTransform() const;

	void SetDirty();

public:
	SceneNode();

	//Setter
	void SetLocalPosition(const Vector3& pos);
	void SetLocalScale(const Vector3& scale);
	void SetRotationZ(float angle);

	//Getter
	Vector3 GetWorldPosition() const;
	Vector3 GetLocalPosition() const { return localPosition; }
	const Matrix4x4& GetWorldTransform() const;
	float GetRotationZ() const { return localRotationZ; }

	void AddChild(std::unique_ptr<SceneNode> child);

	virtual void Update(float deltaSeconds);

	virtual ~SceneNode();

};