#include <iostream>
#include <thread> // 為了讓文字輸出不要跑太快，可用 this_thread::sleep_for
#include <chrono>
#include <cmath>
#include <memory>
#include <vector>
#include "MathLib.h"
#include "AABB.h"
#include "SceneNode.h"
#include "GameManager.h"
#include "GuardAI.h"


template <typename T>
T* SafeCast(SceneNode* node) {
    // dynamic_cast 是 C++ 內建的安全轉型
    // 如果 node 真的是 T 型別 (或 T 的子類別)，它會回傳指標
    return dynamic_cast<T*>(node);
}


class NamedNode : public SceneNode {
public:
    std::string Name;
    NamedNode(std::string name) :Name(name) {}
    ~NamedNode() override {
        std::cout << "Running Destructor : " << Name << "\n";
    }
};



int main() {
    // ==========================================
    // 1. 建立物件 (使用 make_unique)
    // ==========================================

    // 建立小偷 (Thief)
    // 注意：用 auto 讓編譯器自己推導型別 (std::unique_ptr<SceneNode>)
    auto thief = std::make_unique<SceneNode>();
    thief->SetLocalPosition(Vector3(0, -10, 0)); // 小偷在 (0, 10, 0)

    // 建立守衛 (Guard)
    // 注意：這裡是 make_unique<GuardAI>
    auto guard = std::make_unique<GuardAI>();
    guard->SetLocalPosition(Vector3(0, 0, 0));
    guard->SetRotationZ(0.0f); // 面向 +Y，背對小偷
    guard->RotationSpeed = 60.0f;

    


    SceneNode* rawGuardPtr = guard.get();
    SceneNode* rawThiefPtr = thief.get();

    GuardAI* castedGuard = SafeCast<GuardAI>(rawGuardPtr);

    if (castedGuard) {
        std::cout << "[SafeCast] Success! rawGuard is indeed a GuardAI.\n";
    }
    else {
        std::cout << "[SafeCast] Failed! Something is wrong.\n";
    }

    GuardAI* castedThief = SafeCast<GuardAI>(rawThiefPtr);
    if (castedThief) {
        std::cout << "[SafeCast] Danger! Thief became a Guard?!\n";
    }
    else {
        std::cout << "[SafeCast] Safe! Thief is NOT a GuardAI. (Return nullptr)\n";
    }
    std::cout << "------------------------------\n\n";

    // ==========================================
    // 2. 設定關聯 (最重要的一步)
    // ==========================================

    guard->SetTarget(thief.get());
    guard->AddObserver(&GameManager::GetInstance());
    // B. 建立場景樹 (Scene Tree)
    // 我們建立一個 Root 節點來管理所有人
    auto root = std::make_unique<SceneNode>();

    // 關鍵：將 guard 和 thief 的擁有權 "移交 (Move)" 給 root
    // ⚠️ 注意：這行執行後，變數 'guard' 和 'thief' 就變成 nullptr 了！
    // 所以上面 SetTarget 必須先做！
    root->AddChild(std::move(guard));
    root->AddChild(std::move(thief));

    // ==========================================
    // 3. 遊戲迴圈
    // ==========================================

    float dt = 0.1f;
    const int totalFrames = 80;

    std::cout << "--- Phase 8: Smart Pointer Test ---\n";

    for (int i = 0; i < totalFrames; i++) {
        // 現在只需要呼叫 root 的 Update
        // 它會自動遞迴呼叫底下的小偷和守衛
        root->Update(dt);
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    std::cout << "\n------------------------------------------------\n";
    std::cout << "Final Score: " << GameManager::GetInstance().Score << "\n";
    std::cout << "------------------------------------------------\n";

    std::system("pause");
    return 0;
}