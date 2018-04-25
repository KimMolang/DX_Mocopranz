#pragma once
// **64bit ������ __asm ��� ����� �Ұ�! http://girtowin.tistory.com/90
// error C4235: ��ǥ�� Ȯ���� ����: �� ��Ű��ó������ '__asm' Ű���带 ����� �� �����ϴ�.


// Check nullptr
#define CHECK_NULLPTR( _ptr )	\
{ if(_ptr == nullptr)  {/*__asm{ int 3 };*/ return; }}

#define CHECK_NULLPTR_RETURN( _ptr, _return )	\
{ if(_ptr == nullptr)  {/*__asm{ int 3 };*/ return _return; }}

#define CHECK_NULLPTR_MSG( _ptr, _message )	\
{ if(_ptr == nullptr)  { MessageBox(nullptr, _message, L"System Message", MB_OK); /*__asm{ int 3 };*/ return; }}

#define CHECK_NULLPTR_MSG_RETURN( _ptr, _message, _return )	\
{ if(_ptr == nullptr)  { MessageBox(nullptr, _message, L"System Message", MB_OK); /*__asm{ int 3 };*/ return _return; }}


// Check failed
#define CHECK_FAILED( _hr )	\
{ if( ((HRESULT)(_hr)) < 0 ) { /*__asm{ int 3 };*/ return E_FAIL; }}

#define CHECK_FAILED_RETURN( _hr, _return )	\
{ if( ((HRESULT)(_hr)) < 0 ) { /*__asm{ int 3 };*/ return _return; }}

#define CHECK_FAILED_MSG( _hr, _message )	\
{ if( ((HRESULT)(_hr)) < 0 )  { MessageBox(nullptr, _message, L"System Message", MB_OK); /*__asm{ int 3 };*/ return E_FAIL; }}

#define CHECK_FAILED_MSG_RETURN( _hr, _message, _return )	\
{ if( ((HRESULT)(_hr)) < 0 )  { MessageBox(nullptr, _message, L"System Message", MB_OK); /*__asm{ int 3 };*/ return _return; }}


// Check true or false
#define CHECK_FALSE_MSG( _bool, _message )	\
{ if( _bool == false ) { MessageBox(nullptr, _message, L"System Message", MB_OK); /*__asm{ int 3 };*/ return; }}

#define CHECK_TRUE_MSG( _bool, _message )	\
{ if( _bool == true ) { MessageBox(nullptr, _message, L"System Message", MB_OK); /*__asm{ int 3 };*/ return; }}

// assert
//#define ASSERT(expr, ...) if(!(expr)) __asm{ int 3 }

// Msg
#define MSG_BOX( _message )	MessageBox(nullptr, _message, L"System Message", MB_OK)
#define MSG_BOX_TAG( _message, _tag )	MessageBox(nullptr, _message, _tag, MB_OK)

