#include <iostream>
#include <thread> // 為了讓文字輸出不要跑太快，可用 this_thread::sleep_for
#include <chrono>
#include <cmath>
#include "MathLib.h"
#include "AABB.h"
#include "SceneNode.h"

class RotatorNode :public SceneNode {
public:
    float RotationSpeed = 90.0f;
    void Update(float deltaSeconds) override {
        //1.算出這幀該轉多少
        float currentAngle = GetRotationZ();
        //2.計算新角度
        float newAngle = currentAngle + (RotationSpeed * deltaSeconds);

        SetRotationZ(newAngle);
        SceneNode::Update(deltaSeconds);
    }
};



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




int main() {
    // --- 1. 初始化場景 (Setup Scene) ---
    // 重新 Setup :
    RotatorNode guard;
    guard.SetLocalPosition(Vector3(0, 0, 0)); // 守衛在中心
    guard.RotationSpeed = 45.0f;

    SceneNode thief;
    // 注意：這裡不設父子關係 (No SetParent)
    // 小偷固定在世界座標 (10, 0, 0)
    thief.SetLocalPosition(Vector3(10, 0, 0));
 

    float fovThreshold = std::cos(45.0f * 3.1415926f / 180.0f);

    std::cout << "--- Polymorphism Test: Auto-Rotating Sun ---" << std::endl;

    float dt = 0.1f;


    for (int fps = 0; fps <= 60; fps++) {
        // 守衛原地自轉
        guard.Update(dt);

        // 檢查視線
        bool bSeen = CheckInSight(guard, thief, fovThreshold);

        if (bSeen) {
            printf("Frame %2d (Angle %.1f) | [!] I SEE YOU!\n", fps, guard.GetRotationZ());
        }
        else {
            printf("Frame %2d (Angle %.1f) | ...\n", fps, guard.GetRotationZ());
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    
   

    std::system("pause");
    return 0;
}