#include "SqliteDataBase.h"
std::map<std::string, std::list<std::string>> SqliteDataBase::_data;


SqliteDataBase::SqliteDataBase(const char* db)
{
	if (sqlite3_open(db, &_db) != SQLITE_OK) {
		_db = nullptr;
		std::cout << "Failed to open DB\n";
		exit(1);
	}
	// Iniate Relevant SQL Tables
	char** errMessage = nullptr;
	std::string query = "create table if not exists data (id integer primarykey auto increment not null , gameId integer primary key not null,username text not null, correctAnswers integer not null, totalAnswers integer not null, averageAnswerTime float not null);";
	sqlite3_exec(_db, query.c_str(), nullptr, nullptr, errMessage);
}

SqliteDataBase::SqliteDataBase()
{
}

SqliteDataBase::~SqliteDataBase() {
	sqlite3_close(_db);
	_db = nullptr;
}


int SqliteDataBase::callback(void* data, int argc, char** argv, char** azColName)
{
//Inserting all values under their categories in the table
	for (int i = 0; i < argc; i++)
	{
		SqliteDataBase::_data[azColName[i]].push_back(argv[i]);
	}
	return 0;
}

bool SqliteDataBase::doesUserExist(string username)
{
	std::string query = "select count(*) from users where username=\"" + username + "\";";
	bool dataPointer = false;
	char** errMessage = nullptr;
	if (sqlite3_exec(_db, query.c_str(), [](void* data, int argc, char** argv, char** azColName) {
		if (argc != 0 && !strcmp(argv[0], "1")) {
			bool* existRes = static_cast<bool*>(data);
			*existRes = bool(atoi(argv[0]));
		}
		return 0;
		}, &dataPointer, errMessage) != SQLITE_OK) {
		std::cout << "Error While Parsing Query " << " with " << errMessage;
		return false;
	}
	return dataPointer;
}

bool SqliteDataBase::doesPasswordMatch(string username, string password)
{
	std::string query = "select count(*) from users where username=\"" + username + "\" and password=\"" + password + "\";";
	bool dataPointer = false;
	char** errMessage = nullptr;
	if (sqlite3_exec(_db, query.c_str(), [](void* data, int argc, char** argv, char** azColName) {
		if (argc != 0 && !strcmp(argv[0], "1")) {
			bool* existRes = static_cast<bool*>(data);
			*existRes = bool(atoi(argv[0]));
		}
		return 0;
		}, &dataPointer, errMessage) != SQLITE_OK) {
		std::cout << "Error While Parsing Query " << " with " << errMessage;
		return false;
	}
	return dataPointer;
}

void SqliteDataBase::addNewUser(string username, string password, string email)
{
	char** errMessage = nullptr;
	string sqlStatement = "INSERT INTO USERS (USERNAME, PASSWORD, EMAIL) VALUES ('" + username + "', '" + password + "', '" + email + "');";
	sqlite3_exec(_db, sqlStatement.c_str(), nullptr, nullptr, errMessage);
	sqlStatement = "INSERT INTO STATISTICS (USERNAME, TOTALGAMES, TOTALANSWERS, CORRECTANSWERS, AVERAGEANSWERTIME) VALUES ('" + username + "', 0, 0, 0, 0);";
	sqlite3_exec(_db, sqlStatement.c_str(), nullptr, nullptr, errMessage);
}

//v2
list<Question> SqliteDataBase::getQuestions(int numOfQuestions)
{
	char** errMessage = nullptr;
	string sqlStatement = "select * from questions order by random() limit " + std::to_string(numOfQuestions) + ";";
	list<Question> questionsList;
	sqlite3_exec(_db, sqlStatement.c_str(), [](void* data, int argc, char** argv, char** azColName) {
		if (argc != 0) {
			auto questionsList = static_cast<list<Question>*>(data);
			questionsList->push_back(Question(argv[1], argv[2], argv[3], argv[4], argv[5], atoi(argv[6])));
		}
		return 0;
	}, &questionsList, errMessage);
	return questionsList;
}

float SqliteDataBase::getPlayerAverageAnswerTime(string username)
{
	char** errMessage = nullptr;
	string sqlStatement = "SELECT AVERAGEANSWERTIME FROM STATISTICS WHERE USERNAME='" + username + "';";
	float ans = 0.0f;
	sqlite3_exec(_db, sqlStatement.c_str(), [](void* data, int argc, char** argv, char** azColName) {
		if (argc != 0 && !strcmp(argv[0], "1")) {
			float* existRes = static_cast<float*>(data);
			*existRes = atof(argv[0]);
		}
		return 0;
	}, &ans, errMessage);
	return ans;
}

int SqliteDataBase::getNumOfCorrectAnswers(string username)
{
	char** errMessage = nullptr;
	string sqlStatement = "SELECT CORRECTANSWERS FROM STATISTICS WHERE USERNAME='" + username + "';";
	SqliteDataBase::_data.clear();
	sqlite3_exec(_db, sqlStatement.c_str(), callback, nullptr, errMessage);
	return stoi((*(*SqliteDataBase::_data.find("correctAnswers")).second.begin()));
}

int SqliteDataBase::getNumOfTotalAnswers(string username)
{
	char** errMessage = nullptr;
	string sqlStatement = "SELECT TOTALANSWERS FROM STATISTICS WHERE USERNAME='" + username + "';";
	int totalAnswers = 0;
	sqlite3_exec(_db, sqlStatement.c_str(), [](void* data, int argc, char** argv, char** azColName) {
		if (argc != 0) {
			int* existRes = static_cast<int*>(data);
			*existRes = atoi(argv[0]);
		}
		return 0;
	}, & totalAnswers, errMessage);
	return totalAnswers;
}

int SqliteDataBase::getNumOfPlayerGames(string username)
{
	char** errMessage = nullptr;
	string sqlStatement = "SELECT TOTALGAMES FROM STATISTICS WHERE USERNAME='" + username + "';";
	int totalGames = 0;
	sqlite3_exec(_db, sqlStatement.c_str(), [](void* data, int argc, char** argv, char** azColName) {
		if (argc != 0) {
			int* existRes = static_cast<int*>(data);
			*existRes = atoi(argv[0]);
		}
		return 0;
		}, & totalGames, errMessage);
	return totalGames;
}

int SqliteDataBase::getPlayerScore(string username)
{
	return (int)(getNumOfCorrectAnswers(username) / (getPlayerAverageAnswerTime(username) * getNumOfTotalAnswers(username) + 1)) * 10;
}

vector<pair<string, int>> SqliteDataBase::getHighScores()
{
	vector<pair<string, int>> high_score;
	char** errMessage = nullptr;
	string sqlStatement = "SELECT * FROM STATISTICS";
	int totalAnswers = 0;
	SqliteDataBase::_data.clear();
	sqlite3_exec(_db, sqlStatement.c_str(), callback, nullptr, errMessage);

	if (SqliteDataBase::_data.size() != 0)
	{
		list<string> usernames = (*SqliteDataBase::_data.find("username")).second;		
		auto start = usernames.begin(), end = usernames.end();
		for (start; start != end; ++start)
		{
			high_score.push_back(make_pair((*start), getPlayerScore((*start))));
		}
		sort(high_score.begin(), high_score.end(), [](const pair<string, int>& start, const pair<string, int>& end) {return start.second > end.second; });
	}

	if (high_score.size() > 10)
	{
		high_score.resize(10);
	}

	return high_score;
}

void SqliteDataBase::userAnswer(string username, bool correct)
{
	char** errMessage = nullptr;
	string sqlStatement = "SELECT * FROM STATISTICS WHERE USERNAME='" + username + "';";
	int totalAnswers = 0;
	SqliteDataBase::_data.clear();
	sqlite3_exec(_db, sqlStatement.c_str(), callback, nullptr, errMessage);
	if (SqliteDataBase::_data.size() != 0)
	{
		sqlStatement = "UPDATE STATISTICS SET TOTALANSWERS = ";
		sqlStatement += std::to_string(stoi((*(*SqliteDataBase::_data.find("totalAnswers")).second.begin())) + 1);
		
		if (correct)
		{
			sqlStatement += ", CORRECTANSWERS = " + std::to_string(stoi((*(*SqliteDataBase::_data.find("correctAnswers")).second.begin())) + 1);
		}
		sqlStatement += " WHERE USERNAME = '" + username + "';";
		sqlite3_exec(_db, sqlStatement.c_str(), nullptr, nullptr, errMessage);
	}
}
