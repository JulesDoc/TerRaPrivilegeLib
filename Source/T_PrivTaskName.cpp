#include "T_PrivTaskName.hpp"

T_PrivTaskName::T_PrivTaskName(const T_String& taskName) :
	m_TaskName(taskName) {}

T_PrivTaskName::~T_PrivTaskName() {}

T_String T_PrivTaskName::getTaskName() const {
	return m_TaskName;
}

void T_PrivTaskName::setTaskName(const T_String& taskName) {
	m_TaskName = taskName;
}