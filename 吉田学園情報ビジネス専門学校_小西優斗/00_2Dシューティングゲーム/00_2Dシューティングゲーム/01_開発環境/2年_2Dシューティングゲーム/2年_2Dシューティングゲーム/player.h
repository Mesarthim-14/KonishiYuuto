#ifndef _PLAYER_H_
#define _PLAYER_H_
//=============================================================================
//
// プレイヤークラスヘッダー [player.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "character.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define DECISION_PLAYER_SIZE_X	(15)		// 当たり判定
#define DECISION_PLAYER_SIZE_Y	(15)		// 当たり判定
#define PLAYER_REMAIN_NUM		(2)			// 残機
#define PLAYER_SHOT_POS_X		(11.0f)		// 弾の出現位置
#define PLAYER_SHOT_POS_Y		(30.0f)		// 弾の出現位置

//=============================================================================
// 前方宣言
//=============================================================================
class CShield;
class CGage;
class CLaser;
class CBombUi;

//=============================================================================
// プレイヤークラス
//=============================================================================
class CPlayer : public CCharacter
{
public:
	CPlayer();			// コンストラクタ
	~CPlayer();			// デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);				// 初期化処理
	void Uninit(void);														// 終了処理
	void Update(void);														// 更新処理
	void Draw(void);														// 描画処理

	// static関数
	static CPlayer * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);	// ポリゴン生成
	
	// メンバ関数
	void PlayerControl(void);												// プレイヤー制御
	void Resurrection(void);												// 復活
	void UpdateState(void);													// プレイヤー状態更新
	bool BombCollision(void);												// ボムの当たり判定
	void Death(void);														// 死んだときの処理

	// Get関数
	bool GetUseLaser(void);													// レーザーの情報
	bool GetShildInfo(void);												// シールドの情報
	CGage *GetGage(void);													// レーザーゲージ
	CLaser *GetLaser(void);													// レーザーの情報

private:
	int m_StateCount;						// プレイヤーの状態カウンター
	int m_BulletState;						// バレット間隔のカウンター
	int m_nStock;							// ストック
	int m_nResurrectionCnt;					// 復活フレーム
	int m_nLaserFlame;						// レーザーのカウント
	int m_nLaserCounter;					// レーザーの切り替わりカウンター
	int m_nBombFlame;						// ボムの当たり判定フレーム
	int m_nBombNum;							// ボムに当たった敵のナンバー
	int m_nBombCount;						// ボムの数
	bool m_bShildInfo;						// シールドの情報
	bool m_bShildScaleInfo;					// シールドの拡大状況
	bool m_bPlayerDraw;						// プレイヤーの表示
	bool m_bUseLaser;						// レーザーを使っているか
	bool m_bPressInfo;						// 押したときの情報
	bool m_bBombUse;						// ボムを使ったとき
	CShield *m_pShield;						// シールドのポインタ
	CGage *m_pGage;							// ゲージのポインタ
	CLaser *m_pLaser;						// レーザーのポインタ
	CBombUi *m_pBombUi;						// ボムのUI
	TYPE m_BombType;						// ボムタイプ
};

#endif