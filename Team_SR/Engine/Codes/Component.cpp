#include "..\Headers\Component.h"

USING(Engine)
const std::wstring CComponent::Tag = L"Component_";
CComponent::CComponent(LPDIRECT3DDEVICE9 pDevice)
	: m_pDevice(pDevice)
{
	SafeAddRef(m_pDevice);
}

HRESULT CComponent::ReadyComponentPrototype()
{
	return S_OK;
}

HRESULT CComponent::ReadyComponent(void * pArg)
{
	return S_OK;
}

void CComponent::Free()
{
	SafeRelease(m_pDevice);
}
