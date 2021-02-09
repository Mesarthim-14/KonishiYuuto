//=============================================================================
//
// 真っすぐ弾を打つエネミークラス [enemy_through.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "enemy_through.h"
#include "game.h"
#include "player.h"
#include "bullet.h"
#include "renderer.h"
#include "texture.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define THROUGH_ENEMY_LIFE				(7)				// 真っすぐ弾を打つ敵の体力
#define THROUGH_BULLET_NUM				(30)			// 真っすぐ弾を打つ敵の弾数
#define THROUGH_MOVE_X					(0.0f)			// 真っすぐ弾を打つ敵の移動量
#define THROUGH_MOVE_Y					(2.0f)			// 真っすぐ弾を打つ敵の移動量
#define THROUGH_ACCELERATION_X			(0.05f)			// 真っすぐ弾を打つ敵の加速量
#define THROUGH_ACCELERATION_Y			(0.04f)			// 真っすぐ弾を打つ敵の加速量
#define THROUGH_DECELERATION_X			(0.05f)			// 真っすぐ弾を打つ敵の減速量
#define THROUGH_DECELERATION_Y			(0.04f)			// 真っすぐ弾を打つ敵の減速量
#define THROUGH_STOP_TIME				(70)			// 真っすぐ弾を打つ敵の静止時間
#define THROUGH_BULLET_SPEED_Y			(8.0f)			// 真っすぐ弾を打つ敵の弾の早さ
#define THROUGH_COUNTER_BULLET_NUM		(5)				// 真っすぐ弾を打つ敵のカウンター弾の数
#define COUNTINUE_BULLET_INTERVAL		(5)				// 連続弾の間隔
#define THROUGH_BULLET_RANDOM_INTERVAL	(50)			// ランダムのインターバル
#define THROUGH_BULLET_FIRST_INTERVAL	(30)			// 最初の弾のインターバル

//=============================================================================
// コンストラクタ
//=============================================================================
CEnemyThrough::CEnemyThrough(TYPE Priority)
{
	m_nStopCounter = 0;
	m_nContinueInter = 0;
	m_nBulletNum = 0;
	m_bTwo_Sides = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CEnemyThrough::~CEnemyThrough()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CEnemyThrough * CEnemyThrough::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,
	D3DXVECTOR3 size, TYPE type, COLOR_TYPE Ctype, ENEMY_TYPE Etype)
{
	// 初期化処理
	CEnemyThrough *pNormalEnemy = new CEnemyThrough;

	if (pNormalEnemy != NULL)
	{
		// 初期化処理
		pNormalEnemy->SetEnemyType(Ctype, Etype);							// エネミーの種類
		pNormalEnemy->SetMove(D3DXVECTOR3(-0.001f, THROUGH_MOVE_Y, 0.0f));	// 移動量
		pNormalEnemy->SetLife(THROUGH_ENEMY_LIFE);							// ライフ初期化
		pNormalEnemy->SetCounterBullet(THROUGH_COUNTER_BULLET_NUM);			// カウンター弾の設定
		pNormalEnemy->Init(pos, size, type);								// 初期化情報
		pNormalEnemy->SetBulletFlame(THROUGH_BULLET_FIRST_INTERVAL);
	}

	// テクスチャ振り分け
	switch (Ctype)
	{
		// 白いとき
	case COLOR_TYPE_WHITE:

		// テクスチャの設定
		pNormalEnemy->BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_ENEMY_BLUE));

		break;

		// 黒いとき
	case COLOR_TYPE_BLACK:

		// テクスチャの設定
		pNormalEnemy->BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_ENEMY_RED));
		break;
	}

	return pNormalEnemy;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CEnemyThrough::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// 初期化処理
	CEnemy::Init(pos, size, type);

	if (pos.x <= SCREEN_WIDTH / 2)
	{
		m_bTwo_Sides = true;
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CEnemyThrough::Uninit(void)
{
	// 終了処理
	CEnemy::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CEnemyThrough::Update(void)
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
void CEnemyThrough::Draw(void)
{
	// 描画処理
	CEnemy::Draw();
}

//=============================================================================
// 移動の処理
//=============================================================================
void CEnemyThrough::MoveUpdate(void)
{
	if (m_bTwo_Sides == false)
	{
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 move = GetMove();

		// 出現したら
		if (pos.x >= SCREEN_WIDTH / 2)
		{
			// 横の移動を増やす
			move.x -= THROUGH_ACCELERATION_X;
			move.y += THROUGH_ACCELERATION_Y;
		}
		else
		{	// 半分を越えたら

			// 移動を減らす
			move.x += THROUGH_DECELERATION_X;
			move.y -= THROUGH_DECELERATION_Y;
		}

		if (move.x >= 0.0f)
		{
			m_nStopCounter++;
			move.x = 0.0f;
		}

		if (move.y <= 0.0f)
		{
			move.y = 0.0f;
		}

		// 静止時間を過ぎたら
		if (m_nStopCounter >= THROUGH_STOP_TIME)
		{
			m_bTwo_Sides = true;
			m_nStopCounter = 0;
		}

		// 移動量設定
		SetMove(move);
	}
	else
	{
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 move = GetMove();

		// 出現したら
		if (pos.x <= SCREEN_WIDTH / 2)
		{
			// 横の移動を増やす
			move.x += THROUGH_ACCELERATION_X;
			move.y += THROUGH_DECELERATION_Y;
		}
		else
		{
			// 半分を越えたら
			// 移動を減らす
			move.x -= THROUGH_DECELERATION_X;
			move.y -= THROUGH_DECELERATION_Y;
		}

		if (move.x <= 0.0f)
		{
			m_nStopCounter++;
			move.x = 0.0f;
		}
		if (move.y <= 0.0f)
		{
			move.y = 0.0f;
		}

		// 静止時間を過ぎたら
		if (m_nStopCounter >= THROUGH_STOP_TIME)
		{
			m_bTwo_Sides = false;
			m_nStopCounter = 0;
		}

		// 移動量設定
		SetMove(move);
	}
}

//=============================================================================
// 弾発射処理
//=============================================================================
void CEnemyThrough::BulletUpdate(void)
{
	// 直線弾の発射
	if (GetBulletFlame() <= 0)
	{
		// 発射フレーム加算
		m_nContinueInter++;

		// 連続弾の発射間隔
		if (m_nContinueInter % COUNTINUE_BULLET_INTERVAL == 0)
		{
			D3DXVECTOR3 pos = GetPos();

			// 色の種類
			switch (GetColorType())
			{
				// 白いとき
			case COLOR_TYPE_WHITE:
				CBullet::Create(D3DXVECTOR3(pos.x + 0.0f, pos.y + 40.0f, 0.0f),
					D3DXVECTOR3((float)(rand() % 2 - rand() % 2), THROUGH_BULLET_SPEED_Y, 0.0f),
					D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f),
					TYPE_BULLET, CBullet::BULLET_TYPE_ENEMY, CBullet::BULLET_COLOR_WHITE,
					1000);
				break;

				// 黒いとき
			case COLOR_TYPE_BLACK:
				CBullet::Create(D3DXVECTOR3(pos.x + 0.0f, pos.y + 40.0f, 0.0f),
					D3DXVECTOR3((float)(rand() % 2 - rand() % 2), THROUGH_BULLET_SPEED_Y, 0.0f),
					D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f),
					TYPE_BULLET, CBullet::BULLET_TYPE_ENEMY, CBullet::BULLET_COLOR_BLACK,
					1000);
				break;
			}

			// 連続弾の弾の数
			m_nBulletNum++;
		}

		// 指定された弾分出たら発射しなくする
		if (m_nBulletNum >= THROUGH_BULLET_NUM)
		{
			SetBulletFlame(THROUGH_STOP_TIME + (float)(rand() % THROUGH_BULLET_RANDOM_INTERVAL));
		}
	}

}
//=============================================================================
// 真っすぐな敵の初期化
//=============================================================================
//void CEnemyThrough::InitThrough(D3DXVECTOR3 pos)
//{
//	if (pos.x <= SCREEN_WIDTH / 2)
//	{
//		m_bTwo_Sides = true;
//	}
//}