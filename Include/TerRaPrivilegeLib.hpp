// *******************************************
//
//	File:		TerRaPrivilegeLib.hpp
//
//	Created:	13 August 2019
//	Author:		Julio Calvo
//
// *******************************************

#pragma once

#if ( defined (T_TERRAPRIVILEGELIB_IMPL) )
#	define T_TERRAPRIVILEGELIBDEF_CLASS __declspec ( dllexport )
#	define T_TERRAPRIVILEGELIBDEF_EXPIMP
#else
#	define T_TERRAPRIVILEGELIBDEF_CLASS __declspec ( dllimport )
#	define T_TERRAPRIVILEGELIBDEF_EXPIMP extern
#endif