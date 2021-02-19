#ifndef _HPBAR_H_
#define _HPBAR_H_
//=========================================================
//
// 体力バークラスヘッダー	[hpbar.h]
// Author : Konishi Yuuto
//
//=========================================================

//=========================================================
// インクルード
//=========================================================
#include "scene.h"

//=========================================================
// マクロ定義
//=========================================================
#define BAR_SIZE_X			(500)		// サイズ
#define BAR_SIZE_Y			(20)		// サイズ

//=========================================================
// ヒットポイントバークラス
//=========================================================
class CHpbar : public CScene
{
public:
	CHpbar(TYPE Priority = TYPE_UI);	// コンストラクタ
	~CHpbar();							// デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);	// 初期化処理
	void Uninit(void);											// 終了処理
	void Update(void);											// 更新処理
	void Draw(void);											// 描画処理

	static CHpbar *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, 
		TYPE type, int nLife);									// ポリゴン生成

	void AddDamage(int nNumber);								// ダメージ処理
	void SetHp(int nNumber);									// 体力の回復
private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;							// バッファのポインタ
	D3DXVECTOR3 m_Pos;											// 座標
	int m_nMaxLife;												// 体力
	int m_nLife;												// 体力
};
#endif