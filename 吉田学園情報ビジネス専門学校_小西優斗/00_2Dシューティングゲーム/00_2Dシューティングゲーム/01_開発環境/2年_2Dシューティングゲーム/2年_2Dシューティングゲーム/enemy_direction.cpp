//=============================================================================
//
// �����]���G�l�~�[�N���X [enemy_direction.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "enemy_direction.h"
#include "bullet.h"
#include "texture.h"
#include "player.h"
#include "game.h"
#include "renderer.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define DIRECTION_MOVE_X				(7.0f)			// �����]��������G�̈ړ���
#define DIRECTION_MOVE_Y				(8.0f)			// �����]��������G�̈ړ���
#define DIRECTION_LIFE					(1)				// �����]��������G�̗̑�
#define DIRECTION_COUNTER_BULLET_NUM	(5)				// �����]������G�̃J�E���^�[�e��
#define DIRECTION_RIGHT_NUMBER			(0)				// �E���̓G�̔ԍ�
#define DIRECTION_LEFT_NUMBER			(1)				// �����̓G�̔ԍ�

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemyDirection::CEnemyDirection(TYPE Priority)
{
	m_nDirection = -1;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEnemyDirection::~CEnemyDirection()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CEnemyDirection * CEnemyDirection::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type, 
	COLOR_TYPE Ctype, ENEMY_TYPE Etype, int nNumber)
{
	// ����������
	CEnemyDirection *pEnemyDirection = new CEnemyDirection;

	if (pEnemyDirection != NULL)
	{
		// �G�l�~�[�̏��ݒ�
		pEnemyDirection->SetSize(size);					// �T�C�Y�ݒ�
		pEnemyDirection->SetEnemyType(Ctype, Etype);	// �G�l�~�[�̃^�C�v���
		pEnemyDirection->SetMove(D3DXVECTOR3(0.0f, DIRECTION_MOVE_Y, 0.0f));						// �ړ��ʐݒ�
		pEnemyDirection->SetLife(DIRECTION_LIFE);						// ���C�t������
		pEnemyDirection->SetCounterBullet(DIRECTION_COUNTER_BULLET_NUM);					// �J�E���^�[�e�̐ݒ�
		pEnemyDirection->m_nDirection = nNumber;		// �ԍ��̐ݒ�
		pEnemyDirection->Init(pos, size, type);			// ���������

		// �e�N�X�`���U�蕪��
		switch (Ctype)
		{
			// �����Ƃ�
		case COLOR_TYPE_WHITE:

			// �e�N�X�`���̐ݒ�
			pEnemyDirection->BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_ENEMY_BLUE));

			break;
			// �����Ƃ�
		case COLOR_TYPE_BLACK:
			pEnemyDirection->BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_ENEMY_RED));

			break;
		}
	}

	return pEnemyDirection;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CEnemyDirection::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// ����������
	CEnemy::Init(pos, size, type);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CEnemyDirection::Uninit(void)
{
	// �I������
	CEnemy::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CEnemyDirection::Update(void)
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
void CEnemyDirection::Draw(void)
{
	// �`�揈��
	CEnemy::Draw();
}

//=============================================================================
// �ړ��̏���
//=============================================================================
void CEnemyDirection::MoveUpdate(void)
{
	// �v���C���[�̏����擾
	CPlayer *pPlayer = CGame::GetPlayer();

	// ���W�擾
	D3DXVECTOR3 Target = pPlayer->GetPos();		// �v���C���[�̍��W
	D3DXVECTOR3 pos = GetPos();					// �G�l�~�[��7���W

	// �v���C���[�Ɠ��������ɂȂ�����
	if (pos.y >= Target.y)
	{

		// ��ʔ�����荶�ɂ�����
		if (pos.x <= SCREEN_WIDTH / 2)
		{
			// ���Ɉړ�����
			SetMove(D3DXVECTOR3(5.0f, 0.0f, 0.0f));
		}
		else
		{
			// ���Ɉړ�����
			SetMove(D3DXVECTOR3(-5.0f, 0.0f, 0.0f));
		}
	}

	if (m_nDirection == DIRECTION_RIGHT_NUMBER)
	{
		if (pos.x >= SCREEN_WIDTH / 2)
		{
			// ����
			SetLife(0);
		}
	}
	else if (m_nDirection == DIRECTION_LEFT_NUMBER)
	{
		if (pos.x <= SCREEN_WIDTH / 2)
		{
			// ����
			SetLife(0);
		}
	}
}

//=============================================================================
// �e�̍X�V����
//=============================================================================
void CEnemyDirection::BulletUpdate(void)
{
}