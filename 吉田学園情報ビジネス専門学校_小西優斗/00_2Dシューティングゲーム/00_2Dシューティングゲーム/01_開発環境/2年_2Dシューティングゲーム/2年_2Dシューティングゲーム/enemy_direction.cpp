//=============================================================================
//
// 方向転換エネミークラス [enemy_direction.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "enemy_direction.h"
#include "bullet.h"
#include "texture.h"
#include "player.h"
#include "game.h"
#include "renderer.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define DIRECTION_MOVE_X				(7.0f)			// 方向転換をする敵の移動量
#define DIRECTION_MOVE_Y				(8.0f)			// 方向転換をする敵の移動量
#define DIRECTION_LIFE					(1)				// 方向転換をする敵の体力
#define DIRECTION_COUNTER_BULLET_NUM	(5)				// 方向転換する敵のカウンター弾数
#define DIRECTION_RIGHT_NUMBER			(0)				// 右側の敵の番号
#define DIRECTION_LEFT_NUMBER			(1)				// 左側の敵の番号

//=============================================================================
// コンストラクタ
//=============================================================================
CEnemyDirection::CEnemyDirection(TYPE Priority)
{
	m_nDirection = -1;
}

//=============================================================================
// デストラクタ
//=============================================================================
CEnemyDirection::~CEnemyDirection()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CEnemyDirection * CEnemyDirection::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type, 
	COLOR_TYPE Ctype, ENEMY_TYPE Etype, int nNumber)
{
	// 初期化処理
	CEnemyDirection *pEnemyDirection = new CEnemyDirection;

	if (pEnemyDirection != NULL)
	{
		// エネミーの情報設定
		pEnemyDirection->SetSize(size);					// サイズ設定
		pEnemyDirection->SetEnemyType(Ctype, Etype);	// エネミーのタイプ情報
		pEnemyDirection->SetMove(D3DXVECTOR3(0.0f, DIRECTION_MOVE_Y, 0.0f));						// 移動量設定
		pEnemyDirection->SetLife(DIRECTION_LIFE);						// ライフ初期化
		pEnemyDirection->SetCounterBullet(DIRECTION_COUNTER_BULLET_NUM);					// カウンター弾の設定
		pEnemyDirection->m_nDirection = nNumber;		// 番号の設定
		pEnemyDirection->Init(pos, size, type);			// 初期化情報

		// テクスチャ振り分け
		switch (Ctype)
		{
			// 白いとき
		case COLOR_TYPE_WHITE:

			// テクスチャの設定
			pEnemyDirection->BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_ENEMY_BLUE));

			break;
			// 黒いとき
		case COLOR_TYPE_BLACK:
			pEnemyDirection->BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_ENEMY_RED));

			break;
		}
	}

	return pEnemyDirection;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CEnemyDirection::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// 初期化処理
	CEnemy::Init(pos, size, type);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CEnemyDirection::Uninit(void)
{
	// 終了処理
	CEnemy::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CEnemyDirection::Update(void)
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
void CEnemyDirection::Draw(void)
{
	// 描画処理
	CEnemy::Draw();
}

//=============================================================================
// 移動の処理
//=============================================================================
void CEnemyDirection::MoveUpdate(void)
{
	// プレイヤーの情報を取得
	CPlayer *pPlayer = CGame::GetPlayer();

	// 座標取得
	D3DXVECTOR3 Target = pPlayer->GetPos();		// プレイヤーの座標
	D3DXVECTOR3 pos = GetPos();					// エネミーの7座標

	// プレイヤーと同じ高さになったら
	if (pos.y >= Target.y)
	{

		// 画面半分より左にいたら
		if (pos.x <= SCREEN_WIDTH / 2)
		{
			// 横に移動する
			SetMove(D3DXVECTOR3(5.0f, 0.0f, 0.0f));
		}
		else
		{
			// 横に移動する
			SetMove(D3DXVECTOR3(-5.0f, 0.0f, 0.0f));
		}
	}

	if (m_nDirection == DIRECTION_RIGHT_NUMBER)
	{
		if (pos.x >= SCREEN_WIDTH / 2)
		{
			// 消す
			SetLife(0);
		}
	}
	else if (m_nDirection == DIRECTION_LEFT_NUMBER)
	{
		if (pos.x <= SCREEN_WIDTH / 2)
		{
			// 消す
			SetLife(0);
		}
	}
}

//=============================================================================
// 弾の更新処理
//=============================================================================
void CEnemyDirection::BulletUpdate(void)
{
}