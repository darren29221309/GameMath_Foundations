#include <iostream>
#include <thread> // 為了讓文字輸出不要跑太快，可用 this_thread::sleep_for
#include <chrono>
#include <cmath>
#include <memory>
#include <vector>
#include "MathLib.h"
#include "AABB.h"
#include "SceneNode.h"
#include "GuardAI.h"


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
    thief->SetLocalPosition(Vector3(0, 10, 0)); // 小偷在 (0, 10, 0)

    // 建立守衛 (Guard)
    // 注意：這裡是 make_unique<GuardAI>
    auto guard = std::make_unique<GuardAI>();
    guard->SetLocalPosition(Vector3(0, 0, 0));
    guard->SetRotationZ(90.0f); // 面向 +Y，背對小偷
    guard->RotationSpeed = 60.0f;

    // ==========================================
    // 2. 設定關聯 (最重要的一步)
    // ==========================================

    // A. 設定目標 (SetTarget)
    // Guard 需要知道小偷在哪裡，但不需要 "擁有" 小偷。
    // 所以我們用 .get() 取得 Raw Pointer 傳進去。
    guard->SetTarget(thief.get());

    // B. 建立場景樹 (Scene Tree)
    // 我們建立一個 Root 節點來管理所有人
    auto root = std::make_unique<SceneNode>();

    // 關鍵：將 guard 和 thief 的擁有權 "移交 (Move)" 給 root
    // ?? 注意：這行執行後，變數 'guard' 和 'thief' 就變成 nullptr 了！
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

        // --- 這裡有個小麻煩 ---
        // 因為 guard 已經被 move 進去了，我們手上的 'guard' 變數是空的。
        // 所以沒辦法直接呼叫 guard->GetRotationZ() 來印 Log。

        // 為了簡單起見，我們這次先不印詳細 Log，
        // 或者你可以只依賴 GuardAI 內部 SetState 印出的 "State Changed" Log。

        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    std::cout << "\n[End of Main] Root will be destroyed automatically.\n";
    // 當 main 結束，root 會自動解構 -> 守衛和小偷也會自動解構 -> 完全無 Memory Leak

    std::system("pause");
    return 0;
}