//=============================================================================
//
// �e�N�X�`���̊Ǘ��N���X [texture.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// �C���N���[�h
//=============================================================================
#include "texture.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define TEXTURE_NAME_BG_000			("data/TEXTURE/bg006.png")				// �w�i000
#define TEXTURE_NAME_BG_001			("data/TEXTURE/bg100.png")				// �w�i001
#define TEXTURE_NAME_BG_002			("data/TEXTURE/bg004.png")				// �w�i002
#define TEXTURE_NAME_EFFECT			("data/TEXTURE/effect000.jpg")			// �G�t�F�N�g
#define TEXTURE_NAME_BOMB_UI		("data/TEXTURE/bomb000.png")			// �{����UI
#define TEXTURE_NAME_BOSS			("data/TEXTURE/enemy_boss.png")			// �{�X
#define TEXTURE_NAME_BULLET_000		("data/TEXTURE/bullet000.png")			// �e000
#define TEXTURE_NAME_BULLET_001		("data/TEXTURE/bullet001.png")			// �e001
#define TEXTURE_NAME_BULLET_002		("data/TEXTURE/bullet002.png")			// �e002
#define TEXTURE_NAME_BULLET_003		("data/TEXTURE/bullet003.png")			// �e003
#define TEXTURE_NAME_CROW			("data/TEXTURE/crow.png")				// �J���X
#define TEXTURE_NAME_ENEMY_WHITE	("data/TEXTURE/enemy_normal_white.png")	// ���̓G
#define TEXTURE_NAME_ENEMY_BLACK	("data/TEXTURE/enemy_normal_black.png")	// ���̓G
#define TEXTURE_NAME_ENEMY_BLUE		("data/TEXTURE/BlueEnemy.png")			// �̓G
#define TEXTURE_NAME_ENEMY_RED		("data/TEXTURE/RedEnemy.png")			// �Ԃ̓G
#define TEXTURE_NAME_EXPLOSION_000	("data/TEXTURE/Explosion002.png")		// ����000
#define TEXTURE_NAME_EXPLOSION_001	("data/TEXTURE/Explosion001.png")		// ����001
#define TEXTURE_NAME_EXPLOSION_002	("data/TEXTURE/Explosion100.png")		// ����002
#define TEXTURE_NAME_GAGEBAR_000	("data/TEXTURE/GageBar222.png")			// �Q�[�W�o�[000
#define TEXTURE_NAME_GAGEBAR_001	("data/TEXTURE/Gagebar111.png")			// �Q�[�W�o�[001
#define TEXTURE_NAME_HPBAR			("data/TEXTURE/3Dgame_HPbar001.png")	// HP�o�[
#define TEXTURE_NAME_ICON			("data/TEXTURE/icon002.png")			// �A�C�R��
#define TEXTURE_NAME_LASER			("data/TEXTURE/Laser000.png")			// ���[�U�[
#define TEXTURE_NAME_MESSAGE		("data/TEXTURE/message000.png")			// ���b�Z�[�W
#define TEXTURE_NAME_NUMBER_000		("data/TEXTURE/number.png")				// �i���o�[000
#define TEXTURE_NAME_NUMBER_001		("data/TEXTURE/Number010.png")			// �i���o�[001
#define TEXTURE_NAME_PLAYER			("data/TEXTURE/player001.png")			// �v���C���[
#define TEXTURE_NAME_RESULT_BG		("data/TEXTURE/result.png")				// ���U���g��ʔw�i
#define TEXTURE_NAME_BARRIER_BLUE	("data/TEXTURE/barrier_blue.png")		// �o���A
#define TEXTURE_NAME_BARRIER_RED	("data/TEXTURE/barrier_red.png")		// �ԃo���A
#define TEXTURE_NAME_SHOCK_000		("data/TEXTURE/shock003.png")			// �Ռ�000
#define TEXTURE_NAME_SHOCK_001		("data/TEXTURE/shock002.png")			// �Ռ�001
#define TEXTURE_NAME_SPARK			("data/TEXTURE/shock002.png")			// �Ή�
#define TEXTURE_NAME_START_LOGO		("data/TEXTURE/StartLogo.png")			// �X�^�[�g���S
#define TEXTURE_NAME_SURROUNDINGS	("data/TEXTURE/enemy_q.png")			// ��芪���G�l�~�[
#define TEXTURE_NAME_TITLE			("data/TEXTURE/title.png")				// �^�C�g��
#define TEXTURE_NAME_TUTORIAL		("data/TEXTURE/tutorial.png")			// �`���[�g���A��
#define TEXTURE_NAME_WALL			("data/TEXTURE/wall000.jpg")			// ��
#define TEXTURE_NAME_WAKU			("data/TEXTURE/bg_waku.png")			// �킭
#define TEXTURE_NAME_REMAIN			("data/TEXTURE/remain000.png")			// �c�@
#define TEXTURE_NAME_WARNING		("data/TEXTURE/WARNING.png")			// �x��

//=============================================================================
// static������
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::m_apTexture[TEXTURE_NUM_MAX] = {};		// �e�N�X�`���̃|�C���^

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CTexture::CTexture()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CTexture::~CTexture()
{
}

//=============================================================================
// �e�N�X�`�����[�h
//=============================================================================
HRESULT CTexture::Load(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BG_000, &m_apTexture[TEXTURE_NUM_BG_000]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BG_001, &m_apTexture[TEXTURE_NUM_BG_001]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BG_002, &m_apTexture[TEXTURE_NUM_BG_002]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_EFFECT, &m_apTexture[TEXTURE_NUM_EFFECT]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BOMB_UI, &m_apTexture[TEXTURE_NUM_BOMB_UI]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BOSS, &m_apTexture[TEXTURE_NUM_BOSS]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BULLET_000, &m_apTexture[TEXTURE_NUM_BULLET_000]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BULLET_001, &m_apTexture[TEXTURE_NUM_BULLET_001]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BULLET_002, &m_apTexture[TEXTURE_NUM_BULLET_002]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BULLET_003, &m_apTexture[TEXTURE_NUM_BULLET_003]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_CROW, &m_apTexture[TEXTURE_NUM_CROW]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_ENEMY_WHITE, &m_apTexture[TEXTURE_NUM_ENEMY_WHITE]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_ENEMY_BLACK, &m_apTexture[TEXTURE_NUM_ENEMY_BLACK]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_ENEMY_BLUE, &m_apTexture[TEXTURE_NUM_ENEMY_BLUE]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_ENEMY_RED, &m_apTexture[TEXTURE_NUM_ENEMY_RED]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_EXPLOSION_000, &m_apTexture[TEXTURE_NUM_EXPLOSION_000]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_EXPLOSION_001, &m_apTexture[TEXTURE_NUM_EXPLOSION_001]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_EXPLOSION_002, &m_apTexture[TEXTURE_NUM_EXPLOSION_002]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_GAGEBAR_000, &m_apTexture[TEXTURE_NUM_GAGEBAR_000]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_GAGEBAR_001, &m_apTexture[TEXTURE_NUM_GAGEBAR_001]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_HPBAR, &m_apTexture[TEXTURE_NUM_HPBAR]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_ICON, &m_apTexture[TEXTURE_NUM_ICON]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_LASER, &m_apTexture[TEXTURE_NUM_LASER]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_MESSAGE, &m_apTexture[TEXTURE_NUM_MESSAGE]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_NUMBER_000, &m_apTexture[TEXTURE_NUM_NUMBER_000]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_NUMBER_001, &m_apTexture[TEXTURE_NUM_NUMBER_001]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_PLAYER, &m_apTexture[TEXTURE_NUM_PLAYER]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_RESULT_BG, &m_apTexture[TEXTURE_NUM_RESULT_BG]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BARRIER_BLUE, &m_apTexture[TEXTURE_NUM_BARRIER_BLUE]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_BARRIER_RED, &m_apTexture[TEXTURE_NUM_BARRIER_RED]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_SHOCK_000, &m_apTexture[TEXTURE_NUM_SHOCK_000]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_SHOCK_001, &m_apTexture[TEXTURE_NUM_SHOCK_001]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_SPARK, &m_apTexture[TEXTURE_NUM_SPARK]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_START_LOGO, &m_apTexture[TEXTURE_NUM_START_LOGO]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_SURROUNDINGS, &m_apTexture[TEXTURE_NUM_SURROUNDINGS]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_TITLE, &m_apTexture[TEXTURE_NUM_TITLE]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_TUTORIAL, &m_apTexture[TEXTURE_NUM_TUTORIAL]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_WALL, &m_apTexture[TEXTURE_NUM_UI_WALL]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_WAKU, &m_apTexture[TEXTURE_NUM_UI_WAKU]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_REMAIN, &m_apTexture[TEXTURE_NUM_UI_REMAIN]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_NAME_WARNING, &m_apTexture[TEXTURE_NUM_WARNING]);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���A�����[�h
//=============================================================================
void CTexture::UnLoad(void)
{
	for (int nCount = 0; nCount < TEXTURE_NUM_MAX; nCount++)
	{
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
// �e�N�X�`�����
//=============================================================================
LPDIRECT3DTEXTURE9 CTexture::GetTexture(TEXTURE_TYPE Tex_Num)
{
	if (Tex_Num < TEXTURE_NUM_MAX)
	{
		if (m_apTexture[Tex_Num] != NULL)
		{
			return m_apTexture[Tex_Num];
		}
	}

	return nullptr;
}