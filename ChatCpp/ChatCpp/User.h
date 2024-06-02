
/* 
класс пользователь 
*/

#pragma once
#include <string>
#include "IChat.h"
#include "IUser.h"

class User :public IUser {

	IChat* _chat;						// в каком чате сейчас
	std::string _name;					// логин пользователя

public:
	User(IChat* chat, std::string name);
	virtual ~User();
	void RemoveFromList();				// выход из чата
	std::string getUserName() override;
};