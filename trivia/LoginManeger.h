#pragma once
#include "pch.h"
#include "LoggedUser.h"
#include "IDatabase.h"
#include "SqliteDataBase.h"

using std::string;
using std::remove;

class LoginManeger
{
private:
//Fields
	IDatabase* m_database;
	vector<LoggedUser> m_loggedUsers;

public:
//Methods
	LoginManeger(IDatabase* database);
	~LoginManeger();
	int signup(string username, string password, string email);
	int login(string username, string password);
	int logout(string username);
};

