//=============================================================================
//
// �ʏ�G�l�~�[�N���X [enemy_normal.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "enemy_normal.h"
#include "bullet.h"
#include "texture.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define ENEMY_NORMAL_LIFE				(4)					// �ʏ�̃G�l�~�[�̃��C�t
#define OBLIQUE_MOVE_Y					(3.0f)				// �c�̑���
#define NORMAL_COUNTER_BULLET_NUM		(5)					// �G�̔����e
#define OBLIQUE_POS_Y					(30.0f)				// �����̃t���O�ʒu
#define OBLIQUE_ACCELERATION_X			(0.04f)				// X���W�̉�����
#define OBLIQUE_ACCELERATION_Y			(0.003f)			// Y���W�̉�����
#define OBLIQUE_MOVE_LIMIT				(7.0f)				// �����̐���
#define NORMAL_BULLET_INTERVAL			(35.0f)				// ���ˊԊu���
#define NORMAL_BULLET_RANDOM_INTER		(50)				// ���ˊԊu�̃����_��

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemyNormal::CEnemyNormal(TYPE Priority)
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEnemyNormal::~CEnemyNormal()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CEnemyNormal * CEnemyNormal::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, TYPE type, COLOR_TYPE Ctype, ENEMY_TYPE Etype)
{
	// ����������
	CEnemyNormal *pNormalEnemy = new CEnemyNormal;

	if (pNormalEnemy != NULL)
	{
		// ����������
		pNormalEnemy->SetEnemyType(Ctype, Etype);								// �G�l�~�[�̎��
		pNormalEnemy->SetMove(D3DXVECTOR3(0.0f, OBLIQUE_MOVE_Y, 0.0f));			// �ړ���
		pNormalEnemy->SetLife(ENEMY_NORMAL_LIFE);								// ���C�t������
		pNormalEnemy->SetCounterBullet(NORMAL_COUNTER_BULLET_NUM);					// �J�E���^�[�e�̐ݒ�
	//	pNormalEnemy->SetBulletFlame(NORMAL_BULLET_INTERVAL + (float)(rand() % NORMAL_BULLET_RANDOM_INTER));
		pNormalEnemy->Init(pos, size, type);									// ���������
	}

	// �e�N�X�`���U�蕪��
	switch (Ctype)
	{
		// �����Ƃ�
	case COLOR_TYPE_WHITE:

		// �e�N�X�`���̐ݒ�
		pNormalEnemy->BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_ENEMY_WHITE));

		break;

		// �����Ƃ�
	case COLOR_TYPE_BLACK:

		// �e�N�X�`���̐ݒ�
		pNormalEnemy->BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_ENEMY_BLACK));
		break;
	}

	return pNormalEnemy;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CEnemyNormal::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// ����������
	CEnemy::Init(pos, size, type);
	
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CEnemyNormal::Uninit(void)
{
	// �I������
	CEnemy::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CEnemyNormal::Update(void)
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
void CEnemyNormal::Draw(void)
{
	// �`�揈��
	CEnemy::Draw();
}

//=============================================================================
// �΂߈ړ��̏���
//=============================================================================
void CEnemyNormal::MoveUpdate(void)
{
	// �ړ��ʂ̏��
	D3DXVECTOR3 move = GetMove();
	D3DXVECTOR3 pos = GetPos();

	switch (GetColorType())
	{
		// �����Ƃ�
	case COLOR_TYPE_WHITE:

		// Y���W�����ȏ�ɍs������
		if (pos.y > OBLIQUE_POS_Y)
		{
			// ����������
			move.x += OBLIQUE_ACCELERATION_X;
			move.y += OBLIQUE_ACCELERATION_Y;

		}
		break;

		// �����Ƃ�
	case COLOR_TYPE_BLACK:

		// Y���W�����ȏ�ɍs������
		if (pos.y > OBLIQUE_POS_Y)
		{
			// ����������
			move.x -= OBLIQUE_ACCELERATION_X;
			move.y += OBLIQUE_ACCELERATION_Y;

		}
		break;
	}

	// ����ȏ�ړ��ʂ𑝂₳�Ȃ�
	if (move.x >= OBLIQUE_MOVE_LIMIT)
	{
		move.x = OBLIQUE_MOVE_LIMIT;
	}
	if (move.y >= OBLIQUE_MOVE_LIMIT)
	{
		move.y = OBLIQUE_MOVE_LIMIT;
	}

	// �ړ��ʐݒ�
	SetMove(move);
}

//=============================================================================
// �e�̍X�V����
//=============================================================================
void CEnemyNormal::BulletUpdate(void)
{
}