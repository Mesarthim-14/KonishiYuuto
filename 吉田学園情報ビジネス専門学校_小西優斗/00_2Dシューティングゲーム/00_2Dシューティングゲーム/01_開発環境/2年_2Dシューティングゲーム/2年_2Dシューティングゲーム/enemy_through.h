#ifndef _ENEMY_THROUGH_H_
#define _ENEMY_THROUGH_H_
//=============================================================================
//
// 真っすぐ弾を打つエネミークラスヘッダー [enemy_through.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "enemy.h"

//=============================================================================
// エネミークラス
//=============================================================================
class CEnemyThrough : public CEnemy
{
public:
	CEnemyThrough(TYPE Priority = TYPE_ENEMY);	// コンストラクタ
	~CEnemyThrough();							// デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);		// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理

	void MoveUpdate(void);											// 斜め移動の処理
	void BulletUpdate(void);										// 弾の更新

	static CEnemyThrough * Create(
		D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size,
		TYPE type, COLOR_TYPE Ctype, ENEMY_TYPE Etype);				// エネミー生成

private:
	int m_nStopCounter;		// 止まっている時間のカウント
	int m_nContinueInter;	// 弾の出る間隔
	int m_nBulletNum;		// 弾のカウンター
	bool m_bTwo_Sides;		// 真っすぐ弾を打つ敵のフラグ
};

#endif