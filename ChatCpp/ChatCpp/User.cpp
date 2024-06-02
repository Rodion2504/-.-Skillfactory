
#include <iostream>
#include "Chat.h"
#include "User.h"
using namespace std;

User::User(IChat* chat, string name) : _chat(chat), _name(name)
{
	_chat->Attach(this);				// заносим себя в список участников чата	
	cout << "\n< " << _name << " > вошёл в чат." << "\n\n";
}

User::~User()
{
	RemoveFromList();
	cout << "\n< " << _name << " > вышёл из чата." << "\n\n";
}

// удаление из списка(list) участников чата, выход из чата
void User::RemoveFromList()
{
	_chat->Detach(this);

}

std::string User::getUserName() { return _name; }