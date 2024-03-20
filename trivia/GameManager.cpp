#include "GameManager.h"
GameManager::GameManager(IDatabase* database) : m_database(database)
{ /**/
}
GameManager::~GameManager()
{
}

IDatabase* GameManager::getDB()
{
    return m_database;
}

Game GameManager::createGame(Room room)
{
    vector<LoggedUser> players;
    vector<string> users = room.getAllUsers();
    auto start = users.begin(), end = users.end();

    for (start; start != end; ++start)
    {
        players.push_back(LoggedUser(*start));
    }

    Game *game = new Game(m_database->getQuestions(room.getData().numOfQuestionsInGame), players, room.getData().id);
    m_games.push_back(*game);

    return *game;


}

void GameManager::deleteGame(unsigned int gameId)
{
    auto it = std::find_if(m_games.begin(), m_games.end(), [gameId](Game& game) {
        return game.getID() == gameId;
        });

    if (it != m_games.end()) {
        m_games.erase(it);
    }
}

std::vector<Game>& GameManager::getGames()
{
    return m_games;
}




