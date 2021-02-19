//=============================================================================
//
// �X�l�[�N�G�l�~�[�N���X [enemy_snake.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "enemy_snake.h"
#include "bullet.h"
#include "texture.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define SNAKE_COUNTER_BULLET_NUM		(5)				// �G�̔����e
#define SNAKE_LIFE						(3)				// �W�O�U�O�ړ��G�̗̑�
#define SNAKE_MOVE_X					(0.7f)			// �W�O�U�O�ړ���X�ړ���
#define SNAKE_MOVE_Y					(1.5f)			// �W�O�U�O�ړ���Y�ړ���
#define SNAKE_SWITCH_TIME				(100)			// X�ړ��؂�ւ��̎���
#define SNAKE_OBLIQUE_POS_Y				(30.0f)			// �����̃t���O�ʒu


//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemySnake::CEnemySnake(TYPE Priority)
{
	m_nSwitchCounter = 0;
	m_bSnakeSwitch = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEnemySnake::~CEnemySnake()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CEnemySnake * CEnemySnake::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, TYPE type, COLOR_TYPE Ctype, ENEMY_TYPE Etype)
{
	// ����������
	CEnemySnake *pNormalEnemy = new CEnemySnake;

	if (pNormalEnemy != NULL)
	{
		// ����������
		pNormalEnemy->SetEnemyType(Ctype, Etype);								// �G�l�~�[�̎��
		pNormalEnemy->SetMove(D3DXVECTOR3(0.0f, SNAKE_MOVE_Y, 0.0f));			// �ړ���
		pNormalEnemy->SetLife(SNAKE_LIFE);								// ���C�t������
		pNormalEnemy->SetCounterBullet(SNAKE_COUNTER_BULLET_NUM);					// �J�E���^�[�e�̐ݒ�
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
HRESULT CEnemySnake::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// ����������
	CEnemy::Init(pos, size, type);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CEnemySnake::Uninit(void)
{
	// �I������
	CEnemy::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CEnemySnake::Update(void)
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
void CEnemySnake::Draw(void)
{
	// �`�揈��
	CEnemy::Draw();
}

//=============================================================================
// �΂߈ړ��̏���
//=============================================================================
void CEnemySnake::MoveUpdate(void)
{
	SetMove(GetMove());

	D3DXVECTOR3 pos = GetPos();

	// Y���W�����ȏ�ɍs������
	if (pos.y > SNAKE_OBLIQUE_POS_Y)
	{
		m_nSwitchCounter++;

		if (m_bSnakeSwitch == false)
		{
			SetMove(D3DXVECTOR3(SNAKE_MOVE_X, SNAKE_MOVE_Y, 0.0f));

			m_bSnakeSwitch = true;
		}
		if (m_nSwitchCounter % SNAKE_SWITCH_TIME == 0)
		{
			D3DXVECTOR3 move = GetMove();

			// ���]
			move.x *= -1;
			SetMove(move);
		}
	}
}

//=============================================================================
// �e�̍X�V����
//=============================================================================
void CEnemySnake::BulletUpdate(void)
{

}