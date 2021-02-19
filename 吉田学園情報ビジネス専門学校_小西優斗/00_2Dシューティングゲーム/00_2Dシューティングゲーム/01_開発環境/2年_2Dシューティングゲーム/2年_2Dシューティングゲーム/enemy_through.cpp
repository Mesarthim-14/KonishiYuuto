//=============================================================================
//
// �^�������e��łG�l�~�[�N���X [enemy_through.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "enemy_through.h"
#include "game.h"
#include "player.h"
#include "bullet.h"
#include "renderer.h"
#include "texture.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define THROUGH_ENEMY_LIFE				(7)				// �^�������e��łG�̗̑�
#define THROUGH_BULLET_NUM				(30)			// �^�������e��łG�̒e��
#define THROUGH_MOVE_X					(0.0f)			// �^�������e��łG�̈ړ���
#define THROUGH_MOVE_Y					(2.0f)			// �^�������e��łG�̈ړ���
#define THROUGH_ACCELERATION_X			(0.05f)			// �^�������e��łG�̉�����
#define THROUGH_ACCELERATION_Y			(0.04f)			// �^�������e��łG�̉�����
#define THROUGH_DECELERATION_X			(0.05f)			// �^�������e��łG�̌�����
#define THROUGH_DECELERATION_Y			(0.04f)			// �^�������e��łG�̌�����
#define THROUGH_STOP_TIME				(70)			// �^�������e��łG�̐Î~����
#define THROUGH_BULLET_SPEED_Y			(8.0f)			// �^�������e��łG�̒e�̑���
#define THROUGH_COUNTER_BULLET_NUM		(5)				// �^�������e��łG�̃J�E���^�[�e�̐�
#define COUNTINUE_BULLET_INTERVAL		(5)				// �A���e�̊Ԋu
#define THROUGH_BULLET_RANDOM_INTERVAL	(50)			// �����_���̃C���^�[�o��
#define THROUGH_BULLET_FIRST_INTERVAL	(30)			// �ŏ��̒e�̃C���^�[�o��

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemyThrough::CEnemyThrough(TYPE Priority)
{
	m_nStopCounter = 0;
	m_nContinueInter = 0;
	m_nBulletNum = 0;
	m_bTwo_Sides = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEnemyThrough::~CEnemyThrough()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CEnemyThrough * CEnemyThrough::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move,
	D3DXVECTOR3 size, TYPE type, COLOR_TYPE Ctype, ENEMY_TYPE Etype)
{
	// ����������
	CEnemyThrough *pNormalEnemy = new CEnemyThrough;

	if (pNormalEnemy != NULL)
	{
		// ����������
		pNormalEnemy->SetEnemyType(Ctype, Etype);							// �G�l�~�[�̎��
		pNormalEnemy->SetMove(D3DXVECTOR3(-0.001f, THROUGH_MOVE_Y, 0.0f));	// �ړ���
		pNormalEnemy->SetLife(THROUGH_ENEMY_LIFE);							// ���C�t������
		pNormalEnemy->SetCounterBullet(THROUGH_COUNTER_BULLET_NUM);			// �J�E���^�[�e�̐ݒ�
		pNormalEnemy->Init(pos, size, type);								// ���������
		pNormalEnemy->SetBulletFlame(THROUGH_BULLET_FIRST_INTERVAL);
	}

	// �e�N�X�`���U�蕪��
	switch (Ctype)
	{
		// �����Ƃ�
	case COLOR_TYPE_WHITE:

		// �e�N�X�`���̐ݒ�
		pNormalEnemy->BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_ENEMY_BLUE));

		break;

		// �����Ƃ�
	case COLOR_TYPE_BLACK:

		// �e�N�X�`���̐ݒ�
		pNormalEnemy->BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_ENEMY_RED));
		break;
	}

	return pNormalEnemy;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CEnemyThrough::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// ����������
	CEnemy::Init(pos, size, type);

	if (pos.x <= SCREEN_WIDTH / 2)
	{
		m_bTwo_Sides = true;
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CEnemyThrough::Uninit(void)
{
	// �I������
	CEnemy::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CEnemyThrough::Update(void)
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
void CEnemyThrough::Draw(void)
{
	// �`�揈��
	CEnemy::Draw();
}

//=============================================================================
// �ړ��̏���
//=============================================================================
void CEnemyThrough::MoveUpdate(void)
{
	if (m_bTwo_Sides == false)
	{
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 move = GetMove();

		// �o��������
		if (pos.x >= SCREEN_WIDTH / 2)
		{
			// ���̈ړ��𑝂₷
			move.x -= THROUGH_ACCELERATION_X;
			move.y += THROUGH_ACCELERATION_Y;
		}
		else
		{	// �������z������

			// �ړ������炷
			move.x += THROUGH_DECELERATION_X;
			move.y -= THROUGH_DECELERATION_Y;
		}

		if (move.x >= 0.0f)
		{
			m_nStopCounter++;
			move.x = 0.0f;
		}

		if (move.y <= 0.0f)
		{
			move.y = 0.0f;
		}

		// �Î~���Ԃ��߂�����
		if (m_nStopCounter >= THROUGH_STOP_TIME)
		{
			m_bTwo_Sides = true;
			m_nStopCounter = 0;
		}

		// �ړ��ʐݒ�
		SetMove(move);
	}
	else
	{
		D3DXVECTOR3 pos = GetPos();
		D3DXVECTOR3 move = GetMove();

		// �o��������
		if (pos.x <= SCREEN_WIDTH / 2)
		{
			// ���̈ړ��𑝂₷
			move.x += THROUGH_ACCELERATION_X;
			move.y += THROUGH_DECELERATION_Y;
		}
		else
		{
			// �������z������
			// �ړ������炷
			move.x -= THROUGH_DECELERATION_X;
			move.y -= THROUGH_DECELERATION_Y;
		}

		if (move.x <= 0.0f)
		{
			m_nStopCounter++;
			move.x = 0.0f;
		}
		if (move.y <= 0.0f)
		{
			move.y = 0.0f;
		}

		// �Î~���Ԃ��߂�����
		if (m_nStopCounter >= THROUGH_STOP_TIME)
		{
			m_bTwo_Sides = false;
			m_nStopCounter = 0;
		}

		// �ړ��ʐݒ�
		SetMove(move);
	}
}

//=============================================================================
// �e���ˏ���
//=============================================================================
void CEnemyThrough::BulletUpdate(void)
{
	// �����e�̔���
	if (GetBulletFlame() <= 0)
	{
		// ���˃t���[�����Z
		m_nContinueInter++;

		// �A���e�̔��ˊԊu
		if (m_nContinueInter % COUNTINUE_BULLET_INTERVAL == 0)
		{
			D3DXVECTOR3 pos = GetPos();

			// �F�̎��
			switch (GetColorType())
			{
				// �����Ƃ�
			case COLOR_TYPE_WHITE:
				CBullet::Create(D3DXVECTOR3(pos.x + 0.0f, pos.y + 40.0f, 0.0f),
					D3DXVECTOR3((float)(rand() % 2 - rand() % 2), THROUGH_BULLET_SPEED_Y, 0.0f),
					D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f),
					TYPE_BULLET, CBullet::BULLET_TYPE_ENEMY, CBullet::BULLET_COLOR_WHITE,
					1000);
				break;

				// �����Ƃ�
			case COLOR_TYPE_BLACK:
				CBullet::Create(D3DXVECTOR3(pos.x + 0.0f, pos.y + 40.0f, 0.0f),
					D3DXVECTOR3((float)(rand() % 2 - rand() % 2), THROUGH_BULLET_SPEED_Y, 0.0f),
					D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f),
					TYPE_BULLET, CBullet::BULLET_TYPE_ENEMY, CBullet::BULLET_COLOR_BLACK,
					1000);
				break;
			}

			// �A���e�̒e�̐�
			m_nBulletNum++;
		}

		// �w�肳�ꂽ�e���o���甭�˂��Ȃ�����
		if (m_nBulletNum >= THROUGH_BULLET_NUM)
		{
			SetBulletFlame(THROUGH_STOP_TIME + (float)(rand() % THROUGH_BULLET_RANDOM_INTERVAL));
		}
	}

}
//=============================================================================
// �^�������ȓG�̏�����
//=============================================================================
//void CEnemyThrough::InitThrough(D3DXVECTOR3 pos)
//{
//	if (pos.x <= SCREEN_WIDTH / 2)
//	{
//		m_bTwo_Sides = true;
//	}
//}