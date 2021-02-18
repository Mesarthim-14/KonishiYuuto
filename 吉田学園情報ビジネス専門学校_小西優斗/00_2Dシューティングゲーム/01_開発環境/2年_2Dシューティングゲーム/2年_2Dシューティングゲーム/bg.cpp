//=============================================================================
//
// バッググラウンド処理 [bg.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "bg.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_BG				(3)			// BGの数
#define BG_SPEED			(2)			// スピード
#define BG_DIVISION_BASE	(0.008f)	// スクロールの基本値
#define BG_DIVISION			(0.004f)	// スクロールの値

//=============================================================================
// コンストラクタ
//=============================================================================
CBackground::CBackground(TYPE Priority) : CScene(Priority)
{
	for (int nCount = 0; nCount < MAX_BG; nCount++)
	{
		m_apScene2D[nCount] = NULL;
	}
}

//=============================================================================
// デストラクタ
//=============================================================================
CBackground::~CBackground()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CBackground * CBackground::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// メモリ確保
	CBackground *pBackground = new CBackground;

	// 初期化処理
	pBackground->Init(pos, size, type);

	return pBackground;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBackground::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	for (int nCount = 0; nCount < MAX_BG; nCount++)
	{
		// 使われていないとき
		if (m_apScene2D[nCount] == NULL)
		{
			// 初期化処理
			m_apScene2D[nCount] = new CScene2D;				// メモリ確保
			m_apScene2D[nCount]->InitScroll(BG_SPEED, BG_DIVISION_BASE + BG_DIVISION*(float)nCount);	// スクロール情報
			m_apScene2D[nCount]->Init(pos, size, type);													// 初期化情報
			m_apScene2D[nCount]->BindTexture(CTexture::GetTexture((CTexture::TEXTURE_TYPE)((int)CTexture::TEXTURE_NUM_BG_000 + nCount)));				// テクスチャ情報

		}
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CBackground::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_BG; nCount++)
	{
		if (m_apScene2D[nCount] != NULL)
		{
			// 終了処理
			m_apScene2D[nCount]->Uninit();
			m_apScene2D[nCount] = NULL;
		}
	}

	// リリース
	Release();
}
 
//=============================================================================
// 更新処理
//=============================================================================
void CBackground::Update(void)
{
	for (int nCount = 0; nCount < MAX_BG; nCount++)
	{
		if (m_apScene2D[nCount] != NULL)
		{
			// 更新処理
			m_apScene2D[nCount]->Update();
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CBackground::Draw(void)
{

}