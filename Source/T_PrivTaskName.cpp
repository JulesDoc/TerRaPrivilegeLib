// *******************************************
//
//	File:		T_PrivTaskName.cpp
//
//	Created:	13 August 2019
//	Author:		Julio Calvo
//
// *******************************************

#include "T_PrivTaskName.hpp"

T_PrivTaskName::T_PrivTaskName() {}

T_PrivTaskName::T_PrivTaskName(const QString& taskName) 
{
	setTaskName(taskName);
}

T_PrivTaskName::~T_PrivTaskName() {}

const QString &T_PrivTaskName::getTaskName() const 
{
	PRECONDITION(!isUnknown());
	return m_TaskName;
}

void T_PrivTaskName::setTaskName(const QString& taskName) 
{
	m_TaskName = taskName;
	m_TaskName.trimmed();
	setUnknown(m_TaskName.isEmpty());
}

bool T_PrivTaskName::isEqual(const T_Object & rcObject) const 
{
	const T_PrivTaskName& other = dynamic_cast<const T_PrivTaskName&>(rcObject);
	return m_TaskName == other.m_TaskName;
}

bool T_PrivTaskName::isLessThan(const T_Object & rcObject) const 
{
	const T_PrivTaskName& other = dynamic_cast<const T_PrivTaskName&>(rcObject);
	return m_TaskName < other.m_TaskName;
}

void T_PrivTaskName::writeTo(T_OSTREAM& out) const 
{
	PRECONDITION(!isUnknown());
	out << m_TaskName;
}

void T_PrivTaskName::readFrom(T_ISTREAM& in) 
{
	QString name;
	in >> name;
	setTaskName(name);
}

void T_PrivTaskName::asString(T_String& cout) const 
{
	PRECONDITION(!isUnknown());
	cout << m_TaskName;
}