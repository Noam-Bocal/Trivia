#pragma once
#include "pch.h"

class IRequestHandler;
struct RequestInfo
{
	unsigned char id;
	vector<uint8_t> buffer;

	RequestInfo(string buff)
	{
		id = stoi(buff.substr(0, 3));
		string json_str = buff.substr(7);
		buffer = vector<uint8_t>(json_str.begin(), json_str.end());
	}
};

struct RequestResult {
	string response;
	IRequestHandler* newHandler;
};

class IRequestHandler
{
public:
	virtual bool isRequestRelevant(RequestInfo reqInfo) = 0;
	virtual RequestResult handleRequest(RequestInfo reqInfo) = 0;

	mutex roomManagerMutex;
};
