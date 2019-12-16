// *******************************************
//
//	File:		T_PrivTaskAlloc.cpp
//
//	Created:	13 August 2019
//	Author:		Julio Calvo
//
// *******************************************

#include "T_PrivTaskAlloc.hpp"

T_PrivTaskAlloc::T_PrivTaskAlloc() {}

T_PrivTaskAlloc::T_PrivTaskAlloc(const T_PrivUser& privUser)
{
	setPrivUser(privUser);
}

T_PrivTaskAlloc::~T_PrivTaskAlloc() {}

void T_PrivTaskAlloc::check_and_set_unknown()
{
	setUnknown(m_User.isUnknown());
}

void T_PrivTaskAlloc::setPrivUser(const T_PrivUser& privUser)
{
	m_User = privUser;
	check_and_set_unknown();
}

const T_PrivUser& T_PrivTaskAlloc::getPrivUser() const
{
	PRECONDITION(!isUnknown());
	return m_User;
}

const QList<T_PrivTask>& T_PrivTaskAlloc::getAllowedTasks() const
{
	return m_AllowedTasks;
}

void T_PrivTaskAlloc::setAllowedTasks(const QList<T_PrivTask>& listTasks)
{
	m_AllowedTasks = listTasks;
	check_and_set_unknown();
}

bool T_PrivTaskAlloc::isTaskAllowed(const T_PrivTaskName& privTaskName) const
{
	PRECONDITION(!isUnknown());
	for (auto it = m_AllowedTasks.begin(); it != m_AllowedTasks.end(); ++it) {
		if ((*it).getPrivTaskName().getTaskName() == privTaskName.getTaskName()) return true;
	}
	return false;
}

void T_PrivTaskAlloc::appendAllowedTask(const T_PrivTask& privTask)
{
	m_AllowedTasks.push_back(privTask);
}

bool T_PrivTaskAlloc::isEqual(const T_Object& otherObject) const 
{
	const T_PrivTaskAlloc& other = dynamic_cast<const T_PrivTaskAlloc&>(otherObject);

	return
		m_AllowedTasks == other.m_AllowedTasks &&
		m_User == other.m_User;
}

bool T_PrivTaskAlloc::isLessThan(const T_Object& otherObject) const 
{
	const T_PrivTaskAlloc& other = dynamic_cast<const T_PrivTaskAlloc&>(otherObject);
	return m_User.getUserName() < other.m_User.getUserName();
}

void T_PrivTaskAlloc::writeTo(T_OSTREAM& out) const 
{
	out << m_User << m_AllowedTasks;
}

void T_PrivTaskAlloc::readFrom(T_ISTREAM& in) 
{
	QString text;
	in >> text;
	m_User.setUserName(text);
}

void T_PrivTaskAlloc::asString(T_String& cout) const
{
	cout << "UserName " << m_User.getUserName() << "has following tasks: ";
	for (auto element : m_AllowedTasks) {
		cout << element.getPrivTaskName().getTaskName();
	}
}