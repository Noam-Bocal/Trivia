#pragma once
#include "LoggedUser.h"

struct RoomData
{
	unsigned int id;
	string name;
	unsigned int maxPlayers;
	unsigned int numOfQuestionsInGame;
	unsigned int timePerQuestion;
	unsigned int isActive;
};

class Room
{
private:
	RoomData m_metadata;
	vector<LoggedUser> m_users;

public:
	Room(RoomData roomData);
	Room() {};
	~Room();
	void addUser(LoggedUser);
	void removeUser(LoggedUser);
	vector<string> getAllUsers();
	RoomData getData();
	void setActive(bool active);
};
