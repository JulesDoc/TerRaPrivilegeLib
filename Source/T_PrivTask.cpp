#include "T_PrivTask.hpp"

T_PrivTask::T_PrivTask(const T_PrivTaskName& taskName) :
	m_Task(taskName) {}

T_PrivTask::T_PrivTask(const T_PrivTaskName& taskName, const T_TerRaProgram& program, const T_String& taskDescription):
	m_Task(taskName), m_Program(program), m_TaskDescription(taskDescription) {}

T_PrivTask::~T_PrivTask(){}

T_String T_PrivTask::getTaskName() const {
	return m_Task.getTaskName();
}

T_String T_PrivTask::getTaskDescription() const {
	return m_TaskDescription;
}

void T_PrivTask::setTaskDescription(const T_String& taskDesc) {
	m_TaskDescription = taskDesc;
	m_Task.getTaskName();
}

bool T_PrivTask::isEqual(const T_Object& otherObject) const {
	const T_PrivTask& other = dynamic_cast<const T_PrivTask&>(otherObject);
	return m_Task.getTaskName() == other.m_Task.getTaskName();
}

bool T_PrivTask::isLessThan(const T_Object& otherObject) const {
	const T_PrivTask& other = dynamic_cast<const T_PrivTask&>(otherObject);
	return m_Task.getTaskName() < other.m_Task.getTaskName();
}