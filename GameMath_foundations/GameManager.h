#pragma once


class GameManager {
public:
	static GameManager& GetInstance();



	int Score = 0;

	void AddScore(int value);

private:
	GameManager();

	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;



};