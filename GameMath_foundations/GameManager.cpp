#include "GameManager.h"


GameManager::GameManager() {};

void GameManager::AddScore(int value) {
	Score+=value;
}

GameManager& GameManager::GetInstance() {
	static GameManager instance;
	return instance;
}
