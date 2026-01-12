#include "SceneNode.h"
#include <cmath>

SceneNode::SceneNode()
	:localPosition(0, 0, 0)
	, localScale(1, 1, 1)
	, localRotationZ(0.0f)
	, bIsDirty(true)
{
}

void SceneNode::SetDirty() {
	if (bIsDirty)return;
	bIsDirty = true;

	for (SceneNode* child : children) {
		child->SetDirty();
	}
}


void SceneNode::SetParent(SceneNode* newParent) {
	//原有父節點
	if (parent) {
		parent->RemoveChild(this);
	}

	parent = newParent;
	if (parent) {
		parent->AddChild(this);
	}

	SetDirty();
}

void SceneNode::AddChild(SceneNode* child) {
	children.push_back(child);
}

void SceneNode::RemoveChild(SceneNode* child) {
	auto it = std::remove(children.begin(), children.end(), child);
	children.erase(it, children.end());
}


void SceneNode::SetLocalPosition(const Vector3& pos) {
	localPosition = pos;
	SetDirty();
}

void SceneNode::SetLocalScale(const Vector3& scale) {
	localScale = scale;
	SetDirty();
}

void SceneNode::SetRotationZ(float rot) {
	localRotationZ = rot;
	SetDirty();
}

void SceneNode::UpdateTransform() const {
	//判斷是否需要重算
	if (!bIsDirty)return;

	//局部變換矩陣
	//縮放->旋轉->位移
	//M_local = S * R * T

	//1.縮放
	Matrix4x4 matScale;
	matScale.m[0][0] = localScale.X;
	matScale.m[1][1] = localScale.Y;
	matScale.m[2][2] = localScale.Z;

	//2.旋轉
	Matrix4x4 matRot = Matrix4x4::CreateRotationZ(localRotationZ);

	//3.位移
	Matrix4x4 matTrans;
	matTrans.m[3][0] = localPosition.X;
	matTrans.m[3][1] = localPosition.Y;
	matTrans.m[3][2] = localPosition.Z;

	//4.組合
	Matrix4x4 localTransform = matScale * matRot * matTrans;

	if (parent) {
		//有父節點: world = local * ParentWorld
		worldTransform = localTransform * parent->GetWorldTransform();
	}
	else {
		worldTransform = localTransform;
	}

	bIsDirty = false;
}

Vector3 SceneNode::GetWorldPosition() const {
	UpdateTransform();

	//提取位移
	return Vector3(
		worldTransform.m[3][0],
		worldTransform.m[3][1],
		worldTransform.m[3][2]
	);
}

const Matrix4x4& SceneNode::GetWorldTransform() const {
	UpdateTransform();
	return worldTransform;
}