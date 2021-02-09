#ifndef _SCENE2D_H_
#define _SCENE2D_H_
//=============================================================================
//
// �V�[��2D�N���X�w�b�_�[ [scene2d.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "scene.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define PLAYER_SIZE_X	(85)	// ���@��X���W
#define PLAYER_SIZE_Y	(85)	// ���@��Y���W
#define MAX_POLYGON		(2048)	// �|���S���̍ő吔

//=============================================================================
// �O�u�錾
//=============================================================================
class CScene;

//=============================================================================
// �����_���[�N���X
//=============================================================================
class CScene2D : public CScene
{
public:

	CScene2D(TYPE Priority = TYPE_NONE);	// �R���X�g���N�^
	~CScene2D();							// �f�X�g���N�^

	// �����o�֐�
	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type);	// ����������
	virtual void Uninit(void);											// �I������
	virtual void Update(void);											// �X�V����
	virtual void Draw(void);											// �`�揈��

	void BindTexture(const LPDIRECT3DTEXTURE9 pTexture);						// �e�N�X�`���̐ݒ�
	void InitAnimation(int nCounterAnim, int nPatternAnim, int nLoop);	// �A�j���[�V������񏉊���
	void InitScroll(int nSpeed, float fDivision);						// �摜�X�N���[���̐ݒ�
	void UpdateAnimation(void);											// �A�j���[�V�����̍X�V
	void UpdateScroll(void);											// �摜�X�N���[���̍X�V
	bool ScaleUp(D3DXVECTOR3 pos);										// �|���S���g��
	bool ScaleDown(D3DXVECTOR3 pos, int nLife);							// �|���S���k��
	bool TransParency(D3DXVECTOR3 pos, int nLife);						// �����x�̕ω�

	// Set�֐�
	void SetPosition(D3DXVECTOR3 pos);									// �ʒu����ɍX�V
	void SetPos(const D3DXVECTOR3 &pos);
	void SetMove(const D3DXVECTOR3 &move);										// �ړ���
	void SetSize(const D3DXVECTOR3 &size);										// �T�C�Y��ݒ�
	void SetScaleSize(D3DXVECTOR3 size);								// �g��T�C�Y��ݒ�

	// Get�֐�
	D3DXVECTOR3 GetPos(void);											// �ʒu����Ԃ�
	D3DXVECTOR3 GetMove(void);
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void);							// �o�b�t�@�̏��
	D3DXVECTOR3 GetSize(void);											// �T�C�Y�̏��

private:
	D3DXVECTOR3 m_pos;						// ���_���W
	D3DXVECTOR3 m_move;						// �ړ���
	D3DXVECTOR3 m_size;						// �|���S���̃T�C�Y
	LPDIRECT3DTEXTURE9 m_pTexture;			// �e�N�X�`���̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�̃|�C���^
	int m_nCountAnim;						// �A�j���[�V�����e�N�X�`��
	int m_nCountAnimPattern;				// �A�j���[�V�����̃p�^�[��
	int m_nCounterAnim;						// �A�j���[�V�����̃J�E���^�[
	int m_nPatternAnim;						// �A�j���[�V�����̃p�^�[����
	int m_nSpeedTexture;					// �e�N�X�`���̈ړ����x
	int m_nTransParencyNum;					// �����x
	int m_nLoop;							// ���[�v���邩�ǂ���
	float m_fDivisionCounter;				// �X�N���[���̃J�E���^�[
	float m_fDivisionBaseNum;				// �X�N���[���̈ړ���
	float m_fScaleUp;						// �g���
	float m_fScaleDown;						// �k����
	float m_nEffectCntFlame;				// �G�t�F�N�g�̃J�E���g
};

#endif