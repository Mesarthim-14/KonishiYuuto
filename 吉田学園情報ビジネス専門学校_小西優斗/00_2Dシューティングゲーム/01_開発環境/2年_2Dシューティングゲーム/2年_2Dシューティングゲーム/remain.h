#ifndef _REMAIN_H_
#define _REMAIN_H_
//=============================================================================
//
// 残機クラスヘッダー [remain.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "scene.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define REMAIN_SIZE_X	(15.0f)			// スコアの縦のサイズ
#define REMAIN_SIZE_Y	(30.0f)			// スコアの横のサイズ

//=============================================================================
// 前置宣言
//=============================================================================
class CNumber;

//=============================================================================
// レンダラークラス
//=============================================================================
class CRemain : public CScene
{
public:
	CRemain(TYPE Priority = TYPE_SCORE);			// コンストラクタ
	~CRemain();			// デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);		// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理

	void SetRemain(int nNumber);									// 残機設定

private:
	CNumber *m_pRemain;		// 桁数分
	int m_nRemain;			// スコア
};

#endif