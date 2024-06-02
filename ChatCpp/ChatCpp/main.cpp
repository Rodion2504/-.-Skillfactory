#define _CRTDBG_MAP_ALLOC
#ifdef _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif  _CRTDBG_MAP_ALLOC

#include <iostream>
#include <string>
#include <locale>

#include "Chat.h"
#include "User.h"
#include "StoreUsers.h"
#include "StoreMessage.h"
#include "Utils.h"

using namespace std;

void Hello(Chat*, StoreUsers*);

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "ru-RU");										

#ifdef _CRTDBG_MAP_ALLOC
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);	// отслеживание утечек памяти
#endif  _CRTDBG_MAP_ALLOC

	StoreUsers* su1 = new StoreUsers;
	StoreMessage* sm1 = new StoreMessage;
	Chat* ch1 = new Chat(su1, sm1);
	Hello(ch1, su1);

	delete su1;
	delete sm1;
	delete ch1;

	return 0;
}

// сюда пользователь попадает при запуске программы и при выходе из чата
void Hello(Chat* chat, StoreUsers* su) {

	string name;				// логин пользователя
	string pass;				// пароль пользователя
	const size_t size{ 1024 };	// размер буфера пользовательского ввода
	char s[size]{};				// буфер пользовательского ввода

	while (true)
	{
		std::cout << "\tЧат.\n 1. Войти.\n 2. Зарегистрироваться.\n 3. Выход.\n";

		cin.getline(s, size);						

		size_t counter = count(s);						// счётчик введённых символов
		if (counter == 1) {
			if (s[0] != '1' && s[0] != '2' && s[0] != '3') {
				s[0] = 0;
				cout << "\nВыберите 1,2 or 3\n\n";
				continue;								// если это не 1, 2 или 3
			}
		} 
		else {
			for (size_t i = 0; i < 1024; ++i) s[i] = 0;
			cout << "\nВыберите 1,2 or 3\n\n";
			continue;									// если введено больше одного символа
		}		

		switch (s[0])
		{
		case '1':
			do {
				cout << "\nВход в чат\nВведите логин(цифры и латиница): ";
			} while (!enter(&name));

			do {

			cout << "Введите пароль(не более восьми символов, цифры и латиница): ";
			} while (!enter(&pass));

			if (su->checkLogin(name, pass)) {			// если такой пользователь есть в базе
				if (!chat->UserInChat(name)) {			
					new User(chat, name);
					name.clear();
					pass.clear();
					// вход в чат после ввода логина и пароля здесь
					chat->Notify();
				}
				else cout << "Пользователь " << name << " уже в чате." << endl;
			}
			else cout << "\nНет такого пользователя.\n\n";
			name.clear();
			pass.clear();
			break;

		case '2':
			do {
				cout << "\nРегистрация пользователя:\nВведите логин(не более восьми символов, цифры и латиница): ";
			} while (!enter(&name));

			do {
				cout << "Введите пароль(не более восьми символов, цифры и латиница): ";
			} while (!enter(&pass));

			if (su->checkName(name)) {					// если существует
				cout << "\nТакой пользователь уже есть\n";
				name.clear();
				pass.clear();
			}
			else {
				su->toStore(name, pass);				// сохраняем логин и пароль нового пользователя
				new User(chat, name);					// заносим пользователя в список этого чата
				name.clear();
				pass.clear();
				// вход в чат после регистрации здесь
				chat->Notify();
			}
			break;

		case '3':

			return;

		default:
			cout << "\nВыберите 1,2 or 3\n";
			break;
		}
	}
}
