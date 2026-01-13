#include <iostream>
#include <thread> // 為了讓文字輸出不要跑太快，可用 this_thread::sleep_for
#include <chrono>
#include "MathLib.h"
#include "AABB.h"
#include "SceneNode.h"

int main() {
    // --- 1. 初始化場景 (Setup Scene) ---

    // A. 太陽系統
    SceneNode sun;
    sun.SetLocalPosition(Vector3(0, 0, 0));

    SceneNode earth;
    earth.SetParent(&sun);
    earth.SetLocalPosition(Vector3(10, 0, 0)); // 地球在太陽右邊 10 單位

    // 定義地球的碰撞盒形狀 (半徑為 1 的方塊)
    // 注意：這只是「原始形狀」，還沒被放到世界中
    AABB earthShape(Vector3(-1, -1, -1), Vector3(1, 1, 1));

    // B. 隕石 (靜止障礙物)
    SceneNode asteroid;
    asteroid.SetLocalPosition(Vector3(0, 10, 0)); // 放在 (0, 10, 0) 也就是 90 度的位置

    // 定義隕石的碰撞盒形狀 (大一點，半徑為 2)
    AABB asteroidShape(Vector3(-2, -2, -2), Vector3(2, 2, 2));

    // 因為隕石不會動，我們可以先更新一次它的 AABB，或者在迴圈裡更新也可以
    // 為了保險起見，我們養成好習慣：在迴圈裡更新所有東西
    AABB earthWorldAABB = earthShape;     // 準備兩個變數來存「世界空間」的 AABB
    AABB asteroidWorldAABB = asteroidShape;

    std::cout << "--- Simulation Start: Earth vs Asteroid ---" << std::endl;

    // --- 2. 遊戲迴圈 (Game Loop) ---
    // 模擬 0 到 100 度
    for (int angle = 0; angle <= 100; angle += 5) {

        // --- Logic Update (邏輯更新) ---
        sun.SetRotationZ((float)angle); // 太陽轉動 -> 帶動地球

        // ==========================================
        // TODO: 請在此處實作物理更新與碰撞檢測
        // ==========================================

        // 步驟 1: 獲取 Earth 和 Asteroid 最新的 World Transform (矩陣)
        Matrix4x4 earthMatrix = earth.GetWorldTransform();
        Matrix4x4 asteroidMatrix = asteroid.GetWorldTransform();

        // 步驟 2: 使用矩陣更新 earthWorldAABB 和 asteroidWorldAABB
        // 注意：要用 Update() 函數
        earthWorldAABB.Update(earthMatrix);
        asteroidWorldAABB.Update(asteroidMatrix);

        // 步驟 3: 檢查是否碰撞 (Intersects)
        // 如果撞到了：
        //    1. 印出 "BOOM! Collision at angle: " << angle
        //    2. break 跳出迴圈 (模擬遊戲結束)
        if (earthWorldAABB.Intersects(asteroidWorldAABB)) {
            printf("BOOM! Collision at angle: %d\n", angle);
            break;
        }

        // ==========================================
        // Debug 輸出 (沒撞到時顯示位置)
        // 為了不讓畫面太亂，你可以只印 Earth 的位置
        Vector3 earthPos = earth.GetWorldPosition();
        printf("Angle: %d | Earth Pos: (%.1f, %.1f)\n", angle, earthPos.X, earthPos.Y);

        // 稍微暫停一下，讓你能在 Console 看到過程
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::system("pause");
    return 0;
}