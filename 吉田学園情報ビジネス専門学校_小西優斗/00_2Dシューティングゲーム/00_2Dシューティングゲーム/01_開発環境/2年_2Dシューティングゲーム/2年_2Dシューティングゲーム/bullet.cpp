//=============================================================================
//
// バレットクラスの処理 [bullet.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "bullet.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "explosion.h"
#include "sound.h"
#include "enemy.h"
#include "effect.h"
#include "laser.h"
#include "boss.h"
#include "score.h"
#include "game.h"
#include "gage.h"
#include "spark.h"
#include "surroundings.h"
#include "texture.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define PLAYER_BULLET_ANIME_SPEED	(2)				// アニメーションの速度
#define PLAYER_BULLET_ANIME_COUNTER	(4)				// アニメーションの数
#define CURRENT_BULLET_SPEED_X		(5.0f)			// 追従時の弾の速度
#define COUNTER_BULLET_SPEED_Y		(5.0f)			// 追従時の弾の速度
#define BULLET_SCORE_NUM			(10)			// 弾を吸収したときのスコア

#define FIRE_WARK_ANGLE				(20)			// 花火弾の角度
#define FIRE_WARK_SPPED				(2)				// 花火弾の速度
#define FIRE_WARK_DISTANCE			(20)			// 花火弾の発生距離

#define BULLET_COLOR_MAX			(50)			// 変色の最大値
#define BULLET_COLOR_MIN			(0)				// 変色の最小値

//=============================================================================
// コンストラクタ
//=============================================================================
CBullet::CBullet() : CScene2D(TYPE_BULLET)
{
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
	m_type = BULLET_TYPE_NONE;
	m_Ctype = BULLET_COLOR_NONE;
	m_Bcategory = BULLET_CATEGORY_NONE;
	m_nSubColor = 0;
	m_nSubCol = 5;
}

//=============================================================================
// デストラクタ
//=============================================================================
CBullet::~CBullet()
{
}

//=============================================================================
// インスタンス生成
//=============================================================================
CBullet * CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size,
	TYPE type, BULLET_TYPE Btype, BULLET_COLOR Ctype,
	int nLife)
{
	// インスタンス生成
	CBullet *pBullet = new CBullet;

	// 初期化処理
	pBullet->Init(pos, size, type);		// 初期化情報
	pBullet->SetType(Btype, Ctype);		// タイプの設定

	// バレットの種類
	switch (Btype)
	{
		// プレイヤーの時
	case BULLET_TYPE_PLAYER:

		// 色の種類
		switch (Ctype)
		{
		case BULLET_COLOR_WHITE:		// 白い弾

			// テクスチャ
			pBullet->BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_BULLET_000));
			// アニメーション初期化
			pBullet->InitAnimation(PLAYER_BULLET_ANIME_SPEED, PLAYER_BULLET_ANIME_COUNTER, -1);
			break;

		case BULLET_COLOR_BLACK:		// 黒い弾

			// テクスチャ
			pBullet->BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_BULLET_001));
			// アニメーション初期化
			pBullet->InitAnimation(PLAYER_BULLET_ANIME_SPEED, PLAYER_BULLET_ANIME_COUNTER, -1);
			break;
		}

		break;

		// 敵の時
	case BULLET_TYPE_ENEMY:

		// 色の種類
		switch (Ctype)
		{
			// 白い弾
		case BULLET_COLOR_WHITE:
			// テクスチャの設定
			pBullet->BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_BULLET_002));
			break;

			// 黒い弾
		case BULLET_COLOR_BLACK:
			// テクスチャの設定
			pBullet->BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_BULLET_003));
			break;
		}
	}
	// 弾の設定
	pBullet->SetBullet(move, nLife, size);

	return pBullet;
}

//=============================================================================
// 敵のカウンター弾
//=============================================================================
CBullet * CBullet::CounterAttack(
	D3DXVECTOR3 pos, D3DXVECTOR3 size,
	TYPE type, BULLET_TYPE Btype, BULLET_COLOR Ctype, BULLET_CATEGORY Bcate,
	int nLife, int nBulletNum)
{
	for (int nCount = 0; nCount < nBulletNum; nCount++)
	{
		// プレイヤーの情報
		CPlayer *pPlayer = CGame::GetPlayer();
		D3DXVECTOR3 Ppos = pPlayer->GetPos();

		//自機を取得する
		float fPposx = Ppos.x, fPposy = Ppos.y;		// 自機の座標
		float fEposx = pos.x, fEposy = pos.y;		// 敵の座標
		float fAngle;								// 角度

		//角度を決める
		fAngle = atan2f((fEposx - fPposx), (fEposy - fPposy));

		// インスタンス生成
		CBullet *pBullet = new CBullet;

		// 初期化処理
		pBullet->Init(pos, size, type);		// 初期化情報
		pBullet->SetType(Btype, Ctype);		// タイプ情報設定
		pBullet->SetCategory(Bcate);		// バレットの種類

		// 色の種類
		switch (Ctype)
		{
			// 白い弾
		case BULLET_COLOR_WHITE:

			// テクスチャ情報
			pBullet->BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_BULLET_002));
			break;

			// 黒い弾
		case BULLET_COLOR_BLACK:

			// テクスチャ情報
			pBullet->BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_BULLET_003));
			break;
		}

		// ランダム弾の設定
		D3DXVECTOR3 EffectMove =
			D3DXVECTOR3((0.25f*(float)(rand() % 5 - rand() % 5 - rand() % 5)),
				COUNTER_BULLET_SPEED_Y + (0.3f*(float)(rand() % 5 + rand() % 5 + rand() % 5)),
				0.0f);

		// 弾の設定
		pBullet->SetBullet(EffectMove, nLife, size);
	}

	return S_OK;
}

//=============================================================================
// 自機取得弾
//=============================================================================
CBullet * CBullet::CurrentAttack(D3DXVECTOR3 pos, D3DXVECTOR3 Ppos,
	D3DXVECTOR3 size, TYPE type,
	BULLET_TYPE Btype, BULLET_COLOR Ctype,
	int nLife)
{
	//自機を取得する
	float fPposx = Ppos.x, fPposy = Ppos.y;		// 自機の座標
	float fEposx = pos.x, fEposy = pos.y;		// 敵の座標
	float fAngle;								// 角度

	//角度を決める
	fAngle = atan2f((fEposx - fPposx), (fEposy - fPposy));

	// インスタンス生成
	CBullet *pBullet = new CBullet;

	// 初期化処理
	pBullet->Init(pos, size, type);
	pBullet->SetType(Btype, Ctype);

	// 色の種類
	switch (Ctype)
	{
	case BULLET_COLOR_WHITE:		// 白い弾

		// テクスチャ
		pBullet->BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_BULLET_002));
		break;

		// 黒い弾
	case BULLET_COLOR_BLACK:

		// テクスチャ
		pBullet->BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_BULLET_003));
		break;
	}

	// 目的の座標
	D3DXVECTOR3 Target = D3DXVECTOR3(
		(sinf(fAngle)*-CURRENT_BULLET_SPEED_X),
		cosf(fAngle)*-COUNTER_BULLET_SPEED_Y, 0.0f);

	// 弾の設定
	pBullet->SetBullet(Target, nLife, size);

	return pBullet;
}

//=============================================================================
// 花火型バレット
//=============================================================================
CBullet * CBullet::FireWorks(D3DXVECTOR3 pos, D3DXVECTOR3 size,
	TYPE type, BULLET_TYPE Btype, BULLET_COLOR Ctype, BULLET_CATEGORY Bcate, int nLife)
{
	// インスタンス生成
	CBullet *pBullet = new CBullet;

	// 距離の設定
	int nDistance = rand() % FIRE_WARK_DISTANCE - rand() % FIRE_WARK_DISTANCE - rand() % FIRE_WARK_DISTANCE;
	int nSpeed = 5+ rand() % FIRE_WARK_SPPED + rand() % FIRE_WARK_SPPED;

	// ランダムで出現を決める
	D3DXVECTOR3 TargetPos = D3DXVECTOR3(pos.x + nDistance * cosf(D3DXToRadian(90 + (rand() % FIRE_WARK_ANGLE - rand() % FIRE_WARK_ANGLE))),
		pos.y - nDistance * sinf(D3DXToRadian(90 + (rand() % FIRE_WARK_ANGLE - rand() % FIRE_WARK_ANGLE))), 0.0f);

	// 移動量設定
	D3DXVECTOR3 move = D3DXVECTOR3(cosf(D3DXToRadian(90 + (rand() % FIRE_WARK_ANGLE - rand() % FIRE_WARK_ANGLE))) * nSpeed,
		sinf(D3DXToRadian(90 + (rand() % FIRE_WARK_ANGLE - rand() % FIRE_WARK_ANGLE))) * nSpeed, 0.0f);

	// 初期化処理
	pBullet->Init(TargetPos, size, type);

	switch (Ctype)
	{
		// 白い弾
	case BULLET_COLOR_WHITE:

		// テクスチャの設定
		pBullet->BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_BULLET_002));
		break;

		// 黒い弾の処理
	case BULLET_COLOR_BLACK:

		// テクスチャの設定
		pBullet->BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_BULLET_003));
		break;
	}

	// タイプの設定
	pBullet->SetType(Btype, Ctype);

	// 弾の種類
	pBullet->SetCategory(Bcate);

	// ライフの設定
	int nRandomLife = nLife + (rand() % 40);

	// 弾の設定
	pBullet->SetBullet(move, nRandomLife, size);

	return pBullet;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBullet::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// 初期化処理
	CScene2D::Init(pos, size, type);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CBullet::Uninit(void)
{
	// 2Dポリゴン終了処理
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CBullet::Update(void)
{
	// 2Dポリゴン更新処理
	CScene2D::Update();

	// 現在の位置を取得
	m_Pos = GetPos();

	// 移動の更新
	m_Pos += m_move;

	// 飛距離のカウンター減算
	m_nLife--;

	// 座標を渡す
	SetPosition(m_Pos);

	// 花火の時
	if (m_Bcategory == BULLET_CATEGORY_FIREWORKS)
	{
		// 花火弾の更新
		FireWorksUpdate();
	}

	// ライフが0になったら
	if (m_nLife <= 0)
	{
		// 終了処理
		Uninit();
		return;
	}

	// 画面外判定
	if (m_Pos.x  < 0.0f || m_Pos.x  > SCREEN_WIDTH ||
		m_Pos.y  < 0.0f || m_Pos.y  > SCREEN_HEIGHT)
	{
		// 体力を0にする
		m_nLife = 0;
	}

	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		CScene *pScene = NULL;

		if (pScene == NULL)
		{
			// シーンを取得
			pScene = CScene::GetTop(nCount);

			while (pScene)
			{
				CScene *pSceneNext = pScene->GetNext();

				TYPE type = pScene->GetType();

				CScene2D *pScene2D = (CScene2D*)pScene;

				// エネミーの時
				if (type == TYPE_ENEMY)
				{
					// ターゲットの情報確保
					D3DXVECTOR3 Target = pScene2D->GetPos();

					// 敵のサイズ取得
					CEnemy *pEnemy = (CEnemy*)pScene2D;
					D3DXVECTOR3 size = pEnemy->GetSize();

					// エネミーの弾じゃないとき
					if (m_type != BULLET_TYPE_ENEMY)
					{
						// 当たり判定処理
						if (Collision(Target, size) == true)
						{
							m_nLife = 0;
							// エネミーにダメージを与える
							pEnemy->HitDamage(1);
							break;
						}
					}
				}
				else if (type == TYPE_BOSS)
				{
					// ターゲットの情報確保
					D3DXVECTOR3 Target = pScene2D->GetPos();

					// 敵のサイズ取得
					CBoss *pBoss = (CBoss*)pScene2D;
					D3DXVECTOR3 size = pBoss->GetSize();

					// エネミーの弾じゃないとき
					if (m_type != BULLET_TYPE_ENEMY)
					{
						// 当たり判定処理
						if (Collision(Target, size) == true)
						{
							for (int nCount = 0; nCount < SPARK_BOSS_NUM; nCount++)
							{
								CSpark::Create(D3DXVECTOR3(m_Pos.x, m_Pos.y - 30.0f, 0.0f),
									D3DXVECTOR3(SPARK_SIZE_X, SPARK_SIZE_Y, 0.0f),
									TYPE_EFFECT, SPARK_BOSS_ANGLE, SPARK_BASE_BOSS_ANGLE, SPARK_BOSS_DISTANCE, SPARK_LIFE);
							}

							m_nLife = 0;

							// エネミーにダメージを与える
							pBoss->HitBossDamage(2);
							break;
						}
					}
				}
				else if (type == TYPE_SURROUNDINGS)
				{
					// ターゲットの情報確保
					D3DXVECTOR3 Target = pScene2D->GetPos();

					// 敵のサイズ取得
					CSurroundings *pSurroundings = (CSurroundings*)pScene2D;
					D3DXVECTOR3 size = pSurroundings->GetSize();

					// エネミーの弾じゃないとき
					if (m_type != BULLET_TYPE_ENEMY)
					{
						// 当たり判定処理
						if (Collision(Target, size) == true)
						{
							m_nLife = 0;

							// エネミーにダメージを与える
							pSurroundings->HitSurroundings(2);
							break;
						}
					}
				}

				// プレイヤーの時
				else if (type == TYPE_PLAYER)
				{
					// ターゲットの情報確保
					D3DXVECTOR3 Target = pScene2D->GetPos();
					// 
					if (m_type != BULLET_TYPE_PLAYER)
					{
						// 当たり判定処理
						if (Collision(Target, D3DXVECTOR3(DECISION_PLAYER_SIZE_X, DECISION_PLAYER_SIZE_Y, 0.0f)) == true)
						{
							// バレットのライフを0にする
							m_nLife = 0;

							// プレイヤーの情報を受け取る
							CPlayer *pPlayer = (CPlayer*)pScene2D;
							bool bPlayerInfo = pPlayer->GetShildInfo();

							if (bPlayerInfo == false)
							{
								// 違う色だった時
								if (m_Ctype == BULLET_COLOR_WHITE)
								{
									// エネミーにダメージを与える
									pPlayer->HitDamage(1);
								}
								else
								{
									// スコアを加算
									CScore *pScore = CGame::GetScore();
									pScore->SetScore(BULLET_SCORE_NUM);

									CGage *pGage = pPlayer->GetGage();
									pGage->AddGage(1);
								}
							}
							else
							{
								// 違う色だった時
								if (m_Ctype == BULLET_COLOR_BLACK)
								{
									// エネミーにダメージを与える
									pPlayer->HitDamage(1);
								}
								else
								{
									// スコアを加算
									CScore *pScore = CGame::GetScore();
									pScore->SetScore(BULLET_SCORE_NUM);

									// ゲージ量を増やす
									CGage *pGage = pPlayer->GetGage();
									pGage->AddGage(1);
								}
							}
							break;
						}
					}
				}

				pScene = pSceneNext;
			}
		}
	}

}

//=============================================================================
// 描画処理
//=============================================================================
void CBullet::Draw(void)
{
	// 2Dポリゴン描画処理
	CScene2D::Draw();
}

//=============================================================================
// 花火の更新処理
//=============================================================================
void CBullet::FireWorksUpdate(void)
{
	// 花火の処理
	ScaleDown(m_Pos, FIRE_WORKS_LIFE);
	m_move.y += 1.0f;
}

//====================================================================
// ポリゴンの点灯
//====================================================================
void CBullet::FlashPolygon(void)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// 頂点情報を設定
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// カラーの減算
	m_nSubColor += m_nSubCol;

	// カラー変更の最大値
	if (m_nSubColor >= BULLET_COLOR_MAX)
	{
		// 制限
		m_nSubColor = BULLET_COLOR_MAX;

		// 値を反転
		m_nSubCol *= -1;
	}
	else if (m_nSubColor <= BULLET_COLOR_MIN)
	{
		// カラーの最小値の制限
		m_nSubColor = BULLET_COLOR_MIN;

		// フレームカウント
		m_nSubColor++;

		// 値を反転
		m_nSubCol *= -1;
	}

	// 色の種類
	switch (m_Ctype)
	{
		// 白いとき
	case BULLET_COLOR_WHITE:

		// 頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255 - m_nSubColor, 255, 255 - m_nSubColor, 255);	// 左上頂点の色	透明度255
		pVtx[1].col = D3DCOLOR_RGBA(255 - m_nSubColor, 255, 255 - m_nSubColor, 255);	// 右上頂点の色	透明度255
		pVtx[2].col = D3DCOLOR_RGBA(255 - m_nSubColor, 255, 255 - m_nSubColor, 255);	// 左下頂点の色	透明度255
		pVtx[3].col = D3DCOLOR_RGBA(255 - m_nSubColor, 255, 255 - m_nSubColor, 255);	// 右下頂点の色	透明度255
		break;

		// 黒いとき
	case BULLET_COLOR_BLACK:

		// 頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255 - m_nSubColor, 255 - m_nSubColor, 255);	// 左上頂点の色	透明度255
		pVtx[1].col = D3DCOLOR_RGBA(255, 255 - m_nSubColor, 255 - m_nSubColor, 255);	// 右上頂点の色	透明度255
		pVtx[2].col = D3DCOLOR_RGBA(255, 255 - m_nSubColor, 255 - m_nSubColor, 255);	// 左下頂点の色	透明度255
		pVtx[3].col = D3DCOLOR_RGBA(255, 255 - m_nSubColor, 255 - m_nSubColor, 255);	// 右下頂点の色	透明度255
		break;

	}

	// 頂点バッファをアンロックする
	pVtxBuff->Unlock();
}

//=============================================================================
// 当たり判定
//=============================================================================
bool CBullet::Collision(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	if (m_Bcategory = BULLET_CATEGORY_COUNTER)
	{
		// プレイヤーの情報取得
		CPlayer *pPlayer = CGame::GetPlayer();
		bool bPlayerInfo = pPlayer->GetShildInfo();

		if (bPlayerInfo == true)
		{
			if (m_Ctype == BULLET_COLOR_WHITE)
			{
				size = D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, 0.0f);
			}
		}
		else
		{
			if (m_Ctype == BULLET_COLOR_BLACK)
			{
				size = D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, 0.0f);
			}
		}
	}
	if (m_type == BULLET_TYPE_PLAYER)
	{
		if (pos.x - size.x / 2 < m_Pos.x + m_Size.x / 5.0f &&
			pos.x + size.x / 2 > m_Pos.x - m_Size.x / 5.0f &&
			pos.y - size.y / 2 < m_Pos.y + m_Size.y / 5.0f - 20.0f &&
			pos.y + size.y / 2 > m_Pos.y - m_Size.y / 2.0f)
		{
			return true;
		}
	}
	else
	{
		if (pos.x - size.x / 2 < m_Pos.x + m_Size.x / 2 &&
			pos.x + size.x / 2 > m_Pos.x - m_Size.x / 2 &&
			pos.y - size.y / 2 < m_Pos.y + m_Size.y / 2 &&
			pos.y + size.y / 2 > m_Pos.y - m_Size.y / 2)
		{
			return true;
		}
	}
	return false;
}

//=============================================================================
// 弾の設定
//=============================================================================
void CBullet::SetBullet(D3DXVECTOR3 move, int nLife, D3DXVECTOR3 size)
{
	// 変数に代入
	m_move = move;
	m_nLife = nLife;
	m_Size = size;
}

//=============================================================================
// 弾の種類の設定
//=============================================================================
void CBullet::SetType(BULLET_TYPE type, BULLET_COLOR Ctype)
{
	m_type = type;
	m_Ctype = Ctype;
}

//=============================================================================
// 弾の種類の設定
//=============================================================================
void CBullet::SetCategory(BULLET_CATEGORY Bcate)
{
	m_Bcategory = Bcate;
}

//=============================================================================
// ライフを減らす
//=============================================================================
void CBullet::DecreaseLife(int nNumber)
{
	m_nLife -= nNumber;
}

//=============================================================================
// サイズの情報
//=============================================================================
D3DXVECTOR3 CBullet::GetSize(void)
{
	return m_Size;
}

//=============================================================================
// 色の情報
//=============================================================================
CBullet::BULLET_COLOR CBullet::GetCtype(void)
{
	return m_Ctype;
}