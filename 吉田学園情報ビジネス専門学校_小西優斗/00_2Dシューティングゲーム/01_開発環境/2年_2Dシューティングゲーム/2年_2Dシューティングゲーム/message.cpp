//=============================================================================
//
// メッセージクラス [message.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "message.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MESSAGE_SCALE_UP_NUM		(0.1f)		// 拡大の値
#define MESSAGE_USE_TIME			(210)		// メッセージの出現時間

//====================================================================
// ポリゴン生成
//====================================================================
CMessage * CMessage::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// インスタンス生成
	CMessage *pMessage = new CMessage;

	if (pMessage != NULL)
	{
		// 初期化処理
		pMessage->Init(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), type);

		// テクスチャの設定
		pMessage->BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_MESSAGE));

		// サイズを代入
		pMessage->m_size = size;
	}
	return pMessage;
}

//====================================================================
// コンストラクタ
//====================================================================
CMessage::CMessage() : CScene2D(TYPE_UI)
{
	m_fScale = 0.0f;
	m_fScaleNum = 0.0f;
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nMessageCounter = 0;
	m_bEndMessage = false;
}

//====================================================================
// デストラクタ
//====================================================================
CMessage::~CMessage()
{

}

//====================================================================
// 初期化処理
//====================================================================
HRESULT CMessage::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// 初期化処理
	CScene2D::Init(pos, size, type);

	// 縮小量を設定
	m_fScaleNum = MESSAGE_SCALE_UP_NUM;

	return S_OK;
}

//====================================================================
// 終了処理
//====================================================================
void CMessage::Uninit(void)
{
	// 終了処理
	CScene2D::Uninit();
}

//====================================================================
// 更新処理
//====================================================================
void CMessage::Update(void)
{
	// 出現しているカウンタ
	m_nMessageCounter++;

	// 更新処理
	CScene2D::Update();

	if (m_nMessageCounter >= MESSAGE_USE_TIME)
	{
		// 縮小
		ScaleDown();
	}
	else
	{
		// 拡大
		ScaleUp();
	}
}

//====================================================================
// 描画処理
//====================================================================
void CMessage::Draw(void)
{
	// 描画処理
	CScene2D::Draw();
}

//====================================================================
// 拡大
//====================================================================
void CMessage::ScaleUp(void)
{
	if (m_fScale <= 1.0f)
	{
		// 縮小量を加算
		m_fScale += m_fScaleNum;

		D3DXVECTOR3 size = D3DXVECTOR3(m_size.x * m_fScale, m_size.y * m_fScale, 0.0f);

		// Scene2Dにサイズを渡す
		SetSize(size);
	}
	else
	{
		m_fScale = 1.0f;
	}
}

//====================================================================
// 縮小
//====================================================================
void CMessage::ScaleDown(void)
{
	if (m_fScale >= 0.0f)
	{
		// 縮小量を加算
		m_fScale -= m_fScaleNum;

		D3DXVECTOR3 size = D3DXVECTOR3(m_size.x * m_fScale, m_size.y * m_fScale, 0.0f);

		// Scene2Dにサイズを渡す
		SetSize(size);
	}
	else
	{
		m_fScale = 0.0f;
		m_bEndMessage = true;
	}
}

//====================================================================
// アイコンの終了フラグ情報
//====================================================================
bool CMessage::GetEndMessage(void)
{
	return m_bEndMessage;
}