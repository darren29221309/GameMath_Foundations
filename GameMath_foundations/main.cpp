#include <iostream>
#include <thread> // 為了讓文字輸出不要跑太快，可用 this_thread::sleep_for
#include <chrono>
#include <cmath>
#include "MathLib.h"
#include "AABB.h"
#include "SceneNode.h"







bool CheckInSight(const SceneNode& oberver,const SceneNode& target,float halfAngleCos) {
    // ==========================================
    // TODO: 請在此處實作你的數學邏輯
    // ==========================================

    // 1. 取得世界座標 (GetWorldPosition)
    Vector3 obeVec = oberver.GetWorldPosition();
    Vector3 tarVec = target.GetWorldPosition();
    // 2. 計算方向向量 (target - observer) 並 Normalize
    // (這需要你在 MathLib 裡實作 operator-)
    Vector3 dir = tarVec - obeVec;
    dir.Normalize();
    // 3. 取得守衛的正前方向量
    // 利用 observer.GetWorldTransform().TransformVector(Vector3(1,0,0))
    Vector3 obeForwardDirection = oberver.GetWorldTransform().TransformVector(Vector3(1, 0, 0));
    obeForwardDirection.Normalize();

    // 4. 計算點積 (Dot)
    float dotResult = dir.Dot(obeForwardDirection);

    // 5. 回傳 (Dot > halfAngleCos)

    return dotResult > halfAngleCos; // 暫時回傳 false，等你寫好邏輯
}

class GuardAI : public SceneNode {
public:
    enum class AIState { Patrol, Alert };
    void SetTarget(SceneNode* target) { m_Target = target; }
    AIState GetState() const { return m_State; }
    float RotationSpeed = 90.0f;
    static const float VIEW_COS;
    void Update(float deltaSeconds) override {

        if (m_Target == nullptr) {
            SceneNode::Update(deltaSeconds);
            return;
        }

        switch (m_State) {
        case AIState::Patrol:
        {
            //巡邏
            float newAngle = GetRotationZ() + (RotationSpeed * deltaSeconds);
            SetRotationZ(newAngle);
            if (CheckInSight(*this, *m_Target, VIEW_COS)) {
                SetState(AIState::Alert);
            }
            break;
        }


        case AIState::Alert:
            //警戒
            if (!CheckInSight(*this, *m_Target, VIEW_COS)) {
                SetState(AIState::Patrol);
            }
            break;
        }

        SceneNode::Update(deltaSeconds);
    }
private:
    AIState m_State = AIState::Patrol;
    SceneNode* m_Target = nullptr;

    void SetState(AIState newState) {
        if (m_State == newState)return;

        std::cout << "State Changed: " << (int)m_State << " -> " << (int)newState << "\n";

        m_State = newState;
    }
};
const float GuardAI::VIEW_COS = 0.707106f;


int main() {
    // --- 1. 初始化場景 (Setup Scene) ---
    // 重新 Setup :
    GuardAI guard;
    guard.SetLocalPosition(Vector3(0, 0, 0)); // 守衛在中心
    guard.RotationSpeed = 60.0f;

    SceneNode thief;
    // 注意：這裡不設父子關係 (No SetParent)
    // 小偷固定在世界座標 (0, 10, 0)
    thief.SetLocalPosition(Vector3(0, 10, 0));
 
    guard.SetTarget(&thief);

    std::cout << "--- Phase 6: FSM Test (Guard vs Thief) ---\n";
    std::cout << "Guard at (0,0), Thief at (10,0)\n";
    std::cout << "Expected: Patrol -> Alert (when looking at Thief)\n\n";

    float dt = 0.1f;
    const int totalFrames = 80;


    for (int fps = 0; fps <= totalFrames; fps++) {
        // 守衛原地自轉
        guard.Update(dt);

        float currentAngle = guard.GetRotationZ();

        // 取得狀態字串
        const char* stateStr = "UNKNOWN";
        if (guard.GetState() == GuardAI::AIState::Patrol) stateStr = "PATROL";
        else if (guard.GetState() == GuardAI::AIState::Alert)  stateStr = "ALERT !!!";

        printf("Frame [%2d] | Angle: %5.1f | State: %s\n",
            fps, currentAngle, stateStr);

        // --- C. 模擬幀率 (Sleep) ---
        // 讓 Console 不要跑太快，方便肉眼觀察
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    
   
    std::cout << "\nTest Finished.\n";
    std::system("pause");
    return 0;
}