//=============================================================================
//
// 通常エネミークラス [enemy_normal.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "enemy_normal.h"
#include "bullet.h"
#include "texture.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define ENEMY_NORMAL_LIFE				(4)					// 通常のエネミーのライフ
#define OBLIQUE_MOVE_Y					(3.0f)				// 縦の速さ
#define NORMAL_COUNTER_BULLET_NUM		(5)					// 敵の反撃弾
#define OBLIQUE_POS_Y					(30.0f)				// 加速のフラグ位置
#define OBLIQUE_ACCELERATION_X			(0.04f)				// X座標の加速量
#define OBLIQUE_ACCELERATION_Y			(0.003f)			// Y座標の加速量
#define OBLIQUE_MOVE_LIMIT				(7.0f)				// 加速の制限
#define NORMAL_BULLET_INTERVAL			(35.0f)				// 発射間隔基盤
#define NORMAL_BULLET_RANDOM_INTER		(50)				// 発射間隔のランダム

//=============================================================================
// コンストラクタ
//=============================================================================
CEnemyNormal::CEnemyNormal(TYPE Priority)
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CEnemyNormal::~CEnemyNormal()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CEnemyNormal * CEnemyNormal::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, TYPE type, COLOR_TYPE Ctype, ENEMY_TYPE Etype)
{
	// 初期化処理
	CEnemyNormal *pNormalEnemy = new CEnemyNormal;

	if (pNormalEnemy != NULL)
	{
		// 初期化処理
		pNormalEnemy->SetEnemyType(Ctype, Etype);								// エネミーの種類
		pNormalEnemy->SetMove(D3DXVECTOR3(0.0f, OBLIQUE_MOVE_Y, 0.0f));			// 移動量
		pNormalEnemy->SetLife(ENEMY_NORMAL_LIFE);								// ライフ初期化
		pNormalEnemy->SetCounterBullet(NORMAL_COUNTER_BULLET_NUM);					// カウンター弾の設定
	//	pNormalEnemy->SetBulletFlame(NORMAL_BULLET_INTERVAL + (float)(rand() % NORMAL_BULLET_RANDOM_INTER));
		pNormalEnemy->Init(pos, size, type);									// 初期化情報
	}

	// テクスチャ振り分け
	switch (Ctype)
	{
		// 白いとき
	case COLOR_TYPE_WHITE:

		// テクスチャの設定
		pNormalEnemy->BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_ENEMY_WHITE));

		break;

		// 黒いとき
	case COLOR_TYPE_BLACK:

		// テクスチャの設定
		pNormalEnemy->BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_ENEMY_BLACK));
		break;
	}

	return pNormalEnemy;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CEnemyNormal::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// 初期化処理
	CEnemy::Init(pos, size, type);
	
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CEnemyNormal::Uninit(void)
{
	// 終了処理
	CEnemy::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CEnemyNormal::Update(void)
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
void CEnemyNormal::Draw(void)
{
	// 描画処理
	CEnemy::Draw();
}

//=============================================================================
// 斜め移動の処理
//=============================================================================
void CEnemyNormal::MoveUpdate(void)
{
	// 移動量の情報
	D3DXVECTOR3 move = GetMove();
	D3DXVECTOR3 pos = GetPos();

	switch (GetColorType())
	{
		// 白いとき
	case COLOR_TYPE_WHITE:

		// Y座標が一定以上に行ったら
		if (pos.y > OBLIQUE_POS_Y)
		{
			// 加速させる
			move.x += OBLIQUE_ACCELERATION_X;
			move.y += OBLIQUE_ACCELERATION_Y;

		}
		break;

		// 黒いとき
	case COLOR_TYPE_BLACK:

		// Y座標が一定以上に行ったら
		if (pos.y > OBLIQUE_POS_Y)
		{
			// 加速させる
			move.x -= OBLIQUE_ACCELERATION_X;
			move.y += OBLIQUE_ACCELERATION_Y;

		}
		break;
	}

	// 上限以上移動量を増やさない
	if (move.x >= OBLIQUE_MOVE_LIMIT)
	{
		move.x = OBLIQUE_MOVE_LIMIT;
	}
	if (move.y >= OBLIQUE_MOVE_LIMIT)
	{
		move.y = OBLIQUE_MOVE_LIMIT;
	}

	// 移動量設定
	SetMove(move);
}

//=============================================================================
// 弾の更新処理
//=============================================================================
void CEnemyNormal::BulletUpdate(void)
{
}