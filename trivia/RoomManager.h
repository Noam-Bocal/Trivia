#pragma once
#include "Room.h"
#include <map>

using std::map;

class RoomManager
{
private:
//map<roomID, Room> ;
	map<unsigned int, Room> m_rooms;

public:

	void createRoom(LoggedUser user, RoomData room);
	void deleteRoom(int ID);
	unsigned int getRoomState(int ID);
	vector<RoomData> getRooms();
	Room& getRoom(int ID);
};