// *******************************************
//
//	File:		T_PrivUser.cpp
//
//	Created:	13 August 2019
//	Author:		Julio Calvo
//
// *******************************************

#include <sstream>

#include "T_PrivUser.hpp"

T_PrivUser::T_PrivUser() {}

T_PrivUser::T_PrivUser(const QString& userName, const QString& firstName, const QString& lastName)
{
	setUserName(userName);
	setFirstName(firstName);
	setLastName(lastName);
}

void T_PrivUser::setUserName(const QString& userName) 
{
	m_UserName = userName;
	m_UserName.trimmed();
	check_and_set_unknown();
}

const QString& T_PrivUser::getUserName() const 
{
	PRECONDITION(!isUnknown());
	return m_UserName;
}

void T_PrivUser::setFirstName(const QString& firstName) 
{
	m_FirstName = firstName;
	m_FirstName.trimmed();
	check_and_set_unknown();
}

const QString& T_PrivUser::getFirstName() const 
{
	return m_FirstName;
}

void T_PrivUser::setLastName(const QString& lastName) 
{
	m_LastName = lastName;
	m_LastName.trimmed();
	check_and_set_unknown();
}

const QString& T_PrivUser::getLastName() const 
{
	return m_LastName;
}

void T_PrivUser::setUpdateBlock(const T_UpdateBlock & updateBlock)
{
	m_UpdateBlock = updateBlock;
}

const T_UpdateBlock& T_PrivUser::getUpdateBlock() const
{
	return m_UpdateBlock;
}

bool T_PrivUser::isEqual(const T_Object & object) const
{
	return m_UserName == dynamic_cast<const T_PrivUser&>(object).m_UserName;
}

bool T_PrivUser::isLessThan(const T_Object & object) const
{
	return m_UserName < dynamic_cast<const T_PrivUser&>(object).m_UserName;
}

void T_PrivUser::writeTo(T_OSTREAM & out) const
{
	PRECONDITION(!isUnknown());
	out << m_UserName;
}

void T_PrivUser::readFrom(T_ISTREAM & in)
{
	QString userName;
	in >> userName;
	setUserName(userName);
}

void T_PrivUser::asString(T_String & sout) const
{
	sout << m_UserName;
}

void T_PrivUser::check_and_set_unknown()
{
	setUnknown(m_UserName.isEmpty());
}