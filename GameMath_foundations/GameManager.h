#pragma once
#include "IObserver.h"
#include <iostream>

class GameManager:public IObserver {
public:
	static GameManager& GetInstance();



	int Score = 0;
	void AddScore(int value);

	//¤¶­±¨ç¼Æ
	void OnNotify(const std::string& eventName, int parameter) override {
		if (eventName == "TargetSpotted") {
			std::cout << "[GameManager] Received event: " << eventName << ". Add score: " << parameter << "\n";
			AddScore(parameter);
		}
	}
private:
	GameManager();

	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;



};