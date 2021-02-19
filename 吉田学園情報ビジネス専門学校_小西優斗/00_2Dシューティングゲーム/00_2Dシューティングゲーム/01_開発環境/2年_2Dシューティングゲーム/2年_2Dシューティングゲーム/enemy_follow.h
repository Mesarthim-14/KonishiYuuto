#ifndef _ENEMY_FOLLOW_H_
#define _ENEMY_FOLLOW_H_
//=============================================================================
//
// 追従エネミークラスヘッダー [enemy_follow.h]
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
class CEnemyFollow : public CEnemy
{
public:
	CEnemyFollow(TYPE Priority = TYPE_ENEMY);	// コンストラクタ
	~CEnemyFollow();							// デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);	// 初期化処理
	void Uninit(void);											// 終了処理
	void Update(void);											// 更新処理
	void Draw(void);											// 描画処理

	void MoveUpdate(void);										// 斜め移動の処理
	void BulletUpdate(void);									// 弾の更新処理
	void Appearance(void);

	static CEnemyFollow * Create(D3DXVECTOR3 pos,
		D3DXVECTOR3 size, TYPE type, COLOR_TYPE Ctype, ENEMY_TYPE Etype);				// エネミー生成
private:
	int m_nFollowCounter;	// 追従までの時間
	int m_nSubNum;			// 加算値
	int m_nSubNumber;		// 透明度の値
	bool m_bFlashFlag;		// 点滅フラグ
	bool m_bFollowFlag;		// 追従のフラグ
};

#endif