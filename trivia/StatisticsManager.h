#pragma once
#include "IDatabase.h"

class StatisticsManager
{
public:
	StatisticsManager(IDatabase* database);
	vector<pair<string, int>> getHighScore();
	int getUserStatistics(string username);

private:
	IDatabase* m_database;
};
