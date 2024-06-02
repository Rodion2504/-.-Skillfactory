
#include <iostream>
#include "StoreUsers.h"

StoreUsers::StoreUsers() :_u(new vector<sUser>) {}
StoreUsers::~StoreUsers() { delete _u; }

// сверка логина и пароля с базой.
// true - если такая пара логин/пароль есть в базе. 
bool StoreUsers::checkLogin(string name, string pass)
{
    if(_u->empty()) return false;
    for (size_t i = 0; i < _u->size(); ++i) {
        if ((*_u)[i]._name == name && (*_u)[i]._pass == pass) return true;
    }
    return false;
}

// проверка уникальности имени
// true - если такое имя уже есть
bool StoreUsers::checkName(string& name)
{
    if (_u->empty()) return false;
    for (size_t i = 0; i < _u->size(); ++i) {
        if ((*_u)[i]._name == name) return true;
    }
    return false;
}

// занести нового пользователя в базу
void StoreUsers::toStore(string name, string pass) { _u->push_back(sUser{name, pass}); }

// вывести данные всех пользователей в консоль
void  StoreUsers::showUsers() {
    if (_u->empty()) { 
        cout << "Зарегистрированных пользователей нет";
        return; 
    }
    cout << "Количество зарегистрированных пользователей: " << _u->size();
    for (size_t i = 0; i < _u->size(); ++i) {
        std::cout << "\nПользователь: " << (*_u)[i]._name << "\nПароль: " << (*_u)[i]._pass;
    }
}