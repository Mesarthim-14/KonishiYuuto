//=============================================================================
//
// �X�^�[�g���S�N���X [start_logo.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//====================================================================
// �C���N���[�h
//====================================================================
#include "start_logo.h"
#include "renderer.h"
#include "manager.h"
#include "alert.h"
#include "texture.h"

//====================================================================
// �}�N����`
//====================================================================
#define START_LOGO_COLOR_NUM	(5)			// �F�̕ω�
#define START_LOGO_COLOR_MAX	(150)		// �J���[�ύX�̍ő�
#define START_LOGO_COLOR_MIN	(0)			// �J���[�ύX�̍ŏ�
#define START_LOGO_CHANGE_TIME	(35)		// �J���[��ς���t���[��

//====================================================================
// �|���S������
//====================================================================
CStartLogo * CStartLogo::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// �C���X�^���X����
	CStartLogo *pStartLogo = new CStartLogo;

	if (pStartLogo != NULL)
	{
		// ����������
		pStartLogo->Init(pos, size, type);

		// �e�N�X�`���̐ݒ�
		pStartLogo->BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_START_LOGO));

		// �T�C�Y����
		pStartLogo->m_size = size;
	}
	return pStartLogo;
}

//====================================================================
// �R���X�g���N�^
//====================================================================
CStartLogo::CStartLogo() : CScene2D(TYPE_UI)
{
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nFlashFlame = 0;
	m_nSubNumber = 0;
	m_nSubNum = START_LOGO_COLOR_NUM;
	m_bDisappearFlag = false;
}

//====================================================================
// �f�X�g���N�^
//====================================================================
CStartLogo::~CStartLogo()
{

}

//====================================================================
// ����������
//====================================================================
HRESULT CStartLogo::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// ����������
	CScene2D::Init(pos, size, type);

	return S_OK;
}

//====================================================================
// �I������
//====================================================================
void CStartLogo::Uninit(void)
{
	// �I������
	CScene2D::Uninit();
}

//====================================================================
// �X�V����
//====================================================================
void CStartLogo::Update(void)
{
	// �X�V����
	CScene2D::Update();

	// �_�ł�����
	FlashPolygon();
}

//====================================================================
// �`�揈��
//====================================================================
void CStartLogo::Draw(void)
{
	// �`�揈��
	CScene2D::Draw();
}

//====================================================================
// �|���S���̓_��
//====================================================================
void CStartLogo::FlashPolygon(void)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �J���[�̌��Z
	m_nSubNumber += m_nSubNum;

	// ����ɍs������
	if (m_nSubNumber >= 255)
	{
		m_nSubNumber = 255;
		m_bDisappearFlag = true;

	}
	else if (m_nSubNumber <= 0)
	{
		m_nSubNumber = 0;
		m_nSubNum *= -1;
	}

	if (m_bDisappearFlag == true)
	{
		m_nFlashFlame++;

		if (m_nFlashFlame >= 20)
		{
			m_nFlashFlame = 0;
			m_nSubNum *= -1;
			m_bDisappearFlag = false;
		}
	}

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255 - m_nSubNumber);	// ���㒸�_�̐F	�����x255
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255 - m_nSubNumber);	// �E�㒸�_�̐F	�����x255
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255 - m_nSubNumber);	// �������_�̐F	�����x255
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255 - m_nSubNumber);	// �E�����_�̐F	�����x255

	// ���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}