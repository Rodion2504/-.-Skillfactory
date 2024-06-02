
/* 
	класс чат
*/

#include <iostream>
#include "Chat.h"
#include "User.h"
#include "StoreUsers.h"
#include "StoreMessage.h"
#include "Utils.h"

using namespace std;

Chat::Chat(StoreUsers* su, StoreMessage* sm) :_su(su), _sm(sm) {}

Chat::~Chat()
{
	//cout << "\nЧат удалён\n ";
	list<IUser* >::iterator iterator = user_list.begin();	// перечислитель устанавливаем на первый объект в списке
	if (user_list.empty()) return;							// если список пустой, ничего удалять не надо
	while (iterator != user_list.end())						// цикл по всем объектам в списке
	{
		delete (*iterator);									// удаляем всех пользователей (вызываем деструктор ~User)
		++iterator;
	}
}

// заносим юзера в список рассылки
void Chat::Attach(IUser* user) { user_list.push_back(user); }

// убираем юзера из списка рассылки
void Chat::Detach(IUser* user) { user_list.remove(user); }

// ЭТОТ МЕТОД ЦЕНТРАЛЬНЫЙ В ЧАТЕ !!!
void Chat::Notify()
{
	_sm->showMessageAll();									// вывести юзеру общие сообщения чата
	list<IUser* >::iterator iterator = --user_list.end();	// перечислитель устанавливаем на последний объект в списке
	string user = (*iterator)->getUserName();
	_sm->showMsgTo(user);									// вывести пользователю личные сообщения

	cout << "\nВ строке \"Кому:\" указывать логин если сообщение личное. Оставить пустым иначе.\n \"exit\" для выхода из чата.\n";
	const size_t size{ 1024 };		// размер буфера пользовательского ввода
	char buff[size]{};				// буфер пользовательского ввода

	while (true) {
		cout << "Кому: ";
		cin.getline(buff, size);
		string to = string(buff);
		for (size_t i = 0; i < 1024; ++i) buff[i] = 0;		// очистка буфера ввода

		cout << "< " << user << " > ";
		cin.getline(buff, size);
		string message = string(buff);
		for (size_t i = 0; i < 1024; ++i) buff[i] = 0;		// очистка буфера ввода

		if (message == "exit" || message == "quit") break;	// выход из чата
		_sm->setMessage(user, to, message);					// пишем в базу
	}

	delete (*iterator);		// удалить пользователя из чата	

}

// проверка что этот пользователь уже вошёл в чат
bool Chat::UserInChat(string& name)
{
	list<IUser* >::iterator iterator = user_list.begin();	// перечислитель устанавливаем на первый объект в списке
	while (iterator != user_list.end())						// цикл по всем объектам в списке
	{
		if ((*iterator)->getUserName() == name) return true;// если такой пользователь в этом чате найден
		++iterator;
	}
	return false;
}

