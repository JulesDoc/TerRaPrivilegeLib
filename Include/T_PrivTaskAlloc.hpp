// *******************************************
//
//	File:		T_PrivTaskAlloc.hpp
//
//	Created:	13 August 2019
//	Author:		Julio Calvo
//
// *******************************************

#pragma once

#include "tstring.hpp"
#include "TSORTABL.hpp"
#include "TerRaPrivilegeLib.hpp"
#include "T_PrivUser.hpp"
#include "T_PrivTask.hpp"

T_CLASSDEF(T_PrivTaskAlloc)

class T_TERRAPRIVILEGELIBDEF_CLASS T_PrivTaskAlloc : public T_Object {

public:
	T_PrivTaskAlloc();
	T_PrivTaskAlloc(const T_PrivUser& privUser);
	virtual ~T_PrivTaskAlloc();

	void setPrivUser(const T_PrivUser& privUser);
	const T_PrivUser& getPrivUser() const;

	void setAllowedTasks(const QList<T_PrivTask>& listTasks);
	const QList<T_PrivTask>& getAllowedTasks() const;

	bool isTaskAllowed(const T_PrivTaskName& privTaskName) const;
	void appendAllowedTask(const T_PrivTask& privTask);

protected:
	virtual bool isEqual(const T_Object& object) const;
	virtual bool isLessThan(const T_Object& object) const;
	// archiving
	virtual void writeTo(T_OSTREAM& out) const;
	virtual void readFrom(T_ISTREAM& in);
	// formatting in strings
	virtual void asString(T_String& sout) const;

private:
	void check_and_set_unknown();

private:
	QList<T_PrivTask> m_AllowedTasks;
	T_PrivUser m_User;
};

Q_DECLARE_METATYPE(T_PrivTaskAlloc);