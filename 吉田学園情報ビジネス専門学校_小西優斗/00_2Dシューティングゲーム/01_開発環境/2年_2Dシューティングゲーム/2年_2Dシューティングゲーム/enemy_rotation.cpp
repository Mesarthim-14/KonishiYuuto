//=============================================================================
//
// �ʏ�G�l�~�[�N���X [enemy_rotation.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "enemy_rotation.h"
#include "bullet.h"
#include "renderer.h"
#include "texture.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define ROTATION_LIFE					(5)				// ���G�̗̑�
#define ROTATION_COUNTER_BULLET_NUM		(5)				// ���G�̃J�E���^�[�e�̐�
#define ROTATION_SCALE_UP				(0.04f)			// ���G�̊g��
#define ROTATION_ADD_OMEGA_NUM			(2.0f)			// �p�x�̉��Z
#define RADIAN_RIMIT					(190.0f)		// ���a�̐���

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemyRotation::CEnemyRotation(TYPE Priority)
{
	m_fRadius = 0.0f;
	m_fAddRadius = 0.7f;
	m_fTheta = 0.0f;
	m_fOmega = 0.2f;
	m_fScale = 0.0f;
	m_fScaleNum = 0.0f;
	m_BaseSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEnemyRotation::~CEnemyRotation()
{
}

//=============================================================================
// �C���X�^���X����
//=============================================================================
CEnemyRotation * CEnemyRotation::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXVECTOR3 size,
	TYPE type, COLOR_TYPE Ctype, ENEMY_TYPE Etype,
	float fRadius, float fTheta)
{
	// ����������
	CEnemyRotation *pEnemyRotation = new CEnemyRotation;

	if (pEnemyRotation != NULL)
	{
		// ����������
		pEnemyRotation->SetEnemyType(Ctype, Etype);						// �G�̎�ސݒ�
		pEnemyRotation->SetLife(ROTATION_LIFE);							// ���C�t������
		pEnemyRotation->SetCounterBullet(ROTATION_COUNTER_BULLET_NUM);	// �J�E���^�[�e�̐ݒ�
		pEnemyRotation->SetRotation(fRadius, fTheta);					// ��]���
		pEnemyRotation->SetScaleNum(ROTATION_SCALE_UP);					// �傫���̒l�̐ݒ�
		pEnemyRotation->m_fOmega = ROTATION_ADD_OMEGA_NUM;				// �p�x�̉��Z��
		pEnemyRotation->Init(pos, D3DXVECTOR3(0.0f, 0.0f, 0.0f), type);	// ���������
		pEnemyRotation->m_BaseSize = size;

		// �F�̎��
		switch (Ctype)
		{
			// �����G�̎�
		case COLOR_TYPE_WHITE:

			// �e�N�X�`���̐ݒ�
			pEnemyRotation->BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_ENEMY_WHITE));

			break;
			// �����Ƃ�
		case COLOR_TYPE_BLACK:

			// �e�N�X�`���̐ݒ�
			pEnemyRotation->BindTexture(CTexture::GetTexture(CTexture::TEXTURE_NUM_ENEMY_BLACK));
			break;
		}
	}

	return pEnemyRotation;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CEnemyRotation::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// ����������
	CEnemy::Init(pos, size, type);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CEnemyRotation::Uninit(void)
{
	// �I������
	CEnemy::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CEnemyRotation::Update(void)
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
void CEnemyRotation::Draw(void)
{
	// �`�揈��
	CEnemy::Draw();
}

//=============================================================================
// �΂߈ړ��̏���
//=============================================================================
void CEnemyRotation::MoveUpdate(void)
{
	// ���S��ݒ�
	D3DXVECTOR3 Center = D3DXVECTOR3((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2), 0.0f);

	// �g��
	ScaleUp(m_BaseSize);

	// ���a���Z
	m_fRadius -= m_fAddRadius;

	// �p�x���Z
	m_fTheta += m_fOmega;

	if (m_fRadius <= m_fRadiusNum - RADIAN_RIMIT)
	{
		m_fAddRadius *= -1.2f;
	}

	// ���W
	SetPosition(D3DXVECTOR3(Center.x + m_fRadius * cosf(D3DXToRadian(m_fTheta)),
		Center.y + m_fRadius * sinf(D3DXToRadian(m_fTheta)), 0.0f));

}

//=============================================================================
// �e�̍X�V����
//=============================================================================
void CEnemyRotation::BulletUpdate(void)
{
}

//=============================================================================
// �p�x�̐ݒ�
//=============================================================================
void CEnemyRotation::SetRotation(float fRadius, float fTheta)
{
	m_fTheta = fTheta;
	m_fRadius = fRadius;
	m_fRadiusNum = fRadius;
}