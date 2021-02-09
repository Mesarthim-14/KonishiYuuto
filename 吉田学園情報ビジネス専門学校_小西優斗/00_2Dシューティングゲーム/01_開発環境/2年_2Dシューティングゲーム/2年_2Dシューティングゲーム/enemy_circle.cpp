//=============================================================================
//
// サークルエネミークラス [enemy_circle.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "enemy_circle.h"
#include "bullet.h"
#include "texture.h"
#include "ui.h"
#include "renderer.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define CIRCLE_COUNTER_BULLET_NUM		(5)				// サークル配置の敵のカウンターバレット数
#define CIRCLE_MOVE_Y					(4.0f)			// サークル配置の敵のY軸の移動量
#define CIRCLE_LIFE						(3)				// サークル配置の敵の体力
#define CIRCLE_FLAME					(60)			// サークル配置の敵の移動変更フレーム

//=============================================================================
// コンストラクタ
//=============================================================================
CEnemyCircle::CEnemyCircle(TYPE Priority)
{
	m_center = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// デストラクタ
//=============================================================================
CEnemyCircle::~CEnemyCircle()
{

}

//=============================================================================
// インスタンス生成
//=============================================================================
CEnemyCircle * CEnemyCircle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,
	TYPE type, COLOR_TYPE Ctype, ENEMY_TYPE Etype, float fRadius, float fTheta)
{
	// メモリ確保
	CEnemyCircle *pEnemyCircle = new CEnemyCircle;

	if (pEnemyCircle != NULL)
	{
		// 初期化処理
		pEnemyCircle->SetSize(size);									// サイズの設定
		pEnemyCircle->SetEnemyType(Ctype, Etype);						// 敵の種類の情報
		pEnemyCircle->SetMove(D3DXVECTOR3(0.0f, CIRCLE_MOVE_Y, 0.0f));	// 移動量設定
		pEnemyCircle->SetLife(CIRCLE_LIFE);								// ライフ初期化
		pEnemyCircle->SetCounterBullet(CIRCLE_COUNTER_BULLET_NUM);		// カウンター弾の設定
		pEnemyCircle->SetRotation(fRadius, fTheta);						// 回転の設定
		pEnemyCircle->Init(pos, size, type);							// 初期化情報

		if (pos.x <= SCREEN_WIDTH / 2)
		{
			pEnemyCircle->m_center = D3DXVECTOR3(WALL_SIZE_X, CIRCLE_INITIAL_Y, 0.0f);
		}
		else
		{
			pEnemyCircle->m_center = D3DXVECTOR3(SCREEN_WIDTH - WALL_SIZE_X, CIRCLE_INITIAL_Y, 0.0f);
		}

		// 色の設定
		switch (Ctype)
		{
			// 白いとき
		case COLOR_TYPE_WHITE:

			// テクスチャの設定
			pEnemyCircle->BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_ENEMY_WHITE));

			break;

			// 黒いとき
		case COLOR_TYPE_BLACK:

			// テクスチャの設定
			pEnemyCircle->BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_ENEMY_BLACK));
			
			break;
		}
	}
	return pEnemyCircle;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CEnemyCircle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// 初期化処理
	CEnemy::Init(pos, size, type);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CEnemyCircle::Uninit(void)
{
	// 終了処理
	CEnemy::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CEnemyCircle::Update(void)
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
void CEnemyCircle::Draw(void)
{
	// 描画処理
	CEnemy::Draw();
}

//=============================================================================
// 斜め移動の処理
//=============================================================================
void CEnemyCircle::MoveUpdate(void)
{
	// 半分より左だったら
	if (m_center.x <= SCREEN_WIDTH / 2)
	{
		D3DXVECTOR3 move = GetMove();

		// 反転するタイミング
		if (GetMoveCounter() <= CIRCLE_FLAME)
		{

			if (move.x <= 2.0f)
			{
				move.x += 0.1f;
			}
			else
			{
				move.x = 2.0f;
			}
		}
		else
		{

			if (move.x >= -2.0f)
			{
				move.x -= 0.05f;
			}
			else
			{
				move.x = -2.0f;
			}
		}

		// 中心の移動
		m_center += move;

		// 角度加算
		m_fTheta += m_fOmega;

		// 座標
		SetPosition(D3DXVECTOR3(m_center.x + m_fRadius * cosf(D3DXToRadian(m_fTheta)),
			m_center.y + m_fRadius * sinf(D3DXToRadian(m_fTheta)), 0.0f));

		// 移動量設定
		SetMove(move);
	}
	else
	{
		D3DXVECTOR3 move = GetMove();

		// 反転するタイミング
		if (GetMoveCounter() <= CIRCLE_FLAME)
		{

			if (move.x >= -2.0f)
			{
				move.x -= 0.1f;
			}
			else
			{
				move.x = -2.0f;
			}
		}
		else
		{
			if (move.x <= 2.0f)
			{
				move.x += 0.05f;
			}
			else
			{
				move.x = +2.0f;
			}
		}

		// 中心の移動
		m_center += move;

		// 角度加算
		m_fTheta -= m_fOmega;

		// 座標
		SetPosition(D3DXVECTOR3(m_center.x + m_fRadius * cosf(D3DXToRadian(m_fTheta)),
			m_center.y + m_fRadius * sinf(D3DXToRadian(m_fTheta)), 0.0f));

		// 移動量
		SetMove(move);
	}
}

//=============================================================================
// 弾の更新処理
//=============================================================================
void CEnemyCircle::BulletUpdate(void)
{

}

//=============================================================================
// 角度の設定
//=============================================================================
void CEnemyCircle::SetRotation(float fRadius, float fTheta)
{
	m_fTheta = fTheta;
	m_fRadius = fRadius;
	m_fRadiusNum = fRadius;
}