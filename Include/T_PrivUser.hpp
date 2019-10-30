// *******************************************
//
//	File:		T_PrivUser.hpp
//
//	Created:	13 August 2019
//	Author:		Julio Calvo
//
// *******************************************

#pragma once

#include "tstring.hpp"
#include "TSORTABL.hpp"
#include "QString"
#include "T_UpdateBlock.hpp"
#include "TerRaPrivilegeLib.hpp"

T_CLASSDEF(T_PrivUser)

class T_TERRAPRIVILEGELIBDEF_CLASS T_PrivUser : public T_Object {
public:
	T_PrivUser();
	T_PrivUser(const QString& userName, const QString& firstName = QString(), const QString& lastName = QString());

	void setUserName(const QString& userName);
	const QString& getUserName() const;

	void setFirstName(const QString& firstName);
	const QString& getFirstName() const;

	void setLastName(const QString& lastName);
	const QString& getLastName() const;

	void setUpdateBlock(const T_UpdateBlock& updateBlock);
	const T_UpdateBlock& getUpdateBlock() const;

	virtual ~T_PrivUser() {};

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
	QString m_UserName;
	QString m_FirstName;
	QString m_LastName;
	T_UpdateBlock m_UpdateBlock;
};

Q_DECLARE_METATYPE(T_PrivUser);