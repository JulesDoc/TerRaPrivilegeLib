// *******************************************
//
//	File:		T_PrivTaskName.hpp
//
//	Created:	13 August 2019
//	Author:		Julio Calvo
//
// *******************************************

#pragma once

#include "tstring.hpp"
#include "TSORTABL.hpp"
#include "TerRaPrivilegeLib.hpp"

T_CLASSDEF(T_PrivTaskName)

class T_TERRAPRIVILEGELIBDEF_CLASS T_PrivTaskName : public T_Sortable {
public:
	T_PrivTaskName();
	T_PrivTaskName(const QString& taskName);
	virtual ~T_PrivTaskName();

	const QString &getTaskName() const;
	void setTaskName(const QString& taskName);

protected:
	virtual T_BOOL isEqual(const T_Object& compObject) const;
	virtual T_BOOL isLessThan(const T_Object& compObject) const;
	// archiving
	virtual void writeTo(T_OSTREAM& out) const;
	virtual void readFrom(T_ISTREAM& in);
	// formatting in strings
	virtual void asString(T_String& sout) const;

private:
	QString m_TaskName;
};