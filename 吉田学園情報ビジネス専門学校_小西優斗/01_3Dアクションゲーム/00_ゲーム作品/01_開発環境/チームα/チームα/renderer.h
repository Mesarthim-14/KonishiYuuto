#ifndef _RENDERER_H_
#define _RENDERER_H_
//=============================================================================
//
// レンダラー処理 [renderer.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "main.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CShader;

//=============================================================================
//レンダリングクラス
//=============================================================================
class CRenderer
{
public:
	CRenderer();	// コンストラクタ
	~CRenderer();	// デストラクタ

	HRESULT Init(HWND hWnd, bool bWindow);	// 初期化処理
	void Uninit(void);						// 終了処理
	void Update(void);						// 更新処理
	void Draw(void);						// 描画処理

	bool SetUpViewport(int nNumber);		// ビューポート設定
	LPDIRECT3DDEVICE9 GetDevice(void);		// デバイス情報
	D3DVIEWPORT9 GetViewPort(int nCount);	// ビューポート情報
private:
	LPDIRECT3DDEVICE9 m_pD3DDevice;				// Deviceオブジェクト(描画に必要)
	LPDIRECT3D9	m_pD3D;							// Direct3Dオブジェクト
	LPDIRECT3D9 m_pD3DInterface;				// DirectXインターフェース
	D3DPRESENT_PARAMETERS *m_pD3DPresentParam;	// プレゼンテーションパラメータ
	CShader *m_pShader;							// シェーダのポインタ
	D3DVIEWPORT9 m_view_port[2];				// ビューポートの設定
};

#endif