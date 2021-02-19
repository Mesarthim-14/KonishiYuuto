//=============================================================================
//
// 自機追従弾を打つエネミークラス [enemy_current.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "enemy_current.h"
#include "game.h"
#include "player.h"
#include "bullet.h"
#include "texture.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define CURRENT_ENEMY_LIFE				(8)					// 自機取得弾を打つ敵の体力
#define CURRENT_NUM_BULLET				(9)					// 自機取得弾の数
#define CURRENT_COUNTER_BULLET_NUM		(10)				// 自機取得弾を打つ敵のカウンター弾の数
#define CURRENT_MOVE					(1.5f)				// 自機取得敵の速さ
#define CURRENT_BULLET_AMPLITUDE_X		(5)					// 自機取得弾の横の振れ幅
#define CURRENT_BULLET_AMPLITUDE_Y		(5)					// 自機取得弾の縦の振れ幅
#define CURRENT_FLAG_POS_Y				(50.0f)				// 減速フラグ位置
#define CURRENT_MOVE_Y					(7.0f)				// 自機取得弾を打つ敵の移動量
#define CURRENT_ACCELERATION_SPEED		(0.4f)				// 自機取得弾を打つ敵の加速量
#define CURRENT_DECELERATION_SPEED		(0.25f)				// 自機取得弾を打つ敵の減速量
#define CURRENT_SPEED_CHANGE_FLAME		(5)					// スピードチェンジのフレーム
#define CURRENT_RETURN_FLAME			(200)				// 自機取得弾を打つ敵の戻っていくフレーム
#define CURRENT_LAPSE_FLAME	(CURRENT_RETURN_FLAME+50)		// 自機取得弾を打つ敵の敵の消滅のフレーム
#define CONTINUOUS_INTERVAL				(7)					// 自機取得弾の間隔
#define CURRENT_FIRST_BULLET_INTERVAL	(50)				// 自機取得弾の間隔
#define TARGET_POS_AMPLITUDE			(1)					// 標的の座標振れ幅
#define CURRENT_BULLET_INTERBAL			(50000.0f)			// 次の弾までの間隔
#define CURRENT_BULLET_INTER			(50000)				// 次の弾までの間隔
#define THROUGH_BULLET_RANDOM_INTERVAL	(50)				// ランダム数値
#define THROUGH_BULLET_TIME				(35.0f)				// 弾の発射

//=============================================================================
// コンストラクタ
//=============================================================================
CEnemyCurrent::CEnemyCurrent(TYPE Priority)
{
	m_nContinueInter = 0;
	m_nBulletNum = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CEnemyCurrent::~CEnemyCurrent()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CEnemyCurrent * CEnemyCurrent::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, TYPE type, COLOR_TYPE Ctype, ENEMY_TYPE Etype)
{
	// 初期化処理
	CEnemyCurrent *pNormalEnemy = new CEnemyCurrent;

	if (pNormalEnemy != NULL)
	{
		// 初期化処理
		pNormalEnemy->SetEnemyType(Ctype, Etype);						// エネミーの種類
		pNormalEnemy->SetMove(D3DXVECTOR3(0.0f, CURRENT_MOVE_Y, 0.0f));	// 移動量
		pNormalEnemy->SetLife(CURRENT_ENEMY_LIFE);						// ライフ初期化
		pNormalEnemy->SetCounterBullet(CURRENT_COUNTER_BULLET_NUM);			// カウンター弾の設定
		pNormalEnemy->Init(pos, size, type);							// 初期化情報
		pNormalEnemy->SetBulletFlame(THROUGH_BULLET_TIME + (float)(rand() % THROUGH_BULLET_RANDOM_INTERVAL));

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
HRESULT CEnemyCurrent::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// 初期化処理
	CEnemy::Init(pos, size, type);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CEnemyCurrent::Uninit(void)
{
	// 終了処理
	CEnemy::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CEnemyCurrent::Update(void)
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
void CEnemyCurrent::Draw(void)
{
	// 描画処理
	CEnemy::Draw();
}

//=============================================================================
// 移動の処理
//=============================================================================
void CEnemyCurrent::MoveUpdate(void)
{
	// 移動量の情報
	D3DXVECTOR3 move = GetMove();

	// Y座標が一定以上に行ったら
	if (GetMoveCounter() >= CURRENT_SPEED_CHANGE_FLAME)
	{
		// 減速
		move.y -= CURRENT_DECELERATION_SPEED;
	}

	// 一定量になったら
	if (move.y <= 0.0f && GetMoveCounter() <= CURRENT_RETURN_FLAME)
	{
		move.y = 0.0f;
	}

	if (GetMoveCounter() >= CURRENT_RETURN_FLAME)
	{
		// 画面外へ戻る処理
		move.y -= CURRENT_ACCELERATION_SPEED;
	}

	if (GetMoveCounter() >= CURRENT_LAPSE_FLAME)
	{
		// 消す
		SetLife(0);
	}

	// 移動量設定
	SetMove(move);
}

//=============================================================================
// 弾発射処理
//=============================================================================
void CEnemyCurrent::BulletUpdate(void)
{
	// 弾の発射
//	if (GetBulletFlame() <= 0.0f)
	{
		// 発射フレーム加算
		m_nContinueInter++;

		// 設定した初弾フレームに達したら
		if (m_nContinueInter >= CURRENT_FIRST_BULLET_INTERVAL)
		{
			// カウンターの速さ
			if (m_nContinueInter % CONTINUOUS_INTERVAL == 0)
			{
				D3DXVECTOR3 pos = GetPos();

				// 色の種類7
				switch (GetColorType())
				{
					// 白いとき
				case COLOR_TYPE_WHITE:
				{
					// 現在の位置を取得
					CPlayer *pPlayer = CGame::GetPlayer();
					D3DXVECTOR3 Target = pPlayer->GetPos();

					// 自機取得弾を発射
					CBullet::CurrentAttack(D3DXVECTOR3(
						pos.x + (float)(rand() % CURRENT_BULLET_AMPLITUDE_X - rand() % CURRENT_BULLET_AMPLITUDE_X),
						pos.y + 40.0f + (float)(rand() % CURRENT_BULLET_AMPLITUDE_Y - rand() % CURRENT_BULLET_AMPLITUDE_Y), 0.0f),
						D3DXVECTOR3(Target.x + (float)(rand() % TARGET_POS_AMPLITUDE - rand() % TARGET_POS_AMPLITUDE), Target.y, 0.0f),
						D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f),
						TYPE_BULLET, CBullet::BULLET_TYPE_ENEMY, CBullet::BULLET_COLOR_WHITE,
						1000);

					// 弾のカウント
					m_nBulletNum++;
					break;
				}

				// 黒い弾の時
				case COLOR_TYPE_BLACK:
				{
					// 自機の座標取得
					CPlayer *pPlayer = CGame::GetPlayer();
					D3DXVECTOR3 Target = pPlayer->GetPos();

					// 自機取得弾を発射
					CBullet::CurrentAttack(D3DXVECTOR3(
						pos.x + (float)(rand() % CURRENT_BULLET_AMPLITUDE_X - rand() % CURRENT_BULLET_AMPLITUDE_X),
						pos.y + 40.0f + (float)(rand() % CURRENT_BULLET_AMPLITUDE_Y - rand() % CURRENT_BULLET_AMPLITUDE_Y), 0.0f),
						D3DXVECTOR3(Target.x + (float)(rand() % TARGET_POS_AMPLITUDE - rand() % TARGET_POS_AMPLITUDE), Target.y, 0.0f),
						D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f),
						TYPE_BULLET, CBullet::BULLET_TYPE_ENEMY, CBullet::BULLET_COLOR_BLACK,
						1000);

					// 弾のカウント
					m_nBulletNum++;
					break;
				}
				}
			}

			// 一定量弾を出したら
			if (m_nBulletNum >= CURRENT_NUM_BULLET)
			{
				m_nBulletNum = 0;
				m_nContinueInter = -CURRENT_BULLET_INTER;
				// 弾の発生フレームを戻す
	//			SetBulletFlame(CURRENT_BULLET_INTERBAL);
			}
		}
	}
}