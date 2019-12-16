// *******************************************
//
//	File:		T_PrivTask.hpp
//
//  This class represents a Task which is composed by a name, a TerRaProgram and a descriiption
//
//	Created:	13 August 2019
//	Author:		Julio Calvo
//
// *******************************************

#pragma once

#include <QString>
#include <QVector>
#include <vector>

#include "tstring.hpp"
#include "T_Sortable.hpp"
#include "T_PrivTaskName.hpp"
#include "TerRaPrivilegeLib.hpp"
#include "T_TerRaProgram.hpp"
#include "T_UpdateBlock.hpp"

T_CLASSDEF(T_PrivTask)

class T_TERRAPRIVILEGELIBDEF_CLASS T_PrivTask : public T_Sortable {

public:
	T_PrivTask();
	T_PrivTask(const T_PrivTaskName& taskName, 
			   const T_TerRaProgram& program, 
		       const QString& taskDescription = QString());
	virtual ~T_PrivTask();
	const T_PrivTaskName& getPrivTaskName() const;
	void setPrivTaskName(const T_PrivTaskName& privTaskObj);

	const T_TerRaProgram& getTerraProgram() const;
	void setTerraProgram(const T_TerRaProgram& terraProgObj);

	const QString& getTaskDescription() const;
	void setTaskDescription(const QString& taskDesc);

	void setUpdateBlock(const T_UpdateBlock& updateBlock);
	const T_UpdateBlock& getUpdateBlock() const;

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
	T_PrivTaskName m_TaskName;
	T_TerRaProgram m_Program;
	QString m_TaskDescription;
	T_UpdateBlock m_UpdateBlock;
};

Q_DECLARE_METATYPE(T_PrivTask)

static uint qHash(const T_PrivTask &value)
{
	return value.isUnknown() ? 0 : 1;
}