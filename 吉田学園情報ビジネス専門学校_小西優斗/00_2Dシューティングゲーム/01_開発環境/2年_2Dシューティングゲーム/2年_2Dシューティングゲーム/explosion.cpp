//=============================================================================
//
// �����N���X [explosion.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "explosion.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "sound.h"
#include "texture.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CExplosion::CExplosion() :CScene2D(TYPE_EXPLOSION)
{
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Ctype = COLOR_TYPE_NONE;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CExplosion::~CExplosion()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CExplosion::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// ����������
	CScene2D::Init(pos, size, type);

	// ���W���
	m_Pos = pos;

	// �����̎��
	switch (m_Ctype)
	{
	case COLOR_TYPE_WHITE:
	case COLOR_TYPE_BLACK:
		// �A�j���[�V�����ݒ�
		InitAnimation(EXPLOSION_ANIM_SPEED, EXPLOSION_ANIM_PATTERN, 0);
		break;

	case COLOR_TYPE_BOSS:
		// �A�j���[�V�����ݒ�
		InitAnimation(BOSS_EXPLOSION_ANIM_SPEED, BOSS_EXPLOSION_ANIM_PATTERN, 0);
		break;
	}
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CExplosion::Uninit(void)
{
	// 2D�|���S���I������
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CExplosion::Update(void)
{
	// ���݂̈ʒu���擾
	m_Pos = GetPos();

	m_Pos += m_move;

	// ���W��n��
	SetPosition(m_Pos);

	// 2D�|���S���X�V����
	CScene2D::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CExplosion::Draw(void)
{
	// 2D�|���S���`�揈��
	CScene2D::Draw();
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CExplosion * CExplosion::Create(D3DXVECTOR3 pos,  D3DXVECTOR3 move, D3DXVECTOR3 size, TYPE type, COLOR_TYPE Ctype)
{
	// �������m��
	CExplosion *pExplosion = new CExplosion;

	// ����������
	pExplosion->m_Ctype = Ctype;				// �^�C�v�ݒ�
	pExplosion->Init(pos, size, type);			// ����������
	pExplosion->SetExplosion(move, Ctype);		// �ړ��ʐݒ�

	// �F�̏���
	switch (Ctype)
	{
		// �����Ƃ�
	case COLOR_TYPE_WHITE:
		// �e�N�X�`���ݒ�
		pExplosion->BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_EXPLOSION_000));
		break;

		// �����Ƃ�
	case COLOR_TYPE_BLACK:
		// �e�N�X�`���ݒ�
		pExplosion->BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_EXPLOSION_001));
		break;

		// �{�X�̎�
	case COLOR_TYPE_BOSS:
		// �e�N�X�`���ݒ�
		pExplosion->BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_EXPLOSION_002));
		break;
	}

	return pExplosion;
}

//=============================================================================
// �e�̐ݒ�
//=============================================================================
void CExplosion::SetExplosion(D3DXVECTOR3 move, COLOR_TYPE Ctype)
{
	m_move = move;
	m_Ctype = Ctype;
}