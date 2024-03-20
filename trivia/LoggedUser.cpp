#include "LoggedUser.h"

string LoggedUser::getUsername() const
{
//Return username
	return m_username;
}

LoggedUser::LoggedUser(string username)
{
//Set username
	m_username = username;
}

bool LoggedUser::operator==(const LoggedUser& other) const
{
	// Compare usernames for equality
	return m_username == other.m_username;
}

bool LoggedUser::operator<(const LoggedUser& other) const {
	// Compare usernames for ordering
	return m_username < other.m_username;
}

void LoggedUser::operator=(LoggedUser const& other)
{
	this->m_username = other.getUsername();
}

