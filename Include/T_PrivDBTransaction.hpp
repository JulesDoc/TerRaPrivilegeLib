// *******************************************
//
//	File:		T_PrivDBTransaction.hpp
//
//	Created:	13 August 2019
//	Author:		Julio Calvo
//
// *******************************************

#pragma once

#include <T_Row.hpp>
#include <T_Database.hpp>
#include <T_BaseDBTransaction.hpp>
#include <T_DateUpdatedRecycleCondition.hpp>
#include <QStringList>
#include <QSet>
#include <QVector>

#include "T_PrivTaskAlloc.hpp"
#include "T_PrivTask.hpp"
#include "T_PrivUser.hpp"
#include "T_TerRaProgram.hpp"
#include "TerRaPrivilegeLib.hpp"


T_CLASSDEF(T_PrivDBTransaction)

class T_TERRAPRIVILEGELIBDEF_CLASS T_PrivDBTransaction : public T_BaseDBTransaction {
public:
	T_PrivDBTransaction(T_Database& rDatabase, bool bAutoCommit);
	virtual ~T_PrivDBTransaction();

	//return the list of current users
	QVector<T_PrivUser> deliverListOfUsers();

	//return the list of users with permision to execute a given task
	QVector<T_PrivUser> deliverListOfUserInTask(const QString& taskName);

	//return the list of current Objs T_PrivTask from sec_task
	QMultiMap<T_TerRaProgram, T_PrivTask> deliverListOfTasks();

	//return the list of current programs
	QSet<QString> deliverListOfPrograms();

	//return user information related to first and second name.
	T_PrivUser deliverUserInfo(const QString& userName);

	//deliver a list of PrivTask objects composing a given program.
	QVector<T_PrivTask> deliverTasksInProgram(const T_TerRaProgram& program);

	QVector<T_PrivTaskAlloc> deliverTaskAllocationAllUsers();
	/*deliver a PrivTaskAlloc OBJ with a list of PrivTask OBJs for a given user
	and for a given program. By default, constructor only needs to know the user.*/
	T_PrivTaskAlloc deliverTaskAllocation(const QString& userName, const T_TerRaProgram& program = T_TerRaProgram());

	void updateTasksUser(const QVector<QString>& tasksToDB, const QVector<QString>& tasksFromDB, 
						 const QString& userName, const T_DateUpdatedRecycleCondition& rcRecycleCondition);
	//void setTaskUser(const QString& userName, const QStringList& taskNames, const T_DateUpdatedRecycleCondition& rcRecycleCondition);
	//void updateOrInsertPrivUser(const T_PrivTaskAlloc &rcPrivTaskAlloc);

private://methods

	//bool doExec_updateOrInsertPrivUser(const T_PrivTaskAlloc &rcPrivTaskAlloc);
	bool doExec_deliverTaskAllocation(const QString& rUserName, const T_TerRaProgram& rProgram, T_PrivTaskAlloc& rPrivTaskAlloc);
	bool doExec_updateTasksUser(const QVector<QString>& tasksToDB, const QVector<QString>& tasksFromDB,
								const QString& userName, const T_DateUpdatedRecycleCondition& rcRecycleCondition);
};