#include "block.h"

#include "myDirect3D.h"
#include "input.h"
#include "texture.h"
#include "debugproc.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************

#define	VALUE_MOVE_B		(5.0f)							// �ړ���
#define	VALUE_ROTATE_B	 (D3DX_PI * 0.02f)				// ��]��
#define BLOCK_SIZE 20.0f
#define NUM_VERTEX (36)
#define NUM_POLYGON (12)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexBlock(LPDIRECT3DDEVICE9 pDevice);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;	// ���_�o�b�t�@�ւ̃|�C���^

D3DXMATRIX				g_mtxWorldBlock;		// ���[���h�}�g���b�N�X
D3DXVECTOR3				g_posBlock;				// �n�ʂ̈ʒu
D3DXVECTOR3				g_rotBlock;				// �n�ʂ̌���(��])
D3DXVECTOR3				g_sclBlock;				// �n�ʂ̑傫��(�X�P�[��)

float MakeRadian(int Radius) {
	return (Radius*3.14) / 180;
}

HRESULT InitBlock() {
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();


	// ���_���̍쐬
	MakeVertexBlock(pDevice);

	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	g_posBlock = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_rotBlock = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_sclBlock = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
//	g_posBlock.x = 100.0f;
	g_posBlock.y = 0.0f;
	
	return S_OK;

}
void UninitBlock() {
	if (g_pVtxBuffBlock != NULL)
	{// ���_�o�b�t�@�̊J��
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

	//�p�x�ύX
	radius +=1;
	if (radius > 360) {
		radius = 0;
	}

	/*	if (Keyboard_IsPress(DIK_A))
	{
		if (Keyboard_IsPress(DIK_W))
		{// �����ړ�
			g_posBlock.x += sinf(-D3DX_PI * 0.75f) * VALUE_MOVE_B;
			g_posBlock.z -= cosf(-D3DX_PI * 0.75f) * VALUE_MOVE_B;
		}
		else if (Keyboard_IsPress(DIK_S))
		{// ����O�ړ�
			g_posBlock.x += sinf(-D3DX_PI * 0.25f) * VALUE_MOVE_B;
			g_posBlock.z -= cosf(-D3DX_PI * 0.25f) * VALUE_MOVE_B;
		}
		else
		{// ���ړ�
			g_posBlock.x += sinf(-D3DX_PI * 0.50f) * VALUE_MOVE_B;
			g_posBlock.z -= cosf(-D3DX_PI * 0.50f) * VALUE_MOVE_B;
		}
	}
	else if (Keyboard_IsPress(DIK_D))
	{
		if (Keyboard_IsPress(DIK_W))
		{// �E���ړ�
			g_posBlock.x += sinf(D3DX_PI * 0.75f) * VALUE_MOVE_B;
			g_posBlock.z -= cosf(D3DX_PI * 0.75f) * VALUE_MOVE_B;
		}
		else if (Keyboard_IsPress(DIK_S))
		{// �E��O�ړ�
			g_posBlock.x += sinf(D3DX_PI * 0.25f) * VALUE_MOVE_B;
			g_posBlock.z -= cosf(D3DX_PI * 0.25f) * VALUE_MOVE_B;
		}
		else
		{// �E�ړ�
			g_posBlock.x += sinf(D3DX_PI * 0.50f) * VALUE_MOVE_B;
			g_posBlock.z -= cosf(D3DX_PI * 0.50f) * VALUE_MOVE_B;
		}
	}
	else if (Keyboard_IsPress(DIK_W))
	{// ���ړ�
		g_posBlock.x += sinf(D3DX_PI * 1.0f) * VALUE_MOVE_B;
		g_posBlock.z -= cosf(D3DX_PI * 1.0f) * VALUE_MOVE_B;
	}
	else if (Keyboard_IsPress(DIK_S))
	{// ��O�ړ�
		g_posBlock.x += sinf(D3DX_PI * 0.0f) * VALUE_MOVE_B;
		g_posBlock.z -= cosf(D3DX_PI * 0.0f) * VALUE_MOVE_B;
	}

#if 1
	if (Keyboard_IsPress(DIK_Q))
	{// Y������]
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
	{// Y���E��]
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
	{// X���E��]
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
	{// X������]
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
	{// Z���E��]
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
	{// Z������]
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
	{// ���Z�b�g
		g_posBlock.x = 0.0f;
		g_posBlock.y = 0.0f;
		g_posBlock.z = 0.0f;

		g_rotBlock.x = 0.0f;
		g_rotBlock.y = 0.0f;
		g_rotBlock.z = 0.0f;
	}*/

	DebugProc_Print((char *)"*** �R�c�|���S������ ***\n");
	DebugProc_Print((char *)"�ʒu [%f : %f : %f]\n", g_posBlock.x, g_posBlock.y, g_posBlock.z);
	DebugProc_Print((char *)"�O�ړ� : �v\n");
	DebugProc_Print((char *)"��ړ� : �r\n");
	DebugProc_Print((char *)"���ړ� : �`\n");
	DebugProc_Print((char *)"�E�ړ� : �c\n");
	DebugProc_Print((char *)"\n");

	DebugProc_Print((char *)"���� [%f : %f : %f]����ƈړ��p�x%d\n", g_rotBlock.x, g_rotBlock.y, g_rotBlock.z,radius);
	DebugProc_Print((char *)"X����] : �� / ��\n");
	DebugProc_Print((char *)"Y����] : �p / �d\n");
	DebugProc_Print((char *)"Z����] : �� / ��\n");
	DebugProc_Print((char *)"\n");

	DebugProc_Print((char *)"�ʒu�E�������Z�b�g : ENTER\n");
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
		
		

		//UV�l�ݒ�
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

