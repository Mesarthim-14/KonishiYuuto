//=============================================================================
//
// プレイヤー処理 [player.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "player.h"
#include "keyboard.h"
#include "manager.h"
#include "renderer.h"
#include "bullet.h"
#include "shield.h"
#include "ui.h"
#include "laser.h"
#include "fade.h"
#include "game.h"
#include "gage.h"
#include "remain.h"
#include "explosion.h"
#include "muzzle_flash.h"
#include "joypad.h"
#include "bomb.h"
#include "enemy.h"
#include "bullet.h"
#include "bomb_ui.h"
#include "sound.h"
#include "texture.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define PLAYER_LIFE					(1)			// プレイヤーの体力
#define PLAYER_BULLET_SIZE_X		(30)		// プレイヤーの弾のサイズ(横)
#define PLAYER_BULLET_SIZE_Y		(120)		// プレイヤーの弾のサイズ(縦)
#define PLAYER_SPEED				(5.0f)	 	// プレイヤーの速度
#define BULLET_INTERVAL				(5)			// 弾の連射間隔
#define PLAYER_STOCK				(3)			// プレイヤーの残機
#define PLAYER_ARMOR_COUNT			(240)		// 無敵時間
#define PLAYER_BOMB_NUM				(1)			// ボムの数
#define PLAYER_LASER_NUM			(10)		// レーザーに必要な値
#define PLAYER_LASER_FLAME			(100)		// レーザーの終了フレーム
#define PLAYER_RESURRECTION_FLAME	(50)		// 復活のフレーム

//=============================================================================
// コンストラクタ
//=============================================================================
CPlayer::CPlayer() : CCharacter(TYPE_PLAYER)
{
	m_BulletState = 0;
	m_nStock = 0;
	m_nLaserFlame = 0;
	m_nLaserCounter = 0;
	m_bShildInfo = false;
	m_bShildScaleInfo = false;
	m_pShield = NULL;
	m_pGage = NULL;
	m_pLaser = NULL;
	m_pBombUi = NULL;
	m_nResurrectionCnt = 0;
	m_bPlayerDraw = false;
	m_bUseLaser = false;
	m_StateCount = 0;
	m_nBombFlame = 0;
	m_nBombNum = 0;
	m_nBombCount = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CPlayer::~CPlayer()
{

}

//=============================================================================
// インスタンス生成
//=============================================================================
CPlayer * CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// メモリ確保
	CPlayer *pPlayer = new CPlayer;

	// 初期化処理
	pPlayer->Init(pos, size, type);	

	// ゲージの枠生成
	pPlayer->m_pGage = CGage::Create(D3DXVECTOR3(WALL_SIZE_X - 100.0f, SCREEN_HEIGHT - 202.5f, 0.0f), D3DXVECTOR3(GAGE_SIZE_X + 5.0f, GAGE_SIZE_Y + 5.0f, 0.0f),
		TYPE_SCORE, CGage::GAGE_TYPE_FLAME);

	// ゲージ生成
	pPlayer->m_pGage = CGage::Create(D3DXVECTOR3(WALL_SIZE_X - 100.0f, SCREEN_HEIGHT - 200.0f, 0.0f), D3DXVECTOR3(GAGE_SIZE_X, GAGE_SIZE_Y, 0.0f),
		TYPE_SCORE, CGage::GAGE_TYPE_BLUE);

	return pPlayer;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPlayer::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// 値の代入
	m_BulletState = BULLET_INTERVAL;	// 弾の間隔初期化
	m_nLaserFlame = LASER_FLAME;		// レーザーのフレーム
	SetLife(PLAYER_LIFE);				// 体力

	// テクスチャ受け渡し
	BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_PLAYER));

	// ポリゴン初期化
	CCharacter::Init(pos, size, type);

	// 初期シールドの生成
	m_pShield = CShield::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(SHIELD_SIZE_X, SHIELD_SIZE_Y, 0.0f), 
		TYPE_SHIELD, CShield::SHIELD_TYPE_WHITE);

	if (m_pBombUi == NULL)
	{
		m_pBombUi = CBombUi::Create(
			D3DXVECTOR3(195.0f, 630.0f, 0.0f), D3DXVECTOR3(BOMB_UI_SIZE_X, BOMB_UI_SIZE_Y, 0.0f), TYPE_SCORE);
	}

	// シールドを白に
	m_bShildInfo = true;

	// ボムの所持数
	m_nBombCount = PLAYER_BOMB_NUM;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPlayer::Uninit(void)
{
	// 終了処理
	CCharacter::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CPlayer::Update(void)
{
	// 更新処理
	CCharacter::Update();

	// プレイヤーの状態
	UpdateState();

	if (m_bPlayerDraw == false)
	{
		// プレイヤー制御関数
		PlayerControl();

		if (m_pShield != NULL)
		{
			D3DXVECTOR3 pos = GetPos();

			// シールドに座標を渡す
			m_bShildScaleInfo = m_pShield->ScaleUp(pos);
		}
	}

	// ボムの当たり判定
	if (m_bBombUse == true)
	{
		// ボムの当たり判定
		BombCollision();
	}

	STATE state = GetState();

	if (state == STATE_DAMAGE)
	{
		// 死ぬ処理
		Death();
	}

	// 復活処理
	if (m_bPlayerDraw == true)
	{
		Resurrection();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CPlayer::Draw(void)
{
	if (m_bPlayerDraw == false)
	{
		// 描画処理
		CScene2D::Draw();
	}
}

//=============================================================================
// プレイヤー制御関数
//=============================================================================
void CPlayer::PlayerControl(void)
{
	// ジョイパッドの取得
	DIJOYSTATE js = CInputJoypad::GetStick(0);

	D3DXVECTOR3 pos = GetPos();

	if (js.lX != 0.0f || js.lY != 0)
	{
		float fAngle = atan2f((float)js.lX, (float)js.lY);

		// ジョイパッド操作
		pos.x += sinf(fAngle)* PLAYER_SPEED;
		pos.y += cosf(fAngle)* PLAYER_SPEED;
	}

	// 座標を渡す
	SetPosition(pos);

	// キーボード更新
	CKeyboard *pKeyboard = CManager::GetKeyboard();

	// Wキーを押したとき
	if (pKeyboard->GetPress(DIK_W))
	{
		pos.y += cosf(D3DX_PI)*PLAYER_SPEED;
	}
	// Sキーを押したとき
	if (pKeyboard->GetPress(DIK_S))
	{
		pos.y += cosf(0)*PLAYER_SPEED;
	}
	// Aキーを押したとき
	if (pKeyboard->GetPress(DIK_A))
	{
		pos.x -= sinf(D3DX_PI / 2)*PLAYER_SPEED;
	}
	// Dキーを押したとき
	if (pKeyboard->GetPress(DIK_D))
	{
		pos.x += sinf(D3DX_PI / 2)*PLAYER_SPEED;
	}

	// シールド生成の処理
	if (pKeyboard->GetTrigger(DIK_RSHIFT) || CManager::GetJoypad()->GetJoystickTrigger(2, 0))
	{
		if (m_bUseLaser == true)
		{
			m_bUseLaser = false;
		}

		if (m_bShildScaleInfo == true)
		{
			// シールド生成
			if (m_bShildInfo == true)
			{	
				//白いとき
				if (m_pShield != NULL)
				{
					// シールド消滅
					m_pShield->Uninit();
					m_pShield = NULL;
				}
				m_bShildInfo = false;
				// 黒いとき
				m_pShield = CShield::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXVECTOR3(SHIELD_SIZE_X, SHIELD_SIZE_Y, 0.0f),
					TYPE_SHIELD, CShield::SHIELD_TYPE_BLACK);
			}
			else
			{
				// 黒いとき
				if (m_pShield != NULL)
				{
					// シールド消滅
					m_pShield->Uninit();
					m_pShield = NULL;
				}
				m_bShildInfo = true;
				// 白いとき
				m_pShield = CShield::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					D3DXVECTOR3(SHIELD_SIZE_X, SHIELD_SIZE_Y, 0.0f),
					TYPE_SHIELD, CShield::SHIELD_TYPE_WHITE);
			}
		}
	}

	// SPACEキーが押されたら
	if (pKeyboard->GetPress(DIK_SPACE) && m_bUseLaser == false || CManager::GetJoypad()->GetJoystickPress(0, 0))
	{
		// プレイヤーの色
		if (m_bShildScaleInfo == true)
		{
			// バレットの間隔
			if (m_BulletState == BULLET_INTERVAL)
			{
				CSound *pSound = NULL;
				pSound = CManager::GetSound();
				pSound->Play(CSound::SOUND_LABEL_SHOT);

				if (m_bShildInfo == true)
				{
					// 弾の生成
					CBullet::Create(D3DXVECTOR3(pos.x + PLAYER_SHOT_POS_X, pos.y - PLAYER_SHOT_POS_Y, 0.0f),
						D3DXVECTOR3(0.0f, -15.0f, 0.0f),
						D3DXVECTOR3(PLAYER_BULLET_SIZE_X, PLAYER_BULLET_SIZE_Y, 0.0f),
						TYPE_BULLET, CBullet::BULLET_TYPE_PLAYER, CBullet::BULLET_COLOR_WHITE,
						100);

					// 弾の生成
					CBullet::Create(D3DXVECTOR3(pos.x - PLAYER_SHOT_POS_X, pos.y - PLAYER_SHOT_POS_Y, 0.0f),
						D3DXVECTOR3(0.0f, -15.0f, 0.0f),
						D3DXVECTOR3(PLAYER_BULLET_SIZE_X, PLAYER_BULLET_SIZE_Y, 0.0f),
						TYPE_BULLET, CBullet::BULLET_TYPE_PLAYER, CBullet::BULLET_COLOR_WHITE,
						100);

					// マズルフラッシュの生成
					for (int nCount = 0; nCount < MUZZLE_FLASH_NUM; nCount++)
					{
						CMuzzleFlash::Create(D3DXVECTOR3(pos.x + PLAYER_SHOT_POS_X, pos.y - PLAYER_SHOT_POS_Y + 10, 0.0f),
							D3DXVECTOR3(MUZZLE_FLASH_SIZE_X, MUZZLE_FLASH_SIZE_Y, 0.0f),
							TYPE_EFFECT, CMuzzleFlash::MUZZLE_FLASH_COLOR_WHITE, MUZZLE_FLASH_LIFE);

						CMuzzleFlash::Create(D3DXVECTOR3(pos.x - PLAYER_SHOT_POS_X, pos.y - PLAYER_SHOT_POS_Y + 10, 0.0f),
							D3DXVECTOR3(MUZZLE_FLASH_SIZE_X, MUZZLE_FLASH_SIZE_Y, 0.0f),
							TYPE_EFFECT, CMuzzleFlash::MUZZLE_FLASH_COLOR_WHITE, MUZZLE_FLASH_LIFE);
					}
				}
				else
				{
					// 弾の生成
					CBullet::Create(D3DXVECTOR3(pos.x + PLAYER_SHOT_POS_X, pos.y - PLAYER_SHOT_POS_Y , 0.0f),
						D3DXVECTOR3(0.0f, -15.0f, 0.0f),
						D3DXVECTOR3(PLAYER_BULLET_SIZE_X, PLAYER_BULLET_SIZE_Y, 0.0f),
						TYPE_BULLET, CBullet::BULLET_TYPE_PLAYER, CBullet::BULLET_COLOR_BLACK,
						100);
					// 弾の生成
					CBullet::Create(D3DXVECTOR3(pos.x - PLAYER_SHOT_POS_X, pos.y - PLAYER_SHOT_POS_Y, 0.0f),
						D3DXVECTOR3(0.0f, -15.0f, 0.0f),
						D3DXVECTOR3(PLAYER_BULLET_SIZE_X, PLAYER_BULLET_SIZE_Y, 0.0f),
						TYPE_BULLET, CBullet::BULLET_TYPE_PLAYER, CBullet::BULLET_COLOR_BLACK,
						100);

					// マズルフラッシュの生成
					for (int nCount = 0; nCount < MUZZLE_FLASH_NUM; nCount++)
					{
						CMuzzleFlash::Create(D3DXVECTOR3(pos.x + PLAYER_SHOT_POS_X, pos.y - PLAYER_SHOT_POS_Y + 10, 0.0f),
							D3DXVECTOR3(MUZZLE_FLASH_SIZE_X, MUZZLE_FLASH_SIZE_Y, 0.0f),
							TYPE_EFFECT, CMuzzleFlash::MUZZLE_FLASH_COLOR_BLACK, MUZZLE_FLASH_LIFE);

						CMuzzleFlash::Create(D3DXVECTOR3(pos.x - PLAYER_SHOT_POS_X, pos.y - PLAYER_SHOT_POS_Y + 10, 0.0f),
							D3DXVECTOR3(MUZZLE_FLASH_SIZE_X, MUZZLE_FLASH_SIZE_Y, 0.0f),
							TYPE_EFFECT, CMuzzleFlash::MUZZLE_FLASH_COLOR_BLACK, MUZZLE_FLASH_LIFE);
					}
				}
			}
		}
		// カウンターを減算
		m_BulletState--;

		// 0になったら元の値に戻す
		if (m_BulletState <= 0)
		{
			m_BulletState = BULLET_INTERVAL;
		}
	}

	// Lキーが押されたら
	if (pKeyboard->GetTrigger(DIK_L) && m_pGage->GetLaserNum() >= PLAYER_LASER_NUM || CManager::GetJoypad()->GetJoystickTrigger(7, 0))
	{
			if (m_bShildScaleInfo == true)
			{
				if (m_bShildInfo == true)
				{
					// トリガー
					if (m_bUseLaser == true)
					{
						if (m_nLaserCounter >= PLAYER_LASER_FLAME)
						{
							m_bUseLaser = false;
							m_nLaserCounter = 0;
						}
					}
					else
					{
						if (m_nLaserCounter >= PLAYER_LASER_FLAME)
						{
							if (m_pLaser == NULL)
							{
								// 弾の生成
								m_pLaser = CLaser::Create(D3DXVECTOR3(pos.x + 0.0f, pos.y + 5.0f, 0.0f),
									D3DXVECTOR3(0.0f, -15.0f, 0.0f),
									D3DXVECTOR3(LASER_SIZE_X, LASER_SIZE_Y, 0.0f),
									TYPE_LASER, CLaser::LASER_COLOR_WHITE);
							}

							// サウンドの処理
							CSound *pSound = NULL;
							pSound = CManager::GetSound();
							pSound->Play(CSound::SOUND_LABEL_LASER);

							m_bUseLaser = true;
							m_nLaserCounter = 0;
						}
					}
				}
				else if (m_bShildInfo == false)
				{
					// ボタンが押された
					// トリガー
					if (m_bUseLaser == true)
					{
						if (m_nLaserCounter >= PLAYER_LASER_FLAME)
						{
							m_bUseLaser = false;
							m_nLaserCounter = 0;
						}
					}
					else
					{
						if (m_nLaserCounter >= PLAYER_LASER_FLAME)
						{
							if (m_pLaser == NULL)
							{	
								// レーザーの生成
								m_pLaser = CLaser::Create(D3DXVECTOR3(pos.x + 0.0f, pos.y + 15.0f, 0.0f),
									D3DXVECTOR3(0.0f, -15.0f, 0.0f),
									D3DXVECTOR3(LASER_SIZE_X, LASER_SIZE_Y, 0.0f),
									TYPE_LASER, CLaser::LASER_COLOR_BLACK);
							}

							// 音の処理
							CSound *pSound = NULL;
							pSound = CManager::GetSound();
							pSound->Play(CSound::SOUND_LABEL_LASER);

							m_bUseLaser = true;
							m_nLaserCounter = 0;
						}
					}
				}
			}
	}

	// ボムの処理
	if (m_nBombCount > 0 &&pKeyboard->GetTrigger(DIK_B) && m_bUseLaser == false || 
		m_nBombCount > 0 &&CManager::GetJoypad()->GetJoystickTrigger(5, 0))
	{
		m_nBombCount--;

		CSound *pSound = NULL;
		pSound = CManager::GetSound();
		pSound->Play(CSound::SOUND_LABEL_BOMB);

		if (m_pBombUi != NULL)
		{
			// ボムのUIを消す
			m_pBombUi->Uninit();
			m_pBombUi = NULL;
		}
		if (m_bShildInfo == true)
		{
			// ボムの衝撃波生成
			for (int nCount = 0; nCount < BOMB_NUM; nCount++)
			{
				CBomb::Create(pos,
					D3DXVECTOR3(BOMB_SIZE_X, BOMB_SIZE_Y, 0.0f),
					TYPE_EFFECT, CBomb::BOMB_TYPE_SHOCK, CBomb::BOMB_COLOR_WHITE,
					nCount* (BOMB_ANGLE / BOMB_NUM), 180, BOMB_DISTANCE, BOMB_LIFE);

				CBomb::Create(pos,
					D3DXVECTOR3(BOMB_SIZE_X, BOMB_SIZE_Y, 0.0f),
					TYPE_EFFECT, CBomb::BOMB_TYPE_SHOCK, CBomb::BOMB_COLOR_WHITE,
					nCount* (BOMB_ANGLE / BOMB_NUM), 180, BOMB_DISTANCE, BOMB_LIFE);
			}

			// ボムの火花生成
			for (int nCount = 1; nCount < BOMB_SPARK_NUM + 1; nCount++)
			{
				CBomb::Create(pos,
					D3DXVECTOR3(BOMB_SPARK_SIZE_X, BOMB_SPARK_SIZE_Y, 0.0f),
					TYPE_EFFECT, CBomb::BOMB_TYPE_SPARK, CBomb::BOMB_COLOR_WHITE,
					nCount * (BOMB_SPARK_ANGLE / BOMB_SPARK_NUM), 90, BOMB_SPARK_DISTANCE, BOMB_SPARK_LIFE);

				CBomb::Create(pos,
					D3DXVECTOR3(BOMB_SPARK_SIZE_X, BOMB_SPARK_SIZE_Y, 0.0f),
					TYPE_EFFECT, CBomb::BOMB_TYPE_SPARK, CBomb::BOMB_COLOR_WHITE,
					nCount * (BOMB_SPARK_ANGLE / BOMB_SPARK_NUM), 90, BOMB_SPARK_DISTANCE, BOMB_SPARK_LIFE);
			}
		}
		else
		{
			// ボムの衝撃波生成
			for (int nCount = 0; nCount < BOMB_NUM; nCount++)
			{
				CBomb::Create(pos,
					D3DXVECTOR3(BOMB_SIZE_X, BOMB_SIZE_Y, 0.0f),
					TYPE_EFFECT, CBomb::BOMB_TYPE_SHOCK, CBomb::BOMB_COLOR_BLACK,
					nCount* (BOMB_ANGLE / BOMB_NUM), 180, BOMB_DISTANCE, BOMB_LIFE);

				CBomb::Create(pos,
					D3DXVECTOR3(BOMB_SIZE_X, BOMB_SIZE_Y, 0.0f),
					TYPE_EFFECT, CBomb::BOMB_TYPE_SHOCK, CBomb::BOMB_COLOR_BLACK,
					nCount* (BOMB_ANGLE / BOMB_NUM), 180, BOMB_DISTANCE, BOMB_LIFE);
			}

			// ボムの火花生成
			for (int nCount = 1; nCount < BOMB_SPARK_NUM + 1; nCount++)
			{
				CBomb::Create(pos,
					D3DXVECTOR3(BOMB_SPARK_SIZE_X, BOMB_SPARK_SIZE_Y, 0.0f),
					TYPE_EFFECT, CBomb::BOMB_TYPE_SPARK, CBomb::BOMB_COLOR_BLACK,
					nCount * (BOMB_SPARK_ANGLE / BOMB_SPARK_NUM), 90, BOMB_SPARK_DISTANCE, BOMB_SPARK_LIFE);

				CBomb::Create(pos,
					D3DXVECTOR3(BOMB_SPARK_SIZE_X, BOMB_SPARK_SIZE_Y, 0.0f),
					TYPE_EFFECT, CBomb::BOMB_TYPE_SPARK, CBomb::BOMB_COLOR_BLACK,
					nCount * (BOMB_SPARK_ANGLE / BOMB_SPARK_NUM), 90, BOMB_SPARK_DISTANCE, BOMB_SPARK_LIFE);

			}

		}
		m_bBombUse = true;
	}
	if (m_bUseLaser == true)
	{
		m_nLaserFlame++;

		if (m_nLaserFlame >= LASER_FLAME)
		{
			// ゲージの減算
			m_pGage->SubtractGame(PLAYER_LASER_NUM);
			m_nLaserFlame = 0;
		}

		// ゲージが一定量以下だったら
		if (m_pGage->GetLaserNum() <= PLAYER_LASER_NUM)
		{
			m_bUseLaser = false;
		}
		m_nLaserCounter++;
	}
	else
	{
		m_nLaserCounter++;
	}

	// レーザーが使われていたら
	if (m_pLaser != NULL)
	{

		if (m_pLaser->GetSize().x <= 0.0f)
		{
			// レーザーの終了処理
			m_pLaser->Uninit();
			m_pLaser = NULL;

			m_bUseLaser = false;

			// 音の処理
			CSound *pSound = NULL;
			pSound = CManager::GetSound();
			pSound->Stop(CSound::SOUND_LABEL_LASER);

		}
	}

	// 左判定
	if (pos.x - PLAYER_SIZE_X / 2 < WALL_SIZE_X)
	{
		pos.x = WALL_SIZE_X + PLAYER_SIZE_X / 2;
	}
	// 右判定
	if (pos.x + PLAYER_SIZE_X / 2 > SCREEN_WIDTH - WALL_SIZE_X)
	{
		pos.x =  SCREEN_WIDTH - WALL_SIZE_X - PLAYER_SIZE_X / 2;
	}
	// 上判定
	if (pos.y - PLAYER_SIZE_Y / 2 < 0.0f)
	{
		pos.y = PLAYER_SIZE_Y / 2;
	}
	// 下判定
	if (pos.y + PLAYER_SIZE_Y / 2 > SCREEN_HEIGHT)
	{
		pos.y = SCREEN_HEIGHT - PLAYER_SIZE_Y / 2;
	}

	// 座標を渡す
	SetPosition(pos);

}

//=============================================================================
// 復活
//=============================================================================
void CPlayer::Resurrection(void)
{
	// 復活のカウント
	m_nResurrectionCnt++;

	if (m_bPlayerDraw == false)
	{
		// 復活しました
		m_bPlayerDraw = true;

		SetState(STATE_REVIVE);
		m_nBombCount = PLAYER_BOMB_NUM;

		if (m_pBombUi == NULL)
		{
			m_pBombUi = CBombUi::Create(
				D3DXVECTOR3(195.0f, 630.0f, 0.0f), D3DXVECTOR3(BOMB_UI_SIZE_X, BOMB_UI_SIZE_Y, 0.0f), TYPE_SCORE);
		}

		// スコアを加算
		CRemain *pRemain = CGame::GetRemain();
		if (pRemain != NULL)
		{
			// 残機を減らす
			pRemain->SetRemain(1);
		}
	}

	if (m_nResurrectionCnt >= PLAYER_RESURRECTION_FLAME)
	{
		// 残機のカウントを上げる
		m_nStock++;

		// 残機が無かったらリザルト
		if (m_nStock >= PLAYER_STOCK&& CManager::GetFade()->Get() == CFade::FADE_NONE)
		{
			// 終了処理
			Uninit();

			// フェード処理
			CManager::GetFade()->SetFade(CManager::MODE_RESULT);

			// 音の処理
			CSound *pSound = NULL;
			pSound = CManager::GetSound();
			pSound->Stop(CSound::SOUND_LABEL_GAME);
			return;
		}

		// レーザーが使われていたら
		if (m_pLaser != NULL)
		{
			// レーザーの終了処理
			m_pLaser->Uninit();
			m_pLaser = NULL;

			m_bUseLaser = false;
		}

		// ライフと座標を戻す
		SetLife(PLAYER_LIFE);
		SetPosition(D3DXVECTOR3(SCREEN_WIDTH / 2, 700.0f, 0.0f));

		D3DXVECTOR3 pos = GetPos();

		// シールド生成
		m_pShield = CShield::Create(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f),
			D3DXVECTOR3(SHIELD_SIZE_X, SHIELD_SIZE_Y, 0.0f),
			TYPE_SHIELD, CShield::SHIELD_TYPE_WHITE);

		// 初期化
		m_nResurrectionCnt = 0;
		m_bPlayerDraw = false;
		m_bShildInfo = true;

		// レーザーの値を減らす
		int nGame = m_pGage->GetLaserNum();
		m_pGage->SubtractGame(nGame);
	}
}

//=============================================================================
// プレイヤー状態更新
//=============================================================================
void CPlayer::UpdateState(void)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();
	// 頂点情報を設定
	VERTEX_2D *pVtx;
	// 頂点バッファをロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 状態の情報取得
	STATE state = GetState();

	switch (state)
	{
		// 通常状態
	case STATE_NORMAL:
		// 頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// 左上頂点の色	透明度255
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// 右上頂点の色	透明度255
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// 左下頂点の色	透明度255
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// 右下頂点の色	透明度255
		break;

		// 蘇生時
	case STATE_REVIVE:
		// 復活
		m_StateCount++;

		
		if (m_StateCount % 2 == 0)
		{
			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 50);	// 左上頂点の色	透明度255
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 50);	// 右上頂点の色	透明度255
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 50);	// 左下頂点の色	透明度255
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 50);	// 右下頂点の色	透明度255
		}
		else
		{
			// 頂点カラーの設定
			pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// 左上頂点の色	透明度255
			pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// 右上頂点の色	透明度255
			pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// 左下頂点の色	透明度255
			pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// 右下頂点の色	透明度255
		}

		if (m_StateCount >= PLAYER_ARMOR_COUNT)
		{
			// 通常状態に戻す
			SetState(STATE_NORMAL);
			m_StateCount = 0;
		}
		break;
	case STATE_LASER:
		break;
	}

	// 頂点バッファをアンロックする
	pVtxBuff->Unlock();
}

//=============================================================================
// ボムの当たり判定
//=============================================================================
bool CPlayer::BombCollision(void)
{
	m_nBombFlame++;

	CScene *pScene = NULL;

	if (pScene == NULL)
	{
		// シーンを取得
		pScene = CScene::GetTop(TYPE_ENEMY);

		while (pScene)
		{
			CScene *pSceneNext = pScene->GetNext();

			TYPE type = pScene->GetType();

			// メモリのキャスト
			CScene2D *pScene2D = (CScene2D*)pScene;

			if (pScene2D != NULL)
			{
				// ターゲットの情報確保
				D3DXVECTOR3 Target = pScene2D->GetPos();

				// 敵のサイズ取得
				CEnemy *pEnemy = (CEnemy*)pScene2D;
				D3DXVECTOR3 size = pEnemy->GetSize();

				// 自分の座標
				D3DXVECTOR3 pos = GetPos();

				for (int nCntAngle = 0; nCntAngle < 360; nCntAngle++)
				{
					// 自分と相手の当たり判定
					if (Target.x - size.x / 2 >= pos.x + 350.0f * cosf(D3DXToRadian(nCntAngle)) &&
						Target.x + size.x / 2 <= pos.x - 350.0f * cosf(D3DXToRadian(nCntAngle)) &&
						Target.y + size.y / 2 <= pos.y - 350.0f * cosf(D3DXToRadian(nCntAngle)) &&
						Target.y - size.y / 2 >= pos.y + 350.0f * cosf(D3DXToRadian(nCntAngle)))
					{
						// ライフをへらす
						pEnemy->HitDamage(30);
						return true;
					}

				}
			}
			pScene = pSceneNext;
		}

		// シーンを取得
		pScene = CScene::GetTop(TYPE_BULLET);

		while (pScene)
		{

			CScene *pSceneNext = pScene->GetNext();

			// メモリのキャスト
			CScene2D *pScene2D = (CScene2D*)pScene;

			// ターゲットの情報確保
			D3DXVECTOR3 Target = pScene2D->GetPos();

			// 敵のサイズ取得
			CBullet *pBullet = (CBullet*)pScene2D;
			D3DXVECTOR3 size = pBullet->GetSize();
			
			// 自分の座標
			D3DXVECTOR3 pos = GetPos();

			for (int nCntAngle = 0; nCntAngle < 360; nCntAngle++)
			{
				// 自分と相手の当たり判定
				if (Target.x - size.x / 2 >= pos.x + 350.0f * cosf(D3DXToRadian(nCntAngle)) &&
					Target.x + size.x / 2 <= pos.x - 350.0f * cosf(D3DXToRadian(nCntAngle)) &&
					Target.y + size.y / 2 <= pos.y - 350.0f * cosf(D3DXToRadian(nCntAngle)) &&
					Target.y - size.y / 2 >= pos.y + 350.0f * cosf(D3DXToRadian(nCntAngle)))
				{

					pBullet->DecreaseLife(10000);
		//			return true;

				}
			}
			pScene = pSceneNext;
		}

	}


	if (m_nBombFlame >= 1)
	{
		m_bBombUse = false;
		m_nBombFlame = 0;
	}

	return false;
}

//=============================================================================
// 死んだときの関数
//=============================================================================
void CPlayer::Death(void)
{
	// 状態の情報取得
	STATE state = GetState();

	if (state == STATE_DAMAGE)
	{
		int nLife = GetLife();

		if (nLife <= 0)
		{
			CSound *pSound = NULL;
			pSound = CManager::GetSound();
			pSound->Play(CSound::SOUND_LABEL_BOMB);
			D3DXVECTOR3 pos = GetPos();

			if (m_bShildInfo == true)
			{
				// 爆発生成
				CExplosion::Create(
					pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y, 0.0f),
					TYPE_EXPLOSION, CExplosion::COLOR_TYPE_WHITE);
			}
			else
			{
				// 爆発生成
				CExplosion::Create(
					pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(EXPLOSION_SIZE_X, EXPLOSION_SIZE_Y, 0.0f),
					TYPE_EXPLOSION, CExplosion::COLOR_TYPE_BLACK);
			}

			// 体力が無くなったら
			if (nLife <= 0)
			{
				if (m_pShield != NULL)
				{
					// シールド消滅
					m_pShield->Uninit();
					m_pShield = NULL;
				}
			}

			SetLife(10000);

			// 復活の処理
			Resurrection();
		}
	}

}

//=============================================================================
// シールド状態を返す
//=============================================================================
bool CPlayer::GetShildInfo(void)
{
	return m_bShildInfo;
}

//=============================================================================
// レーザーを使っているか
//=============================================================================
bool CPlayer::GetUseLaser(void)
{
	return m_bUseLaser;
}

//=============================================================================
// レーザーゲージの状態
//=============================================================================
CGage *CPlayer::GetGage(void)
{
	return m_pGage;
}

//=============================================================================
// レーザーの情報
//=============================================================================
CLaser * CPlayer::GetLaser(void)
{
	return m_pLaser;
}
