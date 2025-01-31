#pragma once
#ifndef __RENDERER_H__

#include "Base.h"

BEGIN(Engine)

class CRenderer final : public CBase
{
private:
	explicit CRenderer(LPDIRECT3DDEVICE9 pDevice);
	virtual ~CRenderer() = default;

public:
	HRESULT AddGameObjectInRenderer(ERenderID eID, class CGameObject* pGameObject);
	HRESULT Render(HWND hWnd = nullptr);

private:
	HRESULT RenderPriority();
	HRESULT RenderNoAlpha();
	HRESULT RenderAlpha();
	HRESULT RenderUI();

public:
	static CRenderer* Create(LPDIRECT3DDEVICE9 pDevice);
	virtual void Free() override;
public:
	D3DCAPS9 _Caps9;
	size_t MaxTexState = 8;
private:
	LPDIRECT3DDEVICE9	m_pDevice;

	typedef list<class CGameObject*> GAMEOBJECTS;
	GAMEOBJECTS	m_GameObjects[(_uint)ERenderID::MaxCount];
};
END

#define __RENDERER_H__
#endif