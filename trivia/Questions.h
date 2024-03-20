#pragma once
#include "pch.h"

class Question {
public:
    Question(string q, string ans1, string ans2, string ans3, string ans4, int correct)
    {
        this->question = question;
        this->answers.push_back(ans1);
        this->answers.push_back(ans2);
        this->answers.push_back(ans3);
        this->answers.push_back(ans4);
        this->correctAnswer = correct;
    }
    virtual ~Question()
    {

    }

    std::string getQuestion() { return question; };
    std::vector<std::string> getAnswers() { return answers; };
    int getCorrectAnswer() { return correctAnswer; };
private:
    std::string question;
    std::vector<std::string> answers;
    int correctAnswer;
};