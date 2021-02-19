#ifndef _TEXTURE_H_
#define _TEXTURE_H_
//=============================================================================
//
// �e�N�X�`���̊Ǘ��w�b�_�[ [texture.h]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "main.h"

//=============================================================================
// �}�N����`
//=============================================================================

//=============================================================================
//�N���X�錾
//=============================================================================
class CTexture
{
public:

	// �e�N�X�`���̔ԍ��̗񋓌^
	typedef enum
	{
		TEXTURE_NUM_NONE = -1,		// �����l
		TEXTURE_NUM_BG_000,			// �w�i0
		TEXTURE_NUM_BG_001,			// �w�i1
		TEXTURE_NUM_BG_002,			// �w�i2
		TEXTURE_NUM_EFFECT,			// �G�t�F�N�g
		TEXTURE_NUM_BOMB_UI,		// �{����UI
		TEXTURE_NUM_BOSS,			// �{�X
		TEXTURE_NUM_BULLET_000,		// �e000
		TEXTURE_NUM_BULLET_001,		// �e001
		TEXTURE_NUM_BULLET_002,		// �e002
		TEXTURE_NUM_BULLET_003,		// �e002
		TEXTURE_NUM_CROW,			// �J���X
		TEXTURE_NUM_ENEMY_WHITE,	// ���̓G
		TEXTURE_NUM_ENEMY_BLACK,	// ���̓G
		TEXTURE_NUM_ENEMY_BLUE,		// �̓G
		TEXTURE_NUM_ENEMY_RED,		// �Ԃ̓G
		TEXTURE_NUM_EXPLOSION_000,	// ����000
		TEXTURE_NUM_EXPLOSION_001,	// ����001
		TEXTURE_NUM_EXPLOSION_002,	// ����002
		TEXTURE_NUM_GAGEBAR_000,	// �Q�[�W�o�[000
		TEXTURE_NUM_GAGEBAR_001,	// �Q�[�W�o�[001
		TEXTURE_NUM_HPBAR,			// HP�o�[
		TEXTURE_NUM_ICON,			// �A�C�R��
		TEXTURE_NUM_LASER,			// ���[�U�[
		TEXTURE_NUM_MESSAGE,		// ���b�Z�[�W
		TEXTURE_NUM_NUMBER_000,		// �i���o�[000
		TEXTURE_NUM_NUMBER_001,		// �i���o�[001
		TEXTURE_NUM_PLAYER,			// �v���C���[
		TEXTURE_NUM_RESULT_BG,		// ���U���g��ʔw�i
		TEXTURE_NUM_BARRIER_BLUE,	// �o���A
		TEXTURE_NUM_BARRIER_RED,	// �ԃo���A
		TEXTURE_NUM_SHOCK_000,		// �Ռ�000
		TEXTURE_NUM_SHOCK_001,		// �Ռ�001
		TEXTURE_NUM_SPARK,			// �Ή�
		TEXTURE_NUM_START_LOGO,		// �X�^�[�g�̃��S
		TEXTURE_NUM_SURROUNDINGS,	// ��芪���G�l�~�[
		TEXTURE_NUM_TITLE,			// �^�C�g��
		TEXTURE_NUM_TUTORIAL,		// �`���[�g���A��
		TEXTURE_NUM_UI_WALL,		// ��
		TEXTURE_NUM_UI_WAKU,		// �킭
		TEXTURE_NUM_UI_REMAIN,		// �c�@
		TEXTURE_NUM_WARNING,		// �x��
		TEXTURE_NUM_MAX
	}TEXTURE_TYPE;

	CTexture();		// �R���X�g���N�^
	~CTexture();	// �f�X�g���N�^

	static HRESULT Load(void);										// �e�N�X�`�����[�h
	static void UnLoad(void);										// �e�N�X�`���A�����[�h
	static LPDIRECT3DTEXTURE9 GetTexture(TEXTURE_TYPE Tex_Type);	// �e�N�X�`���̏��
private:
	static LPDIRECT3DTEXTURE9 m_apTexture[TEXTURE_NUM_MAX];				// �e�N�X�`���̃|�C���^
};
#endif
