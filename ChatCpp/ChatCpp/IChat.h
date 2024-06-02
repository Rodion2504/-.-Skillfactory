
/* 
	Абстрактный класс-интерфейс. Все классы чатов наследуются от него. 
*/

#pragma once
#include "IUser.h"

// интерфейс чата
class IChat {
public:
	virtual ~IChat() {};
	virtual void Attach(IUser*) = 0;	// подписать пользователя(занести в список)
	virtual void Detach(IUser*) = 0;	// отписать пользователя(удалить из списка)
	virtual void Notify() = 0;			// цикл ввода сообщений
};
