#pragma once // 防止重複 include
#include "SceneNode.h"
#include <iostream>
#include <cmath>

// 簡單的 AI 測試類別
class GuardAI : public SceneNode {
public:
    enum class AIState { Patrol, Alert };

    // 參數調整
    float RotationSpeed = 90.0f;

    // 設定目標 (注意：這裡用 Raw Pointer 是對的，因為我們只是"看"它，不"擁有"它)
    void SetTarget(SceneNode* target) { m_Target = target; }

    void Update(float deltaSeconds) override {
        // 1. 如果沒目標，就當一般物件更新
        if (m_Target == nullptr) {
            SceneNode::Update(deltaSeconds);
            return;
        }

        // 2. 狀態機邏輯
        switch (m_State) {
        case AIState::Patrol:
            // 轉身
        {
            float newAngle = GetRotationZ() + (RotationSpeed * deltaSeconds);
            SetRotationZ(newAngle);

            // 檢查是否看到目標
            if (CheckInSight()) {
                SetState(AIState::Alert);
            }
        }
        break;

        case AIState::Alert:
            // 發現目標！停止轉動，死盯著看
            // 如果目標跑出視野 (這裡簡化判斷，假設一直盯著)
            if (!CheckInSight()) {
                SetState(AIState::Patrol);
            }
            break;
        }

        // 3. 記得呼叫父類別更新 (讓子節點也能更新)
        SceneNode::Update(deltaSeconds);
    }

private:
    AIState m_State = AIState::Patrol;
    SceneNode* m_Target = nullptr;

    // 視野常數 (45度)
    const float VIEW_COS = 0.707106f;

    void SetState(AIState newState) {
        if (m_State == newState) return;

        // 簡單印出狀態切換
        std::cout << ">>> [AI State Change] "
            << (m_State == AIState::Patrol ? "Patrol" : "Alert")
            << " -> "
            << (newState == AIState::Patrol ? "Patrol" : "Alert")
            << "\n";

        m_State = newState;
    }

    bool CheckInSight() {
        if (!m_Target) return false;

        // 1. 算出方向向量
        Vector3 myPos = GetWorldPosition();
        Vector3 targetPos = m_Target->GetWorldPosition();
        Vector3 dirToTarget = targetPos - myPos;
        dirToTarget.Normalize();

        // 2. 算出自己面對的方向 (假設由矩陣變換算出來)
        // 這裡用簡單做法：直接算目前角度的向量
        // (注意：你的 MathLib 如果有 TransformVector 也可以用那個)
        float rad = GetRotationZ() * 3.14159f / 180.0f;
        Vector3 myForward(std::cos(rad), std::sin(rad), 0.0f);

        // 3. 點積判斷
        float dot = dirToTarget.Dot(myForward);
        return dot > VIEW_COS;
    }
};