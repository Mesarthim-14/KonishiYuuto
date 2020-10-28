//=============================================================================
//
// チュートリアルの処理 [tutorial.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//====================================================================
// インクルード
//====================================================================
#include "tutorial.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// static初期化
//=============================================================================
LPDIRECT3DTEXTURE9 CTutorial::m_apTexture[MAX_TUTORIAL_TEXTURE] = {};

//====================================================================
// ポリゴン生成
//====================================================================
CTutorial * CTutorial::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// インスタンス生成
	CTutorial *pTutorial = new CTutorial;

	if (pTutorial != NULL)
	{
		// 初期化処理
		pTutorial->Init(pos, size, type);

		// テクスチャの設定
		pTutorial->BindTexture(m_apTexture[0]);
	}
	return pTutorial;
}

//====================================================================
// コンストラクタ
//====================================================================
CTutorial::CTutorial()
{

}

//====================================================================
// デストラクタ
//====================================================================
CTutorial::~CTutorial()
{
}

//====================================================================
// 初期化処理
//====================================================================
HRESULT CTutorial::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// 初期化処理
	CScene2D::Init(pos, size, type);

	return S_OK;
}

//====================================================================
// 終了処理
//====================================================================
void CTutorial::Uninit(void)
{
	// 終了処理
	CScene2D::Uninit();
}

//====================================================================
// 更新処理
//====================================================================
void CTutorial::Update(void)
{
	// 更新処理
	CScene2D::Update();
}

//====================================================================
// 描画処理
//====================================================================
void CTutorial::Draw(void)
{
	// 描画処理
	CScene2D::Draw();

}

//====================================================================
// テクスチャロード
//====================================================================
HRESULT CTutorial::Load(void)
{
	// レンダラーの情報を受け取る
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "date/TEXTURE/tutorial.png",
		&m_apTexture[0]);

	return S_OK;
}

//====================================================================
// テクスチャアンロード
//====================================================================
void CTutorial::UnLoad(void)
{
	for (int nCount = 0; nCount < MAX_TUTORIAL_TEXTURE; nCount++)
	{
		// テクスチャの開放
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}