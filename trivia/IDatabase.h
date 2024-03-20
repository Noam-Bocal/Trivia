#pragma once
#include "pch.h"
#include "Question.h"


class IDatabase
{
public:
//V - 1
	virtual bool doesUserExist(string username) = 0;
	virtual bool doesPasswordMatch(string username, string password) = 0;
	virtual void addNewUser(string username, string password, string email) = 0;

//V - 2
	virtual list<Question> getQuestions(int) = 0;
	virtual float getPlayerAverageAnswerTime(string username) = 0;
	virtual int getNumOfCorrectAnswers(string username) = 0;
	virtual int getNumOfTotalAnswers(string username) = 0;
	virtual int getNumOfPlayerGames(string username) = 0;
	virtual int getPlayerScore(string username) = 0;	
	virtual vector<pair<string, int>> getHighScores() = 0;
	virtual void userAnswer(string username, bool correct) = 0;
};

