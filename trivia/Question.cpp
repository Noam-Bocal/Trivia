#include "Question.h"
Question::Question(std::string question, std::string answer1, std::string answer2, std::string answer3, std::string answer4, int correctAnswer)
{
	this->m_question = question;
	this->m_possibleAnswers.push_back(answer1);
	this->m_possibleAnswers.push_back(answer2);
	this->m_possibleAnswers.push_back(answer3);
	this->m_possibleAnswers.push_back(answer4);
	this->m_correctId = correctAnswer;
}


Question::~Question()
{
}

std::string Question::getQuestion() const
{
	return m_question;
}

int Question::getCorrectAnswerId() const
{
	return m_correctId;
}

std::vector<std::string> Question::getPossibleAnswers() const
{
	return m_possibleAnswers;
}
