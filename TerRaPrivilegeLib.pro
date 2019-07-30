
include(../terrasys.pri)

DEFINES += T_TERRAPRIVILEGELIB_IMPL
QT += xml core
 
SOURCES += \
	$$TERRA_SOURCE_DIR/T_PrivUser.cpp \
	$$TERRA_SOURCE_DIR/T_PrivTaskAlloc.cpp \
	$$TERRA_SOURCE_DIR/T_TerRaProgram.cpp \
	$$TERRA_SOURCE_DIR/T_PrivDBTransaction.cpp \
	$$TERRA_SOURCE_DIR/T_PrivTask.cpp \
	$$TERRA_SOURCE_DIR/T_PrivTaskName.cpp
	 
HEADERS += \  
	$$TERRA_INCLUDE_DIR/TerRaPrivilegeLib.hpp \
	$$TERRA_INCLUDE_DIR/T_PrivUser.hpp \
	$$TERRA_INCLUDE_DIR/T_PrivTaskAlloc.hpp \
	$$TERRA_INCLUDE_DIR/T_TerRaProgram.hpp \
	$$TERRA_INCLUDE_DIR/T_PrivDBTransaction.hpp \
	$$TERRA_INCLUDE_DIR/T_PrivTask.hpp \
	$$TERRA_INCLUDE_DIR/T_PrivTaskName.hpp
	
