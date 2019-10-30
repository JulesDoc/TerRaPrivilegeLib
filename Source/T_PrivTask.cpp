// *******************************************
//
//	File:		T_PrivTask.cpp
//
//	Created:	13 August 2019
//	Author:		Julio Calvo
//
// *******************************************

#include "T_PrivTask.hpp"

T_PrivTask::T_PrivTask() 

{
	;

}

T_PrivTask::T_PrivTask(const T_PrivTaskName& privTaskName, const T_TerRaProgram& program, const QString& taskDescription)
{
	setPrivTaskName(privTaskName);
	setTerraProgram(program);
	setTaskDescription(taskDescription);
}

T_PrivTask::~T_PrivTask(){}

void T_PrivTask::check_and_set_unknown()
{
	/*
	bool bUnknown =
		m_TaskName.isUnknown() ||
		m_Program.isUnknown();
	setUnknown(bUnknown);
	*/

	bool bUnknown = false;
	if(m_TaskName.isUnknown())
		bUnknown = true;
	if (m_Program.isUnknown())
		bUnknown = true;
	
	setUnknown(bUnknown);
}

const T_PrivTaskName& T_PrivTask::getPrivTaskName() const
{
	PRECONDITION(!isUnknown());
	return m_TaskName;
}

void T_PrivTask::setPrivTaskName(const T_PrivTaskName & privTaskObj)
{
	m_TaskName = privTaskObj;
	check_and_set_unknown();
}

const T_TerRaProgram& T_PrivTask::getTerraProgram() const
{
	PRECONDITION(!isUnknown());
	return m_Program;
}

void T_PrivTask::setTerraProgram(const T_TerRaProgram & terraProgObj)
{
	m_Program = terraProgObj;
	check_and_set_unknown();
}

const QString& T_PrivTask::getTaskDescription() const {
	return m_TaskDescription;
}

void T_PrivTask::setTaskDescription(const QString& taskDesc) {
	m_TaskDescription = taskDesc;
}

void T_PrivTask::setUpdateBlock(const T_UpdateBlock & updateBlock)
{
	m_UpdateBlock = updateBlock;
}

const T_UpdateBlock & T_PrivTask::getUpdateBlock() const
{
	return m_UpdateBlock;
}

bool T_PrivTask::isEqual(const T_Object& otherObject) const {
	const T_PrivTask& other = dynamic_cast<const T_PrivTask&>(otherObject);
	return
		m_TaskName == other.m_TaskName &&
		m_Program.isEquivalent(other.m_Program) &&
		m_TaskDescription == other.m_TaskDescription;
}

bool T_PrivTask::isLessThan(const T_Object& otherObject) const {
	const T_PrivTask& other = dynamic_cast<const T_PrivTask&>(otherObject);
	return m_TaskName.getTaskName() < other.m_TaskName.getTaskName();
}

void T_PrivTask::writeTo(T_OSTREAM& out) const {
	out << m_TaskName.getTaskName();
}

void T_PrivTask::readFrom(T_ISTREAM& in) {
	QString text;
	in >> text;
	m_TaskName.setTaskName(text);
}

void T_PrivTask::asString(T_String& cout) const {
	cout << m_TaskName.getTaskName();
}