//=============================================================================
//
// 追従エネミークラス [enemy_follow.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "enemy_follow.h"
#include "bullet.h"
#include "texture.h"
#include "player.h"
#include "game.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define FOLLOW_MOVE_X					(4.0f)			// 追従する敵の移動量
#define FOLLOW_MOVE_Y					(4.0f)			// 追従する敵の移動量
#define FOLLOW_LIFE						(1)				// 追従する敵の体力
#define FOLLOW_COUNTER_BULLET_NUM		(5)				// 追従する敵のカウンター弾数
#define FOLLOW_MOVE_TIME				(50)			// 追従する敵動く時間
#define COLOR_NUM						(4)				// 透明度
#define ALPHA_NUM						(255)			// 透明度

//=============================================================================
// コンストラクタ
//=============================================================================
CEnemyFollow::CEnemyFollow(TYPE Priority)
{
	m_bFlashFlag = false;
	m_bFollowFlag = false;
	m_nFollowCounter = 0;
	m_nSubNum = 0;
	m_nSubNumber = ALPHA_NUM;
}

//=============================================================================
// デストラクタ
//=============================================================================
CEnemyFollow::~CEnemyFollow()
{

}

//=============================================================================
// インスタンス生成
//=============================================================================
CEnemyFollow * CEnemyFollow::Create(D3DXVECTOR3 pos,
	D3DXVECTOR3 size, TYPE type, COLOR_TYPE Ctype, ENEMY_TYPE Etype)
{
	// メモリ確保
	CEnemyFollow *pEnemy = new CEnemyFollow;

	if (pEnemy != NULL)
	{
		// 初期化処理
		pEnemy->SetSize(size);									// サイズ設定
		pEnemy->SetEnemyType(Ctype, Etype);						// エネミーの種類設定
		pEnemy->SetLife(FOLLOW_LIFE);							// ライフ初期化
		pEnemy->m_nSubNum = COLOR_NUM;							// カラー変更の値
		pEnemy->SetCounterBullet(FOLLOW_COUNTER_BULLET_NUM);	// カウンター弾の設定
		pEnemy->Init(pos, size, type);							// 初期化処理
		pEnemy->TransparentInit();								// 透明にさせる
	}

	// 色の種類
	switch (Ctype)
	{
		// 白いとき
	case COLOR_TYPE_WHITE:

		//　テクスチャの設定
		pEnemy->BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_ENEMY_WHITE));
		break;

		// 黒いとき
	case COLOR_TYPE_BLACK:

		// テクスチャの設定
		pEnemy->BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_ENEMY_BLACK));
	
		break;
	}

	return pEnemy;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CEnemyFollow::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// 初期化処理
	CEnemy::Init(pos, size, type);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CEnemyFollow::Uninit(void)
{
	// 終了処理
	CEnemy::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CEnemyFollow::Update(void)
{
	// 移動更新
	MoveUpdate();

	// 弾の更新
	BulletUpdate();

	// 更新処理
	CEnemy::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CEnemyFollow::Draw(void)
{
	// 描画処理
	CEnemy::Draw();
}

//=============================================================================
// 斜め移動の処理
//=============================================================================
void CEnemyFollow::MoveUpdate(void)
{
	if (m_bFlashFlag == false)
	{
		// 透明度の変更
		Appearance();
	}

	if (m_bFollowFlag == false)
	{
		m_nFollowCounter++;

		if (m_nFollowCounter >= 50)
		{
			m_bFollowFlag = true;

			// プレイヤー情報を取得
			CPlayer *pPlayer = CGame::GetPlayer();
			D3DXVECTOR3 Ppos = pPlayer->GetPos();
			D3DXVECTOR3 pos = GetPos();

			//自機を取得する
			float fPposx = Ppos.x, fPposy = Ppos.y;		// 自機の座標
			float fEposx = pos.x, fEposy = pos.y;	// 敵の座標
			float fAngle;								// 角度

			//角度を決める
			fAngle = atan2f((fEposx - fPposx), (fEposy - fPposy));

			// 透明な敵の移動
			D3DXVECTOR3 FollowMove = D3DXVECTOR3(
				(sinf(fAngle)*-FOLLOW_MOVE_X),
				cosf(fAngle)*-FOLLOW_MOVE_Y, 0.0f);

			// 移動量の設定
			SetMove(FollowMove);
		}
	}

}

//=============================================================================
// 弾の更新処理
//=============================================================================
void CEnemyFollow::BulletUpdate(void)
{

}

//=============================================================================
// 透明から出現
//=============================================================================
void CEnemyFollow::Appearance(void)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// 頂点情報を設定
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// カラーの減算
	m_nSubNumber -= m_nSubNum;

	// カラー変更の最大値
	if (m_nSubNumber <= 0)
	{
		// 制限
		m_nSubNumber = 0;

		m_bFlashFlag = true;
	}

	// 頂点カラーの設定
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255 - m_nSubNumber);	// 左上頂点の色	透明度255
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255 - m_nSubNumber);	// 右上頂点の色	透明度255
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255 - m_nSubNumber);	// 左下頂点の色	透明度255
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255 - m_nSubNumber);	// 右下頂点の色	透明度255

	// 頂点バッファをアンロックする
	pVtxBuff->Unlock();
}

//=============================================================================
// 透明の初期化
//=============================================================================
void CEnemy::TransparentInit(void)
{
	if (m_Etype == ENEMY_TYPE_FOLLOW)
	{
		LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

		// 頂点情報を設定
		VERTEX_2D *pVtx;

		// 頂点バッファをロックし、頂点情報へのポインタを取得
		pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 0);	// 左上頂点の色	透明度255
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 0);	// 右上頂点の色	透明度255
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 0);	// 左下頂点の色	透明度255
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 0);	// 右下頂点の色	透明度255

		// 頂点バッファをアンロックする
		pVtxBuff->Unlock();
	}
}
