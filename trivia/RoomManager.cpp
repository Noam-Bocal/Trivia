#include "RoomManager.h"

void RoomManager::createRoom(LoggedUser user, RoomData room)
{
	//Create new room
	this->m_rooms.insert(std::pair<unsigned int, Room>(room.id - 1, Room(room)));
	this->m_rooms[room.id -1 ].addUser(user);

}

void RoomManager::deleteRoom(int ID)
{
	//Delete room by id
	m_rooms.erase(ID - 1);
}

unsigned int RoomManager::getRoomState(int ID)
{
	//Return the room activate
	return m_rooms[ID].getData().isActive;
}

vector<RoomData> RoomManager::getRooms()
{
	vector<RoomData> data;
	auto start = m_rooms.begin(), end = m_rooms.end();

	//Add all the rooms data into the vector
	for (start; start != end; ++start)
	{
		data.push_back(start->second.getData());
	}

	return data;
}

Room& RoomManager::getRoom(int ID)
{
	//Return specific room by id
	return m_rooms[ID - 1];
}
