//=============================================================================
//
// 通常エネミークラス [enemy_rotation.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "enemy_rotation.h"
#include "bullet.h"
#include "renderer.h"
#include "texture.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define ROTATION_LIFE					(5)				// 回る敵の体力
#define ROTATION_COUNTER_BULLET_NUM		(5)				// 回る敵のカウンター弾の数
#define ROTATION_SCALE_UP				(0.04f)			// 回る敵の拡大
#define ROTATION_ADD_OMEGA_NUM			(2.0f)			// 角度の加算
#define RADIAN_RIMIT					(190.0f)		// 半径の制限

//=============================================================================
// コンストラクタ
//=============================================================================
CEnemyRotation::CEnemyRotation(TYPE Priority)
{
	m_fRadius = 0.0f;
	m_fAddRadius = 0.7f;
	m_fTheta = 0.0f;
	m_fOmega = 0.2f;
	m_fScale = 0.0f;
	m_fScaleNum = 0.0f;
	m_BaseSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// デストラクタ
//=============================================================================
CEnemyRotation::~CEnemyRotation()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CEnemyRotation * CEnemyRotation::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size,
	TYPE type, COLOR_TYPE Ctype, ENEMY_TYPE Etype,
	float fRadius, float fTheta)
{
	// 初期化処理
	CEnemyRotation *pEnemyRotation = new CEnemyRotation;

	if (pEnemyRotation != NULL)
	{
		// 初期化処理
		pEnemyRotation->SetEnemyType(Ctype, Etype);						// 敵の種類設定
		pEnemyRotation->SetLife(ROTATION_LIFE);							// ライフ初期化
		pEnemyRotation->SetCounterBullet(ROTATION_COUNTER_BULLET_NUM);	// カウンター弾の設定
		pEnemyRotation->SetRotation(fRadius, fTheta);					// 回転情報
		pEnemyRotation->SetScaleNum(ROTATION_SCALE_UP);					// 大きさの値の設定
		pEnemyRotation->m_fOmega = ROTATION_ADD_OMEGA_NUM;				// 角度の加算量
		pEnemyRotation->Init(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), type);	// 初期化情報
		pEnemyRotation->m_BaseSize = size;

		// 色の種類
		switch (Ctype)
		{
			// 白い敵の時
		case COLOR_TYPE_WHITE:

			// テクスチャの設定
			pEnemyRotation->BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_ENEMY_WHITE));

			break;
			// 黒いとき
		case COLOR_TYPE_BLACK:

			// テクスチャの設定
			pEnemyRotation->BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_ENEMY_BLACK));
			break;
		}
	}

	return pEnemyRotation;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CEnemyRotation::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// 初期化処理
	CEnemy::Init(pos, size, type);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CEnemyRotation::Uninit(void)
{
	// 終了処理
	CEnemy::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CEnemyRotation::Update(void)
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
void CEnemyRotation::Draw(void)
{
	// 描画処理
	CEnemy::Draw();
}

//=============================================================================
// 斜め移動の処理
//=============================================================================
void CEnemyRotation::MoveUpdate(void)
{
	// 中心を設定
	D3DXVECTOR3 Center = D3DXVECTOR3((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f);

	// 拡大
	ScaleUp(m_BaseSize);

	// 半径加算
	m_fRadius -= m_fAddRadius;

	// 角度加算
	m_fTheta += m_fOmega;

	if (m_fRadius <= m_fRadiusNum - RADIAN_RIMIT)
	{
		m_fAddRadius *= -1.2f;
	}

	// 座標
	SetPosition(D3DXVECTOR3(Center.x + m_fRadius * cosf(D3DXToRadian(m_fTheta)),
		Center.y + m_fRadius * sinf(D3DXToRadian(m_fTheta)), 0.0f));

}

//=============================================================================
// 弾の更新処理
//=============================================================================
void CEnemyRotation::BulletUpdate(void)
{
}

//=============================================================================
// 角度の設定
//=============================================================================
void CEnemyRotation::SetRotation(float fRadius, float fTheta)
{
	m_fTheta = fTheta;
	m_fRadius = fRadius;
	m_fRadiusNum = fRadius;
}