#ifndef _SCORE_H_
#define _SCORE_H_
//=============================================================================
//
// スコアクラスヘッダー [score.h]
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
#define MAX_NUMBER		(8)
#define NUMBER_SIZE_X	(15.0f)			// スコアの縦のサイズ
#define NUMBER_SIZE_Y	(30.0f)			// スコアの横のサイズ

//=============================================================================
// 前置宣言
//=============================================================================
class CNumber;

//=============================================================================
// レンダラークラス
//=============================================================================
class CScore : public CScene
{
public:
	CScore(TYPE Priority = TYPE_SCORE);				// コンストラクタ
	~CScore();				// デストラクタ

	// メンバ関数
	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);	// 初期化処理
	void Uninit(void);											// 終了処理
	void Update(void);											// 更新処理
	void Draw(void);											// 描画処理

	void SetScore(int nScore);									// スコアの設定
	int GetScore(void);											// スコアの情報

private:
	CNumber *m_apNumber[MAX_NUMBER];		// 桁数分
	int m_nScore;							// スコア
};

#endif