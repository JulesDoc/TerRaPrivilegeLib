#include "T_TerRaProgram.hpp"

QMap<T_TerRaProgram::tagProgramName, T_String> T_TerRaProgram::m_tagToStringMap{};

T_TerRaProgram::T_TerRaProgram(const tagProgramName& tagProgramName) {
	qRegisterMetaTypeStreamOperators<T_TerRaProgram>("T_TerRaProgram");
	if (m_tagToStringMap.empty()) fillMap();
	setProgramName(tagProgramName);
}

T_TerRaProgram::T_TerRaProgram(const T_String& programName)  {
	m_ProgramStringName = programName;
	if (m_tagToStringMap.empty()) fillMap();
	setProgramName(m_tagToStringMap.key(m_ProgramStringName.trimmed(), INVALID));
}


void T_TerRaProgram::setProgramName(const tagProgramName& tagProgramName) {
	PRECONDITION(tagProgramName >= UNKNOWN && tagProgramName < UPPER_LIMIT);
	m_ProgramName = tagProgramName;
	setUnknown(tagProgramName == UNKNOWN);
}

void T_TerRaProgram::setProgramName(const T_String& programName) {
	setProgramName(m_tagToStringMap.key(programName.trimmed(), INVALID));
}

T_TerRaProgram::tagProgramName T_TerRaProgram::getProgramName() const {
	return m_ProgramName;
}

T_String T_TerRaProgram::getProgramStringName() const {
	return m_ProgramStringName;
}

bool T_TerRaProgram::isEqual(const T_Object& otherObject) const {
	const T_TerRaProgram& other = dynamic_cast<const T_TerRaProgram&>(otherObject);
	return m_ProgramName == other.m_ProgramName;
}

bool T_TerRaProgram::isLessThan(const T_Object& otherObject) const {
	const T_TerRaProgram& other = dynamic_cast<const T_TerRaProgram&>(otherObject);
	return m_ProgramName < other.m_ProgramName;
}

void T_TerRaProgram::writeTo(T_OSTREAM& out) const {
	PRECONDITION(!isUnknown() && !m_tagToStringMap.empty());
	auto it = m_tagToStringMap.find(m_ProgramName);
	out << *it;
}

void T_TerRaProgram::readFrom(T_ISTREAM& in) {
	T_String programName;
	in >> programName;
	setProgramName(programName);
}

void T_TerRaProgram::asString(T_String& sout) const {
	PRECONDITION(!isUnknown() && !m_tagToStringMap.empty());
	auto it = m_tagToStringMap.find(m_ProgramName);
	sout << *it;
}

void T_TerRaProgram::fillMap() {
	m_tagToStringMap.insert(UNKNOWN, QString());

	m_tagToStringMap.insert(T_MAESTRO, "Maestro Tester");
	m_tagToStringMap.insert(T_RUN_SINGLE_FXM_EXAM, "T_RUN_SINGLE_FXM_EXAM");
	m_tagToStringMap.insert(T_TERRABENCH, "TerRaBench");
	m_tagToStringMap.insert(T_TERRACAP, "TerRaCap");
	m_tagToStringMap.insert(T_TERRACONFIG, "TerRaConfig");
	m_tagToStringMap.insert(T_TERRALOG, "TerRaLog");
	m_tagToStringMap.insert(T_TERRANV, "TerRaNv");
	m_tagToStringMap.insert(T_TERRAPRIV, "TerRaPriv");
	m_tagToStringMap.insert(T_TERRAPUB, "TerRaPub");
	m_tagToStringMap.insert(T_TERRAQ, "TerRaQ");
	m_tagToStringMap.insert(T_TERRAREF, "TerRaRef");
	m_tagToStringMap.insert(T_TERRAREVFDG, "TerRaRevFdg");
	m_tagToStringMap.insert(T_TERRAREVQ, "TerRaRevQ");
	m_tagToStringMap.insert(T_TERRATRON, "TerRaTron");
}