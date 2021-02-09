#ifndef _ENEMY_H_
#define _ENEMY_H_
//=============================================================================
//
// エネミークラスヘッダー [enemy.h]
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
#define MAX_ENEMY				(256)			// 敵の最大数
#define ENEMY_SIZE_X			(50)			// エネミーのサイズ
#define ENEMY_SIZE_Y			(50)			// エネミーのサイズ
#define ENEMY_NORMAL_SIZE_X		(60)			// 敵の横幅
#define ENEMY_NORMAL_SIZE_Y		(60)			// 敵の縦幅
#define ENEMY_CURRENT_SIZE_X	(70)			// 自機取得弾を打つ敵の大きさ
#define ENEMY_CURRENT_SIZE_Y	(70)			// 自機取得弾を打つ敵の大きさ
#define ENEMY_SNAKE_SIZE_X		(40)			// ジグザグ敵
#define ENEMY_SNAKE_SIZE_Y		(40)			// ジグザグ敵
#define ENEMY_THROUGH_SIZE_X	(70)			// 真っすぐ弾を打つ敵のサイズ
#define ENEMY_THROUGH_SIZE_Y	(70)			// 真っすぐ弾を打つ敵のサイズ
#define ENEMY_DIRECTION_SIZE_X	(50)			// 方向転換する敵のサイズ
#define ENEMY_DIRECTION_SIZE_Y	(50)			// 方向転換する敵のサイズ
#define ENEMY_FOLLOW_SIZE_X		(50)			// 真っすぐ弾を打つ敵のサイズ
#define ENEMY_FOLLOW_SIZE_Y		(50)			// 真っすぐ弾を打つ敵のサイズ

#define INSIDE_ROTATION_RADIUS	(400)			// 回る敵の外側の半径
#define OUTSIDE_ROTATION_RADIUS	(325)			// 回る敵の内側の半径

#define CIRCLE_ENEMY_NUM		(5)				// サークル配置の敵の数
#define CIRCLE_ANGLE			(-45.0f)		// サークル配置の敵の角度
#define CIRCLE_MAX_ANGLE		(150)			// 敵の出現のサークルの角度
#define CIRCLE_DISTANCE			(210.0f)		// サークルの距離
#define CIRCLE_INITIAL_Y		(-125.0f)		// 初期の座標

//=============================================================================
// 前方宣言
//=============================================================================
class CLight;

//=============================================================================
// エネミークラス
//=============================================================================
class CEnemy : public CCharacter
{
public:
	// 敵の色
	typedef enum
	{
		COLOR_TYPE_NONE = 0,	// 初期値
		COLOR_TYPE_WHITE,		// 白い敵
		COLOR_TYPE_BLACK,		// 赤い敵
		COLOR_TYPE_MAX
	}COLOR_TYPE;

	// 敵の種類
	typedef enum
	{
		ENEMY_TYPE_NONE = 0,		// 初期値
		ENEMY_TYPE_NORMAL,			// 通常敵
		ENEMY_TYPE_CURRENT,			// 自機取得弾を打つ敵
		ENEMY_TYPE_SNAKE,			// ジグザグ移動
		ENEMY_TYPE_THROUGH,			// 真っすぐ弾を打つ敵
		ENEMY_TYPE_ROTATION,		// 回ってくる敵
		ENEMY_TYPE_CIRCLE,			// サークル配置の敵
		ENEMY_TYPE_DIRECTION,		// 方向転換する敵
		ENEMY_TYPE_FOLLOW,			// 追従する敵
		ENEMY_TYPE_MAX
	}ENEMY_TYPE;

	CEnemy(TYPE Priority = TYPE_ENEMY);	// コンストラクタ
	~CEnemy();							// デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);		// 初期化処理
	void Uninit(void);												// 終了処理
	void Update(void);												// 更新処理
	void Draw(void);												// 描画処理
	void Death(void);												// 死んだときの処理
	virtual void UpdateState(void);									// 状態の更新処理

	bool Collision(void);											// 当たり判定
	void InitThrough(D3DXVECTOR3 pos);								// 初期位置取得
	void TransparentInit(void);										// 透明の初期化

	void NormalBullet(void);										// 通常弾
	void ContinuousBullet(int nBulletNum);							// 連続弾
	void ScaleUp(D3DXVECTOR3 BaseSize);								// 拡大
	void Appearance(void);											// 透明から出現

	// Set関数
	void SetEnemyType(COLOR_TYPE Ctype, ENEMY_TYPE Etype);			// 情報セット
	void SetCounterBullet(int nCounter);									// カウンターバレットの設定
	void SetFirstBulletTime(int nTime);								// 初弾の発生フレーム設定
	void SetLight(void);											// ライトの設定
	void SetBulletFlame(float fBulletFlame);						// 弾の発射フレーム設定
	void SetMoveCounter(int nCounter);								// 移動時のフレームカウンター
	void SetScaleNum(float fScaleNum);								// 拡大量設定

	// Get関数
	COLOR_TYPE GetColorType(void) { return m_Ctype; }			// カラータイプの情報
	float GetBulletFlame(void) { return m_fBulletFlame; }		// 弾の発射フレーム情報
	int GetMoveCounter(void) { return m_nMoveCounter; }			// 移動時のカウンター

	// 純粋仮想関数
	virtual void MoveUpdate() = 0;											// 移動の更新
	virtual void BulletUpdate() = 0;										// 弾の発射更新処理

private:
	CLight *m_pLight;						// ライトのポインタ
	D3DXVECTOR3 m_center;					// センター
	COLOR_TYPE m_Ctype;						// カラーの種類
	ENEMY_TYPE m_Etype;						// エネミーの種類
	float m_fBulletFlame;					// バレット間隔のカウンター
	int m_nMoveCounter;						// 移動時に使用するカウンター
	int m_nEnemyCounter;					// エネミー制御のカウンター
	int m_nStateCnt;						// エネミーの状態カウンター
	int m_nCountinueInter;					// 連続弾の間隔
	int m_nContinueCnt;						// 連続弾のカウント
	int m_nBulletNum;						// 弾の数
	int m_nCounterBulletNum;				// カウンター弾の設定
	int m_nFirstBulletFrame;				// 初弾のフレーム
	int m_nThroughStopCnt;					// 止まっているフレーム
	int m_nOutsideScreenCnt;				// スクリーン外のカウント
	int m_nDirection;						// 方向転換の敵のナンバー
	int m_nSubNumber;						// テクスチャの透明度変更変数
	int m_nSubNum;							// 透明度の数値
	float m_fScale;							// 縮小用変数
	float m_fScaleNum;						// 縮小量
	float m_fThroughBulletCnt;				// 真っすぐ飛ばす敵のバレットカウント
	bool m_bSnakeSwitch;					// ジグザグ移動のフラグ
	bool m_bTwo_Sides;						// 真っすぐ弾を打つ敵のフラグ
	bool m_bRotationScale;					// ローテーションの拡大フラグ
	bool m_bFlashFlag;						// フラッシュのフラグ
	bool m_bFollowFlag;						// 追従の敵のフラグ

};

#endif