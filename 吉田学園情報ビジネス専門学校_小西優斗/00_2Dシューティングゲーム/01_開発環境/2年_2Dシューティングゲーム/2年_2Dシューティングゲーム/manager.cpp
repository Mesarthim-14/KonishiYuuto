//=============================================================================
//
// マネージャー処理 [manager.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "fade.h"
#include "game.h"
#include "joypad.h"
#include "keyboard.h"
#include "manager.h"
#include "renderer.h"
#include "result.h"
#include "sound.h"
#include "title.h"
#include "texture.h"

//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// static初期化
//=============================================================================
CRenderer *CManager::m_pRenderer = NULL;
CInput *CManager::m_pInput = NULL;
CKeyboard *CManager::m_pKeyboard = NULL;
CSound *CManager::m_pSound = NULL;
CTitle *CManager::m_pTitle = NULL;
CGame *CManager::m_pGame = NULL;
CResult *CManager::m_pResult = NULL;
CFade *CManager::m_pFade = NULL;
CManager::MODE CManager::m_Mode = MODE_TITLE;
CInputJoypad *CManager::m_pJoypad = NULL;

//=============================================================================
// マネージャーコンストラクタ
//=============================================================================
CManager::CManager()
{

}

//=============================================================================
// マネージャーデストラクタ
//=============================================================================
CManager::~CManager()
{

}

//=============================================================================
// マネージャー初期化処理
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	// レンダラー初期化処理
	m_pRenderer = new CRenderer;
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Init(hWnd, bWindow);
	}

	// キーボード初期化処理
	m_pKeyboard = new CKeyboard;
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard->Init(hInstance, hWnd);
	}

	// ジョイパッド
	m_pJoypad = new CInputJoypad;
	// ジョイパッドの初期化
	if (FAILED(m_pJoypad->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	if (m_pFade == NULL)
	{
		// フェード初期化処理
		m_pFade = CFade::Create();
	}

	// テクスチャのロード
	CTexture::Load();

	// サウンド初期化処理
	m_pSound = new CSound;
	if (m_pSound != NULL)
	{
		m_pSound->Init(hWnd);
	}


	return S_OK;
}

//=============================================================================
// マネージャー終了処理
//=============================================================================
void CManager::Uninit(void)
{
	// 使われていた時
	if (m_pKeyboard != NULL)
	{
		// キーボード終了処理
		m_pKeyboard->Uninit();

		// キーボードのメモリ開放
		delete m_pKeyboard;
		m_pKeyboard = NULL;
	}

	if (m_pFade != NULL)
	{
		// 終了処理
		m_pFade->Uninit();
		// メモリの解放
		delete m_pFade;
		m_pFade = NULL;
	}

	if (m_pJoypad != NULL)
	{
		// 終了処理
		m_pJoypad->Uninit();
		// メモリの解放
		delete m_pJoypad;
		m_pJoypad = NULL;
	}

	// サウンドの終了処理
	if (m_pSound != NULL)
	{
		m_pSound->Uninit();

		// サウンドのメモリ開放
		delete m_pSound;
		m_pSound = NULL;
	}

	// 全てのリリース
	CScene::ReleaseAll();
	// テクスチャのアンロード
	CTexture::UnLoad();

	// 使われていた時
	if (m_pRenderer != NULL)
	{
		// レンダラー終了処理
		m_pRenderer->Uninit();

		// レンダラーのメモリ開放
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

//=============================================================================
// マネージャー更新処理
//=============================================================================
void CManager::Update(void)
{
	if (m_pKeyboard != NULL)
	{
		// キーボード更新処理
		m_pKeyboard->Update();
	}

	// ジョイパッドクラスの更新処理
	if (m_pJoypad != NULL)
	{
		m_pJoypad->Update();
	}

	if (m_pRenderer != NULL)
	{
		// レンダラー更新処理
		m_pRenderer->Update();
	}

	// フェード更新
	if (m_pFade != NULL)
	{
		m_pFade->Update();
	}

	switch (m_Mode)
	{
	case MODE_TITLE:

		// タイトル初期化処理
		if (m_pTitle != NULL)
		{
			m_pTitle->Update();
		}
		break;
	case MODE_GAME:
		// タイトル初期化処理
		if (m_pGame != NULL)
		{
			m_pGame->Update();
		}
		break;
	case MODE_RESULT:
		// タイトル初期化処理
		if (m_pResult != NULL)
		{
			m_pResult->Update();
		}
		break;
	}
}

//=============================================================================
// マネージャー描画処理
//=============================================================================
void CManager::Draw(void)
{
	if (m_pRenderer != NULL)
	{
		// 描画処理
		m_pRenderer->Draw();
	}
}

//=============================================================================
// FPS表示呼び出し
//=============================================================================
void CManager::SetFPS(int nCountFPS)
{
	if (m_pRenderer != NULL)
	{
		// FPS表示を呼び出す
		m_pRenderer->SetFPS(nCountFPS);
	}
}

//=============================================================================
// レンダラー情報を返す
//=============================================================================
CRenderer * CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//=============================================================================
// キーボード情報を返す
//=============================================================================
CKeyboard * CManager::GetKeyboard(void)
{
	return m_pKeyboard;
}

//=============================================================================
// サウンド情報を返す
//=============================================================================
CSound * CManager::GetSound(void)
{
	return m_pSound;
}

//=============================================================================
// タイトルの情報を返す
//=============================================================================
CTitle * CManager::GetTitle(void)
{
	return m_pTitle;
}

CResult * CManager::GetResult(void)
{
	return m_pResult;
}

CFade * CManager::GetFade(void)
{
	return m_pFade;
}

CInputJoypad * CManager::GetJoypad(void)
{
	return m_pJoypad; 
}

//=============================================================================
// モード情報設定
//=============================================================================
void CManager::SetMode(MODE mode)
{

	// 終了処理
	switch (m_Mode)
	{
	case MODE_TITLE:
		// タイトル終了処理
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
			delete m_pTitle;
			m_pTitle = NULL;
		}
		break;

	case MODE_GAME:
		// ゲーム終了処理
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
			delete m_pGame;
			m_pGame = NULL;
		}
		break;

	case MODE_RESULT:
		// リザルト終了処理
		if (m_pResult != NULL)
		{
			m_pResult->Uninit();
			delete m_pResult;
			m_pResult = NULL;
		}
		break;

	default:
		break;
	}

	// リリース
	CScene::ReleaseAll();

	m_Mode = mode;

	// 初期化処理
	switch (m_Mode)
	{
	case MODE_TITLE:

		// タイトルの初期化
		if (m_pTitle == NULL)
		{
			m_pTitle = new CTitle;
			if (m_pTitle != NULL)
			{
				m_pTitle->Init();
			}
		}
		break;
	case MODE_GAME:
		// ゲームの初期化
		if (m_pGame == NULL)
		{
			m_pGame = new CGame;
			if (m_pGame != NULL)
			{
				m_pGame->Init();
			}
		}
		break;
	case MODE_RESULT:
		// リザルト
		if (m_pResult == NULL)
		{
			m_pResult = new CResult;
			if (m_pResult != NULL)
			{
				m_pResult->Init();
			}
		}
		break;

	default:
		break;
	}
}

CManager::MODE CManager::GetMode(void)
{
	return m_Mode;
}
