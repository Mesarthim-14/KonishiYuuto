#ifndef _PLAYER_H_
#define _PLAYER_H_
//=============================================================================
//
// �v���C���[�N���X�w�b�_�[ [player.h]
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
#define DECISION_PLAYER_SIZE_X	(15)		// �����蔻��
#define DECISION_PLAYER_SIZE_Y	(15)		// �����蔻��
#define PLAYER_REMAIN_NUM		(2)			// �c�@
#define PLAYER_SHOT_POS_X		(11.0f)		// �e�̏o���ʒu
#define PLAYER_SHOT_POS_Y		(30.0f)		// �e�̏o���ʒu

//=============================================================================
// �O���錾
//=============================================================================
class CShield;
class CGage;
class CLaser;
class CBombUi;

//=============================================================================
// �v���C���[�N���X
//=============================================================================
class CPlayer : public CCharacter
{
public:
	CPlayer();			// �R���X�g���N�^
	~CPlayer();			// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);				// ����������
	void Uninit(void);														// �I������
	void Update(void);														// �X�V����
	void Draw(void);														// �`�揈��

	// static�֐�
	static CPlayer * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);	// �|���S������
	
	// �����o�֐�
	void PlayerControl(void);												// �v���C���[����
	void Resurrection(void);												// ����
	void UpdateState(void);													// �v���C���[��ԍX�V
	bool BombCollision(void);												// �{���̓����蔻��
	void Death(void);														// ���񂾂Ƃ��̏���

	// Get�֐�
	bool GetUseLaser(void);													// ���[�U�[�̏��
	bool GetShildInfo(void);												// �V�[���h�̏��
	CGage *GetGage(void);													// ���[�U�[�Q�[�W
	CLaser *GetLaser(void);													// ���[�U�[�̏��

private:
	int m_StateCount;						// �v���C���[�̏�ԃJ�E���^�[
	int m_BulletState;						// �o���b�g�Ԋu�̃J�E���^�[
	int m_nStock;							// �X�g�b�N
	int m_nResurrectionCnt;					// �����t���[��
	int m_nLaserFlame;						// ���[�U�[�̃J�E���g
	int m_nLaserCounter;					// ���[�U�[�̐؂�ւ��J�E���^�[
	int m_nBombFlame;						// �{���̓����蔻��t���[��
	int m_nBombNum;							// �{���ɓ��������G�̃i���o�[
	int m_nBombCount;						// �{���̐�
	bool m_bShildInfo;						// �V�[���h�̏��
	bool m_bShildScaleInfo;					// �V�[���h�̊g���
	bool m_bPlayerDraw;						// �v���C���[�̕\��
	bool m_bUseLaser;						// ���[�U�[���g���Ă��邩
	bool m_bPressInfo;						// �������Ƃ��̏��
	bool m_bBombUse;						// �{�����g�����Ƃ�
	CShield *m_pShield;						// �V�[���h�̃|�C���^
	CGage *m_pGage;							// �Q�[�W�̃|�C���^
	CLaser *m_pLaser;						// ���[�U�[�̃|�C���^
	CBombUi *m_pBombUi;						// �{����UI
	TYPE m_BombType;						// �{���^�C�v
};

#endif