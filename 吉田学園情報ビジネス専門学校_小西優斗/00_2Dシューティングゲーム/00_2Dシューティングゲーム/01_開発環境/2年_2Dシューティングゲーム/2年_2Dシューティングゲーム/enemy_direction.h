#ifndef _ENEMY_DIRECTION_H_
#define _ENEMY_DIRECTION_H_
//=============================================================================
//
// 方向転換の敵エネミークラスヘッダー [enemy_direction.h]
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
class CEnemyDirection : public CEnemy
{
public:
	CEnemyDirection(TYPE Priority = TYPE_ENEMY);	// コンストラクタ
	~CEnemyDirection();							// デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);		// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理

	void MoveUpdate(void);										// 斜め移動の処理
	void BulletUpdate(void);									// 弾の更新処理

	static CEnemyDirection * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type,
		COLOR_TYPE Ctype, ENEMY_TYPE Etype, int nNumber);				// エネミー生成
private:
	int m_nDirection;			// 左右の番号
};

#endif