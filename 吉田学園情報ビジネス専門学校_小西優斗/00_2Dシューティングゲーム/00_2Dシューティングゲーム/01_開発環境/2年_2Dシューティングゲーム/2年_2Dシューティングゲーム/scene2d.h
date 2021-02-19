#ifndef _SCENE2D_H_
#define _SCENE2D_H_
//=============================================================================
//
// シーン2Dクラスヘッダー [scene2d.h]
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
#define PLAYER_SIZE_X	(85)	// 自機のX座標
#define PLAYER_SIZE_Y	(85)	// 自機のY座標
#define MAX_POLYGON		(2048)	// ポリゴンの最大数

//=============================================================================
// 前置宣言
//=============================================================================
class CScene;

//=============================================================================
// レンダラークラス
//=============================================================================
class CScene2D : public CScene
{
public:

	CScene2D(TYPE Priority = TYPE_NONE);	// コンストラクタ
	~CScene2D();							// デストラクタ

	// メンバ関数
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);	// 初期化処理
	virtual void Uninit(void);											// 終了処理
	virtual void Update(void);											// 更新処理
	virtual void Draw(void);											// 描画処理

	void BindTexture(const LPDIRECT3DTEXTURE9 pTexture);						// テクスチャの設定
	void InitAnimation(int nCounterAnim, int nPatternAnim, int nLoop);	// アニメーション情報初期化
	void InitScroll(int nSpeed, float fDivision);						// 画像スクロールの設定
	void UpdateAnimation(void);											// アニメーションの更新
	void UpdateScroll(void);											// 画像スクロールの更新
	bool ScaleUp(D3DXVECTOR3 pos);										// ポリゴン拡大
	bool ScaleDown(D3DXVECTOR3 pos, int nLife);							// ポリゴン縮小
	bool TransParency(D3DXVECTOR3 pos, int nLife);						// 透明度の変化

	// Set関数
	void SetPosition(D3DXVECTOR3 pos);									// 位置を常に更新
	void SetPos(const D3DXVECTOR3 &pos);
	void SetMove(const D3DXVECTOR3 &move);										// 移動量
	void SetSize(const D3DXVECTOR3 &size);										// サイズを設定
	void SetScaleSize(D3DXVECTOR3 size);								// 拡大サイズを設定

	// Get関数
	D3DXVECTOR3 GetPos(void);											// 位置情報を返す
	D3DXVECTOR3 GetMove(void);
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void);							// バッファの情報
	D3DXVECTOR3 GetSize(void);											// サイズの情報

private:
	D3DXVECTOR3 m_pos;						// 頂点座標
	D3DXVECTOR3 m_move;						// 移動量
	D3DXVECTOR3 m_size;						// ポリゴンのサイズ
	LPDIRECT3DTEXTURE9 m_pTexture;			// テクスチャのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// 頂点バッファのポインタ
	int m_nCountAnim;						// アニメーションテクスチャ
	int m_nCountAnimPattern;				// アニメーションのパターン
	int m_nCounterAnim;						// アニメーションのカウンター
	int m_nPatternAnim;						// アニメーションのパターン数
	int m_nSpeedTexture;					// テクスチャの移動速度
	int m_nTransParencyNum;					// 透明度
	int m_nLoop;							// ループするかどうか
	float m_fDivisionCounter;				// スクロールのカウンター
	float m_fDivisionBaseNum;				// スクロールの移動量
	float m_fScaleUp;						// 拡大量
	float m_fScaleDown;						// 縮小量
	float m_nEffectCntFlame;				// エフェクトのカウント
};

#endif