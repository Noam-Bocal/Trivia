#pragma once
#include <string.h>
#include <iostream>
#include <vector>
#include <map>
#include "Question.h"
#include "LoggedUser.h"
#include "Helper.h"

struct GameData
{
    Question currentQuestion;
    unsigned int correctAnswerCount;
    unsigned int wrongAnswerCount;
    unsigned int averageAnswerTime;

    GameData() : currentQuestion("", "", "", "", "", 0), correctAnswerCount(0), wrongAnswerCount(0), averageAnswerTime(0)
    {}

    GameData(const Question& question) : currentQuestion(question), correctAnswerCount(0), wrongAnswerCount(0), averageAnswerTime(0)
    {}
};


class Game
{
public:
    int countPlayers;
    Game(list<Question> questions, vector<LoggedUser> players, int gameId);
    ~Game();
    Question getQuestionForUser(LoggedUser user);
    bool submitAnswer(LoggedUser user, unsigned int answerId);
    unsigned int getID();
    std::map<LoggedUser, GameData> getUsersData();
    void removePlayer(LoggedUser user);
    int nextQuestion(Question q, LoggedUser user)
    {
        int i = 0;
        for (auto& question : m_questions)
        {
            if (question.getQuestion() == q.getQuestion())
            {
                if (i + 1 == m_questions.size()) //no more questions
                {
                    m_players[user].currentQuestion = Question("", "", "", "", "", 5);
                    return 1;
                }
                m_players[user].currentQuestion = m_questions[i+1];
                return 0;
            }
            i++;
        }

    }
    int getNumOfQuestions();

private:
    std::vector<Question> m_questions;
    std::map<LoggedUser, GameData> m_players;
    int m_gameId;
};