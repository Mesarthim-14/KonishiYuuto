//=============================================================================
//
// �G�l�~�[�̏����@[enemy.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "enemy.h"
#include "renderer.h"
#include "manager.h"
#include "bullet.h"
#include "ui.h"
#include "explosion.h"
#include "light.h"
#include "player.h"
#include "effect.h"
#include "score.h"
#include "game.h"
#include "shock.h"
#include "spark.h"
#include "sound.h"
#include "texture.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define ENEMY_OUTSIDE_FLAME			(120)			// �G����ʊO�ɂ����t���[��
#define SNAKE_OUTSIDE_FLAME			(160)			// �G����ʊO�ɂ����t���[��
#define ENEMY_SCORE					(200)			// �G�l�~�[�̃X�R�A
#define ENEMY_STATE_COUNT			(1)				// �G�l�~�[�̓������t���[��

#define COUNTINUE_BULLET_INTERVAL	(5)				// �A���e�̊Ԋu

#define WARNING_COLOR_MAX			(255)			// �����x�ύX�l�̍ő吔
#define ENEMY_ATTACK_NUM			(10)			// �U����
#define MAX_SCALE_NUM				(1.0f)			// �g�嗦�̍ő�

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CEnemy::CEnemy(TYPE Priority) : CCharacter(Priority)
{
	m_center = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fBulletFlame = 0.0f;
	m_Ctype = COLOR_TYPE_NONE;
	m_Etype = ENEMY_TYPE_NONE;
	m_nCountinueInter = 0;
	m_nBulletNum = 0;
	m_nStateCnt = 0;
	m_nCounterBulletNum = 0;
	m_bSnakeSwitch = false;
	m_bTwo_Sides = false;
	m_nFirstBulletFrame = 0;
	m_nThroughStopCnt = 0;
	m_pLight = NULL;
	m_nOutsideScreenCnt = 0;
	m_fThroughBulletCnt = 0.0f;
	m_fScale = 0.0f;
	m_fScaleNum = 0.0f;
	m_bRotationScale = false;
	m_nDirection = 0;
	m_bFlashFlag = false;
	m_nSubNumber = 255;
	m_nSubNum = 0;
	m_bFollowFlag = false;
	m_nEnemyCounter = 0;
	m_nMoveCounter = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEnemy::~CEnemy()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CEnemy::Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// �o���b�g�Ԋu������
//	m_fBulletFlame = BULLET_INTERVAL + (float)(rand() % BULLET_RANDOM_INTERVAL);

	// ����������
	CCharacter::Init(pos, size, type);

	// ���C�g�̐ݒ�
	SetLight();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CEnemy::Uninit(void)
{
	// 2D�|���S���I������
	CCharacter::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CEnemy::Update(void)
{
	// �o���b�g�̃t���[��
	m_fBulletFlame--;

	// �ړ����̃J�E���^�[
	m_nMoveCounter++;

	// �L�����N�^�[�X�V����
	CCharacter::Update();

	// ��Ԃ̍X�V����
	UpdateState();

	if (m_pLight != NULL)
	{
		D3DXVECTOR3 pos = GetPos();

		// ���C�g�̈ړ�
		m_pLight->SetPosition(pos);
	}

	// �v���C���[�Ƃ̓����蔻��
	Collision();

	D3DXVECTOR3 pos = GetPos();

	SetPosition(pos);

	// �G����ʊO�ɏo����
	if (pos.x < 0.0f ||
		pos.x > SCREEN_WIDTH - WALL_SIZE_X ||
		pos.y < 0.0f ||
		pos.y > SCREEN_HEIGHT)
	{
		// ��ʊO���Z
		m_nOutsideScreenCnt++;
	}

	if (m_Etype != ENEMY_TYPE_SNAKE)
	{
		// ��ʊO��100�t���[��������
		if (m_nOutsideScreenCnt >= ENEMY_OUTSIDE_FLAME)
		{
			// ���C�g�̏I������
			if (m_pLight != NULL)
			{
				m_pLight->Uninit();
				m_pLight = NULL;
			}

			// �I������
			Uninit();
		}
	}
	else
	{
		// ��ʊO��100�t���[��������
		if (m_nOutsideScreenCnt >= SNAKE_OUTSIDE_FLAME)
		{
			// ���C�g�̏I������
			if (m_pLight != NULL)
			{
				m_pLight->Uninit();
				m_pLight = NULL;
			}

			// �I������
			Uninit();
		}
	}

	// ���񂾂Ƃ�
	Death();
}

//=============================================================================
// �`�揈��
//=============================================================================
void CEnemy::Draw(void)
{
	// �L�����N�^�[�`�揈��
	CCharacter::Draw();
}

//=============================================================================
// �G�l�~�[�q�b�g��
//=============================================================================
void CEnemy::Death(void)
{
	D3DXVECTOR3 pos = GetPos();

	int nLife = GetLife();

	// ���C�t��0�ɂȂ�����
	if (nLife <= 0)
	{
		// �T�E���h�ݒ�
		CSound *pSound = NULL;
		pSound = CManager::GetSound();
		pSound->Play(CSound::SOUND_LABEL_EXPLOSION);

		// �F�̎��
		switch (m_Ctype)
		{
			// �����Ƃ�
		case COLOR_TYPE_WHITE:

			for (int nCount = 0; nCount < SPARK_NUM; nCount++)
			{
				// �ΉԂ̏���
				CSpark::Create(pos,
					D3DXVECTOR3(SPARK_SIZE_X, SPARK_SIZE_Y, 0.0f),
					TYPE_EFFECT, SPARK_ANGLE, SPARK_BASE_ANGLE, SPARK_DISTANCE, SPARK_LIFE);
			}
			break;

			// �����Ƃ�
		case COLOR_TYPE_BLACK:

			for (int nCount = 0; nCount < SPARK_NUM; nCount++)
			{
				// �ΉԂ̏���
				CSpark::Create(pos,
					D3DXVECTOR3(SPARK_SIZE_X, SPARK_SIZE_Y, 0.0f),
					TYPE_EFFECT, SPARK_ANGLE, SPARK_BASE_ANGLE, SPARK_DISTANCE, SPARK_LIFE);
			}
			break;

		default:
			break;
		}

		// �X�R�A�����Z
		CScore *pScore = CGame::GetScore();
		pScore->SetScore(ENEMY_SCORE);

		CScene *pScene = NULL;

		if (pScene == NULL)
		{
			// �V�[�����擾
			pScene = CScene::GetTop(TYPE_BULLET);

			while (pScene)
			{
				CScene *pSceneNext = pScene->GetNext();

				TYPE type = pScene->GetType();

				// �������̃L���X�g
				CScene2D *pScene2D = (CScene2D*)pScene;

				if (pScene2D != NULL)
				{
					// �e�̐F�擾
					CBullet *pBullet = (CBullet*)pScene2D;
					CBullet::BULLET_COLOR Ctype = pBullet->GetCtype();

					// �F�̎��
					switch (Ctype)
					{
						// �����Ƃ�
					case CBullet::BULLET_COLOR_BLACK:

						// ����������������
						if (m_Ctype == COLOR_TYPE_BLACK)
						{
							// �J�E���^�[�e����
							CBullet::CounterAttack(
								pos, D3DXVECTOR3(COUNTER_BULLET_SIZE_X, COUNTER_BULLET_SIZE_Y, 0.0f),
								TYPE_BULLET, CBullet::BULLET_TYPE_ENEMY,
								CBullet::BULLET_COLOR_BLACK, CBullet::BULLET_CATEGORY_COUNTER,
								1000, m_nCounterBulletNum);
						}
						break;

						// �����Ƃ�
					case CBullet::BULLET_COLOR_WHITE:

						// ����������������
						if (m_Ctype == COLOR_TYPE_WHITE)
						{
							// �J�E���^�[�e����
							CBullet::CounterAttack(
								pos, D3DXVECTOR3(COUNTER_BULLET_SIZE_X, COUNTER_BULLET_SIZE_Y, 0.0f),
								TYPE_BULLET, CBullet::BULLET_TYPE_ENEMY,
								CBullet::BULLET_COLOR_WHITE, CBullet::BULLET_CATEGORY_COUNTER,
								1000, m_nCounterBulletNum);
						}
						break;
					}
					break;

				}
				pScene = pSceneNext;
			}
		}

		if (m_pLight != NULL)
		{
			// ���C�g�폜
			m_pLight->Uninit();
		}

		// �G�l�~�[�폜
		Uninit();

	}
}

//=============================================================================
// ��Ԃ̍X�V
//=============================================================================
void CEnemy::UpdateState(void)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff = GetVtxBuff();

	// ���_����ݒ�
	VERTEX_2D *pVtx;

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	STATE state = GetState();

	// �G�l�~�[�̏��
	switch (state)
	{
		// �ʏ펞
	case STATE_NORMAL:
		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// ���㒸�_�̐F	�����x255
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// �E�㒸�_�̐F	�����x255
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// �������_�̐F	�����x255
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);	// �E�����_�̐F	�����x255
		break;

		// �_���[�W��
	case STATE_DAMAGE:

		// ��ԃJ�E���^�[
		m_nStateCnt++;

		// ���_�J���[�̐ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 100);	// ���㒸�_�̐F	�����x255
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 100);	// �E�㒸�_�̐F	�����x255
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 100);	// �������_�̐F	�����x255
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 100);	// �E�����_�̐F	�����x255

		// ���Œʏ��Ԃɖ߂�
		if (m_nStateCnt >= ENEMY_STATE_COUNT)
		{
			SetState(STATE_NORMAL);
			m_nStateCnt = 0;
		}
		break;
	}

	// ���_�o�b�t�@���A�����b�N����
	pVtxBuff->Unlock();

}

//=============================================================================
// ���e�̔����t���[���ݒ�
//=============================================================================
void CEnemy::SetFirstBulletTime(int nTime)
{
	m_nFirstBulletFrame = nTime;
}

//=============================================================================
// ���C�g�̐ݒ�
//=============================================================================
void CEnemy::SetLight(void)
{
	if (m_pLight == NULL)
	{
		// �e�N�X�`���U�蕪��
		switch (m_Ctype)
		{
			// �����Ƃ�
		case COLOR_TYPE_WHITE:
			// ���̐���
			m_pLight = CLight::Create(GetPos(), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(LIGHT_SIZE_X, LIGHT_SIZE_Y, 0.0f),
				TYPE_LIGHT, CLight::LIGHT_TYPE_WHITE);
			break;

			// �����Ƃ�
		case COLOR_TYPE_BLACK:

			// ���̐���
			m_pLight = CLight::Create(GetPos(), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				D3DXVECTOR3(LIGHT_SIZE_X, LIGHT_SIZE_Y, 0.0f),
				TYPE_LIGHT, CLight::LIGHT_TYPE_BLACK);
			break;

		}
	}
}

//=============================================================================
// �e�̔��˃t���[���ݒ�
//=============================================================================
void CEnemy::SetBulletFlame(float fBulletFlame)
{
	m_fBulletFlame = fBulletFlame;
}

//=============================================================================
// �ړ����̃t���[���J�E���^�[
//=============================================================================
void CEnemy::SetMoveCounter(int nCounter)
{
	m_nMoveCounter = nCounter;
}

//=============================================================================
// �g��ʐݒ�
//=============================================================================
void CEnemy::SetScaleNum(float fScaleNum)
{
	m_fScaleNum = fScaleNum;
}

//=============================================================================
// �G�l�~�[�̃^�C�v�ݒ�
//=============================================================================
void CEnemy::SetEnemyType(COLOR_TYPE Ctype, ENEMY_TYPE Etype)
{
	m_Ctype = Ctype;
	m_Etype = Etype;
}

void CEnemy::SetCounterBullet(int nCounter)
{
	m_nCounterBulletNum = nCounter;
}

////=============================================================================
//// ���i�̓G�̍X�V
////=============================================================================
//void CEnemy::ThroughUpdate(void)
//{
////	m_fThroughBulletCnt--;
////
////	// �����e�̔���
////	if (m_fThroughBulletCnt <= 0)
////	{
////		ContinuousBullet(THROUGH_BULLET_NUM);
////	}
////
////	if (m_bTwo_Sides == false)
////	{
////		D3DXVECTOR3 pos = GetPos();
////		D3DXVECTOR3 move = GetMove();
////
////		// �o��������
////		if (pos.x >= SCREEN_WIDTH / 2)
////		{
////			// ���̈ړ��𑝂₷
////			move.x -= THROUGH_ACCELERATION_X;
////			move.y += THROUGH_ACCELERATION_Y;
////		}
////		else
////		{	// �������z������
////
////			// �ړ������炷
////			move.x += THROUGH_DECELERATION_X;
////			move.y -= THROUGH_DECELERATION_Y;
////		}
////
////		if (move.x >= 0.0f)
////		{
////			m_nThroughStopCnt++;
////			move.x = 0.0f;
////		}
////
////		if (move.y <= 0.0f)
////		{
////			move.y = 0.0f;
////		}
////
////		// �Î~���Ԃ��߂�����
////		if (m_nThroughStopCnt >= THROUGH_STOP_TIME)
////		{
////			m_bTwo_Sides = true;
////			m_nThroughStopCnt = 0;
////		}
////
////		// �ړ��ʐݒ�
////		SetMove(move);
////	}
////	else
////	{
////		D3DXVECTOR3 pos = GetPos();
////		D3DXVECTOR3 move = GetMove();
////
////		// �o��������
////		if (pos.x <= SCREEN_WIDTH / 2)
////		{
////			// ���̈ړ��𑝂₷
////			move.x += THROUGH_ACCELERATION_X;
////			move.y += THROUGH_DECELERATION_Y;
////		}
////		else
////		{	
////			// �������z������
////			// �ړ������炷
////			move.x -= THROUGH_DECELERATION_X;
////			move.y -= THROUGH_DECELERATION_Y;
////		}
////
////		if (move.x <= 0.0f)
////		{
////			m_nThroughStopCnt++;
////			move.x = 0.0f;
////		}
////		if (move.y <= 0.0f)
////		{
////			move.y = 0.0f;
////		}
////
////		// �Î~���Ԃ��߂�����
////		if (m_nThroughStopCnt >= THROUGH_STOP_TIME)
////		{
////			m_bTwo_Sides = false;
////			m_nThroughStopCnt = 0;
////		}
////
////		// �ړ��ʐݒ�
////		SetMove(move);
////	}
////
////	// �w�肳�ꂽ�e���o���甭�˃t���[����ݒ�
////	if (m_nContinueCnt >= THROUGH_BULLET_NUM)
////	{
////		m_fThroughBulletCnt = THROUGH_STOP_TIME;
////		m_nContinueCnt = 0;
////	}
//}
//
//
////=============================================================================
//// �T�[�N���z�u�̓G�̍X�V
////=============================================================================
//void CEnemy::CircleUpdate(void)
//{
////	m_nEnemyCounter++;
////
////	// ������荶��������
////	if (m_center.x <= SCREEN_WIDTH / 2)
////	{
////		D3DXVECTOR3 move = GetMove();
////
////		// ���]����^�C�~���O
////		if (m_nEnemyCounter <= CIRCLE_FLAME)
////		{
////
////			if (move.x <= 2.0f)
////			{
////				move.x += 0.1f;
////			}
////			else
////			{
////				move.x = 2.0f;
////			}
////		}
////		else
////		{
////
////			if (move.x >= -2.0f)
////			{
////				move.x -= 0.05f;
////			}
////			else
////			{
////				move.x = -2.0f;
////			}
////		}
////
////		// ���S�̈ړ�
////		m_center += move;
////
////		// �p�x���Z
////		m_fTheta += m_fOmega;
////
////		// ���W
////		SetPosition(D3DXVECTOR3(m_center.x + m_fRadius * cosf(D3DXToRadian(m_fTheta)),
////			m_center.y + m_fRadius * sinf(D3DXToRadian(m_fTheta)), 0.0f));
////
////		// �ړ��ʐݒ�
////		SetMove(move);
////	}
////	else
////	{
////		D3DXVECTOR3 move = GetMove();
////
////		// ���]����^�C�~���O
////		if (m_nEnemyCounter <= CIRCLE_FLAME)
////		{
////
////			if (move.x >= -2.0f)
////			{
////				move.x -= 0.1f;
////			}
////			else
////			{
////				move.x = -2.0f;
////			}
////		}
////		else
////		{
////			if (move.x <= 2.0f)
////			{
////				move.x += 0.05f;
////			}
////			else
////			{
////				move.x = +2.0f;
////			}
////		}
////
////		// ���S�̈ړ�
////		m_center += move;
////
////		// �p�x���Z
////		m_fTheta -= m_fOmega;
////
////		// ���W
////		SetPosition(D3DXVECTOR3(m_center.x + m_fRadius * cosf(D3DXToRadian(m_fTheta)),
////			m_center.y + m_fRadius * sinf(D3DXToRadian(m_fTheta)), 0.0f));
////
////		// �ړ���
////		SetMove(move);
////	}
//}
//
////=============================================================================
//// �����]������G�̍X�V����
////=============================================================================
//void CEnemy::DirectionUpdate(void)
//{
////	// �v���C���[�̏����擾
////	CPlayer *pPlayer = CGame::GetPlayer();
////	
////	// ���W�擾
////	D3DXVECTOR3 Target = pPlayer->GetPos();		// �v���C���[�̍��W
////	D3DXVECTOR3 pos = GetPos();					// �G�l�~�[��7���W
////
////	// �v���C���[�Ɠ��������ɂȂ�����
////	if (pos.y >= Target.y)
////	{
////
////		// ��ʔ�����荶�ɂ�����
////		if (pos.x <= SCREEN_WIDTH /2)
////		{
////			// ���Ɉړ�����
////			SetMove(D3DXVECTOR3(5.0f, 0.0f, 0.0f));
////		}
////		else
////		{
////			// ���Ɉړ�����
////			SetMove(D3DXVECTOR3(-5.0f, 0.0f, 0.0f));
////		}
////	}
////
////	if (m_nDirection == 0)
////	{
////		if (pos.x >= SCREEN_WIDTH / 2)
////		{
////			// ����
////			SetLife(0);
////		}
////	}
////	else if (m_nDirection == 1)
////	{
////		if (pos.x <= SCREEN_WIDTH / 2)
////		{
////			// ����
////			SetLife(0);
////		}
////	}
//}
//
////=============================================================================
//// �Ǐ]���Ă���G
////=============================================================================
//void CEnemy::FollowUpdate(void)
//{
////	if (m_bFlashFlag == false)
////	{
////		// �����x�̕ύX
////		Appearance();
////	}
////
////	if (m_bFollowFlag == false)
////	{
////		m_nEnemyCounter++;
////
////		if (m_nEnemyCounter >= 50)
////		{
////			m_bFollowFlag = true;
////
////			// �v���C���[�����擾
////			CPlayer *pPlayer = CGame::GetPlayer();
////			D3DXVECTOR3 Ppos = pPlayer->GetPos();
////			D3DXVECTOR3 pos = GetPos();
////
////			//���@���擾����
////			float fPposx = Ppos.x, fPposy = Ppos.y;		// ���@�̍��W
////			float fEposx = pos.x, fEposy = pos.y;	// �G�̍��W
////			float fAngle;								// �p�x
////
////			//�p�x�����߂�
////			fAngle = atan2f((fEposx - fPposx), (fEposy - fPposy));
////
////			// �����ȓG�̈ړ�
////			D3DXVECTOR3 FollowMove = D3DXVECTOR3(
////				(sinf(fAngle)*-FOLLOW_MOVE_X),
////				cosf(fAngle)*-FOLLOW_MOVE_Y, 0.0f);
////
////			// �ړ��ʂ̐ݒ�
////			SetMove(FollowMove);
////		}
////	}
//}

//====================================================================
// �g��
//====================================================================
void CEnemy::ScaleUp(D3DXVECTOR3 BaseSize)
{
	if (m_fScale <= MAX_SCALE_NUM)
	{
		// �k���ʂ����Z
		m_fScale += m_fScaleNum;

		D3DXVECTOR3 size = GetSize();

		// �T�C�Y�̕ύX
		D3DXVECTOR3 ScaleSize = D3DXVECTOR3(BaseSize.x * m_fScale, BaseSize.y * m_fScale, 0.0f);

		// Scene2D�ɃT�C�Y��n��
 		SetScaleSize(ScaleSize);
	}
	else
	{
		m_fScale = MAX_SCALE_NUM;
		m_bRotationScale = true;
	}
}

//=============================================================================
// �����蔻��
//=============================================================================
bool CEnemy::Collision(void)
{
	// �v���C���[�̏����󂯎��
	CPlayer *pPlayer = CGame::GetPlayer();

	// ���W���󂯎��
	D3DXVECTOR3 Target = pPlayer->GetPos();

	// ���g�̏��󂯎��
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 size = GetSize();

	if (Target.x - DECISION_PLAYER_SIZE_X / 2 < pos.x + size.x / 2 &&
		Target.x + DECISION_PLAYER_SIZE_X / 2 > pos.x - size.x / 2 &&
		Target.y - DECISION_PLAYER_SIZE_Y / 2 < pos.y + size.y / 2 &&
		Target.y + DECISION_PLAYER_SIZE_Y / 2 > pos.y - size.y / 2)
	{
		// �����蔻�菈��
		if (m_Etype != ENEMY_TYPE_ROTATION)
		{
			// ������ԈȊO
			if (pPlayer->GetState() != STATE_REVIVE)
			{
				// �v���C���[�Ƀ_���[�W��^����
				pPlayer->HitDamage(ENEMY_ATTACK_NUM);
			}
		}
		else
		{
			// ������ԈȊO
			if (pPlayer->GetState() != STATE_REVIVE)
			{

				if (m_bRotationScale == true)
				{
					// �v���C���[�Ƀ_���[�W��^����
					pPlayer->HitDamage(ENEMY_ATTACK_NUM);
				}
			}
		}

		return true;
	}

	return false;
}