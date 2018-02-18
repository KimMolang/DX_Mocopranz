#include "stdafx.h"
#include "KeyChecker.h"

BEGIN(Engine)
IMPLEMENT_SINGLETON(KeyChecker)


KeyChecker::KeyChecker()
: m_pInput(NULL)
, m_pKeyBoardDevice(NULL)
, m_pMouseDevice(NULL)

, m_bMouseDown(false)
, m_bMousePressed(false)
{
	ZeroMemory(m_byKeyState, sizeof(BYTE) * MAX);
	ZeroMemory(&m_eMouseState, sizeof(DIMOUSESTATE));

	ZeroMemory(&m_bKeyDown, sizeof(bool) * MAX);
	ZeroMemory(&m_bKeyPressd, sizeof(bool) * MAX);
}

KeyChecker::~KeyChecker()
{
	Release();
}

HRESULT KeyChecker::Init(HINSTANCE _hInst, HWND _hWnd)
{
	CHECK_FAILED_MSG_RETURN(DirectInput8Create(
		_hInst
		, DIRECTINPUT_VERSION
		, IID_IDirectInput8
		, (void**)&m_pInput
		, NULL)
			, L"FAILED Create the Direct Input"
			, E_FAIL);

	CHECK_FAILED_MSG_RETURN(InitKeyboard(_hWnd), L"FAILED Create Keyboard", E_FAIL);
	CHECK_FAILED_MSG_RETURN(InitMouse(_hWnd), L"FAILED Create Mouse", E_FAIL);


	return S_OK;
}

HRESULT KeyChecker::InitKeyboard(HWND _hWnd)
{
	CHECK_FAILED(
		m_pInput->CreateDevice(GUID_SysKeyboard, &m_pKeyBoardDevice, NULL));

	m_pKeyBoardDevice->SetCooperativeLevel(_hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
	m_pKeyBoardDevice->SetDataFormat(&c_dfDIKeyboard);
	m_pKeyBoardDevice->Acquire();

	return S_OK;
}

HRESULT KeyChecker::InitMouse(HWND _hWnd)
{
	CHECK_FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pMouseDevice, NULL));

	m_pMouseDevice->SetCooperativeLevel(_hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
	m_pMouseDevice->SetDataFormat(&c_dfDIMouse);
	m_pMouseDevice->Acquire();

	return S_OK;
}

void KeyChecker::UpdateInputState()
{
	m_pKeyBoardDevice->GetDeviceState(MAX, m_byKeyState);
	m_pMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), &m_eMouseState);
}

bool KeyChecker::CheckKeyboardDown(BYTE _byKeyFlag)
{
	if (CheckKeyboardPressed(_byKeyFlag))
		m_bKeyDown[_byKeyFlag] = false;

	if (m_bKeyPressd[_byKeyFlag] && !(m_bKeyDown[_byKeyFlag]))
	{
		m_bKeyDown[_byKeyFlag] = true;
		return true;
	}

	return false;
}

bool KeyChecker::CheckKeyboardPress(BYTE _byKeyFlag)
{
	if (m_byKeyState[_byKeyFlag] & 0x80)
		return true;

	return false;
}

bool KeyChecker::CheckKeyboardPressed(BYTE _byKeyFlag)
{
	if (m_byKeyState[_byKeyFlag] & 0x80)
	{
		m_bKeyPressd[_byKeyFlag] = true;
		return false;
	}
	else if (m_bKeyPressd[_byKeyFlag])
	{
		if (!(m_byKeyState[_byKeyFlag] & 0x80))
		{
			m_bKeyPressd[_byKeyFlag] = false;
			return true;
		}
	}

	return false;
}

bool KeyChecker::CheckMouseDown(EMouseType _eKeyFlag)
{
	if (CheckMousePressed(_eKeyFlag))
		m_bMouseDown = false;

	if (m_bMousePressed && !(m_bMouseDown))
	{
		m_bMouseDown = true;
		return true;
	}

	return false;
}

bool KeyChecker::CheckMousePress(EMouseType _eKeyFlag)
{
	if (m_eMouseState.rgbButtons[_eKeyFlag] & 0x80)
		return true;

	return false;
}

bool KeyChecker::CheckMousePressed(EMouseType _eKeyFlag)
{
	if (m_eMouseState.rgbButtons[_eKeyFlag] & 0x80)
	{
		m_bMousePressed = true;
		return false;
	}
	else if (m_bMousePressed)
	{
		if (!(m_eMouseState.rgbButtons[_eKeyFlag] & 0x80))
		{
			m_bMousePressed = false;
			return true;
		}
	}

	return false;
}

void KeyChecker::Release()
{
	Safe_Release(m_pMouseDevice);
	Safe_Release(m_pKeyBoardDevice);
	Safe_Release(m_pInput);
}


END