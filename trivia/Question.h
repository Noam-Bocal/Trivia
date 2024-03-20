#pragma once
#include <string>
#include <vector>

class Question
{
public:
	Question(std::string, std::string, std::string, std::string, std::string, int);
	virtual ~Question();

	std::string getQuestion() const;
	int getCorrectAnswerId() const;
	std::vector<std::string> getPossibleAnswers() const;
	bool operator==(const Question other) const {
		return this->m_question == other.m_question &&
			this->m_possibleAnswers.size() == other.m_possibleAnswers.size() &&
			std::equal(this->m_possibleAnswers.begin(), this->m_possibleAnswers.end(), other.m_possibleAnswers.begin()) &&
			this->m_correctId == other.m_correctId;

	}

private:
	std::string m_question;
	std::vector<std::string> m_possibleAnswers;
	int m_correctId;
};
