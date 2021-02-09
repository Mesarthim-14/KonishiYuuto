//=============================================================================
//
// �A�C�R���N���X [icon.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//====================================================================
// �C���N���[�h
//====================================================================
#include "icon.h"
#include "renderer.h"
#include "manager.h"
#include "sound.h"
#include "texture.h"

//====================================================================
// �}�N����`
//====================================================================
#define ICON_SCALE_UP_NUM		(0.1f)		// �g��̒l
#define ICON_COLOR_NUM			(10)		// �F�̕ω�
#define ICON_COLOR_MAX			(150)		// �J���[�ύX�̍ő�
#define ICON_COLOR_MIN			(0)			// �J���[�ύX�̍ŏ�
#define ICON_CHANGE_TIME		(35)		// �J���[��ς���t���[��
#define ICON_USE_TIME			(210)		// �A�C�R���̏o������

//====================================================================
// �|���S������
//====================================================================
CIcon * CIcon::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// �C���X�^���X����
	CIcon *pWarning = new CIcon;

	if (pWarning != NULL)
	{
		// ����������
		pWarning->Init(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), type);

		// �e�N�X�`���̐ݒ�
		pWarning->BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_ICON));

		// �T�C�Y����
		pWarning->m_size = size;
	}

	return pWarning;
}

//====================================================================
// �R���X�g���N�^
//====================================================================
CIcon::CIcon() : CScene2D(TYPE_UI)
{
	m_fScale = 0.0f;
	m_fScaleNum = 0.0f;
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nFlashFlame = 0;
	m_nSubNumber = 0;
	m_nIconCounter = 0;
	m_nSubNum = ICON_COLOR_NUM;
	m_bEndIcon = false;
}

//====================================================================
// �f�X�g���N�^
//====================================================================
CIcon::~CIcon()
{

}

//====================================================================
// ����������
//====================================================================
HRESULT CIcon::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// ����������
	CScene2D::Init(pos, size, type);

	// �k���ʂ�ݒ�
	m_fScaleNum = ICON_SCALE_UP_NUM;

	return S_OK;
}

//====================================================================
// �I������
//====================================================================
void CIcon::Uninit(void)
{
	// �I������
	CScene2D::Uninit();
	Release();
}

//====================================================================
// �X�V����
//====================================================================
void CIcon::Update(void)
{
	m_nIconCounter++;

	// �X�V����
	CScene2D::Update();

	if (m_nIconCounter >= ICON_USE_TIME)
	{
		// �k��
		ScaleDown();
	}
	else
	{
		// �g��
		ScaleUp();
	}

	// �_�ł�����
	FlashPolygon();
}

//====================================================================
// �`�揈��
//====================================================================
void CIcon::Draw(void)
{
	// �`�揈��
	CScene2D::Draw();
}

//====================================================================
// �g��
//====================================================================
void CIcon::ScaleUp(void)
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
void CIcon::ScaleDown(void)
{
	// �����Ă��Ȃ�������
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
		m_bEndIcon = true;
	}
}

//====================================================================
// �|���S���̓_��
//====================================================================
void CIcon::FlashPolygon(void)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �J���[�̌��Z
	m_nSubNumber += m_nSubNum;

	// �J���[�ύX�̍ő�l
	if (m_nSubNumber >= ICON_COLOR_MAX)
	{
		// ����
		m_nSubNumber = ICON_COLOR_MAX;

		// �l�𔽓]
		m_nSubNum *= -1;
	}
	else if (m_nSubNumber <= ICON_COLOR_MIN)
	{
		// �J���[�̍ŏ��l�̐���
		m_nSubNumber = ICON_COLOR_MIN;

		// �t���[���J�E���g
		m_nFlashFlame++;

		// ���̃t���[���ȏ�ɂȂ�����
		if (m_nFlashFlame >= ICON_CHANGE_TIME)
		{
			m_nFlashFlame = 0;

			// �l�𔽓]
			m_nSubNum *= -1;
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

//====================================================================
// �A�C�R���̏I���t���O���
//====================================================================
bool CIcon::GetEndIcon(void)
{
	return m_bEndIcon;
}