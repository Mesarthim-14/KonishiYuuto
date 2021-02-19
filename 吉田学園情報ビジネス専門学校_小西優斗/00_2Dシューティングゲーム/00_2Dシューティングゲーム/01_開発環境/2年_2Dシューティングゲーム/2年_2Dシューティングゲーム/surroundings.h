#ifndef _SURROUNDINGS_H_
#define _SURROUNDINGS_H_
//=============================================================================
//
// ��芪���N���X�w�b�_�[	[surroundings.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "enemy.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define SURROUNDINGS_SIZE_X			(50)	// �T�C�Y
#define SURROUNDINGS_SIZE_Y			(50)	// �T�C�Y

//=============================================================================
// �O���錾
//=============================================================================
class CEnemy;
class CHpbar;

//=============================================================================
// �{�X�N���X
//=============================================================================
class CSurroundings : public CEnemy
{
public:
	CSurroundings();			// �R���X�g���N�^
	~CSurroundings();			// �f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);						// ����������
	void Uninit(void);																// �I������
	void Update(void);																// �X�V����
	void Draw(void);																// �`�揈��

	static CSurroundings * Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);	// �|���S������

	void HitSurroundings(int nNumber);												// �̗͂����炷
	void BulletUpdate(void);															// �e��ł���
	void MoveUpdate(void);										// �΂߈ړ��̏���

	int GetLife(void);
private:
	D3DXVECTOR3 m_Pos;		// ���W
	D3DXVECTOR3 m_Move;		// �ړ�
	STATE m_State;			// �G�l�~�[�̏��
	int m_nLife;			// ���C�t
	int m_nStateCnt;		// �G�l�~�[�̏�ԃJ�E���^�[
	int m_nBulletFlame;		// �t���[���̃J�E���g
	int m_nBulletCnt;		// �e���o����
	int m_nFlashFlame;		// �_�ł̃t���[��
	int m_nSubNumber;		// �J���[���Z
	int m_nSubNum;			// �J���[�̌��Z��
	bool m_bColorFlag;		// �e�̐F�̃t���O
};

#endif