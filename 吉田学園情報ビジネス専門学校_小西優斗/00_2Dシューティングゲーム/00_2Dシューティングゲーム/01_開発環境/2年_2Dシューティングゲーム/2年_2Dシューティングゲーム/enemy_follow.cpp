//=============================================================================
//
// �Ǐ]�G�l�~�[�N���X [enemy_follow.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "enemy_follow.h"
#include "bullet.h"
#include "texture.h"
#include "player.h"
#include "game.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define FOLLOW_MOVE_X					(4.0f)			// �Ǐ]����G�̈ړ���
#define FOLLOW_MOVE_Y					(4.0f)			// �Ǐ]����G�̈ړ���
#define FOLLOW_LIFE						(1)				// �Ǐ]����G�̗̑�
#define FOLLOW_COUNTER_BULLET_NUM		(5)				// �Ǐ]����G�̃J�E���^�[�e��
#define FOLLOW_MOVE_TIME				(50)			// �Ǐ]����G��������
#define COLOR_NUM						(4)				// �����x
#define ALPHA_NUM						(255)			// �����x

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemyFollow::CEnemyFollow(TYPE Priority)
{
	m_bFlashFlag = false;
	m_bFollowFlag = false;
	m_nFollowCounter = 0;
	m_nSubNum = 0;
	m_nSubNumber = ALPHA_NUM;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEnemyFollow::~CEnemyFollow()
{

}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CEnemyFollow * CEnemyFollow::Create(D3DXVECTOR3 pos,
	D3DXVECTOR3 size, TYPE type, COLOR_TYPE Ctype, ENEMY_TYPE Etype)
{
	// �������m��
	CEnemyFollow *pEnemy = new CEnemyFollow;

	if (pEnemy != NULL)
	{
		// ����������
		pEnemy->SetSize(size);									// �T�C�Y�ݒ�
		pEnemy->SetEnemyType(Ctype, Etype);						// �G�l�~�[�̎�ސݒ�
		pEnemy->SetLife(FOLLOW_LIFE);							// ���C�t������
		pEnemy->m_nSubNum = COLOR_NUM;							// �J���[�ύX�̒l
		pEnemy->SetCounterBullet(FOLLOW_COUNTER_BULLET_NUM);	// �J�E���^�[�e�̐ݒ�
		pEnemy->Init(pos, size, type);							// ����������
		pEnemy->TransparentInit();								// �����ɂ�����
	}

	// �F�̎��
	switch (Ctype)
	{
		// �����Ƃ�
	case COLOR_TYPE_WHITE:

		//�@�e�N�X�`���̐ݒ�
		pEnemy->BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_ENEMY_WHITE));
		break;

		// �����Ƃ�
	case COLOR_TYPE_BLACK:

		// �e�N�X�`���̐ݒ�
		pEnemy->BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_ENEMY_BLACK));
	
		break;
	}

	return pEnemy;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CEnemyFollow::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// ����������
	CEnemy::Init(pos, size, type);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CEnemyFollow::Uninit(void)
{
	// �I������
	CEnemy::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CEnemyFollow::Update(void)
{
	// �ړ��X�V
	MoveUpdate();

	// �e�̍X�V
	BulletUpdate();

	// �X�V����
	CEnemy::Update();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CEnemyFollow::Draw(void)
{
	// �`�揈��
	CEnemy::Draw();
}

//=============================================================================
// �΂߈ړ��̏���
//=============================================================================
void CEnemyFollow::MoveUpdate(void)
{
	if (m_bFlashFlag == false)
	{
		// �����x�̕ύX
		Appearance();
	}

	if (m_bFollowFlag == false)
	{
		m_nFollowCounter++;

		if (m_nFollowCounter >= 50)
		{
			m_bFollowFlag = true;

			// �v���C���[�����擾
			CPlayer *pPlayer = CGame::GetPlayer();
			D3DXVECTOR3 Ppos = pPlayer->GetPos();
			D3DXVECTOR3 pos = GetPos();

			//���@���擾����
			float fPposx = Ppos.x, fPposy = Ppos.y;		// ���@�̍��W
			float fEposx = pos.x, fEposy = pos.y;	// �G�̍��W
			float fAngle;								// �p�x

			//�p�x�����߂�
			fAngle = atan2f((fEposx - fPposx), (fEposy - fPposy));

			// �����ȓG�̈ړ�
			D3DXVECTOR3 FollowMove = D3DXVECTOR3(
				(sinf(fAngle)*-FOLLOW_MOVE_X),
				cosf(fAngle)*-FOLLOW_MOVE_Y, 0.0f);

			// �ړ��ʂ̐ݒ�
			SetMove(FollowMove);
		}
	}

}

//=============================================================================
// �e�̍X�V����
//=============================================================================
void CEnemyFollow::BulletUpdate(void)
{

}

//=============================================================================
// ��������o��
//=============================================================================
void CEnemyFollow::Appearance(void)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �J���[�̌��Z
	m_nSubNumber -= m_nSubNum;

	// �J���[�ύX�̍ő�l
	if (m_nSubNumber <= 0)
	{
		// ����
		m_nSubNumber = 0;

		m_bFlashFlag = true;
	}

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255 - m_nSubNumber);	// ���㒸�_�̐F	�����x255
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255 - m_nSubNumber);	// �E�㒸�_�̐F	�����x255
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255 - m_nSubNumber);	// �������_�̐F	�����x255
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255 - m_nSubNumber);	// �E�����_�̐F	�����x255

	// ���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();
}

//=============================================================================
// �����̏�����
//=============================================================================
void CEnemy::TransparentInit(void)
{
	if (m_Etype == ENEMY_TYPE_FOLLOW)
	{
		LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

		// ���_����ݒ�
		VERTEX_2D *pVtx;

		// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 0);	// ���㒸�_�̐F	�����x255
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 0);	// �E�㒸�_�̐F	�����x255
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 0);	// �������_�̐F	�����x255
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 0);	// �E�����_�̐F	�����x255

		// ���_�o�b�t�@���A�����b�N����
		pVtxBuff->Unlock();
	}
}
