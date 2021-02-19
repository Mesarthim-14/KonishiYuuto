#ifndef _ENEMY_NORMAL_H_
#define _ENEMY_NORMAL_H_
//=============================================================================
//
// 通常エネミークラスヘッダー [enemy_normal.h]
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
class CEnemyNormal : public CEnemy
{
public:
	CEnemyNormal(TYPE Priority = TYPE_ENEMY);	// コンストラクタ
	~CEnemyNormal();							// デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);		// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理

	void MoveUpdate(void);										// 斜め移動の処理
	void BulletUpdate(void);									// 弾の更新処理

	static CEnemyNormal * Create(
		D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size,
		TYPE type, COLOR_TYPE Ctype, ENEMY_TYPE Etype);				// エネミー生成
private:

};

#endif