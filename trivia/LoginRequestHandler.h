#pragma once
#include "IRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;
class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler(RequestHandlerFactory& reqFactory);
	~LoginRequestHandler();
	virtual bool isRequestRelevant(RequestInfo reqInfo) override;
	virtual RequestResult handleRequest(RequestInfo reqInfo) override;

private:
	RequestHandlerFactory& m_handlerFactory;
	RequestResult login(RequestInfo reqinfo);
	RequestResult signup(RequestInfo reqinfo);

};

