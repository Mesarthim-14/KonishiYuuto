#ifndef _ENEMY_SNAKE_H_
#define _ENEMY_SNAKE_H_
//=============================================================================
//
// スネークエネミークラスヘッダー [enemy_snake.h]
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
class CEnemySnake : public CEnemy
{
public:
	CEnemySnake(TYPE Priority = TYPE_ENEMY);	// コンストラクタ
	~CEnemySnake();							// デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);	// 初期化処理
	void Uninit(void);											// 終了処理
	void Update(void);											// 更新処理
	void Draw(void);											// 描画処理

	void MoveUpdate(void);										// 斜め移動の処理
	void BulletUpdate(void);									// 弾の更新処理

	static CEnemySnake * Create(
		D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size,
		TYPE type, COLOR_TYPE Ctype, ENEMY_TYPE Etype);				// エネミー生成
private:
	int m_nSwitchCounter;			// スイッチのカウンター
	bool m_bSnakeSwitch;			// スイッチのフラグ
};

#endif