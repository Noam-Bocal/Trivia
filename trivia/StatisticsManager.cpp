#include "StatisticsManager.h"

StatisticsManager::StatisticsManager(IDatabase* database) : m_database(database)
{ /**/ }

vector<pair<string, int>> StatisticsManager::getHighScore()
{
	return m_database->getHighScores();
}

int StatisticsManager::getUserStatistics(string username)
{
	return m_database->getPlayerScore(username);
}
