//=============================================================================
//
// エネミーの処理　[enemy.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "enemy.h"
#include "renderer.h"
#include "manager.h"
#include "bullet.h"
#include "ui.h"
#include "explosion.h"
#include "light.h"
#include "player.h"
#include "effect.h"
#include "score.h"
#include "game.h"
#include "shock.h"
#include "spark.h"
#include "sound.h"
#include "texture.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define ENEMY_OUTSIDE_FLAME			(120)			// 敵が画面外にいれるフレーム
#define SNAKE_OUTSIDE_FLAME			(160)			// 敵が画面外にいれるフレーム
#define ENEMY_SCORE					(200)			// エネミーのスコア
#define ENEMY_STATE_COUNT			(1)				// エネミーの透明化フレーム

#define COUNTINUE_BULLET_INTERVAL	(5)				// 連続弾の間隔

#define WARNING_COLOR_MAX			(255)			// 透明度変更値の最大数
#define ENEMY_ATTACK_NUM			(10)			// 攻撃力
#define MAX_SCALE_NUM				(1.0f)			// 拡大率の最大

//=============================================================================
// コンストラクタ
//=============================================================================
CEnemy::CEnemy(TYPE Priority) : CCharacter(Priority)
{
	m_center = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fBulletFlame = 0.0f;
	m_Ctype = COLOR_TYPE_NONE;
	m_Etype = ENEMY_TYPE_NONE;
	m_nCountinueInter = 0;
	m_nBulletNum = 0;
	m_nStateCnt = 0;
	m_nCounterBulletNum = 0;
	m_bSnakeSwitch = false;
	m_bTwo_Sides = false;
	m_nFirstBulletFrame = 0;
	m_nThroughStopCnt = 0;
	m_pLight = NULL;
	m_nOutsideScreenCnt = 0;
	m_fThroughBulletCnt = 0.0f;
	m_fScale = 0.0f;
	m_fScaleNum = 0.0f;
	m_bRotationScale = false;
	m_nDirection = 0;
	m_bFlashFlag = false;
	m_nSubNumber = 255;
	m_nSubNum = 0;
	m_bFollowFlag = false;
	m_nEnemyCounter = 0;
	m_nMoveCounter = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CEnemy::~CEnemy()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// バレット間隔初期化
//	m_fBulletFlame = BULLET_INTERVAL + (float)(rand() % BULLET_RANDOM_INTERVAL);

	// 初期化処理
	CCharacter::Init(pos, size, type);

	// ライトの設定
	SetLight();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CEnemy::Uninit(void)
{
	// 2Dポリゴン終了処理
	CCharacter::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CEnemy::Update(void)
{
	// バレットのフレーム
	m_fBulletFlame--;

	// 移動時のカウンター
	m_nMoveCounter++;

	// キャラクター更新処理
	CCharacter::Update();

	// 状態の更新処理
	UpdateState();

	if (m_pLight != NULL)
	{
		D3DXVECTOR3 pos = GetPos();

		// ライトの移動
		m_pLight->SetPosition(pos);
	}

	// プレイヤーとの当たり判定
	Collision();

	D3DXVECTOR3 pos = GetPos();

	SetPosition(pos);

	// 敵が画面外に出たら
	if (pos.x < 0.0f ||
		pos.x > SCREEN_WIDTH - WALL_SIZE_X ||
		pos.y < 0.0f ||
		pos.y > SCREEN_HEIGHT)
	{
		// 画面外加算
		m_nOutsideScreenCnt++;
	}

	if (m_Etype != ENEMY_TYPE_SNAKE)
	{
		// 画面外に100フレームいたら
		if (m_nOutsideScreenCnt >= ENEMY_OUTSIDE_FLAME)
		{
			// ライトの終了処理
			if (m_pLight != NULL)
			{
				m_pLight->Uninit();
				m_pLight = NULL;
			}

			// 終了処理
			Uninit();
		}
	}
	else
	{
		// 画面外に100フレームいたら
		if (m_nOutsideScreenCnt >= SNAKE_OUTSIDE_FLAME)
		{
			// ライトの終了処理
			if (m_pLight != NULL)
			{
				m_pLight->Uninit();
				m_pLight = NULL;
			}

			// 終了処理
			Uninit();
		}
	}

	// 死んだとき
	Death();
}

//=============================================================================
// 描画処理
//=============================================================================
void CEnemy::Draw(void)
{
	// キャラクター描画処理
	CCharacter::Draw();
}

//=============================================================================
// エネミーヒット時
//=============================================================================
void CEnemy::Death(void)
{
	D3DXVECTOR3 pos = GetPos();

	int nLife = GetLife();

	// ライフが0になったら
	if (nLife <= 0)
	{
		// サウンド設定
		CSound *pSound = NULL;
		pSound = CManager::GetSound();
		pSound->Play(CSound::SOUND_LABEL_EXPLOSION);

		// 色の種類
		switch (m_Ctype)
		{
			// 白いとき
		case COLOR_TYPE_WHITE:

			for (int nCount = 0; nCount < SPARK_NUM; nCount++)
			{
				// 火花の処理
				CSpark::Create(pos,
					D3DXVECTOR3(SPARK_SIZE_X, SPARK_SIZE_Y, 0.0f),
					TYPE_EFFECT, SPARK_ANGLE, SPARK_BASE_ANGLE, SPARK_DISTANCE, SPARK_LIFE);
			}
			break;

			// 黒いとき
		case COLOR_TYPE_BLACK:

			for (int nCount = 0; nCount < SPARK_NUM; nCount++)
			{
				// 火花の処理
				CSpark::Create(pos,
					D3DXVECTOR3(SPARK_SIZE_X, SPARK_SIZE_Y, 0.0f),
					TYPE_EFFECT, SPARK_ANGLE, SPARK_BASE_ANGLE, SPARK_DISTANCE, SPARK_LIFE);
			}
			break;

		default:
			break;
		}

		// スコアを加算
		CScore *pScore = CGame::GetScore();
		pScore->SetScore(ENEMY_SCORE);

		CScene *pScene = NULL;

		if (pScene == NULL)
		{
			// シーンを取得
			pScene = CScene::GetTop(TYPE_BULLET);

			while (pScene)
			{
				CScene *pSceneNext = pScene->GetNext();

				TYPE type = pScene->GetType();

				// メモリのキャスト
				CScene2D *pScene2D = (CScene2D*)pScene;

				if (pScene2D != NULL)
				{
					// 弾の色取得
					CBullet *pBullet = (CBullet*)pScene2D;
					CBullet::BULLET_COLOR Ctype = pBullet->GetCtype();

					// 色の種類
					switch (Ctype)
					{
						// 黒いとき
					case CBullet::BULLET_COLOR_BLACK:

						// 自分が黒だったら
						if (m_Ctype == COLOR_TYPE_BLACK)
						{
							// カウンター弾生成
							CBullet::CounterAttack(
								pos, D3DXVECTOR3(COUNTER_BULLET_SIZE_X, COUNTER_BULLET_SIZE_Y, 0.0f),
								TYPE_BULLET, CBullet::BULLET_TYPE_ENEMY,
								CBullet::BULLET_COLOR_BLACK, CBullet::BULLET_CATEGORY_COUNTER,
								1000, m_nCounterBulletNum);
						}
						break;

						// 白いとき
					case CBullet::BULLET_COLOR_WHITE:

						// 自分が白だったら
						if (m_Ctype == COLOR_TYPE_WHITE)
						{
							// カウンター弾生成
							CBullet::CounterAttack(
								pos, D3DXVECTOR3(COUNTER_BULLET_SIZE_X, COUNTER_BULLET_SIZE_Y, 0.0f),
								TYPE_BULLET, CBullet::BULLET_TYPE_ENEMY,
								CBullet::BULLET_COLOR_WHITE, CBullet::BULLET_CATEGORY_COUNTER,
								1000, m_nCounterBulletNum);
						}
						break;
					}
					break;

				}
				pScene = pSceneNext;
			}
		}

		if (m_pLight != NULL)
		{
			// ライト削除
			m_pLight->Uninit();
		}

		// エネミー削除
		Uninit();

	}
}

//=============================================================================
// 状態の更新
//=============================================================================
void CEnemy::UpdateState(void)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// 頂点情報を設定
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	STATE state = GetState();

	// エネミーの状態
	switch (state)
	{
		// 通常時
	case STATE_NORMAL:
		// 頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// 左上頂点の色	透明度255
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// 右上頂点の色	透明度255
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// 左下頂点の色	透明度255
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// 右下頂点の色	透明度255
		break;

		// ダメージ時
	case STATE_DAMAGE:

		// 状態カウンター
		m_nStateCnt++;

		// 頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 100);	// 左上頂点の色	透明度255
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 100);	// 右上頂点の色	透明度255
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 100);	// 左下頂点の色	透明度255
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 100);	// 右下頂点の色	透明度255

		// 一定で通常状態に戻る
		if (m_nStateCnt >= ENEMY_STATE_COUNT)
		{
			SetState(STATE_NORMAL);
			m_nStateCnt = 0;
		}
		break;
	}

	// 頂点バッファをアンロックする
	pVtxBuff->Unlock();

}

//=============================================================================
// 初弾の発生フレーム設定
//=============================================================================
void CEnemy::SetFirstBulletTime(int nTime)
{
	m_nFirstBulletFrame = nTime;
}

//=============================================================================
// ライトの設定
//=============================================================================
void CEnemy::SetLight(void)
{
	if (m_pLight == NULL)
	{
		// テクスチャ振り分け
		switch (m_Ctype)
		{
			// 白いとき
		case COLOR_TYPE_WHITE:
			// 光の生成
			m_pLight = CLight::Create(GetPos(), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(LIGHT_SIZE_X, LIGHT_SIZE_Y, 0.0f),
				TYPE_LIGHT, CLight::LIGHT_TYPE_WHITE);
			break;

			// 黒いとき
		case COLOR_TYPE_BLACK:

			// 光の生成
			m_pLight = CLight::Create(GetPos(), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(LIGHT_SIZE_X, LIGHT_SIZE_Y, 0.0f),
				TYPE_LIGHT, CLight::LIGHT_TYPE_BLACK);
			break;

		}
	}
}

//=============================================================================
// 弾の発射フレーム設定
//=============================================================================
void CEnemy::SetBulletFlame(float fBulletFlame)
{
	m_fBulletFlame = fBulletFlame;
}

//=============================================================================
// 移動時のフレームカウンター
//=============================================================================
void CEnemy::SetMoveCounter(int nCounter)
{
	m_nMoveCounter = nCounter;
}

//=============================================================================
// 拡大量設定
//=============================================================================
void CEnemy::SetScaleNum(float fScaleNum)
{
	m_fScaleNum = fScaleNum;
}

//=============================================================================
// エネミーのタイプ設定
//=============================================================================
void CEnemy::SetEnemyType(COLOR_TYPE Ctype, ENEMY_TYPE Etype)
{
	m_Ctype = Ctype;
	m_Etype = Etype;
}

void CEnemy::SetCounterBullet(int nCounter)
{
	m_nCounterBulletNum = nCounter;
}

////=============================================================================
//// 直進の敵の更新
////=============================================================================
//void CEnemy::ThroughUpdate(void)
//{
////	m_fThroughBulletCnt--;
////
////	// 直線弾の発射
////	if (m_fThroughBulletCnt <= 0)
////	{
////		ContinuousBullet(THROUGH_BULLET_NUM);
////	}
////
////	if (m_bTwo_Sides == false)
////	{
////		D3DXVECTOR3 pos = GetPos();
////		D3DXVECTOR3 move = GetMove();
////
////		// 出現したら
////		if (pos.x >= SCREEN_WIDTH / 2)
////		{
////			// 横の移動を増やす
////			move.x -= THROUGH_ACCELERATION_X;
////			move.y += THROUGH_ACCELERATION_Y;
////		}
////		else
////		{	// 半分を越えたら
////
////			// 移動を減らす
////			move.x += THROUGH_DECELERATION_X;
////			move.y -= THROUGH_DECELERATION_Y;
////		}
////
////		if (move.x >= 0.0f)
////		{
////			m_nThroughStopCnt++;
////			move.x = 0.0f;
////		}
////
////		if (move.y <= 0.0f)
////		{
////			move.y = 0.0f;
////		}
////
////		// 静止時間を過ぎたら
////		if (m_nThroughStopCnt >= THROUGH_STOP_TIME)
////		{
////			m_bTwo_Sides = true;
////			m_nThroughStopCnt = 0;
////		}
////
////		// 移動量設定
////		SetMove(move);
////	}
////	else
////	{
////		D3DXVECTOR3 pos = GetPos();
////		D3DXVECTOR3 move = GetMove();
////
////		// 出現したら
////		if (pos.x <= SCREEN_WIDTH / 2)
////		{
////			// 横の移動を増やす
////			move.x += THROUGH_ACCELERATION_X;
////			move.y += THROUGH_DECELERATION_Y;
////		}
////		else
////		{	
////			// 半分を越えたら
////			// 移動を減らす
////			move.x -= THROUGH_DECELERATION_X;
////			move.y -= THROUGH_DECELERATION_Y;
////		}
////
////		if (move.x <= 0.0f)
////		{
////			m_nThroughStopCnt++;
////			move.x = 0.0f;
////		}
////		if (move.y <= 0.0f)
////		{
////			move.y = 0.0f;
////		}
////
////		// 静止時間を過ぎたら
////		if (m_nThroughStopCnt >= THROUGH_STOP_TIME)
////		{
////			m_bTwo_Sides = false;
////			m_nThroughStopCnt = 0;
////		}
////
////		// 移動量設定
////		SetMove(move);
////	}
////
////	// 指定された弾分出たら発射フレームを設定
////	if (m_nContinueCnt >= THROUGH_BULLET_NUM)
////	{
////		m_fThroughBulletCnt = THROUGH_STOP_TIME;
////		m_nContinueCnt = 0;
////	}
//}
//
//
////=============================================================================
//// サークル配置の敵の更新
////=============================================================================
//void CEnemy::CircleUpdate(void)
//{
////	m_nEnemyCounter++;
////
////	// 半分より左だったら
////	if (m_center.x <= SCREEN_WIDTH / 2)
////	{
////		D3DXVECTOR3 move = GetMove();
////
////		// 反転するタイミング
////		if (m_nEnemyCounter <= CIRCLE_FLAME)
////		{
////
////			if (move.x <= 2.0f)
////			{
////				move.x += 0.1f;
////			}
////			else
////			{
////				move.x = 2.0f;
////			}
////		}
////		else
////		{
////
////			if (move.x >= -2.0f)
////			{
////				move.x -= 0.05f;
////			}
////			else
////			{
////				move.x = -2.0f;
////			}
////		}
////
////		// 中心の移動
////		m_center += move;
////
////		// 角度加算
////		m_fTheta += m_fOmega;
////
////		// 座標
////		SetPosition(D3DXVECTOR3(m_center.x + m_fRadius * cosf(D3DXToRadian(m_fTheta)),
////			m_center.y + m_fRadius * sinf(D3DXToRadian(m_fTheta)), 0.0f));
////
////		// 移動量設定
////		SetMove(move);
////	}
////	else
////	{
////		D3DXVECTOR3 move = GetMove();
////
////		// 反転するタイミング
////		if (m_nEnemyCounter <= CIRCLE_FLAME)
////		{
////
////			if (move.x >= -2.0f)
////			{
////				move.x -= 0.1f;
////			}
////			else
////			{
////				move.x = -2.0f;
////			}
////		}
////		else
////		{
////			if (move.x <= 2.0f)
////			{
////				move.x += 0.05f;
////			}
////			else
////			{
////				move.x = +2.0f;
////			}
////		}
////
////		// 中心の移動
////		m_center += move;
////
////		// 角度加算
////		m_fTheta -= m_fOmega;
////
////		// 座標
////		SetPosition(D3DXVECTOR3(m_center.x + m_fRadius * cosf(D3DXToRadian(m_fTheta)),
////			m_center.y + m_fRadius * sinf(D3DXToRadian(m_fTheta)), 0.0f));
////
////		// 移動量
////		SetMove(move);
////	}
//}
//
////=============================================================================
//// 方向転換する敵の更新処理
////=============================================================================
//void CEnemy::DirectionUpdate(void)
//{
////	// プレイヤーの情報を取得
////	CPlayer *pPlayer = CGame::GetPlayer();
////	
////	// 座標取得
////	D3DXVECTOR3 Target = pPlayer->GetPos();		// プレイヤーの座標
////	D3DXVECTOR3 pos = GetPos();					// エネミーの7座標
////
////	// プレイヤーと同じ高さになったら
////	if (pos.y >= Target.y)
////	{
////
////		// 画面半分より左にいたら
////		if (pos.x <= SCREEN_WIDTH /2)
////		{
////			// 横に移動する
////			SetMove(D3DXVECTOR3(5.0f, 0.0f, 0.0f));
////		}
////		else
////		{
////			// 横に移動する
////			SetMove(D3DXVECTOR3(-5.0f, 0.0f, 0.0f));
////		}
////	}
////
////	if (m_nDirection == 0)
////	{
////		if (pos.x >= SCREEN_WIDTH / 2)
////		{
////			// 消す
////			SetLife(0);
////		}
////	}
////	else if (m_nDirection == 1)
////	{
////		if (pos.x <= SCREEN_WIDTH / 2)
////		{
////			// 消す
////			SetLife(0);
////		}
////	}
//}
//
////=============================================================================
//// 追従してくる敵
////=============================================================================
//void CEnemy::FollowUpdate(void)
//{
////	if (m_bFlashFlag == false)
////	{
////		// 透明度の変更
////		Appearance();
////	}
////
////	if (m_bFollowFlag == false)
////	{
////		m_nEnemyCounter++;
////
////		if (m_nEnemyCounter >= 50)
////		{
////			m_bFollowFlag = true;
////
////			// プレイヤー情報を取得
////			CPlayer *pPlayer = CGame::GetPlayer();
////			D3DXVECTOR3 Ppos = pPlayer->GetPos();
////			D3DXVECTOR3 pos = GetPos();
////
////			//自機を取得する
////			float fPposx = Ppos.x, fPposy = Ppos.y;		// 自機の座標
////			float fEposx = pos.x, fEposy = pos.y;	// 敵の座標
////			float fAngle;								// 角度
////
////			//角度を決める
////			fAngle = atan2f((fEposx - fPposx), (fEposy - fPposy));
////
////			// 透明な敵の移動
////			D3DXVECTOR3 FollowMove = D3DXVECTOR3(
////				(sinf(fAngle)*-FOLLOW_MOVE_X),
////				cosf(fAngle)*-FOLLOW_MOVE_Y, 0.0f);
////
////			// 移動量の設定
////			SetMove(FollowMove);
////		}
////	}
//}

//====================================================================
// 拡大
//====================================================================
void CEnemy::ScaleUp(D3DXVECTOR3 BaseSize)
{
	if (m_fScale <= MAX_SCALE_NUM)
	{
		// 縮小量を加算
		m_fScale += m_fScaleNum;

		D3DXVECTOR3 size = GetSize();

		// サイズの変更
		D3DXVECTOR3 ScaleSize = D3DXVECTOR3(BaseSize.x * m_fScale, BaseSize.y * m_fScale, 0.0f);

		// Scene2Dにサイズを渡す
 		SetScaleSize(ScaleSize);
	}
	else
	{
		m_fScale = MAX_SCALE_NUM;
		m_bRotationScale = true;
	}
}

//=============================================================================
// 当たり判定
//=============================================================================
bool CEnemy::Collision(void)
{
	// プレイヤーの情報を受け取る
	CPlayer *pPlayer = CGame::GetPlayer();

	// 座標を受け取る
	D3DXVECTOR3 Target = pPlayer->GetPos();

	// 自身の情報受け取る
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 size = GetSize();

	if (Target.x - DECISION_PLAYER_SIZE_X / 2 < pos.x + size.x / 2 &&
		Target.x + DECISION_PLAYER_SIZE_X / 2 > pos.x - size.x / 2 &&
		Target.y - DECISION_PLAYER_SIZE_Y / 2 < pos.y + size.y / 2 &&
		Target.y + DECISION_PLAYER_SIZE_Y / 2 > pos.y - size.y / 2)
	{
		// 当たり判定処理
		if (m_Etype != ENEMY_TYPE_ROTATION)
		{
			// 復活状態以外
			if (pPlayer->GetState() != STATE_REVIVE)
			{
				// プレイヤーにダメージを与える
				pPlayer->HitDamage(ENEMY_ATTACK_NUM);
			}
		}
		else
		{
			// 復活状態以外
			if (pPlayer->GetState() != STATE_REVIVE)
			{

				if (m_bRotationScale == true)
				{
					// プレイヤーにダメージを与える
					pPlayer->HitDamage(ENEMY_ATTACK_NUM);
				}
			}
		}

		return true;
	}

	return false;
}