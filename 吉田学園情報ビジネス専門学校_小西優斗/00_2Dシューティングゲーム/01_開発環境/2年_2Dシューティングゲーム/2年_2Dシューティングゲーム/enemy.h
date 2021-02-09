#ifndef _ENEMY_H_
#define _ENEMY_H_
//=============================================================================
//
// �G�l�~�[�N���X�w�b�_�[ [enemy.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "character.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_ENEMY				(256)			// �G�̍ő吔
#define ENEMY_SIZE_X			(50)			// �G�l�~�[�̃T�C�Y
#define ENEMY_SIZE_Y			(50)			// �G�l�~�[�̃T�C�Y
#define ENEMY_NORMAL_SIZE_X		(60)			// �G�̉���
#define ENEMY_NORMAL_SIZE_Y		(60)			// �G�̏c��
#define ENEMY_CURRENT_SIZE_X	(70)			// ���@�擾�e��łG�̑傫��
#define ENEMY_CURRENT_SIZE_Y	(70)			// ���@�擾�e��łG�̑傫��
#define ENEMY_SNAKE_SIZE_X		(40)			// �W�O�U�O�G
#define ENEMY_SNAKE_SIZE_Y		(40)			// �W�O�U�O�G
#define ENEMY_THROUGH_SIZE_X	(70)			// �^�������e��łG�̃T�C�Y
#define ENEMY_THROUGH_SIZE_Y	(70)			// �^�������e��łG�̃T�C�Y
#define ENEMY_DIRECTION_SIZE_X	(50)			// �����]������G�̃T�C�Y
#define ENEMY_DIRECTION_SIZE_Y	(50)			// �����]������G�̃T�C�Y
#define ENEMY_FOLLOW_SIZE_X		(50)			// �^�������e��łG�̃T�C�Y
#define ENEMY_FOLLOW_SIZE_Y		(50)			// �^�������e��łG�̃T�C�Y

#define INSIDE_ROTATION_RADIUS	(400)			// ���G�̊O���̔��a
#define OUTSIDE_ROTATION_RADIUS	(325)			// ���G�̓����̔��a

#define CIRCLE_ENEMY_NUM		(5)				// �T�[�N���z�u�̓G�̐�
#define CIRCLE_ANGLE			(-45.0f)		// �T�[�N���z�u�̓G�̊p�x
#define CIRCLE_MAX_ANGLE		(150)			// �G�̏o���̃T�[�N���̊p�x
#define CIRCLE_DISTANCE			(210.0f)		// �T�[�N���̋���
#define CIRCLE_INITIAL_Y		(-125.0f)		// �����̍��W

//=============================================================================
// �O���錾
//=============================================================================
class CLight;

//=============================================================================
// �G�l�~�[�N���X
//=============================================================================
class CEnemy : public CCharacter
{
public:
	// �G�̐F
	typedef enum
	{
		COLOR_TYPE_NONE = 0,	// �����l
		COLOR_TYPE_WHITE,		// �����G
		COLOR_TYPE_BLACK,		// �Ԃ��G
		COLOR_TYPE_MAX
	}COLOR_TYPE;

	// �G�̎��
	typedef enum
	{
		ENEMY_TYPE_NONE = 0,		// �����l
		ENEMY_TYPE_NORMAL,			// �ʏ�G
		ENEMY_TYPE_CURRENT,			// ���@�擾�e��łG
		ENEMY_TYPE_SNAKE,			// �W�O�U�O�ړ�
		ENEMY_TYPE_THROUGH,			// �^�������e��łG
		ENEMY_TYPE_ROTATION,		// ����Ă���G
		ENEMY_TYPE_CIRCLE,			// �T�[�N���z�u�̓G
		ENEMY_TYPE_DIRECTION,		// �����]������G
		ENEMY_TYPE_FOLLOW,			// �Ǐ]����G
		ENEMY_TYPE_MAX
	}ENEMY_TYPE;

	CEnemy(TYPE Priority = TYPE_ENEMY);	// �R���X�g���N�^
	~CEnemy();							// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);		// ����������
	void Uninit(void);												// �I������
	void Update(void);												// �X�V����
	void Draw(void);												// �`�揈��
	void Death(void);												// ���񂾂Ƃ��̏���
	virtual void UpdateState(void);									// ��Ԃ̍X�V����

	bool Collision(void);											// �����蔻��
	void InitThrough(D3DXVECTOR3 pos);								// �����ʒu�擾
	void TransparentInit(void);										// �����̏�����

	void NormalBullet(void);										// �ʏ�e
	void ContinuousBullet(int nBulletNum);							// �A���e
	void ScaleUp(D3DXVECTOR3 BaseSize);								// �g��
	void Appearance(void);											// ��������o��

	// Set�֐�
	void SetEnemyType(COLOR_TYPE Ctype, ENEMY_TYPE Etype);			// ���Z�b�g
	void SetCounterBullet(int nCounter);									// �J�E���^�[�o���b�g�̐ݒ�
	void SetFirstBulletTime(int nTime);								// ���e�̔����t���[���ݒ�
	void SetLight(void);											// ���C�g�̐ݒ�
	void SetBulletFlame(float fBulletFlame);						// �e�̔��˃t���[���ݒ�
	void SetMoveCounter(int nCounter);								// �ړ����̃t���[���J�E���^�[
	void SetScaleNum(float fScaleNum);								// �g��ʐݒ�

	// Get�֐�
	COLOR_TYPE GetColorType(void) { return m_Ctype; }			// �J���[�^�C�v�̏��
	float GetBulletFlame(void) { return m_fBulletFlame; }		// �e�̔��˃t���[�����
	int GetMoveCounter(void) { return m_nMoveCounter; }			// �ړ����̃J�E���^�[

	// �������z�֐�
	virtual void MoveUpdate() = 0;											// �ړ��̍X�V
	virtual void BulletUpdate() = 0;										// �e�̔��ˍX�V����

private:
	CLight *m_pLight;						// ���C�g�̃|�C���^
	D3DXVECTOR3 m_center;					// �Z���^�[
	COLOR_TYPE m_Ctype;						// �J���[�̎��
	ENEMY_TYPE m_Etype;						// �G�l�~�[�̎��
	float m_fBulletFlame;					// �o���b�g�Ԋu�̃J�E���^�[
	int m_nMoveCounter;						// �ړ����Ɏg�p����J�E���^�[
	int m_nEnemyCounter;					// �G�l�~�[����̃J�E���^�[
	int m_nStateCnt;						// �G�l�~�[�̏�ԃJ�E���^�[
	int m_nCountinueInter;					// �A���e�̊Ԋu
	int m_nContinueCnt;						// �A���e�̃J�E���g
	int m_nBulletNum;						// �e�̐�
	int m_nCounterBulletNum;				// �J�E���^�[�e�̐ݒ�
	int m_nFirstBulletFrame;				// ���e�̃t���[��
	int m_nThroughStopCnt;					// �~�܂��Ă���t���[��
	int m_nOutsideScreenCnt;				// �X�N���[���O�̃J�E���g
	int m_nDirection;						// �����]���̓G�̃i���o�[
	int m_nSubNumber;						// �e�N�X�`���̓����x�ύX�ϐ�
	int m_nSubNum;							// �����x�̐��l
	float m_fScale;							// �k���p�ϐ�
	float m_fScaleNum;						// �k����
	float m_fThroughBulletCnt;				// �^��������΂��G�̃o���b�g�J�E���g
	bool m_bSnakeSwitch;					// �W�O�U�O�ړ��̃t���O
	bool m_bTwo_Sides;						// �^�������e��łG�̃t���O
	bool m_bRotationScale;					// ���[�e�[�V�����̊g��t���O
	bool m_bFlashFlag;						// �t���b�V���̃t���O
	bool m_bFollowFlag;						// �Ǐ]�̓G�̃t���O

};

#endif