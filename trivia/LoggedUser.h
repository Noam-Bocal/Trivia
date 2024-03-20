#pragma once
#include "pch.h"

using std::string;

class LoggedUser
{
private:
//Fields
	string m_username;

public:
//c'tor
	LoggedUser(string username);

//Methods
	string getUsername() const;

	bool operator==(const LoggedUser& other) const;
	bool operator<(const LoggedUser& other) const;
	void operator=(LoggedUser const& other);
};

