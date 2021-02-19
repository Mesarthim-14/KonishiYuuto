//=============================================================================
//
// アイコンクラス [icon.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//====================================================================
// インクルード
//====================================================================
#include "icon.h"
#include "renderer.h"
#include "manager.h"
#include "sound.h"
#include "texture.h"

//====================================================================
// マクロ定義
//====================================================================
#define ICON_SCALE_UP_NUM		(0.1f)		// 拡大の値
#define ICON_COLOR_NUM			(10)		// 色の変化
#define ICON_COLOR_MAX			(150)		// カラー変更の最大
#define ICON_COLOR_MIN			(0)			// カラー変更の最小
#define ICON_CHANGE_TIME		(35)		// カラーを変えるフレーム
#define ICON_USE_TIME			(210)		// アイコンの出現時間

//====================================================================
// ポリゴン生成
//====================================================================
CIcon * CIcon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// インスタンス生成
	CIcon *pWarning = new CIcon;

	if (pWarning != NULL)
	{
		// 初期化処理
		pWarning->Init(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), type);

		// テクスチャの設定
		pWarning->BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_ICON));

		// サイズを代入
		pWarning->m_size = size;
	}

	return pWarning;
}

//====================================================================
// コンストラクタ
//====================================================================
CIcon::CIcon() : CScene2D(TYPE_UI)
{
	m_fScale = 0.0f;
	m_fScaleNum = 0.0f;
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nFlashFlame = 0;
	m_nSubNumber = 0;
	m_nIconCounter = 0;
	m_nSubNum = ICON_COLOR_NUM;
	m_bEndIcon = false;
}

//====================================================================
// デストラクタ
//====================================================================
CIcon::~CIcon()
{

}

//====================================================================
// 初期化処理
//====================================================================
HRESULT CIcon::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// 初期化処理
	CScene2D::Init(pos, size, type);

	// 縮小量を設定
	m_fScaleNum = ICON_SCALE_UP_NUM;

	return S_OK;
}

//====================================================================
// 終了処理
//====================================================================
void CIcon::Uninit(void)
{
	// 終了処理
	CScene2D::Uninit();
	Release();
}

//====================================================================
// 更新処理
//====================================================================
void CIcon::Update(void)
{
	m_nIconCounter++;

	// 更新処理
	CScene2D::Update();

	if (m_nIconCounter >= ICON_USE_TIME)
	{
		// 縮小
		ScaleDown();
	}
	else
	{
		// 拡大
		ScaleUp();
	}

	// 点滅させる
	FlashPolygon();
}

//====================================================================
// 描画処理
//====================================================================
void CIcon::Draw(void)
{
	// 描画処理
	CScene2D::Draw();
}

//====================================================================
// 拡大
//====================================================================
void CIcon::ScaleUp(void)
{
	if (m_fScale <= 1.0f)
	{
		// 縮小量を加算
		m_fScale += m_fScaleNum;

		D3DXVECTOR3 size = D3DXVECTOR3(m_size.x * m_fScale, m_size.y * m_fScale, 0.0f);

		// Scene2Dにサイズを渡す
		SetSize(size);
	}
	else
	{
		m_fScale = 1.0f;
	}
}

//====================================================================
// 縮小
//====================================================================
void CIcon::ScaleDown(void)
{
	// 消えていなかったら
	if (m_fScale >= 0.0f)
	{
		// 縮小量を加算
		m_fScale -= m_fScaleNum;

		D3DXVECTOR3 size = D3DXVECTOR3(m_size.x * m_fScale, m_size.y * m_fScale, 0.0f);

		// Scene2Dにサイズを渡す
		SetSize(size);
	}
	else
	{
		m_fScale = 0.0f;
		m_bEndIcon = true;
	}
}

//====================================================================
// ポリゴンの点滅
//====================================================================
void CIcon::FlashPolygon(void)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// 頂点情報を設定
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// カラーの減算
	m_nSubNumber += m_nSubNum;

	// カラー変更の最大値
	if (m_nSubNumber >= ICON_COLOR_MAX)
	{
		// 制限
		m_nSubNumber = ICON_COLOR_MAX;

		// 値を反転
		m_nSubNum *= -1;
	}
	else if (m_nSubNumber <= ICON_COLOR_MIN)
	{
		// カラーの最小値の制限
		m_nSubNumber = ICON_COLOR_MIN;

		// フレームカウント
		m_nFlashFlame++;

		// 一定のフレーム以上になったら
		if (m_nFlashFlame >= ICON_CHANGE_TIME)
		{
			m_nFlashFlame = 0;

			// 値を反転
			m_nSubNum *= -1;
		}
	}

	// 頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255 - m_nSubNumber);	// 左上頂点の色	透明度255
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255 - m_nSubNumber);	// 右上頂点の色	透明度255
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255 - m_nSubNumber);	// 左下頂点の色	透明度255
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255 - m_nSubNumber);	// 右下頂点の色	透明度255

	// 頂点バッファをアンロックする
	pVtxBuff->Unlock();
}

//====================================================================
// アイコンの終了フラグ情報
//====================================================================
bool CIcon::GetEndIcon(void)
{
	return m_bEndIcon;
}