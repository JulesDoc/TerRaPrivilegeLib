#pragma once

#include <QMetaType.h>
#include <QMap>

#include "TString.hpp"
#include "TSortabl.hpp"
#include "TerRaPrivilegeLib.hpp"

T_CLASSDEF(T_TerRaProgram)

class T_TERRAPRIVILEGELIBDEF_CLASS T_TerRaProgram : public T_Sortable {

public:
	enum tagProgramName {
		INVALID,     
		UNKNOWN,    
		T_MAESTRO,
		T_RUN_SINGLE_FXM_EXAM,
		T_TERRABENCH,
		T_TERRACAP,
		T_TERRACONFIG,
		T_TERRALOG,
		T_TERRANV,
		T_TERRAPRIV,
		T_TERRAPUB,
		T_TERRAQ,
		T_TERRAREF,
		T_TERRAREVFDG,
		T_TERRAREVQ,
		T_TERRATRON,
		UPPER_LIMIT
	};
	
public:
	T_TerRaProgram(const tagProgramName& programName = UNKNOWN);
	T_TerRaProgram(const T_String& programName);
	virtual ~T_TerRaProgram() {};

	void setProgramName(const tagProgramName& tagProgramName);
	void setProgramName(const T_String& programName);
	tagProgramName getProgramName() const;
	T_String getProgramStringName() const;

	bool isEqual(const T_Object& object) const override;

	bool isLessThan(const T_Object& object) const override;

	void writeTo(T_OSTREAM& out) const override;
	void readFrom(T_ISTREAM& in) override;
	void asString(T_String& sout) const override;

private:
	tagProgramName m_ProgramName;
	T_String m_ProgramStringName;
	static QMap<tagProgramName, T_String> m_tagToStringMap;

private:
	static void fillMap();
	
};

Q_DECLARE_METATYPE(T_TerRaProgram)