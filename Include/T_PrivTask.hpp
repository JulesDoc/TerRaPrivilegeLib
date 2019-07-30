#pragma once
#include <QString>

#include "tstring.hpp"
#include "TSORTABL.hpp"
#include "T_PrivTaskName.hpp"
#include "TerRaPrivilegeLib.hpp"
#include "T_TerRaProgram.hpp"

T_CLASSDEF(T_PrivTask)

class T_TERRAPRIVILEGELIBDEF_CLASS T_PrivTask : public T_Sortable {
public:
	T_PrivTask(const T_PrivTaskName& taskName);
	T_PrivTask(const T_PrivTaskName& taskName, const T_TerRaProgram& program, const T_String& taskDescription = QString());
	virtual ~T_PrivTask();

	T_String getTaskName() const;

	T_String getTaskDescription() const;
	void setTaskDescription(const T_String& taskDesc);

	bool isEqual(const T_Object& object) const;
	
	bool isLessThan(const T_Object& object) const override;

private:
	T_PrivTaskName m_Task;
	T_TerRaProgram m_Program;
	T_String m_TaskDescription;
	
};
