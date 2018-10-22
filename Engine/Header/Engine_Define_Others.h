#pragma once


// Get & Set
#define GET(DATATYPE, ARGNAME, MYDATANAME)				\
inline const DATATYPE& Get##ARGNAME() { return MYDATANAME; }

#define SET(DATATYPE, ARGNAME, MYDATANAME)				\
inline void Set##ARGNAME( const DATATYPE& _data ) { MYDATANAME = _data; }	

#define GET_AND_SET(DATATYPE, ARGNAME, MYDATANAME)		\
GET(DATATYPE, ARGNAME, MYDATANAME)						\
SET(DATATYPE, ARGNAME, MYDATANAME)


#define ARRAY_CNT( arr ) sizeof(arr)/sizeof(x[0])