#ifndef _TEXTURE_H_
#define _TEXTURE_H_
//=============================================================================
//
// テクスチャの管理ヘッダー [texture.h]
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

//=============================================================================
//クラス宣言
//=============================================================================
class CTexture
{
public:

	// テクスチャの番号の列挙型
	typedef enum
	{
		TEXTURE_NUM_NONE = -1,		// 初期値
		TEXTURE_NUM_BG_000,			// 背景0
		TEXTURE_NUM_BG_001,			// 背景1
		TEXTURE_NUM_BG_002,			// 背景2
		TEXTURE_NUM_EFFECT,			// エフェクト
		TEXTURE_NUM_BOMB_UI,		// ボムのUI
		TEXTURE_NUM_BOSS,			// ボス
		TEXTURE_NUM_BULLET_000,		// 弾000
		TEXTURE_NUM_BULLET_001,		// 弾001
		TEXTURE_NUM_BULLET_002,		// 弾002
		TEXTURE_NUM_BULLET_003,		// 弾002
		TEXTURE_NUM_CROW,			// カラス
		TEXTURE_NUM_ENEMY_WHITE,	// 白の敵
		TEXTURE_NUM_ENEMY_BLACK,	// 黒の敵
		TEXTURE_NUM_ENEMY_BLUE,		// 青の敵
		TEXTURE_NUM_ENEMY_RED,		// 赤の敵
		TEXTURE_NUM_EXPLOSION_000,	// 爆発000
		TEXTURE_NUM_EXPLOSION_001,	// 爆発001
		TEXTURE_NUM_EXPLOSION_002,	// 爆発002
		TEXTURE_NUM_GAGEBAR_000,	// ゲージバー000
		TEXTURE_NUM_GAGEBAR_001,	// ゲージバー001
		TEXTURE_NUM_HPBAR,			// HPバー
		TEXTURE_NUM_ICON,			// アイコン
		TEXTURE_NUM_LASER,			// レーザー
		TEXTURE_NUM_MESSAGE,		// メッセージ
		TEXTURE_NUM_NUMBER_000,		// ナンバー000
		TEXTURE_NUM_NUMBER_001,		// ナンバー001
		TEXTURE_NUM_PLAYER,			// プレイヤー
		TEXTURE_NUM_RESULT_BG,		// リザルト画面背景
		TEXTURE_NUM_BARRIER_BLUE,	// 青バリア
		TEXTURE_NUM_BARRIER_RED,	// 赤バリア
		TEXTURE_NUM_SHOCK_000,		// 衝撃000
		TEXTURE_NUM_SHOCK_001,		// 衝撃001
		TEXTURE_NUM_SPARK,			// 火花
		TEXTURE_NUM_START_LOGO,		// スタートのロゴ
		TEXTURE_NUM_SURROUNDINGS,	// 取り巻きエネミー
		TEXTURE_NUM_TITLE,			// タイトル
		TEXTURE_NUM_TUTORIAL,		// チュートリアル
		TEXTURE_NUM_UI_WALL,		// 壁
		TEXTURE_NUM_UI_WAKU,		// わく
		TEXTURE_NUM_UI_REMAIN,		// 残機
		TEXTURE_NUM_WARNING,		// 警告
		TEXTURE_NUM_MAX
	}TEXTURE_TYPE;

	CTexture();		// コンストラクタ
	~CTexture();	// デストラクタ

	static HRESULT Load(void);										// テクスチャロード
	static void UnLoad(void);										// テクスチャアンロード
	static LPDIRECT3DTEXTURE9 GetTexture(TEXTURE_TYPE Tex_Type);	// テクスチャの情報
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[TEXTURE_NUM_MAX];				// テクスチャのポインタ
};
#endif
