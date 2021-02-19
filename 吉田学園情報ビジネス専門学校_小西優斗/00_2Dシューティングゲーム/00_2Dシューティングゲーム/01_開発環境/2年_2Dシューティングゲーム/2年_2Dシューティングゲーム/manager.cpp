//=============================================================================
//
// �}�l�[�W���[���� [manager.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
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
// �}�N����`
//=============================================================================

//=============================================================================
// static������
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
// �}�l�[�W���[�R���X�g���N�^
//=============================================================================
CManager::CManager()
{

}

//=============================================================================
// �}�l�[�W���[�f�X�g���N�^
//=============================================================================
CManager::~CManager()
{

}

//=============================================================================
// �}�l�[�W���[����������
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	// �����_���[����������
	m_pRenderer = new CRenderer;
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Init(hWnd, bWindow);
	}

	// �L�[�{�[�h����������
	m_pKeyboard = new CKeyboard;
	if (m_pKeyboard != NULL)
	{
		m_pKeyboard->Init(hInstance, hWnd);
	}

	// �W���C�p�b�h
	m_pJoypad = new CInputJoypad;
	// �W���C�p�b�h�̏�����
	if (FAILED(m_pJoypad->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}

	if (m_pFade == NULL)
	{
		// �t�F�[�h����������
		m_pFade = CFade::Create();
	}

	// �e�N�X�`���̃��[�h
	CTexture::Load();

	// �T�E���h����������
	m_pSound = new CSound;
	if (m_pSound != NULL)
	{
		m_pSound->Init(hWnd);
	}


	return S_OK;
}

//=============================================================================
// �}�l�[�W���[�I������
//=============================================================================
void CManager::Uninit(void)
{
	// �g���Ă�����
	if (m_pKeyboard != NULL)
	{
		// �L�[�{�[�h�I������
		m_pKeyboard->Uninit();

		// �L�[�{�[�h�̃������J��
		delete m_pKeyboard;
		m_pKeyboard = NULL;
	}

	if (m_pFade != NULL)
	{
		// �I������
		m_pFade->Uninit();
		// �������̉��
		delete m_pFade;
		m_pFade = NULL;
	}

	if (m_pJoypad != NULL)
	{
		// �I������
		m_pJoypad->Uninit();
		// �������̉��
		delete m_pJoypad;
		m_pJoypad = NULL;
	}

	// �T�E���h�̏I������
	if (m_pSound != NULL)
	{
		m_pSound->Uninit();

		// �T�E���h�̃������J��
		delete m_pSound;
		m_pSound = NULL;
	}

	// �S�Ẵ����[�X
	CScene::ReleaseAll();
	// �e�N�X�`���̃A�����[�h
	CTexture::UnLoad();

	// �g���Ă�����
	if (m_pRenderer != NULL)
	{
		// �����_���[�I������
		m_pRenderer->Uninit();

		// �����_���[�̃������J��
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

//=============================================================================
// �}�l�[�W���[�X�V����
//=============================================================================
void CManager::Update(void)
{
	if (m_pKeyboard != NULL)
	{
		// �L�[�{�[�h�X�V����
		m_pKeyboard->Update();
	}

	// �W���C�p�b�h�N���X�̍X�V����
	if (m_pJoypad != NULL)
	{
		m_pJoypad->Update();
	}

	if (m_pRenderer != NULL)
	{
		// �����_���[�X�V����
		m_pRenderer->Update();
	}

	// �t�F�[�h�X�V
	if (m_pFade != NULL)
	{
		m_pFade->Update();
	}

	switch (m_Mode)
	{
	case MODE_TITLE:

		// �^�C�g������������
		if (m_pTitle != NULL)
		{
			m_pTitle->Update();
		}
		break;
	case MODE_GAME:
		// �^�C�g������������
		if (m_pGame != NULL)
		{
			m_pGame->Update();
		}
		break;
	case MODE_RESULT:
		// �^�C�g������������
		if (m_pResult != NULL)
		{
			m_pResult->Update();
		}
		break;
	}
}

//=============================================================================
// �}�l�[�W���[�`�揈��
//=============================================================================
void CManager::Draw(void)
{
	if (m_pRenderer != NULL)
	{
		// �`�揈��
		m_pRenderer->Draw();
	}
}

//=============================================================================
// FPS�\���Ăяo��
//=============================================================================
void CManager::SetFPS(int nCountFPS)
{
	if (m_pRenderer != NULL)
	{
		// FPS�\�����Ăяo��
		m_pRenderer->SetFPS(nCountFPS);
	}
}

//=============================================================================
// �����_���[����Ԃ�
//=============================================================================
CRenderer * CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//=============================================================================
// �L�[�{�[�h����Ԃ�
//=============================================================================
CKeyboard * CManager::GetKeyboard(void)
{
	return m_pKeyboard;
}

//=============================================================================
// �T�E���h����Ԃ�
//=============================================================================
CSound * CManager::GetSound(void)
{
	return m_pSound;
}

//=============================================================================
// �^�C�g���̏���Ԃ�
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
// ���[�h���ݒ�
//=============================================================================
void CManager::SetMode(MODE mode)
{

	// �I������
	switch (m_Mode)
	{
	case MODE_TITLE:
		// �^�C�g���I������
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();
			delete m_pTitle;
			m_pTitle = NULL;
		}
		break;

	case MODE_GAME:
		// �Q�[���I������
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();
			delete m_pGame;
			m_pGame = NULL;
		}
		break;

	case MODE_RESULT:
		// ���U���g�I������
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

	// �����[�X
	CScene::ReleaseAll();

	m_Mode = mode;

	// ����������
	switch (m_Mode)
	{
	case MODE_TITLE:

		// �^�C�g���̏�����
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
		// �Q�[���̏�����
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
		// ���U���g
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
