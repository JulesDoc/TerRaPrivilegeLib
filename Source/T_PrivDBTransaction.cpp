// *******************************************
//
//	File:		T_PrivDBTransaction.cpp
//
//	Created:	13 August 2019
//	Author:		Julio Calvo
//
// *******************************************

#include <T_ExecuteSQL.hpp>
#include <TSEC.h>
#include "T_RowTreeDBFact.hpp"
#include "T_PrivDBTransaction.hpp"
#include "T_UpdateBlock.hpp"
#include "T_RowDBFact.hpp"

T_PrivDBTransaction::T_PrivDBTransaction(T_Database& rDatabase, bool bAutoCommit) : T_BaseDBTransaction(rDatabase, bAutoCommit) {}
T_PrivDBTransaction::~T_PrivDBTransaction() {}

T_PrivUser T_PrivDBTransaction::deliverUserInfo(const QString& userName)
{
	T_PrivUser privUserObj(userName);

	T_ExecuteSQL aExecuteSQL(database(), isAutoCommit());
	QVector<T_SECUsernameRow> rows;
	T_SqlTableStatement sqlStatement;

	sqlStatement.setTableName(SEC_USERNAME_NAME);

	T_SqlFilter filter(QString::fromLatin1("username = ?"));
	filter.appendBindValue(userName);
	sqlStatement.setFilter(filter);

	aExecuteSQL.deliverRows(sqlStatement, rows);

	VERIFY(rows.size() <= 1);
	if (!rows.empty())
	{
		privUserObj.setFirstName(QVariant(rows.front().first_name()).toString());
		privUserObj.setLastName(QVariant(rows.front().last_name()).toString());
		T_SrcUpdate srcObj(QVariant(rows.front().src_update()).toString());
		T_DateUpdated dateObj(QVariant(rows.front().d_updated()).toDateTime());
		T_UpdateBlock updateBlockObj(srcObj, dateObj);
		privUserObj.setUpdateBlock(updateBlockObj);
	}

	return privUserObj;
}

QVector<T_PrivUser> T_PrivDBTransaction::deliverListOfUsers()
{
	QVector<T_PrivUser> listOfUsers;
	QVector<T_SECUsernameRow> rows;
	T_ExecuteSQL aExecuteSQL(database(), isAutoCommit());
	T_SqlTableStatement sqlStatement;

	sqlStatement.setTableName(SEC_USERNAME_NAME);
	aExecuteSQL.deliverRows(sqlStatement, rows);

	if (!rows.empty())
	{
		for (auto element : rows)
		{
			listOfUsers.push_back(deliverUserInfo((QVariant(element.username()).toString())));
		}
	}

	return listOfUsers;
}

QVector<T_PrivUser> T_PrivDBTransaction::deliverListOfUserInTask(const QString& taskName)
{
	QVector<T_PrivUser> vUsers;
	QVector<T_SECTaskallocRow> rows;
	T_ExecuteSQL aExecuteSQL(database(), isAutoCommit());
	T_SqlTableStatement sqlStatement;

	sqlStatement.setTableName(SEC_TASKALLOC_NAME);

	T_SqlFilter filter(QString::fromLatin1("task_name = ?"));
	filter.appendBindValue(taskName);
	sqlStatement.setFilter(filter);

	aExecuteSQL.deliverRows(sqlStatement, rows);

	if (!rows.empty())
	{
		for (auto element : rows)
		{
			vUsers.push_back(deliverUserInfo((QVariant(element.username()).toString())));
		}
	}

	return vUsers;

}

QMultiMap<T_TerRaProgram, T_PrivTask> T_PrivDBTransaction::deliverListOfTasks()
{
	QMultiMap<T_TerRaProgram, T_PrivTask> aMap;
	T_ExecuteSQL aExecuteSQL(database(), isAutoCommit());
	QVector<T_SECTaskRow> rows;
	T_SqlTableStatement sqlStatement;

	sqlStatement.setTableName(SEC_TASK_NAME);
	aExecuteSQL.deliverRows(sqlStatement, rows);

	if (!rows.empty())
	{
		for (auto element : rows)
		{
			T_TerRaProgram pr = T_String(element.prog_name().toString());
			T_PrivTaskName name = T_String(element.task_name().toString());
			QString desc = element.task_desc().toString();
			T_SrcUpdate srcObj(QVariant(element.src_update()).toString());
			T_DateUpdated dateObj(QVariant(element.d_updated()).toDateTime());
			T_UpdateBlock updateBlockObj(srcObj, dateObj);
			T_PrivTask privTaskObj(name, pr, desc);
			privTaskObj.setUpdateBlock(updateBlockObj);
			aMap.insert(pr, privTaskObj);
		}
	}

	return aMap;
}


QSet<QString> T_PrivDBTransaction::deliverListOfPrograms()
{
	QSet<QString> setString;

	QVector<T_SECTaskRow> rows;
	T_ExecuteSQL aExecuteSQL(database(), isAutoCommit());
	T_SqlTableStatement sqlStatement;

	sqlStatement.setTableName(SEC_TASK_NAME);
	aExecuteSQL.deliverRows(sqlStatement, rows);

	if (!rows.empty())
	{
		for (auto element : rows)
		{
			setString.insert(QVariant(element.prog_name()).toString());
		}
	}

	return setString;
}



QVector<T_PrivTask> T_PrivDBTransaction::deliverTasksInProgram(const T_TerRaProgram& rProgram)
{

	PRECONDITION(!rProgram.isUnknown());

	QVector<T_PrivTask> allowedTasks;
	QVector<T_SECTaskRow> rows;
	T_ExecuteSQL aExecuteSQL(database(), isAutoCommit());
	T_SqlTableStatement searchCriteria;
	T_SqlFilter filter(QString::fromLatin1("prog_name = ?"));

	filter.appendBindValue(rProgram.asDBString());
	searchCriteria.setTableName(SEC_TASK_NAME);
	searchCriteria.setFilter(filter);
	aExecuteSQL.deliverRows(searchCriteria, rows);

	allowedTasks.reserve(100);
	for (auto element : rows) {
		T_TerRaProgram pr = T_String(element.prog_name().toString());
		T_PrivTaskName name = T_String(element.task_name().toString());
		QString desc = element.task_desc().toString();
		T_SrcUpdate srcObj(QVariant(element.src_update()).toString());
		T_DateUpdated dateObj(QVariant(element.d_updated()).toDateTime());
		T_UpdateBlock updateBlockObj(srcObj, dateObj);
		T_PrivTask privTaskObj(name, pr, desc);
		privTaskObj.setUpdateBlock(updateBlockObj);
		allowedTasks.push_back(privTaskObj);
	}
	return allowedTasks;
}

QVector<T_PrivTaskAlloc> T_PrivDBTransaction::deliverTaskAllocationAllUsers()
{
	QVector<T_PrivTaskAlloc> result;
	QVector<T_PrivUser> vectorUsers = deliverListOfUsers();
	for (auto user : vectorUsers)
	{
		result.push_back(deliverTaskAllocation(user.getUserName()));
	}
	return result;
}

T_PrivTaskAlloc T_PrivDBTransaction::deliverTaskAllocation(const QString& rPrivUser, const T_TerRaProgram& rProgram)
{
	T_PrivTaskAlloc result(rPrivUser);
	runWithinTransaction(this, &T_PrivDBTransaction::doExec_deliverTaskAllocation, rPrivUser, rProgram, result);
	return result;
}

bool T_PrivDBTransaction::doExec_deliverTaskAllocation(const QString& rUserName, const T_TerRaProgram& rProgram, T_PrivTaskAlloc& rPrivTaskAlloc) {

	QVector<T_SECTaskRow> rows;
	T_ExecuteSQL mySelect(database(), false);
	T_SqlTableStatement searchCriteria;
	T_SqlFilter filter;

	if (!rProgram.isUnknown())
	{
		filter.setFilter(QString::fromLatin1("prog_name = :prog_name AND task_name IN (SELECT task_name FROM sec_taskalloc WHERE username = :username)"));
		filter.appendNamedBindValue(":username", rUserName);
		filter.appendNamedBindValue(":prog_name", rProgram.asDBString());
	}
	else
	{
		filter.setFilter(QString::fromLatin1("task_name IN (SELECT task_name FROM sec_taskalloc WHERE username = :username)"));
		filter.appendNamedBindValue(":username", rUserName);
	}

	searchCriteria.setTableName(SEC_TASK_NAME);
	searchCriteria.setFilter(filter);
	mySelect.deliverRows(searchCriteria, rows);

	T_PrivDBTransaction aDBTransaction(database(), false);
	T_PrivUser privUserObj = aDBTransaction.deliverUserInfo(rUserName);
	rPrivTaskAlloc.setPrivUser(privUserObj);

	for (auto element : rows) {
		T_PrivTaskName taskNameObj(QVariant(element.task_name()).toString());
		T_TerRaProgram programObj(QVariant(element.prog_name()).toString());
		T_PrivTask privTaskObj(taskNameObj, programObj);
		T_SrcUpdate srcObj(QVariant(element.src_update()).toString());
		T_DateUpdated dateObj(QVariant(element.d_updated()).toDateTime());
		T_UpdateBlock updateBlockObj(srcObj, dateObj);
		privTaskObj.setTaskDescription(QVariant(element.task_desc()).toString());
		privTaskObj.setUpdateBlock(updateBlockObj);
		rPrivTaskAlloc.appendAllowedTask(privTaskObj);
	}

	return true;
}

void T_PrivDBTransaction::updateTasksUser(const QVector<QString>& tasksToDB, const QVector<QString>& tasksFromDB,
										  const QString & rUserName, const T_DateUpdatedRecycleCondition& rcRecycleCondition)
{
	runWithinTransaction(this, &T_PrivDBTransaction::doExec_updateTasksUser, tasksToDB, tasksFromDB, rUserName, rcRecycleCondition);
}
bool T_PrivDBTransaction::doExec_updateTasksUser(const QVector<QString>& tasksToDB, const QVector<QString>& tasksFromDB, 
												 const QString & rUserName, const T_DateUpdatedRecycleCondition& rcRecycleCondition)
{
	T_RowDBFact aRowDBFact(database(), false);
	T_SECUsernameRow newRow;
	newRow.set_src_update(T_Database::getSrcUpdateFromProgramName());
	newRow.set_d_updated(QDateTime::currentDateTime());
	T_SECUsernameRow filterRow;
	filterRow.set_username(rUserName);
	bool ok = aRowDBFact.execSqlUpdate(newRow, filterRow, rcRecycleCondition);
	if (ok)
	{
		for (auto task : tasksToDB) {
			T_SECTaskallocRow filterAllocRow;
			filterAllocRow.set_username(rUserName);
			filterAllocRow.set_task_name(task);
			aRowDBFact.execSqlInsert(filterAllocRow);
		}

		for (auto task : tasksFromDB) {
			T_SECTaskallocRow filterAllocRow;
			filterAllocRow.set_username(rUserName);
			filterAllocRow.set_task_name(task);
			aRowDBFact.execSqlDelete(filterAllocRow);
		}
	}
	return true;
}




