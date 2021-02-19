//=============================================================================
//
// レーザークラス [laser.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "laser.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "sound.h"
#include "scene.h"
#include "flash.h"
#include "enemy.h"
#include "explosion.h"
#include "boss.h"
#include "bullet.h"
#include "game.h"
#include "muzzle_flash.h"
#include "texture.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define LASER_DAMAGE		(2)		// ダメージ

//=============================================================================
// インスタンス生成
//=============================================================================
CLaser * CLaser::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,
	D3DXVECTOR3 size, TYPE type, LASER_COLOR Ctype)
{
	// インスタンス生成
	CLaser *pLaser = new CLaser;

	if (pLaser != NULL)
	{
		// 初期化処理
		pLaser->Init(pos, size, type);			// 初期化情報
		pLaser->SetInfo(move, size);			// 情報設定
		pLaser->SetColor(Ctype);				// 色の設定
		pLaser->InitColor();					// 色の初期化
		pLaser->InitScroll(2, -0.03f);			// スクロール情報設定
		pLaser->BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_LASER));	// テクスチャ設定
	}

	return pLaser;
}

//=============================================================================
// コンストラクタ
//=============================================================================
CLaser::CLaser() : CScene2D(TYPE_LASER)
{
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Ctype = LASER_COLOR_NONE;
	m_pVtxBuff = NULL;
	m_bUse = true;
	m_PolygonPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_PolygonSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_PolygonTop = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// デストラクタ
//=============================================================================
CLaser::~CLaser()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CLaser::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// 初期化処理
	CScene2D::Init(pos, size, type);
	m_Pos = pos;

	return S_OK;
}

//=============================================================================
// カラーの設定
//=============================================================================
void CLaser::InitColor(void)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// 頂点情報を設定
	VERTEX_2D *pVtx;

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 色の設定
	switch (m_Ctype)
	{
		// 白いとき
	case LASER_COLOR_WHITE:

		// 頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// 左上頂点の色	透明度255
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// 右上頂点の色	透明度255
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// 左下頂点の色	透明度255
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// 右下頂点の色	透明度255
		break;

		// 黒いとき
	case LASER_COLOR_BLACK:
		// 頂点カラーの設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 40, 255);	// 左上頂点の色	透明度255
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 40, 255);	// 右上頂点の色	透明度255
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 40, 255);	// 左下頂点の色	透明度255
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 40, 255);	// 右下頂点の色	透明度255
		break;
	}

	// 頂点バッファをアンロックする
	pVtxBuff->Unlock();
}

//=============================================================================
// 終了処理
//=============================================================================
void CLaser::Uninit(void)
{
	// 2Dポリゴン終了処理
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CLaser::Update(void)
{
	// 2Dポリゴン更新処理
	CScene2D::Update();

	// 現在の位置を取得
	m_Pos = GetPos();

	// レーザーを動かす処理
	LaserUpdate();

	// 画像のスクロール
	UpdateScroll();

	// 敵との当たり判定
	Collision();

	// Scene2Dに座標を渡す
	SetPos(m_Pos);


	// レーザーの情報を受け取る
	CPlayer *pPlayer = CGame::GetPlayer();
	bool bUse = pPlayer->GetUseLaser();

	// 使われてないとき
	if (bUse == false)
	{
		// 終了処理
		DisappearLaser();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CLaser::Draw(void)
{
	// 2Dポリゴン描画処理
	CScene2D::Draw();
}

//=============================================================================
// カラー設定
//=============================================================================
void CLaser::SetColor(LASER_COLOR Ctype)
{
	m_Ctype = Ctype;
}

//=============================================
// 弾の設定
//=============================================
void CLaser::SetInfo(D3DXVECTOR3 move, D3DXVECTOR3 size)
{
	// 変数に代入
	m_move = move;
	m_Size = size;
}

//=============================================================================
// レーザーの更新
//=============================================================================
void CLaser::LaserUpdate(void)
{
	// レンダラーの情報を受け取る
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// プレイヤーの情報取得
	CPlayer *pPlayer = CGame::GetPlayer();
	D3DXVECTOR3 ShotPos = D3DXVECTOR3(pPlayer->GetPos().x, pPlayer->GetPos().y - 50.0f, 0.0f);

	// 頂点情報を設定
	VERTEX_2D *pVtx;

	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (0.0f <= pVtx[0].pos.y)
	{
		m_Pos += m_move;
	}

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3((ShotPos.x - m_Size.x / 2), m_Pos.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3((ShotPos.x + m_Size.x / 2), m_Pos.y , 0.0f);
	pVtx[2].pos = D3DXVECTOR3((ShotPos.x - m_Size.x / 2), ShotPos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3((ShotPos.x + m_Size.x / 2), ShotPos.y, 0.0f);

	// ポリゴンの座標
	m_PolygonPos = D3DXVECTOR3((pVtx[0].pos.x + pVtx[1].pos.x) / 2, (pVtx[0].pos.y + pVtx[2].pos.y) / 2, 0.0f);

	// ポリゴンのサイズ設定
	m_PolygonSize = D3DXVECTOR3(m_Size.x, (ShotPos.y - pVtx[0].pos.y) / 2, 0.0f);

	// 先端の座標
	if (pVtx[0].pos.y <= ShotPos.y)
	{
		m_PolygonTop = D3DXVECTOR3(m_PolygonPos.x, pVtx[0].pos.y + 50.0f, 0.0f);
	}
	else
	{
		m_PolygonTop = D3DXVECTOR3(ShotPos.x, ShotPos.y + 50.0f, 0.0f);
	
	}

	// レーザー光生成
	FlashCreate(D3DXVECTOR3(ShotPos), CFlash::FLASH_TYPE_SHOT);

	// レーザー光生成
	FlashCreate(D3DXVECTOR3(m_PolygonTop), CFlash::FLASH_TYPE_TOP);

	// // 頂点バッファをアンロック
	pVtxBuff->Unlock();
}

//=============================================================================
// レーザーが消える処理
//=============================================================================
void CLaser::DisappearLaser(void)
{
	// レンダラーの情報を受け取る
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

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

				if (pScene2D != NULL)
				{
					// ターゲットの情報確保
					CScene::TYPE type = pScene->GetType();

					if (type == TYPE_PLAYER)
					{
						D3DXVECTOR3 ShotPos = pScene2D->GetPos();

						// 頂点情報を設定
						VERTEX_2D *pVtx;

						LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

						// 頂点バッファをロックし、頂点情報へのポインタを取得
						pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

						if (0.0f <= pVtx[0].pos.y)
						{
							m_Pos += m_move;
						}

						// サイズを小さくする
						m_Size.x -= 2.5f;

						// 頂点座標の設定
						pVtx[0].pos = D3DXVECTOR3((ShotPos.x - m_Size.x / 2), m_Pos.y, 0.0f);
						pVtx[1].pos = D3DXVECTOR3((ShotPos.x + m_Size.x / 2), m_Pos.y, 0.0f);
						pVtx[2].pos = D3DXVECTOR3((ShotPos.x - m_Size.x / 2), ShotPos.y, 0.0f);
						pVtx[3].pos = D3DXVECTOR3((ShotPos.x + m_Size.x / 2), ShotPos.y, 0.0f);

						// ポリゴンの座標
						m_PolygonPos = D3DXVECTOR3((pVtx[0].pos.x + pVtx[1].pos.x) / 2, (pVtx[0].pos.y + pVtx[2].pos.y) / 2, 0.0f);
						m_PolygonSize = D3DXVECTOR3(m_Size.x, (ShotPos.y - pVtx[0].pos.y) / 2, 0.0f);

						// 先端の座標
						if (pVtx[0].pos.y <= ShotPos.y)
						{
							m_PolygonTop = D3DXVECTOR3(m_PolygonPos.x, pVtx[0].pos.y + 50.0f, 0.0f);
						}
						else
						{
							m_PolygonTop = D3DXVECTOR3(ShotPos.x, ShotPos.y + 50.0f, 0.0f);

						}

						// レーザー光生成
						FlashCreate(D3DXVECTOR3(ShotPos), CFlash::FLASH_TYPE_SHOT);

						// レーザー光生成
						FlashCreate(D3DXVECTOR3(m_PolygonTop), CFlash::FLASH_TYPE_TOP);

						// // 頂点バッファをアンロック
						pVtxBuff->Unlock();

						if (m_Size.x <= 0)
						{
							m_Size.x = 0.0f;
							return;
						}
					}
				}
				pScene = pSceneNext;
			}
		}
	}
}

//=============================================================================
// 当たり判定
//=============================================================================
bool CLaser::Collision(void)
{
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

				if (pScene2D != NULL)
				{
					// ターゲットの情報確保
					CScene::TYPE type = pScene->GetType();

					// エネミーの時
					if (type == TYPE_ENEMY)
					{
						// エネミーの情報取得
						CEnemy *pEnemy = (CEnemy*)pScene2D;
						D3DXVECTOR3 TargetPos = pEnemy->GetPos();
						D3DXVECTOR3 TargetSize = pEnemy->GetSize();

						// 頂点情報を設定
						VERTEX_2D *pVtx;

						LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

						// 頂点バッファをロックし、頂点情報へのポインタを取得
						pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

						if (TargetPos.x - TargetSize.x / 2 < m_PolygonPos.x + m_PolygonSize.x / 2 &&
							TargetPos.x + TargetSize.x / 2 > m_PolygonPos.x - m_PolygonSize.x / 2 &&
							TargetPos.y - TargetSize.y / 2 < (m_PolygonPos.y + m_PolygonSize.y / 2) + 50.0f &&
							TargetPos.y + TargetSize.y / 2 > (m_PolygonPos.y - m_PolygonSize.y / 2) - 50.0f)
						{
							// プエネミーにダメージを与える
							pEnemy->HitDamage(LASER_DAMAGE);
						}

						// // 頂点バッファをアンロック
						pVtxBuff->Unlock();

					}
					else if (type == TYPE_BOSS)
					{
						// ボスの情報取得
						CBoss *pBoss = (CBoss*)pScene2D;
						D3DXVECTOR3 TargetPos = pBoss->GetPos();
						D3DXVECTOR3 TargetSize = pBoss->GetSize();

						// 頂点情報を設定
						VERTEX_2D *pVtx;

						LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

						// 頂点バッファをロックし、頂点情報へのポインタを取得
						pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

						if (TargetPos.x - TargetSize.x / 2 < m_PolygonPos.x + m_PolygonSize.x / 2 &&
							TargetPos.x + TargetSize.x / 2 > m_PolygonPos.x - m_PolygonSize.x / 2 &&
							TargetPos.y + TargetSize.y / 2 > m_PolygonTop.y - 50.0f)
						{
							// 当たった場所に座標を戻す
							m_Pos.y = TargetPos.y + TargetSize.y / 2;
							m_Pos.y -= m_move.y;

							// ボスにダメージを与える
							pBoss->HitBossDamage(LASER_DAMAGE);

						}

						// // 頂点バッファをアンロック
						pVtxBuff->Unlock();

					}
					else if (type == TYPE_BULLET)
					{
						// 弾の情報取得
						CBullet *pBullet = (CBullet*)pScene2D;
						D3DXVECTOR3 TargetPos = pBullet->GetPos();
						D3DXVECTOR3 TargetSize = pBullet->GetSize();

						// 頂点情報を設定
						VERTEX_2D *pVtx;

						LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

						// 頂点バッファをロックし、頂点情報へのポインタを取得
						pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

						if (TargetPos.x - TargetSize.x / 2 < m_PolygonPos.x + m_PolygonSize.x / 2 &&
							TargetPos.x + TargetSize.x / 2 > m_PolygonPos.x - m_PolygonSize.x / 2 &&
							TargetPos.y - TargetSize.y / 2 < (m_PolygonPos.y + m_PolygonSize.y / 2) + 100.0f &&
							TargetPos.y + TargetSize.y / 2 > (m_PolygonPos.y - m_PolygonSize.y / 2) - 50.0f)
						{
							// 当たり判定処理
							{
								// 弾を消す
								pBullet->Uninit();

							}
						}
					}
				}
				pScene = pSceneNext;
			}
		}

	}
	return false;
}

//=============================================================================
// レーザー光の生成
//=============================================================================
void CLaser::FlashCreate(D3DXVECTOR3 pos, CFlash::FLASH_TYPE Ftype)
{
	// 色の種類
	switch (m_Ctype)
	{
		// 白の時
	case LASER_COLOR_WHITE:

			for (int nCntFlash = 0; nCntFlash < FLASH_NUM; nCntFlash++)
			{
				// フラッシュ生成
				CFlash::Create(pos, D3DXVECTOR3(FLASH_SIZE_X, FLASH_SIZE_Y, 0.0f), TYPE_EXPLOSION, CFlash::FLASH_COLOR_WHITE, Ftype, 5);
			}
		break;

		// 黒いとき
	case LASER_COLOR_BLACK:

			for (int nCntFlash = 0; nCntFlash < FLASH_NUM; nCntFlash++)
			{
				// フラッシュ生成
				CFlash::Create(pos, D3DXVECTOR3(FLASH_SIZE_X, FLASH_SIZE_Y, 0.0f), 
					TYPE_EXPLOSION, CFlash::FLASH_COLOR_BLACK, Ftype, 5);
		}
	}
}

//=============================================================================
// サイズの情報
//=============================================================================
D3DXVECTOR3 CLaser::GetSize(void)
{
	return m_Size;
}

//=============================================================================
// 先端の情報
//=============================================================================
D3DXVECTOR3 CLaser::GetTop(void)
{
	return m_PolygonTop;
}