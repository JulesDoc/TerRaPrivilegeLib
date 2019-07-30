#pragma once

#include "tstring.hpp"
#include "TSORTABL.hpp"
#include "QString"
#include "TerRaPrivilegeLib.hpp"

T_CLASSDEF(T_PrivUser)

class T_TERRAPRIVILEGELIBDEF_CLASS T_PrivUser {
public:
	T_PrivUser(const T_String& userName = QString(), const T_String& firstName = QString(), const T_String& lastName = QString());

	void setUserName(const T_String& userName);
	T_String getUserName() const;

	void setFirstName(const T_String& firstName);
	T_String getFirstName() const;

	void setLastName(const T_String& lastName);
	T_String getLastName() const;

	virtual ~T_PrivUser() {};

private:
	T_String m_UserName;
	T_String m_FirstName;
	T_String m_LastName;

};