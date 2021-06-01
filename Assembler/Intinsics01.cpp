// Intinsics01.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "smmintrin.h"
#include "nmmintrin.h"
#include "immintrin.h" //AVX
#include "intrin.h"

int main()
{

	float t1[4] = { 24.5f, 33.4f, 55.6f, 77.8f };
	float t2[4] = { 1.5f, 1.4f, 1.6f, 1.8f };
	float t3[4] = { 0, 0, 0, 0 };

	__int64 dif;

	printf("-----------------Dividir 2 Vectors bucle NORMAL-----------------");
	printf("\n t1 : ");
	for (int i = 0; i < 4; i++)
		printf("%.2f\t", t1[i]);
	printf("\n t2 : ");
	for (int i = 0; i < 4; i++)
		printf("%.2f\t", t2[i]);
	dif = __rdtsc();
	for (int i = 0; i < 4; i++)
		t3[i]=t1[i] / t2[i];
	dif = __rdtsc() - dif;
	for (int i = 0; i < 4; i++)
		printf("%.2f\t", t3[i]);
	printf_s("\n %I64d ticks per NORMAL \n", dif);
	dif = 0;
	printf("-----------------Dividir 2 Vecotrs SSE-----------------");
	printf("\n t1 : ");
	for (int i = 0; i < 4; i++) 
		printf("%.2f\t", t1[i]);
	printf("\n t2 : ");
	for (int i = 0; i < 4; i++)
		printf("%.2f\t", t2[i]);
	dif = __rdtsc();
	__asm {
		lea eax, t1
		lea edi, t2
		lea ecx, t3
		movups xmm0, xmmword ptr[eax]
		movups xmm1, xmmword ptr[edi]
		divps xmm0, xmm1
		movups xmmword ptr[ecx], xmm0
	};
	dif = __rdtsc()-dif;
	printf_s("\n %I64d ticks SSE \n", dif);
	dif = 0;
	printf("\n t3 : ");
	for (int i = 0; i < 4; i++)
		printf("%.2f\t", t3[i]);


	printf("\n ------------Dividir amb Intrinsics SSE-------------- \n");
	__m128 c0,c1,c2;
	dif = __rdtsc();
	c0 = _mm_set_ps(3.5f, 3.6f, 3.7f, 3.8f);
	c1 = _mm_set_ps(4.5f, 5.6f, 6.7f, 7.8f);
	c2 = _mm_div_ps(c0, c1);
	dif = __rdtsc() - dif;
	
	printf("c0 = (%f, %f, %f, %f)\n", c0.m128_f32[0], c0.m128_f32[1], c0.m128_f32[2], c0.m128_f32[3]);
	printf("c1 = (%f, %f, %f, %f)\n", c1.m128_f32[0], c1.m128_f32[1], c1.m128_f32[2], c1.m128_f32[3]);
	printf("c2 = (%f, %f, %f, %f)\n", c2.m128_f32[0], c2.m128_f32[1], c2.m128_f32[2], c2.m128_f32[3]);
	printf_s("\n %I64d ticks Intrinsics SSE \n", dif);

	printf("\n ------------Dividir amb Intrinsics AVX 256-------------- \n");
	__m256 c0a, c1a, c2a;
	dif = __rdtsc();
	c0a = _mm256_set_ps(3.5f, 3.6f, 3.7f, 3.8f,3.9f,4.0f,4.1f,4.2f);
	c1a = _mm256_set_ps(4.5f, 5.6f, 6.7f, 7.8f, 3.9f, 1.0f, 2.1f, 2.2f);
	c2a = _mm256_div_ps(c0a, c1a);
	dif = __rdtsc() - dif;

	printf("c0a = (%f, %f, %f, %f)\n", c0a.m256_f32[0], c0a.m256_f32[1], c0a.m256_f32[2], c0a.m256_f32[3]);
	printf("c1a = (%f, %f, %f, %f)\n", c1a.m256_f32[0], c1a.m256_f32[1], c1a.m256_f32[2], c1a.m256_f32[3]);
	printf("c2a = (%f, %f, %f, %f)\n", c2a.m256_f32[0], c2a.m256_f32[1], c2a.m256_f32[2], c2a.m256_f32[3]);
	printf_s("\n %I64d ticks Intrinsics AVX \n", dif);


	printf("\n ------------Dividir amb Intrinsics FMA3 256-------------- \n");
	__m256 c0b, c1b, c2b,c3b;
	dif = __rdtsc();
	c0b = _mm256_set_ps(3.5f, 3.6f, 3.7f, 3.8f, 3.9f, 4.0f, 4.1f, 3.5f);
	c1b = _mm256_set_ps(2.0f, 5.6f, 6.7f, 7.8f, 3.9f, 1.0f, 2.1f, 2.0f);
	c2b = _mm256_set_ps(10.0f, 7.6f, 9.7f, 2.8f, 5.9f, 1.0f, 4.1f, 10.0f);
	c3b = _mm256_fmadd_ps(c0b, c1b, c2b); //c3b=((c0b*c1b)+c2b)
	dif = __rdtsc() - dif;

	printf("c0b = (%f, %f, %f, %f)\n", c0b.m256_f32[0], c0b.m256_f32[1], c0b.m256_f32[2], c0b.m256_f32[3]);
	printf("c1b = (%f, %f, %f, %f)\n", c1b.m256_f32[0], c1b.m256_f32[1], c1b.m256_f32[2], c1b.m256_f32[3]);
	printf("c2b = (%f, %f, %f, %f)\n", c2b.m256_f32[0], c2b.m256_f32[1], c2b.m256_f32[2], c2b.m256_f32[3]);
	printf("c3b = (%f, %f, %f, %f)\n", c3b.m256_f32[0], c3b.m256_f32[1], c3b.m256_f32[2], c3b.m256_f32[3]);
	printf_s("\n %I64d ticks Intrinsics operació FMA3 \n", dif);

	getchar();
	return 0;
}

