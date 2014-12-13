#pragma once
#ifndef PSIMD_H
#define PSIMD_H

#if defined(__CUDA_ARCH__)
	/* CUDA compiler */
	#define PSIMD_INTRINSIC __forceinline__ __device__
#elif defined(__OPENCL_VERSION__)
	/* OpenCL compiler */
	#define PSIMD_INTRINSIC inline static
#elif defined(__INTEL_COMPILER)
	/* Intel compiler, even on Windows */
	#define PSIMD_INTRINSIC inline static __attribute__((__always_inline__, __const__))
#elif defined(__GNUC__)
	/* GCC-compatible compiler (gcc/clang/icc) */
	#define PSIMD_INTRINSIC inline static __attribute__((__always_inline__, __const__))
#elif defined(_MSC_VER)
	/* MSVC-compatible compiler (cl/icl/clang-cl) */
	#define PSIMD_INTRINSIC __forceinline static
#elif defined(__cplusplus)
	/* Generic C++ compiler */
	#define PSIMD_INTRINSIC inline static
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
	/* Generic C99 compiler */
	#define PSIMD_INTRINSIC inline static
#else
	/* Generic C compiler */
	#define PSIMD_INTRINSIC static
#endif

#if defined(__cplusplus)
	#define PSIMD_CXX_SYNTAX
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112L)
	#define PSIMD_C11_SYNTAX
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901L)
	#define PSIMD_C99_SYNTAX
#else
	#define PSIMD_C89_SYNTAX
#endif

#ifndef _MSC_VER
	#include <stdint.h>
#endif

#if defined(__GNUC__)
	#define PSIMD_HAVE_F64 0
	#define PSIMD_HAVE_F32 1
	#define PSIMD_HAVE_U8 1
	#define PSIMD_HAVE_S8 1
	#define PSIMD_HAVE_U16 1
	#define PSIMD_HAVE_S16 1
	#define PSIMD_HAVE_U32 1
	#define PSIMD_HAVE_S32 1
	#define PSIMD_HAVE_U64 0
	#define PSIMD_HAVE_S64 0

	typedef float    psimd_f32 __attribute__((vector_size(16), aligned(4)));
	typedef uint8_t  psimd_u8  __attribute__((vector_size(16), aligned(1)));
	typedef int8_t   psimd_s8  __attribute__((vector_size(16), aligned(1)));
	typedef uint16_t psimd_u16 __attribute__((vector_size(16), aligned(2)));
	typedef int16_t  psimd_s16 __attribute__((vector_size(16), aligned(2)));
	typedef uint32_t psimd_u32 __attribute__((vector_size(16), aligned(4)));
	typedef int32_t  psimd_s32 __attribute__((vector_size(16), aligned(4)));

	/* Zero-initialization */
	PSIMD_INTRINSIC psimd_s8 psimd_zero_s8(void) {
		return (psimd_s8) { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	}

	PSIMD_INTRINSIC psimd_u8 psimd_zero_u8(void) {
		return (psimd_u8) { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	}

	PSIMD_INTRINSIC psimd_s16 psimd_zero_s16(void) {
		return (psimd_s16) { 0, 0, 0, 0, 0, 0, 0, 0 };
	}

	PSIMD_INTRINSIC psimd_u16 psimd_zero_u16(void) {
		return (psimd_u16) { 0, 0, 0, 0, 0, 0, 0, 0 };
	}

	PSIMD_INTRINSIC psimd_s32 psimd_zero_s32(void) {
		return (psimd_s32) { 0, 0, 0, 0 };
	}

	PSIMD_INTRINSIC psimd_u32 psimd_zero_u32(void) {
		return (psimd_u32) { 0, 0, 0, 0 };
	}

	PSIMD_INTRINSIC psimd_f32 psimd_zero_f32(void) {
		return (psimd_f32) { 0.0f, 0.0f, 0.0f, 0.0f };
	}

	/* Initialization to the same constant */
	PSIMD_INTRINSIC psimd_s8 psimd_splat_s8(int8_t c) {
		return (psimd_s8) { c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c };
	}

	PSIMD_INTRINSIC psimd_u8 psimd_splat_u8(uint8_t c) {
		return (psimd_u8) { c, c, c, c, c, c, c, c, c, c, c, c, c, c, c, c };
	}

	PSIMD_INTRINSIC psimd_s16 psimd_splat_s16(int16_t c) {
		return (psimd_s16) { c, c, c, c, c, c, c, c };
	}

	PSIMD_INTRINSIC psimd_u16 psimd_splat_u16(uint16_t c) {
		return (psimd_u16) { c, c, c, c, c, c, c, c };
	}

	PSIMD_INTRINSIC psimd_s32 psimd_splat_s32(int32_t c) {
		return (psimd_s32) { c, c, c, c };
	}

	PSIMD_INTRINSIC psimd_u32 psimd_splat_u32(uint32_t c) {
		return (psimd_u32) { c, c, c, c };
	}

	PSIMD_INTRINSIC psimd_f32 psimd_splat_f32(float c) {
		return (psimd_f32) { c, c, c, c };
	}

	/* Load vector */
	PSIMD_INTRINSIC psimd_s8 psimd_load_s8(const void* address) {
		return *((const psimd_s8*) address);
	}

	PSIMD_INTRINSIC psimd_u8 psimd_load_u8(const void* address) {
		return *((const psimd_u8*) address);
	}

	PSIMD_INTRINSIC psimd_s16 psimd_load_s16(const void* address) {
		return *((const psimd_s16*) address);
	}

	PSIMD_INTRINSIC psimd_u16 psimd_load_u16(const void* address) {
		return *((const psimd_u16*) address);
	}

	PSIMD_INTRINSIC psimd_s32 psimd_load_s32(const void* address) {
		return *((const psimd_s32*) address);
	}

	PSIMD_INTRINSIC psimd_u32 psimd_load_u32(const void* address) {
		return *((const psimd_u32*) address);
	}

	PSIMD_INTRINSIC psimd_f32 psimd_load_f32(const void* address) {
		return *((const psimd_f32*) address);
	}

	/* Store vector */
	PSIMD_INTRINSIC void psimd_store_s8(void* address, psimd_s8 value) {
		*((psimd_s8*) address) = value;
	}

	PSIMD_INTRINSIC void psimd_store_u8(void* address, psimd_u8 value) {
		*((psimd_u8*) address) = value;
	}

	PSIMD_INTRINSIC void psimd_store_s16(void* address, psimd_s16 value) {
		*((psimd_s16*) address) = value;
	}

	PSIMD_INTRINSIC void psimd_store_u16(void* address, psimd_u16 value) {
		*((psimd_u16*) address) = value;
	}

	PSIMD_INTRINSIC void psimd_store_s32(void* address, psimd_s32 value) {
		*((psimd_s32*) address) = value;
	}

	PSIMD_INTRINSIC void psimd_store_u32(void* address, psimd_u32 value) {
		*((psimd_u32*) address) = value;
	}

	PSIMD_INTRINSIC void psimd_store_f32(void* address, psimd_f32 value) {
		*((psimd_f32*) address) = value;
	}

	/* Vector addition */
	PSIMD_INTRINSIC psimd_s8 psimd_add_s8(psimd_s8 a, psimd_s8 b) {
		return a + b;
	}

	PSIMD_INTRINSIC psimd_u8 psimd_add_u8(psimd_u8 a, psimd_u8 b) {
		return a + b;
	}

	PSIMD_INTRINSIC psimd_s16 psimd_add_s16(psimd_s16 a, psimd_s16 b) {
		return a + b;
	}

	PSIMD_INTRINSIC psimd_u16 psimd_add_u16(psimd_u16 a, psimd_u16 b) {
		return a + b;
	}

	PSIMD_INTRINSIC psimd_s32 psimd_add_s32(psimd_s32 a, psimd_s32 b) {
		return a + b;
	}

	PSIMD_INTRINSIC psimd_u32 psimd_add_u32(psimd_u32 a, psimd_u32 b) {
		return a + b;
	}

	PSIMD_INTRINSIC psimd_f32 psimd_add_f32(psimd_f32 a, psimd_f32 b) {
		return a + b;
	}

	/* Vector subtraction */
	PSIMD_INTRINSIC psimd_s8 psimd_sub_s8(psimd_s8 a, psimd_s8 b) {
		return a - b;
	}

	PSIMD_INTRINSIC psimd_u8 psimd_sub_u8(psimd_u8 a, psimd_u8 b) {
		return a - b;
	}

	PSIMD_INTRINSIC psimd_s16 psimd_sub_s16(psimd_s16 a, psimd_s16 b) {
		return a - b;
	}

	PSIMD_INTRINSIC psimd_u16 psimd_sub_u16(psimd_u16 a, psimd_u16 b) {
		return a - b;
	}

	PSIMD_INTRINSIC psimd_s32 psimd_sub_s32(psimd_s32 a, psimd_s32 b) {
		return a - b;
	}

	PSIMD_INTRINSIC psimd_u32 psimd_sub_u32(psimd_u32 a, psimd_u32 b) {
		return a - b;
	}

	PSIMD_INTRINSIC psimd_f32 psimd_sub_f32(psimd_f32 a, psimd_f32 b) {
		return a - b;
	}

	/* Vector multiplication */
	PSIMD_INTRINSIC psimd_s8 psimd_mul_s8(psimd_s8 a, psimd_s8 b) {
		return a * b;
	}

	PSIMD_INTRINSIC psimd_u8 psimd_mul_u8(psimd_u8 a, psimd_u8 b) {
		return a * b;
	}

	PSIMD_INTRINSIC psimd_s16 psimd_mul_s16(psimd_s16 a, psimd_s16 b) {
		return a * b;
	}

	PSIMD_INTRINSIC psimd_u16 psimd_mul_u16(psimd_u16 a, psimd_u16 b) {
		return a * b;
	}

	PSIMD_INTRINSIC psimd_s32 psimd_mul_s32(psimd_s32 a, psimd_s32 b) {
		return a * b;
	}

	PSIMD_INTRINSIC psimd_u32 psimd_mul_u32(psimd_u32 a, psimd_u32 b) {
		return a * b;
	}

	PSIMD_INTRINSIC psimd_f32 psimd_mul_f32(psimd_f32 a, psimd_f32 b) {
		return a * b;
	}

	/* Vector blend */
	PSIMD_INTRINSIC psimd_s8 psimd_blend_s8(psimd_s8 mask, psimd_s8 a, psimd_s8 b) {
		return (mask & a) | (~mask & b);
	}

	PSIMD_INTRINSIC psimd_u8 psimd_blend_u8(psimd_u8 mask, psimd_u8 a, psimd_u8 b) {
		return (mask & a) | (~mask & b);
	}
	
	PSIMD_INTRINSIC psimd_s16 psimd_blend_s16(psimd_s16 mask, psimd_s16 a, psimd_s16 b) {
		return (mask & a) | (~mask & b);
	}

	PSIMD_INTRINSIC psimd_u16 psimd_blend_u16(psimd_u16 mask, psimd_u16 a, psimd_u16 b) {
		return (mask & a) | (~mask & b);
	}
	
	PSIMD_INTRINSIC psimd_s32 psimd_blend_s32(psimd_s32 mask, psimd_s32 a, psimd_s32 b) {
		return (mask & a) | (~mask & b);
	}

	PSIMD_INTRINSIC psimd_u32 psimd_blend_u32(psimd_u32 mask, psimd_u32 a, psimd_u32 b) {
		return (mask & a) | (~mask & b);
	}
	
	PSIMD_INTRINSIC psimd_f32 psimd_blend_f32(psimd_s32 mask, psimd_f32 a, psimd_f32 b) {
		return (psimd_f32) psimd_blend_s32(mask, (psimd_s32) a, (psimd_s32) b);
	}

	/* Vector absolute value */
	PSIMD_INTRINSIC psimd_f32 psimd_abs_f32(psimd_f32 v) {
		const psimd_s32 mask = (psimd_s32) psimd_splat_f32(-0.0f);
		return (psimd_f32) ((psimd_s32) v & mask);
	}

	/* Vector negation */
	PSIMD_INTRINSIC psimd_f32 psimd_neg_f32(psimd_f32 v) {
		const psimd_s32 mask = (psimd_s32) psimd_splat_f32(-0.0f);
		return (psimd_f32) ((psimd_s32) v ^ mask);
	}

	/* Vector maximum */
	PSIMD_INTRINSIC psimd_s8 psimd_max_s8(psimd_s8 a, psimd_s8 b) {
		return psimd_blend_s8(a > b, a, b);
	}

	PSIMD_INTRINSIC psimd_u8 psimd_max_u8(psimd_u8 a, psimd_u8 b) {
		return psimd_blend_u8(a > b, a, b);
	}

	PSIMD_INTRINSIC psimd_s16 psimd_max_s16(psimd_s16 a, psimd_s16 b) {
		return psimd_blend_s16(a > b, a, b);
	}

	PSIMD_INTRINSIC psimd_u16 psimd_max_u16(psimd_u16 a, psimd_u16 b) {
		return psimd_blend_u16(a > b, a, b);
	}

	PSIMD_INTRINSIC psimd_s32 psimd_max_s32(psimd_s32 a, psimd_s32 b) {
		return psimd_blend_s32(a > b, a, b);
	}

	PSIMD_INTRINSIC psimd_u32 psimd_max_u32(psimd_u32 a, psimd_u32 b) {
		return psimd_blend_u32(a > b, a, b);
	}

	PSIMD_INTRINSIC psimd_f32 psimd_max_f32(psimd_f32 a, psimd_f32 b) {
		return psimd_blend_f32(a > b, a, b);
	}

	/* Vector minimum */
	PSIMD_INTRINSIC psimd_s8 psimd_min_s8(psimd_s8 a, psimd_s8 b) {
		return psimd_blend_s8(a < b, a, b);
	}

	PSIMD_INTRINSIC psimd_u8 psimd_min_u8(psimd_u8 a, psimd_u8 b) {
		return psimd_blend_u8(a < b, a, b);
	}

	PSIMD_INTRINSIC psimd_s16 psimd_min_s16(psimd_s16 a, psimd_s16 b) {
		return psimd_blend_s16(a < b, a, b);
	}

	PSIMD_INTRINSIC psimd_u16 psimd_min_u16(psimd_u16 a, psimd_u16 b) {
		return psimd_blend_u16(a < b, a, b);
	}

	PSIMD_INTRINSIC psimd_s32 psimd_min_s32(psimd_s32 a, psimd_s32 b) {
		return psimd_blend_s32(a < b, a, b);
	}

	PSIMD_INTRINSIC psimd_u32 psimd_min_u32(psimd_u32 a, psimd_u32 b) {
		return psimd_blend_u32(a < b, a, b);
	}

	PSIMD_INTRINSIC psimd_f32 psimd_min_f32(psimd_f32 a, psimd_f32 b) {
		return psimd_blend_f32(a < b, a, b);
	}

	/* Vector unpack */
	#if defined(__clang__)
		PSIMD_INTRINSIC psimd_s16 psimd_unpacklo_s16(psimd_s16 a, psimd_s16 b) {
			return __builtin_shufflevector(a, b, 0, 8+0, 1, 8+1, 2, 8+2, 3, 8+3);
		}

		PSIMD_INTRINSIC psimd_s16 psimd_unpackhi_s16(psimd_s16 a, psimd_s16 b) {
			return __builtin_shufflevector(a, b, 4, 8+4, 5, 8+5, 6, 8+6, 7, 8+7);
		}

		PSIMD_INTRINSIC psimd_u16 psimd_unpacklo_u16(psimd_u16 a, psimd_u16 b) {
			return __builtin_shufflevector(a, b, 0, 8+0, 1, 8+1, 2, 8+2, 3, 8+3);
		}

		PSIMD_INTRINSIC psimd_u16 psimd_unpackhi_u16(psimd_u16 a, psimd_u16 b) {
			return __builtin_shufflevector(a, b, 4, 8+4, 5, 8+5, 6, 8+6, 7, 8+7);
		}

		PSIMD_INTRINSIC psimd_s32 psimd_unpacklo_s32(psimd_s32 a, psimd_s32 b) {
			return __builtin_shufflevector(a, b, 0, 4+0, 1, 4+1);
		}

		PSIMD_INTRINSIC psimd_s32 psimd_unpackhi_s32(psimd_s32 a, psimd_s32 b) {
			return __builtin_shufflevector(a, b, 2, 4+2, 3, 4+3);
		}

		PSIMD_INTRINSIC psimd_u32 psimd_unpacklo_u32(psimd_u32 a, psimd_u32 b) {
			return __builtin_shufflevector(a, b, 0, 4+0, 1, 4+1);
		}

		PSIMD_INTRINSIC psimd_u32 psimd_unpackhi_u32(psimd_u32 a, psimd_u32 b) {
			return __builtin_shufflevector(a, b, 2, 4+2, 3, 4+3);
		}

		PSIMD_INTRINSIC psimd_f32 psimd_unpacklo_f32(psimd_f32 a, psimd_f32 b) {
			return __builtin_shufflevector(a, b, 0, 4+0, 1, 4+1);
		}

		PSIMD_INTRINSIC psimd_f32 psimd_unpackhi_f32(psimd_f32 a, psimd_f32 b) {
			return __builtin_shufflevector(a, b, 2, 4+2, 3, 4+3);
		}
	#else
		PSIMD_INTRINSIC psimd_s16 psimd_unpacklo_s16(psimd_s16 a, psimd_s16 b) {
			return __builtin_shuffle(a, b, (psimd_s16) { 0, 8+0, 1, 8+1, 2, 8+2, 3, 8+3 });
		}

		PSIMD_INTRINSIC psimd_s16 psimd_unpackhi_s16(psimd_s16 a, psimd_s16 b) {
			return __builtin_shuffle(a, b, (psimd_s16) { 4, 8+4, 5, 8+5, 6, 8+6, 7, 8+7 });
		}

		PSIMD_INTRINSIC psimd_u16 psimd_unpacklo_u16(psimd_u16 a, psimd_u16 b) {
			return __builtin_shuffle(a, b, (psimd_s16) { 0, 8+0, 1, 8+1, 2, 8+2, 3, 8+3 });
		}

		PSIMD_INTRINSIC psimd_u16 psimd_unpackhi_u16(psimd_u16 a, psimd_u16 b) {
			return __builtin_shuffle(a, b, (psimd_s16) { 4, 8+4, 5, 8+5, 6, 8+6, 7, 8+7 });
		}

		PSIMD_INTRINSIC psimd_s32 psimd_unpacklo_s32(psimd_s32 a, psimd_s32 b) {
			return __builtin_shuffle(a, b, (psimd_s32) { 0, 4+0, 1, 4+1 });
		}

		PSIMD_INTRINSIC psimd_s32 psimd_unpackhi_s32(psimd_s32 a, psimd_s32 b) {
			return __builtin_shuffle(a, b, (psimd_s32) { 2, 4+2, 3, 4+3 });
		}

		PSIMD_INTRINSIC psimd_u32 psimd_unpacklo_u32(psimd_u32 a, psimd_u32 b) {
			return __builtin_shuffle(a, b, (psimd_s32) { 0, 4+0, 1, 4+1 });
		}

		PSIMD_INTRINSIC psimd_u32 psimd_unpackhi_u32(psimd_u32 a, psimd_u32 b) {
			return __builtin_shuffle(a, b, (psimd_s32) { 2, 4+2, 3, 4+3 });
		}

		PSIMD_INTRINSIC psimd_f32 psimd_unpacklo_f32(psimd_f32 a, psimd_f32 b) {
			return __builtin_shuffle(a, b, (psimd_s32) { 0, 4+0, 1, 4+1 });
		}

		PSIMD_INTRINSIC psimd_f32 psimd_unpackhi_f32(psimd_f32 a, psimd_f32 b) {
			return __builtin_shuffle(a, b, (psimd_s32) { 2, 4+2, 3, 4+3 });
		}
	#endif
#endif

#endif /* PSIMD_H */