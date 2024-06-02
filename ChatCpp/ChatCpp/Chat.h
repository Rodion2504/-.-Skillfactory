/*
	класс чат
*/

#pragma once
#include <list>
#include "IChat.h"
#include "IUser.h"
#include "StoreUsers.h"
#include "StoreMessage.h"

using namespace std;

class Chat :public IChat {

	StoreUsers* _su;			// БД логин/пароль всех юзеров
	StoreMessage* _sm;			// БД все сообщения
	list <IUser* > user_list;	// список пользователей выполнивших вход в этот чат

public:
	Chat() = default;
	Chat(StoreUsers*, StoreMessage*);
	virtual ~Chat();
	void Attach(IUser* user) override;	// добавить в чат
	void Detach(IUser* user) override;	// убрать из чата
	void Notify() override;				// основной цикл ввода сообщений
	bool UserInChat(string& name);		// проверка, что пользователь уже в чате
};