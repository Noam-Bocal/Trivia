#pragma once
#include <WinSock2.h>
#include <iostream>
#include <vector>
#include "Game.h"
#include "Room.h"
#include "SqliteDataBase.h"
#include "IDatabase.h"

class GameManager
{
private:
	IDatabase* m_database;
	std::vector<Game> m_games;

public:
	GameManager(IDatabase* database);
	~GameManager();
	IDatabase* getDB();
	Game createGame(Room room);
	void deleteGame(unsigned int gameId);
	std::vector<Game>& getGames();
};

