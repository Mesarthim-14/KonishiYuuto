#ifndef _ICON_H_
#define _ICON_H_
//=============================================================================
//
// アイコンクラスヘッダー	[icon.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "scene2d.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define ICON_SIZE_X			(50.0f)			// サイズ
#define ICON_SIZE_Y			(50.0f)			// サイズ

//=============================================================================
// 前方宣言
//=============================================================================
class CScene2D;

//=============================================================================
// アイコンクラス
//=============================================================================
class CIcon : public CScene2D
{
public:
	CIcon();			// コンストラクタ
	~CIcon();			// デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);				// 初期化処理
	void Uninit(void);														// 終了処理
	void Update(void);														// 更新処理
	void Draw(void);														// 描画処理

	static CIcon * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);	// ポリゴン生成
	static HRESULT Load(void);												// テクスチャロード
	static void UnLoad(void);												// テクスチャアンロード
	void ScaleUp(void);														// 拡大の処理
	void ScaleDown(void);													// 縮小の処理
	void FlashPolygon(void);												// ポリゴンの点滅
	bool GetEndIcon(void);													// アイコンの終了フラグ情報
private:
	D3DXVECTOR3 m_Pos;												// 座標
	D3DXVECTOR3 m_move;												// 移動量
	D3DXVECTOR3 m_size;												// サイズ
	float m_fScale;													// 縮小用変数
	float m_fScaleNum;												// 縮小量
	int m_nFlashFlame;												// 点滅のフレーム
	int m_nSubNumber;												// カラー減算
	int m_nSubNum;													// カラーの減算量
	int m_nIconCounter;												// アイコンの時間
	bool m_bEndIcon;												// アイコンの終了フラグ
};

#endif