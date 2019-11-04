#include "block.h"

#include "myDirect3D.h"
#include "input.h"
#include "texture.h"
#include "debugproc.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define	VALUE_MOVE_B		(5.0f)							// 移動量
#define	VALUE_ROTATE_B	 (D3DX_PI * 0.02f)				// 回転量
#define BLOCK_SIZE 20.0f
#define NUM_VERTEX (36)
#define NUM_POLYGON (12)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexBlock(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;	// 頂点バッファへのポインタ

D3DXMATRIX				g_mtxWorldBlock;		// ワールドマトリックス
D3DXVECTOR3				g_posBlock;				// 地面の位置
D3DXVECTOR3				g_rotBlock;				// 地面の向き(回転)
D3DXVECTOR3				g_sclBlock;				// 地面の大きさ(スケール)

float MakeRadian(int Radius) {
	return (Radius*3.14) / 180;
}

HRESULT InitBlock() {
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();


	// 頂点情報の作成
	MakeVertexBlock(pDevice);

	// 位置・回転・スケールの初期設定
	g_posBlock = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotBlock = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_sclBlock = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
//	g_posBlock.x = 100.0f;
	g_posBlock.y = 0.0f;
	
	return S_OK;

}
void UninitBlock() {
	if (g_pVtxBuffBlock != NULL)
	{// 頂点バッファの開放
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}

}
static int time = 0;
static float move = 1.0f;
static int MAX =100;
int radius = 0;
void UpdateBlock() {
	time += 1;
	if (time > MAX) {
		move *= -1.0f;
		time = 0;
	}

	g_posBlock.x = sinf(MakeRadian(radius))*50.0f;
	g_posBlock.z=cosf(MakeRadian(radius))*50.0f;
//	g_rotBlock.y += D3DX_PI * 0.01f;

	//角度変更
	radius +=1;
	if (radius > 360) {
		radius = 0;
	}

	/*	if (Keyboard_IsPress(DIK_A))
	{
		if (Keyboard_IsPress(DIK_W))
		{// 左奥移動
			g_posBlock.x += sinf(-D3DX_PI * 0.75f) * VALUE_MOVE_B;
			g_posBlock.z -= cosf(-D3DX_PI * 0.75f) * VALUE_MOVE_B;
		}
		else if (Keyboard_IsPress(DIK_S))
		{// 左手前移動
			g_posBlock.x += sinf(-D3DX_PI * 0.25f) * VALUE_MOVE_B;
			g_posBlock.z -= cosf(-D3DX_PI * 0.25f) * VALUE_MOVE_B;
		}
		else
		{// 左移動
			g_posBlock.x += sinf(-D3DX_PI * 0.50f) * VALUE_MOVE_B;
			g_posBlock.z -= cosf(-D3DX_PI * 0.50f) * VALUE_MOVE_B;
		}
	}
	else if (Keyboard_IsPress(DIK_D))
	{
		if (Keyboard_IsPress(DIK_W))
		{// 右奥移動
			g_posBlock.x += sinf(D3DX_PI * 0.75f) * VALUE_MOVE_B;
			g_posBlock.z -= cosf(D3DX_PI * 0.75f) * VALUE_MOVE_B;
		}
		else if (Keyboard_IsPress(DIK_S))
		{// 右手前移動
			g_posBlock.x += sinf(D3DX_PI * 0.25f) * VALUE_MOVE_B;
			g_posBlock.z -= cosf(D3DX_PI * 0.25f) * VALUE_MOVE_B;
		}
		else
		{// 右移動
			g_posBlock.x += sinf(D3DX_PI * 0.50f) * VALUE_MOVE_B;
			g_posBlock.z -= cosf(D3DX_PI * 0.50f) * VALUE_MOVE_B;
		}
	}
	else if (Keyboard_IsPress(DIK_W))
	{// 奥移動
		g_posBlock.x += sinf(D3DX_PI * 1.0f) * VALUE_MOVE_B;
		g_posBlock.z -= cosf(D3DX_PI * 1.0f) * VALUE_MOVE_B;
	}
	else if (Keyboard_IsPress(DIK_S))
	{// 手前移動
		g_posBlock.x += sinf(D3DX_PI * 0.0f) * VALUE_MOVE_B;
		g_posBlock.z -= cosf(D3DX_PI * 0.0f) * VALUE_MOVE_B;
	}

#if 1
	if (Keyboard_IsPress(DIK_Q))
	{// Y軸左回転
		g_rotBlock.y -= VALUE_ROTATE_B;
		if (g_rotBlock.y > D3DX_PI)
		{
			g_rotBlock.y -= D3DX_PI * 2.0f;
		}
		if (g_rotBlock.y < -D3DX_PI)
		{
			g_rotBlock.y += D3DX_PI * 2.0f;
		}
	}
	if (Keyboard_IsPress(DIK_E))
	{// Y軸右回転
		g_rotBlock.y += VALUE_ROTATE_B;
		if (g_rotBlock.y > D3DX_PI)
		{
			g_rotBlock.y -= D3DX_PI * 2.0f;
		}
		if (g_rotBlock.y < -D3DX_PI)
		{
			g_rotBlock.y += D3DX_PI * 2.0f;
		}
	}
#endif

#if 1
	if (Keyboard_IsPress(DIK_UP))
	{// X軸右回転
		g_rotBlock.x += VALUE_ROTATE_B;
		if (g_rotBlock.x > D3DX_PI)
		{
			g_rotBlock.x -= D3DX_PI * 2.0f;
		}
		if (g_rotBlock.x < -D3DX_PI)
		{
			g_rotBlock.x += D3DX_PI * 2.0f;
		}
	}
	if (Keyboard_IsPress(DIK_DOWN))
	{// X軸左回転
		g_rotBlock.x -= VALUE_ROTATE_B;
		if (g_rotBlock.x > D3DX_PI)
		{
			g_rotBlock.x -= D3DX_PI * 2.0f;
		}
		if (g_rotBlock.x < -D3DX_PI)
		{
			g_rotBlock.x += D3DX_PI * 2.0f;
		}
	}
#endif

#if 1
	if (Keyboard_IsPress(DIK_LEFT))
	{// Z軸右回転
		g_rotBlock.z += VALUE_ROTATE_B;
		if (g_rotBlock.z > D3DX_PI)
		{
			g_rotBlock.z -= D3DX_PI * 2.0f;
		}
		if (g_rotBlock.z < -D3DX_PI)
		{
			g_rotBlock.z += D3DX_PI * 2.0f;
		}
	}
	if (Keyboard_IsPress(DIK_RIGHT))
	{// Z軸左回転
		g_rotBlock.z -= VALUE_ROTATE_B;
		if (g_rotBlock.z > D3DX_PI)
		{
			g_rotBlock.z -= D3DX_PI * 2.0f;
		}
		if (g_rotBlock.z < -D3DX_PI)
		{
			g_rotBlock.z += D3DX_PI * 2.0f;
		}
	}
#endif

	if (Keyboard_IsPress(DIK_RETURN))
	{// リセット
		g_posBlock.x = 0.0f;
		g_posBlock.y = 0.0f;
		g_posBlock.z = 0.0f;

		g_rotBlock.x = 0.0f;
		g_rotBlock.y = 0.0f;
		g_rotBlock.z = 0.0f;
	}*/

	DebugProc_Print((char *)"*** ３Ｄポリゴン操作 ***\n");
	DebugProc_Print((char *)"位置 [%f : %f : %f]\n", g_posBlock.x, g_posBlock.y, g_posBlock.z);
	DebugProc_Print((char *)"前移動 : Ｗ\n");
	DebugProc_Print((char *)"後移動 : Ｓ\n");
	DebugProc_Print((char *)"左移動 : Ａ\n");
	DebugProc_Print((char *)"右移動 : Ｄ\n");
	DebugProc_Print((char *)"\n");

	DebugProc_Print((char *)"向き [%f : %f : %f]それと移動角度%d\n", g_rotBlock.x, g_rotBlock.y, g_rotBlock.z,radius);
	DebugProc_Print((char *)"X軸回転 : ↑ / ↓\n");
	DebugProc_Print((char *)"Y軸回転 : Ｑ / Ｅ\n");
	DebugProc_Print((char *)"Z軸回転 : ← / →\n");
	DebugProc_Print((char *)"\n");

	DebugProc_Print((char *)"位置・向きリセット : ENTER\n");
}
void DrawBlock() {
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	D3DXMatrixIdentity(&g_mtxWorldBlock);

	D3DXMatrixScaling(&mtxScl, g_sclBlock.x, g_sclBlock.y, g_sclBlock.z);
	D3DXMatrixMultiply(&g_mtxWorldBlock, &g_mtxWorldBlock, &mtxScl);


	D3DXMatrixMultiply(&g_mtxWorldBlock, &g_mtxWorldBlock, &mtxRot);

	D3DXMatrixTranslation(&mtxTranslate, g_posBlock.x, g_posBlock.y, g_posBlock.z);
	D3DXMatrixMultiply(&g_mtxWorldBlock, &g_mtxWorldBlock, &mtxTranslate);

	pDevice->SetTransform(D3DTS_WORLD, &g_mtxWorldBlock);

	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_3D));

	pDevice->SetFVF(FVF_VERTEX_3D);
	pDevice->SetTexture(0, Texture_GetTexture(TEXTURE_INDEX_FIELD01));

	pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, NUM_POLYGON);
}


HRESULT MakeVertexBlock(LPDIRECT3DDEVICE9 pDevice)
{
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &g_pVtxBuffBlock, NULL))) {
		return E_FAIL;
	}
	{

		VERTEX_3D *pVtx;

		g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);
//1
		pVtx[0].pos = D3DXVECTOR3(-BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
		pVtx[1].pos = D3DXVECTOR3(BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
		pVtx[2].pos = D3DXVECTOR3(-BLOCK_SIZE, BLOCK_SIZE, -BLOCK_SIZE);
		//2
		pVtx[5].pos = D3DXVECTOR3(BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
		pVtx[3].pos = D3DXVECTOR3(BLOCK_SIZE, BLOCK_SIZE, -BLOCK_SIZE);
		pVtx[4].pos = D3DXVECTOR3(-BLOCK_SIZE, BLOCK_SIZE, -BLOCK_SIZE);

//3
		pVtx[6].pos = D3DXVECTOR3(-BLOCK_SIZE, BLOCK_SIZE, -BLOCK_SIZE);
		pVtx[7].pos = D3DXVECTOR3(BLOCK_SIZE, BLOCK_SIZE, -BLOCK_SIZE);
		pVtx[8].pos = D3DXVECTOR3(-BLOCK_SIZE, -BLOCK_SIZE, -BLOCK_SIZE);
		//4
		pVtx[9].pos = D3DXVECTOR3(BLOCK_SIZE, -BLOCK_SIZE, -BLOCK_SIZE);
		pVtx[10].pos = D3DXVECTOR3(-BLOCK_SIZE, -BLOCK_SIZE, -BLOCK_SIZE);
		pVtx[11].pos = D3DXVECTOR3(BLOCK_SIZE, BLOCK_SIZE, -BLOCK_SIZE);

//5
		pVtx[12].pos = D3DXVECTOR3(BLOCK_SIZE,  BLOCK_SIZE, -BLOCK_SIZE);
		pVtx[13].pos = D3DXVECTOR3(BLOCK_SIZE,  BLOCK_SIZE,  BLOCK_SIZE);
		pVtx[14].pos = D3DXVECTOR3(BLOCK_SIZE, -BLOCK_SIZE, -BLOCK_SIZE);
		//6
		pVtx[15].pos = D3DXVECTOR3(BLOCK_SIZE, -BLOCK_SIZE, BLOCK_SIZE);
		pVtx[16].pos = D3DXVECTOR3(BLOCK_SIZE, -BLOCK_SIZE, -BLOCK_SIZE);
		pVtx[17].pos = D3DXVECTOR3(BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);

//7
		pVtx[18].pos = D3DXVECTOR3( BLOCK_SIZE,  BLOCK_SIZE, BLOCK_SIZE);
		pVtx[19].pos = D3DXVECTOR3(-BLOCK_SIZE,  BLOCK_SIZE, BLOCK_SIZE);
		pVtx[20].pos = D3DXVECTOR3( BLOCK_SIZE, -BLOCK_SIZE, BLOCK_SIZE);
		//8
		pVtx[21].pos = D3DXVECTOR3(-BLOCK_SIZE, -BLOCK_SIZE, BLOCK_SIZE);
		pVtx[23].pos = D3DXVECTOR3(-BLOCK_SIZE,  BLOCK_SIZE, BLOCK_SIZE);
		pVtx[22].pos = D3DXVECTOR3( BLOCK_SIZE, -BLOCK_SIZE, BLOCK_SIZE);
		
//9
		pVtx[24].pos = D3DXVECTOR3(-BLOCK_SIZE,  BLOCK_SIZE, BLOCK_SIZE);
		pVtx[25].pos = D3DXVECTOR3(-BLOCK_SIZE, BLOCK_SIZE, -BLOCK_SIZE);
		pVtx[26].pos = D3DXVECTOR3(-BLOCK_SIZE, -BLOCK_SIZE, BLOCK_SIZE);
		//10
		pVtx[27].pos = D3DXVECTOR3(-BLOCK_SIZE, -BLOCK_SIZE, -BLOCK_SIZE);
		pVtx[29].pos = D3DXVECTOR3(-BLOCK_SIZE, BLOCK_SIZE, -BLOCK_SIZE);
		pVtx[28].pos = D3DXVECTOR3(-BLOCK_SIZE, -BLOCK_SIZE, BLOCK_SIZE);

//11
		pVtx[32].pos = D3DXVECTOR3(-BLOCK_SIZE, -BLOCK_SIZE, BLOCK_SIZE);
		pVtx[31].pos = D3DXVECTOR3( BLOCK_SIZE, -BLOCK_SIZE, -BLOCK_SIZE);
		pVtx[30].pos = D3DXVECTOR3(-BLOCK_SIZE, -BLOCK_SIZE, -BLOCK_SIZE);
		//12
		pVtx[33].pos = D3DXVECTOR3(BLOCK_SIZE, -BLOCK_SIZE, BLOCK_SIZE);
		pVtx[35].pos = D3DXVECTOR3(BLOCK_SIZE, -BLOCK_SIZE, -BLOCK_SIZE);
		pVtx[34].pos = D3DXVECTOR3(-BLOCK_SIZE, -BLOCK_SIZE, BLOCK_SIZE);


		for (int i = 0;i <= NUM_VERTEX;i++) {
			if(i<6)
				pVtx[i].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			if(i>=6&&i<12)
				pVtx[i].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			if(i>=12&&i<18)
				pVtx[i].nor = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
			if(i>=18&&i<24)
				pVtx[i].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
			if (i >= 24 && i < 30)
				pVtx[i].nor = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
			if (i >= 30 && i < NUM_VERTEX)
				pVtx[i].nor = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		}

	

		for (int i = 0;i < NUM_VERTEX;i++) {
			pVtx[i].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
		
		

		//UV値設定
		for (int i = 0;i < NUM_VERTEX;i++) {
			switch (i % 6) {
			case 0:
				pVtx[i].tex = D3DXVECTOR2(0.0f, 0.0f);
				break;
			case 1:
				pVtx[i].tex = D3DXVECTOR2(1.0f, 0.0f);
				break;
			case 2:
				pVtx[i].tex = D3DXVECTOR2(0.0f, 1.0f);
				break;
			case 3:
				pVtx[i].tex = D3DXVECTOR2(1.0f, 1.0f);
				break;
			case 4:
				pVtx[i].tex = D3DXVECTOR2(1.0f, 0.0f);
					break;
				case 5:
					pVtx[i].tex = D3DXVECTOR2(0.0f, 1.0f);
					break;
				default:break;
			}
		}
		
		g_pVtxBuffBlock->Unlock();
	}
	return S_OK;
}

