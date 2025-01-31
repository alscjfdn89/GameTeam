#include "..\Headers\GameObject.h"
#include "Management.h"

#include "Scene.h"


USING(Engine)

const std::wstring CGameObject::Tag = L"GameObject_";

CGameObject::CGameObject(LPDIRECT3DDEVICE9 pDevice)
	: m_pDevice(pDevice), m_pManagement(CManagement::Get_Instance())
{
	SafeAddRef(m_pDevice);
}

CComponent* CGameObject::GetComponent(const wstring& ComponentTag)
{
	auto iter_find = m_Components.find(ComponentTag);
	if (m_Components.end() == iter_find)
		return nullptr;

	return iter_find->second;
}

HRESULT CGameObject::ReadyGameObjectPrototype()
{
	return S_OK;
}

HRESULT CGameObject::ReadyGameObject(void* pArg)
{
	AddStaticComponents();

	return S_OK;
}

_uint CGameObject::UpdateGameObject(float fDeltaTime)
{
	m_pTransformCom->UpdateTransform();

	return _uint();
}

_uint CGameObject::LateUpdateGameObject(float fDeltaTime)
{
	
	return _uint();
}

HRESULT CGameObject::RenderGameObject()
{
	if (FAILED(m_pDevice->SetTransform(D3DTS_WORLD, &m_pTransformCom->m_TransformDesc.matWorld)))
		return E_FAIL;

	return S_OK;
}

void CGameObject::Hit(CGameObject* const _Target, const Collision::Info& _CollisionInfo)
{

}

void CGameObject::MapHit(const PlaneInfo& _PlaneInfo, const Collision::Info& _CollisionInfo)
{

}

void CGameObject::Free()
{
	SafeRelease(m_pDevice);
	SafeRelease(m_pTransformCom);

	for (auto& Pair : m_Components)
	{
		SafeRelease(Pair.second);
	}

	m_Components.clear();
}

HRESULT CGameObject::AddComponent(
	_int iSceneIndex,
	const wstring& PrototypeTag,
	const wstring& ComponentTag,
	CComponent** ppComponent,
	void* pArg)
{
	CComponent* pClone = m_pManagement->CloneComponentPrototype(iSceneIndex, PrototypeTag, pArg);
	if (nullptr == pClone)
		return E_FAIL;

	m_Components.insert(make_pair(ComponentTag, pClone));

	if (ppComponent)
	{
		*ppComponent = pClone;
		SafeAddRef(pClone);
	}

	return S_OK;
}

HRESULT CGameObject::AddStaticComponents()
{
	/* For.Com_Transform */
	if (FAILED(CGameObject::AddComponent(
		STATIC,
		CComponent::Tag + TYPE_NAME<CTransform>(),
		CComponent::Tag + TYPE_NAME<CTransform>(),
		(CComponent**)&m_pTransformCom)))
		return E_FAIL;

	return S_OK;
}
