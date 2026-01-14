#include "SceneNode.h"
#include <cmath>
#include <iostream>
#include <algorithm>
#include <memory>
#include <vector>

SceneNode::SceneNode()
	:localPosition(0, 0, 0)
	, localScale(1, 1, 1)
	, localRotationZ(0.0f)
	, bIsDirty(true)
{
}

SceneNode::~SceneNode() {
	std::cout << "SceneNode Destroyed" << std::endl;
}

void SceneNode::SetDirty() {
	if (bIsDirty)return;
	bIsDirty = true;

	for (const auto& child : m_Children) {
		child->SetDirty();
	}
}

void SceneNode::AddChild(std::unique_ptr<SceneNode> child) {

	if (child == nullptr)return;

	child->m_Parent = this;

	m_Children.push_back(std::move(child));
}


void SceneNode::SetLocalPosition(const Vector3& pos) {
	localPosition = pos;
	SetDirty();
}

void SceneNode::SetLocalScale(const Vector3& scale) {
	localScale = scale;
	SetDirty();
}

void SceneNode::SetRotationZ(float angle) {
	localRotationZ = angle;
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

	if (m_Parent) {
		//有父節點: world = local * ParentWorld
		worldTransform = localTransform * m_Parent->GetWorldTransform();
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

void SceneNode::Update(float deltaSeconds) {
	for (const auto& child : m_Children) {
		child->Update(deltaSeconds);
	}
}
