#pragma once

#include <T_Row.hpp>
#include <T_Database.hpp>
#include <T_DBTransaction.hpp>
#include <TSEC.h>

#include "T_PrivTaskAlloc.hpp"
#include "T_PrivTask.hpp"
#include "T_PrivUser.hpp"
#include "T_TerRaProgram.hpp"
#include "tstring.hpp"
#include "TerRaPrivilegeLib.hpp"

T_CLASSDEF(T_PrivDBTransaction)

class T_TERRAPRIVILEGELIBDEF_CLASS T_PrivDBTransaction : public T_DBTransaction {
public:
	T_PrivDBTransaction(T_Database& rDatabase, bool bAutoCommit);
	virtual ~T_PrivDBTransaction();

	//return user information related to first and second name.
	T_PrivUser deliverUserInfo(const T_String& userName);

	//deliver a list of PrivTask objects composing a given program.
	std::vector<T_PrivTask> deliverTasksInProgram(const T_TerRaProgram& program);

	/*deliver a PrivTaskAlloc OBJ with a list of PrivTask OBJs for a given user
	and for a given program. By default, constructor only needs to know the user.*/
	T_PrivTaskAlloc deliverTaskAllocation(const T_String& userName, const T_TerRaProgram& program = T_TerRaProgram());
	
private://methods
	void reset();
	bool doExec();
	bool doExec_deliverUserInfo();
	bool doExec_deliverTasksInProgram();
	bool doExec_deliverTaskAllocation();

private://attributes
	enum tagDoExecAction {
		UNKNOWN_DO_EXEC_ACTION,
		DELIVER_USER_INFO,
		DELIVER_TASKS_IN_PROGRAM,
		DELIVER_TASKS_ALLOC,
	};

	tagDoExecAction m_doExecAction;
	std::vector<T_PrivTask>* m_pVectorPrivTask;
	const T_TerRaProgram* m_pProgram;
	const T_String* m_pUserName;
	T_PrivTaskAlloc* m_pPrivTaskAlloc;
	T_PrivUser * m_pPrivUser;

};