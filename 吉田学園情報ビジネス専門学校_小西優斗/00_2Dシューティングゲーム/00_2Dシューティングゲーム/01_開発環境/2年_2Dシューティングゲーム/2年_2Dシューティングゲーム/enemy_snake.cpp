//=============================================================================
//
// スネークエネミークラス [enemy_snake.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "enemy_snake.h"
#include "bullet.h"
#include "texture.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define SNAKE_COUNTER_BULLET_NUM		(5)				// 敵の反撃弾
#define SNAKE_LIFE						(3)				// ジグザグ移動敵の体力
#define SNAKE_MOVE_X					(0.7f)			// ジグザグ移動のX移動量
#define SNAKE_MOVE_Y					(1.5f)			// ジグザグ移動のY移動量
#define SNAKE_SWITCH_TIME				(100)			// X移動切り替えの時間
#define SNAKE_OBLIQUE_POS_Y				(30.0f)			// 加速のフラグ位置


//=============================================================================
// コンストラクタ
//=============================================================================
CEnemySnake::CEnemySnake(TYPE Priority)
{
	m_nSwitchCounter = 0;
	m_bSnakeSwitch = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CEnemySnake::~CEnemySnake()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CEnemySnake * CEnemySnake::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, TYPE type, COLOR_TYPE Ctype, ENEMY_TYPE Etype)
{
	// 初期化処理
	CEnemySnake *pNormalEnemy = new CEnemySnake;

	if (pNormalEnemy != NULL)
	{
		// 初期化処理
		pNormalEnemy->SetEnemyType(Ctype, Etype);								// エネミーの種類
		pNormalEnemy->SetMove(D3DXVECTOR3(0.0f, SNAKE_MOVE_Y, 0.0f));			// 移動量
		pNormalEnemy->SetLife(SNAKE_LIFE);								// ライフ初期化
		pNormalEnemy->SetCounterBullet(SNAKE_COUNTER_BULLET_NUM);					// カウンター弾の設定
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
HRESULT CEnemySnake::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// 初期化処理
	CEnemy::Init(pos, size, type);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CEnemySnake::Uninit(void)
{
	// 終了処理
	CEnemy::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CEnemySnake::Update(void)
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
void CEnemySnake::Draw(void)
{
	// 描画処理
	CEnemy::Draw();
}

//=============================================================================
// 斜め移動の処理
//=============================================================================
void CEnemySnake::MoveUpdate(void)
{
	SetMove(GetMove());

	D3DXVECTOR3 pos = GetPos();

	// Y座標が一定以上に行ったら
	if (pos.y > SNAKE_OBLIQUE_POS_Y)
	{
		m_nSwitchCounter++;

		if (m_bSnakeSwitch == false)
		{
			SetMove(D3DXVECTOR3(SNAKE_MOVE_X, SNAKE_MOVE_Y, 0.0f));

			m_bSnakeSwitch = true;
		}
		if (m_nSwitchCounter % SNAKE_SWITCH_TIME == 0)
		{
			D3DXVECTOR3 move = GetMove();

			// 反転
			move.x *= -1;
			SetMove(move);
		}
	}
}

//=============================================================================
// 弾の更新処理
//=============================================================================
void CEnemySnake::BulletUpdate(void)
{

}