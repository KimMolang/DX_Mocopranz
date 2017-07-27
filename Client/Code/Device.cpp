#include "stdafx.h"
#include "Device.h"

extern HWND		g_hWnd;

IMPLEMENT_SINGLETON(CDevice)

const float CDevice::COLOR_BACKBUFFER[COLOR_NUM] = { 0.2f, 0.2f, 0.6f, 1.f };


CDevice::CDevice()
: m_pDevice(nullptr)
, m_pDeviceContext(nullptr)

, m_pSwapChain(nullptr)
, m_pRenderTargetView(nullptr)
, m_pDepthStencilBuffer(nullptr)
, m_pDepthStencilView(nullptr)
{
}


CDevice::~CDevice()
{
	Release();
}

HRESULT CDevice::Init(WinMode _eWinMode)
{
	UINT	deviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
	deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif


	D3D_FEATURE_LEVEL	tFeatureLevel;
	FAILED_CHECK(D3D11CreateDevice(0, D3D_DRIVER_TYPE_HARDWARE,
		0, deviceFlags, 0, 0, D3D11_SDK_VERSION,
		&m_pDevice, &tFeatureLevel, &m_pDeviceContext));

	if (tFeatureLevel != D3D_FEATURE_LEVEL_11_0)
	{
		MSG_BOX(_T("Direct3D Feature Level 11 unsupported."));
		return S_FALSE;
	}


	UINT      msaaQuality;
	FAILED_CHECK(m_pDevice->CheckMultisampleQualityLevels(
		DXGI_FORMAT_R8G8B8A8_UINT, 4, &msaaQuality));


	DXGI_SWAP_CHAIN_DESC tSwapChain;
	tSwapChain.BufferDesc.Width = (UINT)CLIENT_WINCX;
	tSwapChain.BufferDesc.Height = (UINT)CLIENT_WINCY;

	tSwapChain.BufferDesc.RefreshRate.Numerator = 60;
	tSwapChain.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	tSwapChain.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	tSwapChain.BufferDesc.RefreshRate.Denominator = 1;
	tSwapChain.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	tSwapChain.SampleDesc.Count = 1;
	tSwapChain.SampleDesc.Quality = 0;

	tSwapChain.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	tSwapChain.BufferCount = 1;
	tSwapChain.OutputWindow = g_hWnd;
	tSwapChain.Windowed = _eWinMode;
	tSwapChain.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	tSwapChain.Flags = 0;


	IDXGIDevice* dxgiDevice = 0;
	FAILED_CHECK(m_pDevice->QueryInterface(
		__uuidof(IDXGIDevice), (void**)&dxgiDevice));


	IDXGIAdapter* dxgiAdapter = 0;
	FAILED_CHECK(dxgiDevice->GetParent(
		__uuidof(IDXGIAdapter), (void**)&dxgiAdapter));


	IDXGIFactory* dxgiFactory = 0;
	FAILED_CHECK(dxgiAdapter->GetParent(
		__uuidof(IDXGIFactory), (void**)&dxgiFactory));


	FAILED_CHECK(dxgiFactory->CreateSwapChain(m_pDevice, &tSwapChain, &m_pSwapChain));


	::Safe_Release(dxgiDevice);
	::Safe_Release(dxgiAdapter);
	::Safe_Release(dxgiFactory);


	FAILED_CHECK(m_pSwapChain->ResizeBuffers(
		1, (UINT)CLIENT_WINCX, (UINT)CLIENT_WINCY, DXGI_FORMAT_R8G8B8A8_UNORM, 0));


	ID3D11Texture2D* pBackBuffer;
	FAILED_CHECK(m_pSwapChain->GetBuffer(
		0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&pBackBuffer)));

	FAILED_CHECK(m_pDevice->CreateRenderTargetView(pBackBuffer, 0, &m_pRenderTargetView));


	::Safe_Release(pBackBuffer);


	D3D11_TEXTURE2D_DESC tDepthStencil;

	tDepthStencil.Width = (UINT)CLIENT_WINCX;
	tDepthStencil.Height = (UINT)CLIENT_WINCY;
	tDepthStencil.MipLevels = 1;
	tDepthStencil.ArraySize = 1;
	tDepthStencil.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	tDepthStencil.SampleDesc.Count = 1;
	tDepthStencil.SampleDesc.Quality = 0;

	tDepthStencil.Usage = D3D11_USAGE_DEFAULT;
	tDepthStencil.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	tDepthStencil.CPUAccessFlags = 0;
	tDepthStencil.MiscFlags = 0;


	FAILED_CHECK(m_pDevice->CreateTexture2D(
		&tDepthStencil, 0, &m_pDepthStencilBuffer));

	FAILED_CHECK(m_pDevice->CreateDepthStencilView(
		m_pDepthStencilBuffer, 0, &m_pDepthStencilView));


	m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);


	FAILED_CHECK(Init_Blend());
	return S_OK;
}

HRESULT CDevice::Init_Blend()
{
	D3D11_BLEND_DESC tBlend;
	ZeroMemory(&tBlend, sizeof(D3D11_BLEND_DESC));

	tBlend.AlphaToCoverageEnable = true;
	tBlend.IndependentBlendEnable = false;
	tBlend.RenderTarget[0].BlendEnable = true;
	tBlend.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	tBlend.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	tBlend.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	tBlend.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	tBlend.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	tBlend.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	tBlend.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	FAILED_CHECK_RETURN(m_pDevice->CreateBlendState(&tBlend, &m_pBlendState), E_FAIL);

	return S_OK;
}

void CDevice::Release()
{
	::Safe_Release(m_pDepthStencilView);
	::Safe_Release(m_pDepthStencilBuffer);
	::Safe_Release(m_pRenderTargetView);
	::Safe_Release(m_pSwapChain);
	::Safe_Release(m_pBlendState);
	::Safe_Release(m_pDeviceContext);
	::Safe_Release(m_pDevice);
}

void CDevice::Render_Begin(void)
{
	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, COLOR_BACKBUFFER);
	m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
}

void CDevice::Render_End(void)
{
	FAILED(m_pSwapChain->Present(0, 0));
}

void CDevice::Blend_Begin()
{
	m_pDeviceContext->OMSetBlendState(m_pBlendState, nullptr, 0xffffffff);
}

void CDevice::Blend_End()
{
	m_pDeviceContext->OMSetBlendState(nullptr, nullptr, 0xffffffff);
}