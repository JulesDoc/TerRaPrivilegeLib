#include "T_PrivTaskAlloc.hpp"

T_PrivTaskAlloc::T_PrivTaskAlloc() {}

T_PrivTaskAlloc::T_PrivTaskAlloc(const T_String& userName):m_User(userName){}

T_PrivTaskAlloc::~T_PrivTaskAlloc() {}

std::list<T_PrivTask>& T_PrivTaskAlloc::getListOfTasks() {
	return m_ListOfTasks;
}
