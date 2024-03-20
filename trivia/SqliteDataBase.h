#pragma once
#include "IDatabase.h"
#include "sqlite3.h"
#include <map>
#include <list>

using std::map;
using std::list;

class SqliteDataBase :public IDatabase
{
public:
    SqliteDataBase(const char* db);
    SqliteDataBase();
    virtual ~SqliteDataBase();
//Static
    static map<string, list<string>> _data;
    static int callback(void* data, int argc, char** argv, char** azColName);

//Methods 1
    virtual bool doesUserExist(string username) override;
    virtual bool doesPasswordMatch(string username, string password) override;
    virtual void addNewUser(string username, string password, string email) override;

//methods 2
    virtual list<Question> getQuestions(int) override;
    virtual float getPlayerAverageAnswerTime(string username) override;
    virtual int getNumOfCorrectAnswers(string username) override;
    virtual int getNumOfTotalAnswers(string username) override;
    virtual int getNumOfPlayerGames(string username) override;
    virtual int getPlayerScore(string username) override;
    virtual vector<pair<string, int>> getHighScores() override;
    virtual void userAnswer(string username, bool correct) override;
private:
//Fields
    sqlite3* _db;

};

