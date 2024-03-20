#include "Room.h"

Room::Room(RoomData roomData)
{
	m_metadata = roomData;
}

Room::~Room() {
	m_users.clear();
}


void Room::addUser(LoggedUser user)
{
	//Add user
	m_users.push_back(user);
}

void Room::removeUser(LoggedUser user)
{
	//Remove user
	for (int i = 0; i < m_users.size(); i++)
		if (m_users[i].getUsername() == user.getUsername())
			m_users.erase(m_users.begin() + i);
}

vector<string> Room::getAllUsers()
{
	vector<string> users;

	auto start = m_users.begin(), end = m_users.end();

	//Add all the usernames into strings vector
	for (start; start != end; ++start)
		users.push_back(start->getUsername());
	return users;
}

RoomData Room::getData()
{
	return m_metadata;
}

void Room::setActive(bool active)
{
	m_metadata.isActive = active;
}
