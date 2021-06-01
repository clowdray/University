// SIMD_DLL_01.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "windows.h"
#include "intrin.h"
#include "stdio.h"
#pragma intrinsic(__rdtsc)

extern "C" __declspec(dllexport) void __stdcall Dist2Dsse(float *n, float *m, float *r)
{
	__asm
	{	
		mov ecx, n
		sub ecx, 4
		mov ecx, dword ptr[ecx]; get vector lenght
		shr ecx, 3

		mov edi, n
		mov esi, m
		mov edx, r


		bucle :
		movups	xmm0, xmmword ptr[edi]				; x from first point
			movups  xmm1, xmmword ptr[esi]
			subps	xmm0, xmm1						; subtract x from second point
			mulps	xmm0, xmm0						; (x1 - x2) ^ 2
			movups	xmm2, xmmword ptr[edi + 16]		; y from first point
			movups	xmm3, xmmword ptr[esi + 16]
			subps	xmm2, xmm3						; subtract y from second point
			mulps	xmm2, xmm2						; (y1 - y2) ^ 2
			haddps	xmm0, xmm2						; add x and y parts
			sqrtps	xmm0, xmm0

			movups	xmmword ptr[edx], xmm0			; save value

			add		esi, 32
			add		edi, 32
			add		edx, 16
			loop bucle
	}
}

extern "C" __declspec(dllexport) void __stdcall Dist2Davx(float *n, float *m, float *r)
{
	__asm
	{
		mov ecx, n
		sub ecx, 4
		mov ecx, dword ptr[ecx]; get vector lenght
		shr ecx, 4

		mov edi, n
		mov esi, m
		mov edx, r


		bucle :
			vmovups	ymm0, ymmword ptr[edi]			; x from first point
			vmovups ymm1, ymmword ptr[esi]
			vsubps	ymm0, ymm0, ymm1				; subtract x from second point
			vmulps	ymm0, ymm0, ymm0				; (x1 - x2) ^ 2
			vmovups	ymm2, ymmword ptr[edi + 32]		; y from first point
			vmovups	ymm3, ymmword ptr[esi + 32]
			vsubps	ymm2, ymm2, ymm3				; subtract y from second point
			vmulps	ymm2, ymm2, ymm2				; (y1 - y2) ^ 2
			vhaddps	ymm0, ymm0, ymm2				; add x and y parts
			vsqrtps	ymm0, ymm0

			vmovups	ymmword ptr[edx], ymm0

			add		esi, 64
			add		edi, 64
			add		edx, 32
			loop bucle
	}
}

extern "C" __declspec(dllexport) INT64 __stdcall getRDTSC() {
	unsigned __int64 i;
	i = __rdtsc();
	return i;
}






