//=============================================================================
//
// �o�b�O�O���E���h���� [bg.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "bg.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_BG				(3)			// BG�̐�
#define BG_SPEED			(2)			// �X�s�[�h
#define BG_DIVISION_BASE	(0.008f)	// �X�N���[���̊�{�l
#define BG_DIVISION			(0.004f)	// �X�N���[���̒l

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBackground::CBackground(TYPE Priority) : CScene(Priority)
{
	for (int nCount = 0; nCount < MAX_BG; nCount++)
	{
		m_apScene2D[nCount] = NULL;
	}
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBackground::~CBackground()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CBackground * CBackground::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// �������m��
	CBackground *pBackground = new CBackground;

	// ����������
	pBackground->Init(pos, size, type);

	return pBackground;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBackground::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	for (int nCount = 0; nCount < MAX_BG; nCount++)
	{
		// �g���Ă��Ȃ��Ƃ�
		if (m_apScene2D[nCount] == NULL)
		{
			// ����������
			m_apScene2D[nCount] = new CScene2D;				// �������m��
			m_apScene2D[nCount]->InitScroll(BG_SPEED, BG_DIVISION_BASE + BG_DIVISION*(float)nCount);	// �X�N���[�����
			m_apScene2D[nCount]->Init(pos, size, type);													// ���������
			m_apScene2D[nCount]->BindTexture(CTexture::GetTexture((CTexture::TEXTURE_TYPE)((int)CTexture::TEXTURE_NUM_BG_000 + nCount)));				// �e�N�X�`�����

		}
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBackground::Uninit(void)
{
	for (int nCount = 0; nCount < MAX_BG; nCount++)
	{
		if (m_apScene2D[nCount] != NULL)
		{
			// �I������
			m_apScene2D[nCount]->Uninit();
			m_apScene2D[nCount] = NULL;
		}
	}

	// �����[�X
	Release();
}
 
//=============================================================================
// �X�V����
//=============================================================================
void CBackground::Update(void)
{
	for (int nCount = 0; nCount < MAX_BG; nCount++)
	{
		if (m_apScene2D[nCount] != NULL)
		{
			// �X�V����
			m_apScene2D[nCount]->Update();
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBackground::Draw(void)
{

}