#ifndef _RESULTBG_H_
#define _RESULTBG_H_
//=============================================================================
//
// リザルト背景クラスヘッダー [resultbg.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "scene2d.h"

//=============================================================================
// タイトルBgクラス
//=============================================================================
class CResultBg : public CScene2D
{
public:
	CResultBg();			// コンストラクタ
	~CResultBg();			// デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);	// 初期化処理
	void Uninit(void);											// 終了処理
	void Update(void);											// 更新処理
	void Draw(void);											// 描画処理

	static CResultBg * Create(D3DXVECTOR3 pos,					// ポリゴン生成
		D3DXVECTOR3 size, TYPE type);

private:
	D3DXVECTOR3 m_Pos;												// 座標
	D3DXVECTOR3 m_move;												// 移動量
};

#endif