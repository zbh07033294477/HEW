#pragma once

#include <Windows.h>
#include <d3dx9.h>


//*****************************************************************************
// マクロ定義
//*****************************************************************************

#define SCREEN_WIDTH  (1280)              // スクリーン(クライアント領域)の幅
#define SCREEN_HEIGHT  (720)              // スクリーン(クライアント領域)の高さ

#define	NUM_VERTEX		(4)		// 頂点数
#define	NUM_POLYGON		(2)		// ポリゴン数

// 上記２Ｄポリゴン頂点フォーマットに合わせた構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;	// 頂点座標
	float rhw;			// 座標変換用係数(1.0fで固定)
	D3DCOLOR col;		// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャ座標
} VERTEX_2D;

// ２Ｄポリゴン頂点フォーマット( 頂点座標[2D] / 頂点カラー / テクスチャ座標 )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

// 上記３Ｄポリゴン頂点フォーマットに合わせた構造体を定義
typedef struct
{
	D3DXVECTOR3 pos;	// 頂点座標
	D3DXVECTOR3 nor;	// 法線ベクトル
	D3DCOLOR col;		// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャ座標
} VERTEX_3D;

// ３Ｄポリゴン頂点フォーマット( 頂点座標[3D] / 法線 / 頂点カラー / テクスチャ座標 )
#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)


//*****************************************************************************
// プロトタイプ
//*****************************************************************************

//ウィンドウハンドルのGetter
HWND GetHWND();
double frand();
