
/* 
	Абстрактный класс-интерфейс пользователя. Все пользователи наследуются от него. 
*/

#pragma once
#include <string>
#include "IChat.h"

// интерфейс пользователя
class IUser {
public:
	virtual ~IUser() {};
	virtual std::string getUserName() = 0;
};
