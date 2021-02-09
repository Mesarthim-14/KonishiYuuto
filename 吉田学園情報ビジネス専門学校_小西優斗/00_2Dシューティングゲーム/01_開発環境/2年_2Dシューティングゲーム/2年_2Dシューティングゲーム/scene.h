#ifndef _SCENE_H_
#define _SCENE_H_
//=============================================================================
//
// シーンヘッダー [scene.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "main.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_OBJECT		(2048)
#define NUM_VERTEX		(4)		// 頂点の数
#define NUM_POLYGON		(2)		

//=============================================================================
// 前方宣言
//=============================================================================
class CScene2D;

//=============================================================================
// オブジェクトクラス
//=============================================================================
class CScene
{
public:

	//=========================================
	// ポリゴンのタイプ
	//=========================================
	typedef enum
	{
		TYPE_NONE = 0,			// 初期値
		TYPE_BG,				// 背景
		TYPE_SHIELD,			// シールド
		TYPE_LIGHT,				// ライト
		TYPE_ENEMY,				// エネミー
		TYPE_LASER,				// レーザー
		TYPE_EFFECT,			// エフェクト
		TYPE_PLAYER,			// プレイヤー
		TYPE_BULLET,			// 弾
		TYPE_BOSS,				// ボス
		TYPE_SURROUNDINGS,		// ボスの取り巻き
		TYPE_EXPLOSION,			// 爆発
		TYPE_UI,				// 画面の仕切り
		TYPE_BOMB,					// ボム
		TYPE_SCORE,				// スコア
		TYPE_WARNING,			// 警告
		TYPE_FADE,				// フェード
		TYPE_MAX
	}TYPE;

	CScene(TYPE Priority = TYPE_NONE);	// コンストラクタ
	virtual ~CScene();					// デストラクタ

	// メンバ関数
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type) = 0;	// 初期化処理
	virtual void Uninit(void) = 0;											// 終了処理
	virtual void Update(void) = 0;											// 更新処理
	virtual void Draw(void) = 0;											// 描画処理

	static void UpdateAll(void);			// 全てのオブジェクトを更新
	static void DrawAll(void);				// 全てのオブジェクトを描画
	static void ReleaseAll(void);			// 全てのオブジェクトを開放する
	CScene *GetTop(int nCount);				// シーンの情報受け取り
	CScene *GetNext(void);					// 次の情報を受け取る
	void SetType(TYPE type);				// シーンの情報設定
	TYPE GetType(void);						// シーン情報を返す
	static int GetEnemyNum(void);
	static void CountEnemy();
	void DeathRelease(void);

protected:
	void Release(void);						// オブジェクトを開放

private:
	static CScene *m_apScene[MAX_OBJECT];	// シーンオブジェクトの情報
	static int m_nNumEnemy;
	static int m_nNumAll;					// 使用してる数
	TYPE m_type;							// オブジェクトのタイプ
	int m_nID;								// オブジェクトの番号

	static CScene *m_pTop[TYPE_MAX];		// 戦闘のオブジェクトへのポインタ
	static CScene *m_pCur[TYPE_MAX];		// 現在のオブジェクトへのポインタ
	CScene *m_pPrev;						// 前のオブジェクトへのポインタ
	CScene *m_pNext;						// 次のオブジェクトへのポインタ
	bool m_bDeath;							// 死亡フラグ
};

#endif