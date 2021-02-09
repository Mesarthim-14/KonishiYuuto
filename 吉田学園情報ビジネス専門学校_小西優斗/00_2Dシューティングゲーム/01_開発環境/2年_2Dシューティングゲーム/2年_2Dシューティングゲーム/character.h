#ifndef _CHARACTER_H_
#define _CHARACTER_H_
//=============================================================================
//
// キャラクター処理  [character.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"
#include "scene2d.h"

//=============================================================================
// キャラクターのクラス
//=============================================================================
class CCharacter : public CScene2D
{
public:
	typedef enum
	{
		// キャラクターの状態
		STATE_NONE = 0,		// 初期値
		STATE_NORMAL,		// 通常状態
		STATE_REVIVE,		// 復活時
		STATE_LASER,		// レーザー発射時
		STATE_DAMAGE,		// ダメージ状態
		STATE_MAX
	}STATE;

	CCharacter(TYPE Priority = TYPE_PLAYER);	// コンストラクタ
	virtual ~CCharacter();						// デストラクタ

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);	// 初期化処理
	virtual void Uninit();												// 終了処理
	virtual void Update();												// 更新処理
	virtual void Draw();												// 描画処理

	// Set関数
	void SetLife(int nLife);					// ライフの設定
	void HitDamage(int nLife);					// ダメージ処理
	void SetState(STATE state);					// 状態の設定

	// Get関数
	int GetLife(void) { return m_nLife; }		// ライフの情報
	STATE GetState(void) { return m_state; }	// 状態の情報

	// 純粋仮想関数
	virtual void Death(void) = 0;				// 死んだときの処理
	virtual void UpdateState(void) = 0;			// 状態の更新処理

private:
	STATE m_state;							// キャラクターの状態
	int m_nLife;							// 体力
	int m_nAttack;							// 攻撃力
	int m_nSpeed;							// 移動量
};
#endif