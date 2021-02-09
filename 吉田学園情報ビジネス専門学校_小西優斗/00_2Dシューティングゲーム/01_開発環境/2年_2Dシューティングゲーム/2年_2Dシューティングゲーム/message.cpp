//=============================================================================
//
// ���b�Z�[�W�N���X [message.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "message.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MESSAGE_SCALE_UP_NUM		(0.1f)		// �g��̒l
#define MESSAGE_USE_TIME			(210)		// ���b�Z�[�W�̏o������

//====================================================================
// �|���S������
//====================================================================
CMessage * CMessage::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// �C���X�^���X����
	CMessage *pMessage = new CMessage;

	if (pMessage != NULL)
	{
		// ����������
		pMessage->Init(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), type);

		// �e�N�X�`���̐ݒ�
		pMessage->BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_MESSAGE));

		// �T�C�Y����
		pMessage->m_size = size;
	}
	return pMessage;
}

//====================================================================
// �R���X�g���N�^
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
// �f�X�g���N�^
//====================================================================
CMessage::~CMessage()
{

}

//====================================================================
// ����������
//====================================================================
HRESULT CMessage::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// ����������
	CScene2D::Init(pos, size, type);

	// �k���ʂ�ݒ�
	m_fScaleNum = MESSAGE_SCALE_UP_NUM;

	return S_OK;
}

//====================================================================
// �I������
//====================================================================
void CMessage::Uninit(void)
{
	// �I������
	CScene2D::Uninit();
}

//====================================================================
// �X�V����
//====================================================================
void CMessage::Update(void)
{
	// �o�����Ă���J�E���^
	m_nMessageCounter++;

	// �X�V����
	CScene2D::Update();

	if (m_nMessageCounter >= MESSAGE_USE_TIME)
	{
		// �k��
		ScaleDown();
	}
	else
	{
		// �g��
		ScaleUp();
	}
}

//====================================================================
// �`�揈��
//====================================================================
void CMessage::Draw(void)
{
	// �`�揈��
	CScene2D::Draw();
}

//====================================================================
// �g��
//====================================================================
void CMessage::ScaleUp(void)
{
	if (m_fScale <= 1.0f)
	{
		// �k���ʂ����Z
		m_fScale += m_fScaleNum;

		D3DXVECTOR3 size = D3DXVECTOR3(m_size.x * m_fScale, m_size.y * m_fScale, 0.0f);

		// Scene2D�ɃT�C�Y��n��
		SetSize(size);
	}
	else
	{
		m_fScale = 1.0f;
	}
}

//====================================================================
// �k��
//====================================================================
void CMessage::ScaleDown(void)
{
	if (m_fScale >= 0.0f)
	{
		// �k���ʂ����Z
		m_fScale -= m_fScaleNum;

		D3DXVECTOR3 size = D3DXVECTOR3(m_size.x * m_fScale, m_size.y * m_fScale, 0.0f);

		// Scene2D�ɃT�C�Y��n��
		SetSize(size);
	}
	else
	{
		m_fScale = 0.0f;
		m_bEndMessage = true;
	}
}

//====================================================================
// �A�C�R���̏I���t���O���
//====================================================================
bool CMessage::GetEndMessage(void)
{
	return m_bEndMessage;
}