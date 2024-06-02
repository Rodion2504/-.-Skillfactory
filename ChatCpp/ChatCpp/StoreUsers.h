/* 
	Класс для хранения пар логин/пароль.
*/

#pragma once
#include <vector>
#include <string>

using namespace std;

class StoreUsers
{
	struct sUser {
		string _name;
		string _pass;
	};

	vector<sUser>* _u;

public:
	StoreUsers();
	~StoreUsers();
	bool checkLogin(string name, string pass);	// вход
	bool checkName(string& name);				// регистрация(проверка уникальности имени)
	void toStore(string name, string pass);		// занести юзера в базу
	void showUsers();							// вывести всех юзеров в базе в консоль
};

