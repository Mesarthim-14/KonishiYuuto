//=============================================================================
//
// ���@�Ǐ]�e��łG�l�~�[�N���X [enemy_current.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "enemy_current.h"
#include "game.h"
#include "player.h"
#include "bullet.h"
#include "texture.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define CURRENT_ENEMY_LIFE				(8)					// ���@�擾�e��łG�̗̑�
#define CURRENT_NUM_BULLET				(9)					// ���@�擾�e�̐�
#define CURRENT_COUNTER_BULLET_NUM		(10)				// ���@�擾�e��łG�̃J�E���^�[�e�̐�
#define CURRENT_MOVE					(1.5f)				// ���@�擾�G�̑���
#define CURRENT_BULLET_AMPLITUDE_X		(5)					// ���@�擾�e�̉��̐U�ꕝ
#define CURRENT_BULLET_AMPLITUDE_Y		(5)					// ���@�擾�e�̏c�̐U�ꕝ
#define CURRENT_FLAG_POS_Y				(50.0f)				// �����t���O�ʒu
#define CURRENT_MOVE_Y					(7.0f)				// ���@�擾�e��łG�̈ړ���
#define CURRENT_ACCELERATION_SPEED		(0.4f)				// ���@�擾�e��łG�̉�����
#define CURRENT_DECELERATION_SPEED		(0.25f)				// ���@�擾�e��łG�̌�����
#define CURRENT_SPEED_CHANGE_FLAME		(5)					// �X�s�[�h�`�F���W�̃t���[��
#define CURRENT_RETURN_FLAME			(200)				// ���@�擾�e��łG�̖߂��Ă����t���[��
#define CURRENT_LAPSE_FLAME	(CURRENT_RETURN_FLAME+50)		// ���@�擾�e��łG�̓G�̏��ł̃t���[��
#define CONTINUOUS_INTERVAL				(7)					// ���@�擾�e�̊Ԋu
#define CURRENT_FIRST_BULLET_INTERVAL	(50)				// ���@�擾�e�̊Ԋu
#define TARGET_POS_AMPLITUDE			(1)					// �W�I�̍��W�U�ꕝ
#define CURRENT_BULLET_INTERBAL			(50000.0f)			// ���̒e�܂ł̊Ԋu
#define CURRENT_BULLET_INTER			(50000)				// ���̒e�܂ł̊Ԋu
#define THROUGH_BULLET_RANDOM_INTERVAL	(50)				// �����_�����l
#define THROUGH_BULLET_TIME				(35.0f)				// �e�̔���

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemyCurrent::CEnemyCurrent(TYPE Priority)
{
	m_nContinueInter = 0;
	m_nBulletNum = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEnemyCurrent::~CEnemyCurrent()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CEnemyCurrent * CEnemyCurrent::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size, TYPE type, COLOR_TYPE Ctype, ENEMY_TYPE Etype)
{
	// ����������
	CEnemyCurrent *pNormalEnemy = new CEnemyCurrent;

	if (pNormalEnemy != NULL)
	{
		// ����������
		pNormalEnemy->SetEnemyType(Ctype, Etype);						// �G�l�~�[�̎��
		pNormalEnemy->SetMove(D3DXVECTOR3(0.0f, CURRENT_MOVE_Y, 0.0f));	// �ړ���
		pNormalEnemy->SetLife(CURRENT_ENEMY_LIFE);						// ���C�t������
		pNormalEnemy->SetCounterBullet(CURRENT_COUNTER_BULLET_NUM);			// �J�E���^�[�e�̐ݒ�
		pNormalEnemy->Init(pos, size, type);							// ���������
		pNormalEnemy->SetBulletFlame(THROUGH_BULLET_TIME + (float)(rand() % THROUGH_BULLET_RANDOM_INTERVAL));

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
HRESULT CEnemyCurrent::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// ����������
	CEnemy::Init(pos, size, type);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CEnemyCurrent::Uninit(void)
{
	// �I������
	CEnemy::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CEnemyCurrent::Update(void)
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
void CEnemyCurrent::Draw(void)
{
	// �`�揈��
	CEnemy::Draw();
}

//=============================================================================
// �ړ��̏���
//=============================================================================
void CEnemyCurrent::MoveUpdate(void)
{
	// �ړ��ʂ̏��
	D3DXVECTOR3 move = GetMove();

	// Y���W�����ȏ�ɍs������
	if (GetMoveCounter() >= CURRENT_SPEED_CHANGE_FLAME)
	{
		// ����
		move.y -= CURRENT_DECELERATION_SPEED;
	}

	// ���ʂɂȂ�����
	if (move.y <= 0.0f && GetMoveCounter() <= CURRENT_RETURN_FLAME)
	{
		move.y = 0.0f;
	}

	if (GetMoveCounter() >= CURRENT_RETURN_FLAME)
	{
		// ��ʊO�֖߂鏈��
		move.y -= CURRENT_ACCELERATION_SPEED;
	}

	if (GetMoveCounter() >= CURRENT_LAPSE_FLAME)
	{
		// ����
		SetLife(0);
	}

	// �ړ��ʐݒ�
	SetMove(move);
}

//=============================================================================
// �e���ˏ���
//=============================================================================
void CEnemyCurrent::BulletUpdate(void)
{
	// �e�̔���
//	if (GetBulletFlame() <= 0.0f)
	{
		// ���˃t���[�����Z
		m_nContinueInter++;

		// �ݒ肵�����e�t���[���ɒB������
		if (m_nContinueInter >= CURRENT_FIRST_BULLET_INTERVAL)
		{
			// �J�E���^�[�̑���
			if (m_nContinueInter % CONTINUOUS_INTERVAL == 0)
			{
				D3DXVECTOR3 pos = GetPos();

				// �F�̎��7
				switch (GetColorType())
				{
					// �����Ƃ�
				case COLOR_TYPE_WHITE:
				{
					// ���݂̈ʒu���擾
					CPlayer *pPlayer = CGame::GetPlayer();
					D3DXVECTOR3 Target = pPlayer->GetPos();

					// ���@�擾�e�𔭎�
					CBullet::CurrentAttack(D3DXVECTOR3(
						pos.x + (float)(rand() % CURRENT_BULLET_AMPLITUDE_X - rand() % CURRENT_BULLET_AMPLITUDE_X),
						pos.y + 40.0f + (float)(rand() % CURRENT_BULLET_AMPLITUDE_Y - rand() % CURRENT_BULLET_AMPLITUDE_Y), 0.0f),
						D3DXVECTOR3(Target.x + (float)(rand() % TARGET_POS_AMPLITUDE - rand() % TARGET_POS_AMPLITUDE), Target.y, 0.0f),
						D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f),
						TYPE_BULLET, CBullet::BULLET_TYPE_ENEMY, CBullet::BULLET_COLOR_WHITE,
						1000);

					// �e�̃J�E���g
					m_nBulletNum++;
					break;
				}

				// �����e�̎�
				case COLOR_TYPE_BLACK:
				{
					// ���@�̍��W�擾
					CPlayer *pPlayer = CGame::GetPlayer();
					D3DXVECTOR3 Target = pPlayer->GetPos();

					// ���@�擾�e�𔭎�
					CBullet::CurrentAttack(D3DXVECTOR3(
						pos.x + (float)(rand() % CURRENT_BULLET_AMPLITUDE_X - rand() % CURRENT_BULLET_AMPLITUDE_X),
						pos.y + 40.0f + (float)(rand() % CURRENT_BULLET_AMPLITUDE_Y - rand() % CURRENT_BULLET_AMPLITUDE_Y), 0.0f),
						D3DXVECTOR3(Target.x + (float)(rand() % TARGET_POS_AMPLITUDE - rand() % TARGET_POS_AMPLITUDE), Target.y, 0.0f),
						D3DXVECTOR3(BULLET_SIZE_X, BULLET_SIZE_Y, 0.0f),
						TYPE_BULLET, CBullet::BULLET_TYPE_ENEMY, CBullet::BULLET_COLOR_BLACK,
						1000);

					// �e�̃J�E���g
					m_nBulletNum++;
					break;
				}
				}
			}

			// ���ʒe���o������
			if (m_nBulletNum >= CURRENT_NUM_BULLET)
			{
				m_nBulletNum = 0;
				m_nContinueInter = -CURRENT_BULLET_INTER;
				// �e�̔����t���[����߂�
	//			SetBulletFlame(CURRENT_BULLET_INTERBAL);
			}
		}
	}
}