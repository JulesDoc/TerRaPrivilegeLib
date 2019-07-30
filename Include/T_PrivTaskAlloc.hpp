#pragma once

#include "tstring.hpp"
#include "TSORTABL.hpp"
#include "TerRaPrivilegeLib.hpp"
#include "T_PrivUser.hpp"
#include "T_PrivTask.hpp"

T_CLASSDEF(T_PrivTaskAlloc)

class T_TERRAPRIVILEGELIBDEF_CLASS T_PrivTaskAlloc {
public:
	T_PrivTaskAlloc();
	T_PrivTaskAlloc(const T_String& userName);
	virtual ~T_PrivTaskAlloc();

	std::list<T_PrivTask>& getListOfTasks();

private:
	std::list<T_PrivTask> m_ListOfTasks;
	T_PrivUser m_User;
};