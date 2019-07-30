#include <T_SqlTableSelect.hpp>
#include <tsectaskallocrow.hpp>
#include <tsecusernamerow.hpp>
#include "T_PrivDBTransaction.hpp"

T_PrivDBTransaction::T_PrivDBTransaction(T_Database& rDatabase, bool bAutoCommit) : T_DBTransaction(rDatabase, bAutoCommit)
{
	reset();
}

T_PrivDBTransaction::~T_PrivDBTransaction() {}

bool T_PrivDBTransaction::doExec()
{
	switch (m_doExecAction)
	{
	case DELIVER_USER_INFO:
		return doExec_deliverUserInfo();
	case DELIVER_TASKS_IN_PROGRAM:
		return doExec_deliverTasksInProgram();
	case DELIVER_TASKS_ALLOC:
		return doExec_deliverTaskAllocation();
	default:
		VERIFY(FALSE);
		return false;
	}
}

T_PrivUser T_PrivDBTransaction::deliverUserInfo(const T_String& userName) {
	T_PrivUser result(userName);

	m_doExecAction = DELIVER_USER_INFO;
	m_pPrivUser = &result;
	m_pUserName = &userName;
	run();
	reset();

	return result;
}

std::vector<T_PrivTask> T_PrivDBTransaction::deliverTasksInProgram(const T_TerRaProgram& program)
{
	std::vector<T_PrivTask> result;

	m_doExecAction = DELIVER_TASKS_IN_PROGRAM;
	m_pVectorPrivTask = &result;
	m_pProgram = &program;
	run();
	reset();

	return result;
}

T_PrivTaskAlloc T_PrivDBTransaction::deliverTaskAllocation(const T_String& userName, const T_TerRaProgram& program)
{
	T_PrivTaskAlloc result(userName);

	m_doExecAction = DELIVER_TASKS_ALLOC;
	m_pPrivTaskAlloc = &result;
	m_pUserName = &userName;
	m_pProgram = &program;
	run();
	reset();

	return result;
}

void T_PrivDBTransaction::reset()
{
	m_doExecAction = UNKNOWN_DO_EXEC_ACTION;
	m_pVectorPrivTask = nullptr;
	m_pPrivTaskAlloc = nullptr;
	m_pProgram = nullptr;
	m_pUserName = nullptr;

}

bool T_PrivDBTransaction::doExec_deliverUserInfo() {

	std::vector<T_SECUsernameRow> rows;
	T_SqlTableSelect mySelect(database());
	T_SqlTableStatement searchCriteria;
	T_SqlFilter filter(QString::fromLatin1("username = ?"));

	filter.appendBindValue(*m_pUserName);
	searchCriteria.setTableName("sec_username");
	searchCriteria.setFilter(filter);

	mySelect.deliverRows(searchCriteria, rows);
	m_pPrivUser->setFirstName(QVariant(rows.front().m_first_name).toString());
	m_pPrivUser->setLastName(QVariant(rows.front().m_last_name).toString());
	return true;
}



bool T_PrivDBTransaction::doExec_deliverTasksInProgram() {

	PRECONDITION(!m_pProgram->isUnknown());

	std::vector<T_SECTaskRow> rows;
	T_SqlTableSelect mySelect(database());
	T_SqlTableStatement searchCriteria;

	T_SqlFilter filter(QString::fromLatin1("prog_name = ?"));
	filter.appendBindValue(m_pProgram->getProgramStringName());

	searchCriteria.setTableName("sec_task");
	searchCriteria.setFilter(filter);

	mySelect.deliverRows(searchCriteria, rows);
	m_pVectorPrivTask->reserve(100);
	for (auto element : rows) {
		m_pVectorPrivTask->emplace_back(T_PrivTask(
			T_PrivTaskName(QVariant(element.m_task_name).toString()),
			T_TerRaProgram(QVariant(element.m_prog_name).toString()),
			QVariant(element.m_task_desc).toString()));
	}
	return true;
}



bool T_PrivDBTransaction::doExec_deliverTaskAllocation() {

	std::vector<T_SECTaskallocRow> rows;
	T_SqlTableSelect mySelect(database());
	T_SqlTableStatement searchCriteria;

	T_SqlFilter filter(QString::fromLatin1("username= ?"));
	filter.appendBindValue(*m_pUserName);

	searchCriteria.setTableName("sec_taskalloc");
	searchCriteria.setFilter(filter);
	mySelect.deliverRows(searchCriteria, rows);
	for (auto element : rows) {
		T_PrivTaskName taskNameObj(QVariant(element.m_task_name).toString());
		T_PrivTask taskObj(taskNameObj);
		m_pPrivTaskAlloc->getListOfTasks().emplace_back(taskObj);
	}
	if (m_pProgram->isUnknown()) return true;

	/*Can't launch other commit because: 
	PRECONDITION(m_iTransInProgressCounter == 0); In terrabase.cpp line 144

	Otherwise, this could work:
	std::vector<T_PrivTask> vectorOfTaskInProgram;
	vectorOfTaskInProgram = deliverTasksInProgram(m_pProgram->getProgramName());

	Need to rewrite again deliverTaskInProgram*/

	std::vector<T_SECTaskRow> rowsSec;
	T_SqlTableSelect mySelectSec(database());
	T_SqlTableStatement searchCriteriaSec;

	T_SqlFilter filterSec(QString::fromLatin1("prog_name = ?"));
	filterSec.appendBindValue(m_pProgram->getProgramStringName());

	searchCriteriaSec.setTableName("sec_task");
	searchCriteriaSec.setFilter(filterSec);
	mySelectSec.deliverRows(searchCriteriaSec, rowsSec);

	std::vector<T_PrivTask> vectorOfTaskInProgram;
	vectorOfTaskInProgram.reserve(100);
	if (rowsSec.empty()) return false;
	for (auto element : rowsSec) {
		vectorOfTaskInProgram.emplace_back(T_PrivTask(
			T_PrivTaskName(QVariant(element.m_task_name).toString()),
			T_TerRaProgram(QVariant(element.m_prog_name).toString()),
			QVariant(element.m_task_desc).toString()));
	}

	//Having two vectors: one with the task related to user, one with the task related to program. Get list of tasks.
	std::list<T_PrivTask> auxList(m_pPrivTaskAlloc->getListOfTasks());
	for (auto element : m_pPrivTaskAlloc->getListOfTasks()) {
		auto it = std::find(vectorOfTaskInProgram.begin(), vectorOfTaskInProgram.end(), element);
		if (it == vectorOfTaskInProgram.end()) {
			auxList.remove(element);
		}
	}
	m_pPrivTaskAlloc->getListOfTasks() = auxList;

	return true;
}