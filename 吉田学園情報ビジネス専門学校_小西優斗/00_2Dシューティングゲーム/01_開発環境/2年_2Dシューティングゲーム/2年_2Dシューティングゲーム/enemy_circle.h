#ifndef _ENEMY_CIRCLE_H_
#define _ENEMY_CIRCLE_H_
//=============================================================================
//
// サークルエネミークラスヘッダー [enemy_circle.h]
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
class CEnemyCircle : public CEnemy
{
public:
	CEnemyCircle(TYPE Priority = TYPE_ENEMY);	// コンストラクタ
	~CEnemyCircle();							// デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);		// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理

	void MoveUpdate(void);										// 斜め移動の処理
	void BulletUpdate(void);									// 弾の更新処理

	static CEnemyCircle * Create(
		D3DXVECTOR3 pos, D3DXVECTOR3 size,
		TYPE type, COLOR_TYPE Ctype, ENEMY_TYPE Etype, float fRadius, float fTheta);				// エネミー生成

	void SetRotation(float fRadius, float fTheta);
private:
	D3DXVECTOR3 m_center;					// 画面の中心
	float m_fRadius;						// 半径
	float m_fAddRadius;						// 半径加算量
	float m_fTheta;							// 角度
	float m_fOmega;							// 角度加算量
	float m_fRadiusNum;						// 半径の値

};

#endif