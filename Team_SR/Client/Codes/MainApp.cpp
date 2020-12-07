#include "stdafx.h"
#include "MainApp.h"
#include "Logo.h"
#include "Player.h"

CMainApp::CMainApp()
	: m_pManagement(CManagement::Get_Instance())
{
	SafeAddRef(m_pManagement);
}

HRESULT CMainApp::ReadyMainApp()
{
	if (FAILED(m_pManagement->ReadyEngine(g_hWnd, WINCX, WINCY, 
		EDisplayMode::Window, (_uint)ESceneID::MaxCount)))
	{
		PRINT_LOG(L"Error", L"Failed To ReadyEngine");
		return E_FAIL;
	}

	m_pDevice = m_pManagement->GetDevice();
	if (nullptr == m_pDevice)
		return E_FAIL;

	SafeAddRef(m_pDevice);

	if (FAILED(ReadyStaticResources()))
		return E_FAIL;

	if (FAILED(ReadyDefaultSetting()))
		return E_FAIL;

	if (FAILED(m_pManagement->SetUpCurrentScene((_int)ESceneID::Logo,
		CLogo::Create(m_pDevice))))
	{
		PRINT_LOG(L"Error", L"Failed To SetUpCurrentScene");
		return E_FAIL;
	}	

	return S_OK;
}

int CMainApp::UpdateMainApp()
{
	m_pManagement->UpdateEngine();
	m_pManagement->RenderEngine();

	return 0;
}

HRESULT CMainApp::ReadyStaticResources()
{
	/* For.GameObject */
#pragma region GameObject_Player
	if (FAILED(m_pManagement->AddGameObjectPrototype(
		(_int)ESceneID::Static,
		L"GameObject_Player",
		CPlayer::Create(m_pDevice))))
		return E_FAIL;
#pragma endregion

	/* For.Component */

#pragma region Component_VIBuffer_RectTexture
	if (FAILED(m_pManagement->AddComponentPrototype(
		(_int)ESceneID::Static,
		L"Component_VIBuffer_RectTexture",
		CVIBuffer_RectTexture::Create(m_pDevice))))
		return E_FAIL;
#pragma endregion


#pragma region Component_Transform
	if (FAILED(m_pManagement->AddComponentPrototype(
		(_int)ESceneID::Static,
		L"Component_Transform",
		CTransform::Create(m_pDevice))))
		return E_FAIL;
#pragma endregion
#pragma region Component_Texture_Player

#pragma endregion

	return S_OK;
}

HRESULT CMainApp::ReadyDefaultSetting()
{
	if (FAILED(m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE)))
		return E_FAIL;

	if (FAILED(m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE)))
		return E_FAIL;

	return S_OK;
}

CMainApp* CMainApp::Create()
{
	CMainApp* pInstance = new CMainApp;
	if (FAILED(pInstance->ReadyMainApp()))
	{
		PRINT_LOG(L"Error", L"Failed To Create CMainApp");
		SafeRelease(pInstance);
	}

	return pInstance;
}

void CMainApp::Free()
{
	SafeRelease(m_pDevice);
	SafeRelease(m_pManagement);
	CKeyMgr::Destroy_Instance();
	CManagement::ReleaseEngine();
}
