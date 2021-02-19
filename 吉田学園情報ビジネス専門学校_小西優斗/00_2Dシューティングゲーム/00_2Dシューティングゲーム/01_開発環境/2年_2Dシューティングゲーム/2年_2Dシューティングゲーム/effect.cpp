//=============================================================================
//
// �G�t�F�N�g���� [effect.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "effect.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "sound.h"
#include "texture.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define EFFECT_LIFE			(4)			// �G�t�F�N�g�̗̑�

//=============================================================================
// �C���X�^���X����
//=============================================================================
CEffect * CEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, 
	D3DXVECTOR3 size, TYPE type, EFFECT_COLOR Ctype)
{
	// �C���X�^���X����
	CEffect *pEffect = new CEffect;

	if (pEffect != NULL)
	{
		// ����������
		pEffect->Init(pos, size, type);			// ���������
		pEffect->SetMove(move);					// �ړ���
		pEffect->SetColor(Ctype);				// �F�̎��
		pEffect->InitColor();					// �F�̏�����
		pEffect->BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_EFFECT));	// �e�N�X�`���ݒ�
	}
	
	return pEffect;
}

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEffect::CEffect(TYPE Priority) : CScene2D(Priority)
{
	m_Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Ctype = EFFECT_COLOR_NONE;
	m_Etype = EFFECT_TYPE_NONE;
	m_bScaleDown = false;
	m_pVtxBuff = NULL;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEffect::~CEffect()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CEffect::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// ����������
	CScene2D::Init(pos, size, type);
	m_Pos = pos;

	return S_OK;
}

//=============================================================================
// �J���[�̐ݒ�
//=============================================================================
void CEffect::InitColor(void)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �F�̎��
	switch (m_Ctype)
	{
		// �����e�̎�
	case EFFECT_COLOR_WHITE:

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(0, 100, 255, 255);	// ���㒸�_�̐F	�����x255
		pVtx[1].col = D3DCOLOR_RGBA(0, 100, 255, 255);	// �E�㒸�_�̐F	�����x255
		pVtx[2].col = D3DCOLOR_RGBA(0, 100, 255, 255);	// �������_�̐F	�����x255
		pVtx[3].col = D3DCOLOR_RGBA(0, 100, 255, 255);	// �E�����_�̐F	�����x255
		break;

	case EFFECT_COLOR_BLACK:

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 40, 255);	// ���㒸�_�̐F	�����x255
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 40, 255);	// �E�㒸�_�̐F	�����x255
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 40, 255);	// �������_�̐F	�����x255
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 40, 255);	// �E�����_�̐F	�����x255
		break;
	}

	// ���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}

//=============================================================================
// �I������
//=============================================================================
void CEffect::Uninit(void)
{
	// 2D�|���S���I������
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CEffect::Update(void)
{
	// 2D�|���S���X�V����
	CScene2D::Update();

	// ���������Ă���
   	m_bScaleDown = ScaleDown(m_Pos, EFFECT_LIFE);

	// �������Ȃ肫������
	if (m_bScaleDown == true)
	{
		// �I������
		Uninit();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CEffect::Draw(void)
{
	// �����_���[�̏����󂯎��
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// ���Z�������s��
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);			// a�f�X�e�B�l�[�V�����J���[

	// 2D�|���S���`�揈��
	CScene2D::Draw();

	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// a�f�X�e�B�l�[�V�����J���[
}

//=============================================================================
// �J���[�ݒ�
//=============================================================================
void CEffect::SetColor(EFFECT_COLOR Ctype)
{
	m_Ctype = Ctype;
}

//=============================================
// �e�̐ݒ�
//=============================================
void CEffect::SetMove(D3DXVECTOR3 move)
{
	// �ϐ��ɑ��
	m_move = move;
}