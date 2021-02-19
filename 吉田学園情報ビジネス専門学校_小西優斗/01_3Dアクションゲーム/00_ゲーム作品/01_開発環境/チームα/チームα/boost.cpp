//=============================================================================
//
// ブースターの処理 [boost.cpp]
// Author : Konishi Yuuto
//
//=============================================================================

//=============================================================================
// インクルード
//=============================================================================
#include "boost.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "game.h"

//=============================================================================
// static初期化
//=============================================================================
LPDIRECT3DTEXTURE9 CBoost::m_apTexture[MAX_LASER_TEXTURE] = {};
LPD3DXMESH CBoost::m_pMesh = NULL;
LPD3DXBUFFER CBoost::m_pBuffMat = NULL;
DWORD CBoost::m_nNumMat = 0;
int CBoost::m_nBoost = 0;

//=============================================================================
// コンストラクタ
//=============================================================================
CBoost::CBoost()
{
	D3DXVECTOR3 m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nNum = 0;
	m_nBoost = m_nBoost++;
}

//=============================================================================
// デストラクタ
//=============================================================================
CBoost::~CBoost()
{

}

//=============================================================================
// クリエイト
//=============================================================================
CBoost * CBoost::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, int nNumber)
{
	// メモリ確保
	CBoost *pBoost = new CBoost;

	// メモリが確保できていたら
	if (pBoost != NULL)
	{
		// 初期化処理
		pBoost->Init(pos, size, nNumber);		// 初期化情報
		pBoost->SetRot(rot);					// 角度
	}
	else
	{
		return NULL;
	}

	return pBoost;
}

//=============================================================================
// テクスチャロード
//=============================================================================
HRESULT CBoost::Load(void)
{
	// レンダラーの情報を受け取る
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/Texture/razer.png",
		&m_apTexture[0]);

	// Xファイルの読み込み
	D3DXLoadMeshFromX("data/model/razer.x",
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_nNumMat,
		&m_pMesh);

	return S_OK;
}

//=============================================================================
// テクスチャアンロード
//=============================================================================
void CBoost::UnLoad(void)
{
	//メッシュの破棄
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}
	//マテリアルの破棄
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}

	for (int nCount = 0; nCount < MAX_LASER_TEXTURE; nCount++)
	{
		// テクスチャの破棄
		if (m_apTexture[nCount] != NULL)
		{
			m_apTexture[nCount]->Release();
			m_apTexture[nCount] = NULL;
		}
	}
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBoost::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size , const int nNum)
{
	MODEL model;

	// モデルの情報代入
	model.dwNumMat = m_nNumMat;
	model.pBuffMat = m_pBuffMat;
	model.pMesh = m_pMesh;

	//モデル情報を設定
	BindModel(model);
	BindTexture(m_apTexture[0]);

	// 変数代入
	m_nBoostNum = m_nBoost;
	m_nNum = nNum;

	// 初期化処理
	CModel::Init(pos, size);		// 初期化情報

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CBoost::Uninit(void)
{
	m_nBoost = m_nBoost--;

	// 終了処理
	CModel::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CBoost::Update(void)
{
	// ブーストを動かす処理
	BoostMove();

	// 更新処理
	CModel::Update();
}

//=============================================================================
// 描画処理
//=============================================================================
void CBoost::Draw(void)
{
	// レンダラーの情報を受け取る
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//マテリアルデータへのポインタ
	D3DXMATERIAL*pMat;

	// バッファの情報を受け取る
	LPD3DXBUFFER pBuffMat = GetBuffMat();

	//マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)pBuffMat->GetBufferPointer();

	// モデルの描画
	CModel::Draw();
}

//=============================================================================
// ブーストの更新処理
//=============================================================================
void CBoost::BoostMove(void)
{
	// レンダラーの情報を受け取る
	CRenderer *pRenderer = NULL;
	pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	// プレイヤーの情報取得
	CPlayer *pPlayer = CGame::GetPlayer(m_nNum);
	D3DXVECTOR3 rot = pPlayer->GetRot();
	static float fRot = 0.0f;
	D3DXVECTOR3 pos = pPlayer->GetPos();
	D3DXVECTOR3 move = pPlayer->GetMove();
	D3DXVECTOR3 TargetPos = D3DXVECTOR3(0.0f,0.0f,0.0f);

	// 出現情報
	if (1 == m_nBoostNum %2)
	{
		TargetPos = D3DXVECTOR3(pos.x - sinf(rot.y) * -50.0f, pos.y + 160.0f, pos.z - cosf(rot.y) * -50.0f);

		rot = D3DXVECTOR3(rot.x + D3DXToRadian(250.0f), rot.y + 0.0f, rot.z + 0.0f);
	}
	else
	{
		TargetPos = D3DXVECTOR3(pos.x - cosf(rot.y) * -50.0f, pos.y + 160.0f, pos.z - sinf(rot.y) * 50.0f);

		rot = D3DXVECTOR3(rot.x + D3DXToRadian(250.0f), rot.y + D3DXToRadian(60.0f), rot.z + 0.0f);
	}
	fRot += D3DXToRadian(5.0f);

	// 角度
	SetRot(D3DXVECTOR3(rot.x, rot.y, rot.z + fRot));

	// 座標
	SetPos(TargetPos + move);
}