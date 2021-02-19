#ifndef _MISSILE_H_
#define _MISSILE_H_
//=============================================================================
//
// ミサイル処理 [missile.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
//インクルードファイル
//=============================================================================
#include "scene.h"

//=============================================================================
//マクロ定義
//=============================================================================
#define MAX_MODEL_MISSILE_PARTS (2)			// パーツ数
#define MISSILE_SPPED			(45)		// ミサイルの速度
#define MISSILE_SIZE_X			(3.0f)		// サイズ
#define MISSILE_SIZE_Y			(3.0f)		// サイズ
#define MISSILE_SIZE_Z			(3.0f)		// サイズ

//=============================================================================
//前方宣言
//=============================================================================
class CModelAnime;
class CPlayer;

//=============================================================================
//ミサイルクラス
//=============================================================================
class CMissile : public CScene
{
public:

	// モデルファイル情報の構造体
	typedef struct
	{
		char xFileName[1024];	// ファイルネーム
		D3DXVECTOR3 offsetPos;	// 位置のオフセット情報
		D3DXVECTOR3 offsetRot;	// 向きのオフセット情報
		int nParent;			// 親情報
	}MODELFILLEs;

	// 弾の使用者判別用の列挙型
	typedef enum
	{
		MISSILE_USER_NONE = -1,	// 初期値
		MISSILE_USER_PL1,		// PL1
		MISSILE_USER_PL2,		// PL2
		MISSILE_USER_MAX		// 最大数
	}MISSILE_USER;

	CMissile(int nPriority = PRIORITY_0);	// コンストラクタ
	~CMissile();							// デストラクタ

	static CMissile *Create(const D3DXVECTOR3 pos, 
		const D3DXVECTOR3 size,const MISSILE_USER user, float fSpeed);	// インスタンス生成

	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size);		// 初期化処理
	void Uninit(void);													// 終了処理
	void Update(void);													// 更新処理
	void Draw(void);													// 描画処理
	void SetRot(D3DXVECTOR3 rot);										// 角度の設定
	void SetMove(D3DXVECTOR3 move);										// 移動の処理
	HRESULT ReadFile(void);												// ファイル読み込み
	bool Collision(void);												// 当たり判定
	D3DXVECTOR3 VectorMath(D3DXVECTOR3 TargetPos,						// 追従処理
		float fSpeed);
	bool Follow(void);													// 追従
private:
	D3DXVECTOR3 m_pos;										// 位置
	D3DXVECTOR3 m_rot;										// 向き
	D3DXVECTOR3 m_move;										// 移動量
	D3DXVECTOR3 m_size;										// サイズ
	int m_nLife;											// ライフ
	CModelAnime *m_apModelAnime[MAX_MODEL_MISSILE_PARTS];	// 階層モデルクラスのポインタ変数
	int m_nCounter;											// 追従カウンター
	D3DXMATRIX m_mtxWorld;									// ワールドマトリックス
	MISSILE_USER m_user;									// 使用者
	CPlayer *m_pTargetPL;									//敵プレイヤーのポインタ
	int m_nDamage;											//ダメージ数
	float m_fSpeed;											// 速さ
	float m_fHeight;										// 高さ
	bool m_bFollow;											// 追従用のフラグ
};

#endif 