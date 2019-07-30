#include <windows.h>
#include <Lmcons.h>
#include <sstream>

#include "T_PrivUser.hpp"

T_PrivUser::T_PrivUser(const T_String& userName, const T_String& firstName, const T_String& lastName) : 
	                   m_UserName(userName), m_FirstName(firstName), m_LastName(lastName) 
{
	//If userName is empty, it is taken from Windows 10 current logged user.
	if (m_UserName.isEmpty()) {

		TCHAR username[UNLEN + 1];
		DWORD username_len = UNLEN + 1;
		GetUserName(username, &username_len);

		std::stringstream ss;
		ss << username;
		m_UserName = QString::fromStdString(ss.str());
	}
}

void T_PrivUser::setUserName(const T_String& userName) {
	m_UserName = userName;
}

T_String T_PrivUser::getUserName() const {
	return m_UserName;
}

void T_PrivUser::setFirstName(const T_String& firstName) {
	m_FirstName = firstName;
}

T_String T_PrivUser::getFirstName() const {
	return m_FirstName;
}

void T_PrivUser::setLastName(const T_String& lastName) {
	m_LastName = lastName;
}

T_String T_PrivUser::getLastName() const {
	return m_LastName;
}