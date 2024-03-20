#pragma once
#include "WSAInitializer.h"
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <map>
#include <exception>
#include <fstream>
#include <vector>
#include <list>
#include <algorithm>

#define SIGNUP 100
#define LOGIN 101
#define SIGNOUT 103
#define GET_ROOMS 104
#define GET_PLAYER_IN_ROOM 105
#define JOIN_ROOM 106
#define CREATE_ROOM 107
#define GET_ROOM_STATE 108
#define CLOSE_ROOM 102
#define START_GAME 109
#define LEAVE_ROOM 110
#define LEAVE_GAME 111
#define GET_QUESTION 112
#define SUBMIT_ANSWER 113
#define GET_GAME_RESULT 114
#define GET_HIGH_SCORE 115
#define GET_PERSONAL_STATUS 116


#define ALREADY_EXISTS 150
#define DONT_EXISTS 151
#define ALREADY_LOGED 152

#define SIGNUP_SUCCESS 200
#define LOGED_SUCCESS 201
#define SIGNOUT_SUCCESS 202
#define GET_ROOMS_SUCCESS 203
#define GET_PLAYERS_IN_ROOMS_SUCCESS 204
#define JOIN_ROOM_SUCCESS 205
#define CREATE_ROOM_SUCCESS 206
#define GET_ROOM_STATE_SUCCESS 207
#define CLOSE_ROOM_SCCESS 208
#define START_GAME_SUCCESS 209
#define LEAVE_ROOM_SUCCESS 210
#define LEAVE_GAME_SUCCESS 211
#define GET_QUESTION_SUCCESS 212
#define SUBMIT_ANSWER_SUCCESS 213
#define GET_GAME_RESULT_SUCCESS 214
#define NO_MORE_QUESTIONS 215
#define GET_PERSONAL_STATUS_SUCCESS 216
#define GET_HIGH_SCORE_SUCCESS 217

using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::thread;
using std::mutex;
using std::vector;
using std::list;
using std::pair;
using std::map;
using std::make_pair;
using std::sort;
