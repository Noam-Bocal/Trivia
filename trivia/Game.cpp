#include "Game.h"

Game::Game(list<Question> questions, vector<LoggedUser> players, int gameId)
{
    for (const auto& question : questions)
    {
        std::vector<std::string> answers = question.getPossibleAnswers();
        Question q(question.getQuestion(), answers[0], answers[1], answers[2], answers[3], question.getCorrectAnswerId());
        m_questions.push_back(q);
    }

    for (const auto& player : players)
    {
        GameData data = { m_questions[0]};
        m_players[player] = data;
    }

    m_gameId = gameId;
    countPlayers = players.size();

}

Game::~Game()
{
}

Question Game::getQuestionForUser(LoggedUser user)
{
    return m_players[user].currentQuestion;
}

void Game::removePlayer(LoggedUser user)
{
    std::map<LoggedUser, GameData>::iterator it = m_players.find(user);
    m_players.erase(it);
}

bool Game::submitAnswer(LoggedUser user, unsigned int answerId)
{
    if (m_players[user].currentQuestion.getCorrectAnswerId() == answerId)
    {
        m_players[user].correctAnswerCount++;
        return true;
    }
    else
    {
        m_players[user].wrongAnswerCount++;
        return false;
    }
}

unsigned int Game::getID()
{
    return m_gameId;
}

std::map<LoggedUser, GameData> Game::getUsersData()
{
    return m_players;
}

int Game::getNumOfQuestions()
{
    return m_questions.size();
}

