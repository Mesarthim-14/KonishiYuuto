//=============================================================================
//
// 爆発クラス [explosion.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "explosion.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "sound.h"
#include "texture.h"

//=============================================================================
// コンストラクタ
//=============================================================================
CExplosion::CExplosion() :CScene2D(TYPE_EXPLOSION)
{
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Ctype = COLOR_TYPE_NONE;
}

//=============================================================================
// デストラクタ
//=============================================================================
CExplosion::~CExplosion()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CExplosion::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// 初期化処理
	CScene2D::Init(pos, size, type);

	// 座標代入
	m_Pos = pos;

	// 爆発の種類
	switch (m_Ctype)
	{
	case COLOR_TYPE_WHITE:
	case COLOR_TYPE_BLACK:
		// アニメーション設定
		InitAnimation(EXPLOSION_ANIM_SPEED, EXPLOSION_ANIM_PATTERN, 0);
		break;

	case COLOR_TYPE_BOSS:
		// アニメーション設定
		InitAnimation(BOSS_EXPLOSION_ANIM_SPEED, BOSS_EXPLOSION_ANIM_PATTERN, 0);
		break;
	}
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CExplosion::Uninit(void)
{
	// 2Dポリゴン終了処理
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CExplosion::Update(void)
{
	// 現在の位置を取得
	m_Pos = GetPos();

	m_Pos += m_move;

	// 座標を渡す
	SetPosition(m_Pos);

	// 2Dポリゴン更新処理
	CScene2D::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CExplosion::Draw(void)
{
	// 2Dポリゴン描画処理
	CScene2D::Draw();
}

//=============================================================================
// インスタンス生成
//=============================================================================
CExplosion * CExplosion::Create(D3DXVECTOR3 pos,  D3DXVECTOR3 move, D3DXVECTOR3 size, TYPE type, COLOR_TYPE Ctype)
{
	// メモリ確保
	CExplosion *pExplosion = new CExplosion;

	// 初期化処理
	pExplosion->m_Ctype = Ctype;				// タイプ設定
	pExplosion->Init(pos, size, type);			// 初期化処理
	pExplosion->SetExplosion(move, Ctype);		// 移動量設定

	// 色の処理
	switch (Ctype)
	{
		// 白いとき
	case COLOR_TYPE_WHITE:
		// テクスチャ設定
		pExplosion->BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_EXPLOSION_000));
		break;

		// 黒いとき
	case COLOR_TYPE_BLACK:
		// テクスチャ設定
		pExplosion->BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_EXPLOSION_001));
		break;

		// ボスの時
	case COLOR_TYPE_BOSS:
		// テクスチャ設定
		pExplosion->BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_EXPLOSION_002));
		break;
	}

	return pExplosion;
}

//=============================================================================
// 弾の設定
//=============================================================================
void CExplosion::SetExplosion(D3DXVECTOR3 move, COLOR_TYPE Ctype)
{
	m_move = move;
	m_Ctype = Ctype;
}