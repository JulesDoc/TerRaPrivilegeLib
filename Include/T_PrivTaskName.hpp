#pragma once

#include "tstring.hpp"
#include "TSORTABL.hpp"
#include "TerRaPrivilegeLib.hpp"

T_CLASSDEF(T_PrivTaskName)

class T_TERRAPRIVILEGELIBDEF_CLASS T_PrivTaskName {
public:
	T_PrivTaskName(const T_String& taskName);
	virtual ~T_PrivTaskName();

	T_String getTaskName() const;
	void setTaskName(const T_String& taskName);

private:
	T_String m_TaskName;
};