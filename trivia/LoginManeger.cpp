#include "LoginManeger.h"

LoginManeger::LoginManeger(IDatabase* database) : m_database(database)
{

}


LoginManeger::~LoginManeger() {

}

int LoginManeger::signup(string username, string password, string email)
{
	//Check if user does'nt exist
	if (!m_database->doesUserExist(username))
	{
	// Create new User account
		m_database->addNewUser(username, password, email); 
		return SIGNUP_SUCCESS;
	} 

	return ALREADY_EXISTS;
}

int LoginManeger::login(string username, string password)
{
	LoggedUser User(username);
	if (std::find(m_loggedUsers.begin(), m_loggedUsers.end(), User) != m_loggedUsers.end())
		return ALREADY_LOGED;
	//Add user into the connected Users list
	if (m_database->doesPasswordMatch(username, password))
	{
		m_loggedUsers.push_back(User);
		return LOGED_SUCCESS;
	}

	return DONT_EXISTS;
}

int LoginManeger::logout(string username)
{
	LoggedUser User(username);

	//Remove user from the connected Users list
	if (m_database->doesUserExist(username))
	{
		auto it = std::find(m_loggedUsers.begin(), m_loggedUsers.end(), User);

		if (it != m_loggedUsers.end()) {
			m_loggedUsers.erase(it);
		}
		else
			return DONT_EXISTS;
	}

	return SIGNOUT_SUCCESS;
}
