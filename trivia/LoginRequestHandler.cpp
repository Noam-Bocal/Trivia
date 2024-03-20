#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& reqFactory) 
	: m_handlerFactory(reqFactory)
{
}

LoginRequestHandler::~LoginRequestHandler()
{
}

bool LoginRequestHandler::isRequestRelevant(RequestInfo reqInfo)
{
	return reqInfo.id == SIGNUP || reqInfo.id == LOGIN;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo reqInfo)
{
	RequestResult result;
	if (reqInfo.id == LOGIN)
		result = login(reqInfo);
	else
		result = signup(reqInfo);

	return result;
}

RequestResult LoginRequestHandler::login(RequestInfo reqinfo)
{
	//I am not sure about respons.newHandler. what is he supposed to be?
	RequestResult result;
	LoginRequest login = JsonRequestPacketDeserializer::deserializeLoginRequest(reqinfo.buffer);
	if (m_handlerFactory.getLoginManager().login(login.username, login.password) == LOGED_SUCCESS)
	{
		LoginResponse loginResp;
		loginResp.status = LOGED_SUCCESS;
		result.response = JsonResponsePacketSerializer::serializeResponse(loginResp);
		result.newHandler = m_handlerFactory.createMenuRequestHandler(LoggedUser(login.username));
	}	
	else
	{
		ErrorResponse errorResp;
		errorResp.message = "Wrong password or username";
		result.response = JsonResponsePacketSerializer::serializeResponse(errorResp);
		result.newHandler = this;
	}

	return result;

}

RequestResult LoginRequestHandler::signup(RequestInfo reqinfo)
{
	RequestResult result;
	SignupRequest signup = JsonRequestPacketDeserializer::deserializeSignupRequest(reqinfo.buffer);
	if (m_handlerFactory.getLoginManager().signup(signup.username, signup.password, signup.email) == SIGNUP_SUCCESS)
	{
		SignupResponse signupResp;
		signupResp.status = SIGNUP_SUCCESS;
		result.response = JsonResponsePacketSerializer::serializeResponse(signupResp);
		result.newHandler = m_handlerFactory.createMenuRequestHandler(LoggedUser(signup.username));
	}
	else
	{
		ErrorResponse errorResp;
		errorResp.message = "Username already taken";
		result.response = JsonResponsePacketSerializer::serializeResponse(errorResp);
		result.newHandler = nullptr;
	}
	return result;
}


