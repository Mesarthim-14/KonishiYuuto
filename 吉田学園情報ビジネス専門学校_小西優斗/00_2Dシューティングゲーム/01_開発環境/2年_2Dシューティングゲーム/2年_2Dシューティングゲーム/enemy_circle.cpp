//=============================================================================
//
// �T�[�N���G�l�~�[�N���X [enemy_circle.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "enemy_circle.h"
#include "bullet.h"
#include "texture.h"
#include "ui.h"
#include "renderer.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define CIRCLE_COUNTER_BULLET_NUM		(5)				// �T�[�N���z�u�̓G�̃J�E���^�[�o���b�g��
#define CIRCLE_MOVE_Y					(4.0f)			// �T�[�N���z�u�̓G��Y���̈ړ���
#define CIRCLE_LIFE						(3)				// �T�[�N���z�u�̓G�̗̑�
#define CIRCLE_FLAME					(60)			// �T�[�N���z�u�̓G�̈ړ��ύX�t���[��

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemyCircle::CEnemyCircle(TYPE Priority)
{
	m_center = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEnemyCircle::~CEnemyCircle()
{

}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CEnemyCircle * CEnemyCircle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,
	TYPE type, COLOR_TYPE Ctype, ENEMY_TYPE Etype, float fRadius, float fTheta)
{
	// �������m��
	CEnemyCircle *pEnemyCircle = new CEnemyCircle;

	if (pEnemyCircle != NULL)
	{
		// ����������
		pEnemyCircle->SetSize(size);									// �T�C�Y�̐ݒ�
		pEnemyCircle->SetEnemyType(Ctype, Etype);						// �G�̎�ނ̏��
		pEnemyCircle->SetMove(D3DXVECTOR3(0.0f, CIRCLE_MOVE_Y, 0.0f));	// �ړ��ʐݒ�
		pEnemyCircle->SetLife(CIRCLE_LIFE);								// ���C�t������
		pEnemyCircle->SetCounterBullet(CIRCLE_COUNTER_BULLET_NUM);		// �J�E���^�[�e�̐ݒ�
		pEnemyCircle->SetRotation(fRadius, fTheta);						// ��]�̐ݒ�
		pEnemyCircle->Init(pos, size, type);							// ���������

		if (pos.x <= SCREEN_WIDTH / 2)
		{
			pEnemyCircle->m_center = D3DXVECTOR3(WALL_SIZE_X, CIRCLE_INITIAL_Y, 0.0f);
		}
		else
		{
			pEnemyCircle->m_center = D3DXVECTOR3(SCREEN_WIDTH - WALL_SIZE_X, CIRCLE_INITIAL_Y, 0.0f);
		}

		// �F�̐ݒ�
		switch (Ctype)
		{
			// �����Ƃ�
		case COLOR_TYPE_WHITE:

			// �e�N�X�`���̐ݒ�
			pEnemyCircle->BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_ENEMY_WHITE));

			break;

			// �����Ƃ�
		case COLOR_TYPE_BLACK:

			// �e�N�X�`���̐ݒ�
			pEnemyCircle->BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_ENEMY_BLACK));
			
			break;
		}
	}
	return pEnemyCircle;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CEnemyCircle::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// ����������
	CEnemy::Init(pos, size, type);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CEnemyCircle::Uninit(void)
{
	// �I������
	CEnemy::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CEnemyCircle::Update(void)
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
void CEnemyCircle::Draw(void)
{
	// �`�揈��
	CEnemy::Draw();
}

//=============================================================================
// �΂߈ړ��̏���
//=============================================================================
void CEnemyCircle::MoveUpdate(void)
{
	// ������荶��������
	if (m_center.x <= SCREEN_WIDTH / 2)
	{
		D3DXVECTOR3 move = GetMove();

		// ���]����^�C�~���O
		if (GetMoveCounter() <= CIRCLE_FLAME)
		{

			if (move.x <= 2.0f)
			{
				move.x += 0.1f;
			}
			else
			{
				move.x = 2.0f;
			}
		}
		else
		{

			if (move.x >= -2.0f)
			{
				move.x -= 0.05f;
			}
			else
			{
				move.x = -2.0f;
			}
		}

		// ���S�̈ړ�
		m_center += move;

		// �p�x���Z
		m_fTheta += m_fOmega;

		// ���W
		SetPosition(D3DXVECTOR3(m_center.x + m_fRadius * cosf(D3DXToRadian(m_fTheta)),
			m_center.y + m_fRadius * sinf(D3DXToRadian(m_fTheta)), 0.0f));

		// �ړ��ʐݒ�
		SetMove(move);
	}
	else
	{
		D3DXVECTOR3 move = GetMove();

		// ���]����^�C�~���O
		if (GetMoveCounter() <= CIRCLE_FLAME)
		{

			if (move.x >= -2.0f)
			{
				move.x -= 0.1f;
			}
			else
			{
				move.x = -2.0f;
			}
		}
		else
		{
			if (move.x <= 2.0f)
			{
				move.x += 0.05f;
			}
			else
			{
				move.x = +2.0f;
			}
		}

		// ���S�̈ړ�
		m_center += move;

		// �p�x���Z
		m_fTheta -= m_fOmega;

		// ���W
		SetPosition(D3DXVECTOR3(m_center.x + m_fRadius * cosf(D3DXToRadian(m_fTheta)),
			m_center.y + m_fRadius * sinf(D3DXToRadian(m_fTheta)), 0.0f));

		// �ړ���
		SetMove(move);
	}
}

//=============================================================================
// �e�̍X�V����
//=============================================================================
void CEnemyCircle::BulletUpdate(void)
{

}

//=============================================================================
// �p�x�̐ݒ�
//=============================================================================
void CEnemyCircle::SetRotation(float fRadius, float fTheta)
{
	m_fTheta = fTheta;
	m_fRadius = fRadius;
	m_fRadiusNum = fRadius;
}