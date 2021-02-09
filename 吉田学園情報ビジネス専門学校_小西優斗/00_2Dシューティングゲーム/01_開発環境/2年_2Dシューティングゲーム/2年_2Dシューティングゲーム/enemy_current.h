#ifndef _ENEMY_CURRENT_H_
#define _ENEMY_CURRENT_H_
//=============================================================================
//
// 自機追従弾を打つエネミークラスヘッダー [enemy_current.h]
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
class CEnemyCurrent : public CEnemy
{
public:
	CEnemyCurrent(TYPE Priority = TYPE_ENEMY);	// コンストラクタ
	~CEnemyCurrent();							// デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);		// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理

	void MoveUpdate(void);											// 斜め移動の処理
	void BulletUpdate(void);										// 弾の更新
	
	static CEnemyCurrent * Create(
		D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size,
		TYPE type, COLOR_TYPE Ctype, ENEMY_TYPE Etype);				// エネミー生成
private:
	int m_nContinueInter;		// 弾の出る間隔
	int m_nBulletNum;			// 弾のカウンター
};

#endif