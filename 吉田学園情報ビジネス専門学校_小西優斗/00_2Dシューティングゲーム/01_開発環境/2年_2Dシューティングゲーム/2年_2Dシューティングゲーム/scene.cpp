//=============================================================================
//
// ポリゴンの設定 [scene.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "scene.h"
#include "renderer.h"
#include "scene2d.h"

//=============================================================================
// static初期化
//=============================================================================
CScene *CScene::m_apScene[MAX_OBJECT] = {};
CScene *CScene::m_pTop[TYPE_MAX] = {};
CScene *CScene::m_pCur[TYPE_MAX] = {};
int CScene::m_nNumAll = 0;
int CScene::m_nNumEnemy = 0;

//=============================================================================
// コンストラクタ
//=============================================================================
CScene::CScene(TYPE Priority)
{
	// メンバ変数初期化
	m_nID = 0;
	m_type = Priority;
	m_bDeath = false;

	// トップになにも入ってなかったら
	if (m_pTop[Priority] == NULL)
	{
		m_pTop[Priority] = this;
	}

	if (m_pCur[Priority] == NULL)
	{
		// 現在のやつ取得
		m_pCur[Priority] = this;
	}

	m_pCur[Priority]->m_pNext = this;

	// 前のやつ代入
	if (m_pCur[Priority] == this)
	{
		m_pPrev = NULL;
	}
	else
	{
		m_pPrev = m_pCur[Priority];
	}

	// 現在のやつ取得
	m_pCur[Priority] = this;
	m_pNext = NULL;
}

//=============================================================================
// デストラクタ
//=============================================================================
CScene::~CScene()
{

}

//=============================================================================
// 更新処理
//=============================================================================
void CScene::UpdateAll(void)
{
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		if (m_pTop[nCount] != NULL)
		{
			CScene *pScene = m_pTop[nCount];

			do
			{
				CScene *pSceneCur = pScene->m_pNext;

				// 死亡フラグがないとき
				if (pScene->m_bDeath != true)
				{
					// 更新処理
					pScene->Update();
				}
				pScene = pSceneCur;

			} while (pScene != NULL);
		}
	}

	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		if (m_pTop[nCount] != NULL)
		{
			CScene *pScene = m_pTop[nCount];

			do
			{
				CScene *pSceneCur = pScene->m_pNext;

				if (pScene->m_bDeath == true)
				{
					// 死亡フラグの処理
					pScene->DeathRelease();
				}

				pScene = pSceneCur;

			} while (pScene != NULL);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CScene::DrawAll(void)
{
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		if (m_pTop[nCount] != NULL)
		{
			CScene *pScene = m_pTop[nCount];
			do
			{
				CScene *pSceneCur = pScene->m_pNext;

				// 死亡フラグがない時
				if (pScene->m_bDeath != true)
				{
					pScene->Draw();
				}

				pScene = pSceneCur;

			} while (pScene != NULL);
		}
	}
}

//=============================================================================
// 全てのリリース
//=============================================================================
void CScene::ReleaseAll(void)
{
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		CScene *pScene = m_pTop[nCount];
		while (pScene != NULL)
		{
			CScene *pCurScene = pScene->m_pNext;

			if (nCount != TYPE_FADE)
			{
				pScene->Uninit();
			}

			pScene = pCurScene;
		}
	}

	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		if (m_pTop[nCount] != NULL)
		{
			CScene *pScene = m_pTop[nCount];
			do
			{
				CScene *pSceneCur = pScene->m_pNext;

				if (pScene->m_bDeath == true)
				{
					if (nCount != TYPE_FADE)
					{
						pScene->DeathRelease();
					}
				}

				pScene = pSceneCur;

			} while (pScene != NULL);
		}
	}

	// エネミーの総数をリセット
	m_nNumEnemy = 0;
}

//=============================================================================
// 単数リリース
//=============================================================================
void CScene::Release()
{
	// 死亡フラグ
	m_bDeath = true;
}

//=============================================================================
// タイプ設定
//=============================================================================
void CScene::SetType(TYPE type)
{
	m_type = type;
}

//=============================================================================
// エネミーのカウント関数
//=============================================================================
void CScene::CountEnemy()
{
	m_nNumEnemy++;
}

//=============================================================================
// 死亡フラグを持ったやつのリリース
//=============================================================================
void CScene::DeathRelease(void)
{
	// 位置をずらす
	for (int nCount = 0; nCount < TYPE_MAX; nCount++)
	{
		// 先頭だったら
		if (m_pTop[nCount] == this)
		{
			// 先頭を次のオブジェクトにする
			m_pTop[nCount] = m_pNext;
		}

		// 最後だったら
		if (m_pCur[nCount] == this)
		{
			// 最後をその前のオブジェクトにする
			m_pCur[nCount] = m_pPrev;
		}

		if (m_pPrev != NULL)
		{
			m_pPrev->m_pNext = m_pNext;
		}
		if (m_pNext != NULL)
		{
			m_pNext->m_pPrev = m_pPrev;
		}
	}

	// エネミーだったら減算
	if (m_type == TYPE_ENEMY)
	{
		m_nNumEnemy--;
	}

	delete this;
}

//=============================================================================
// エネミーの数情報
//=============================================================================
int CScene::GetEnemyNum(void)
{
	return m_nNumEnemy;
}

//=============================================================================
// 種類の情報
//=============================================================================
CScene::TYPE CScene::GetType(void)
{
	return m_type;
}

//=============================================================================
// シーン情報を返す
//=============================================================================
CScene * CScene::GetTop(int nCount)
{
	return m_pTop[nCount];
}

//=============================================================================
// 次のシーン情報
//=============================================================================
CScene * CScene::GetNext(void)
{
	return m_pNext;
}