#include "helper.h"
#include <cstdint>
#include <cstdio>
#include <immintrin.h>
#include <limits>

typedef float f32;
typedef double f64;
typedef int8_t i8;
typedef uint8_t u8;
typedef int16_t i16;
typedef uint16_t u16;
typedef int32_t i32;
typedef uint32_t u32;

static void avx512_f64_mult()
{
	using type = f64;
	puts("Задание 1. f64 C = A * B");
	type c[8] = {};
	type a[8] = {1.1,   13.37, 3.5, 1.0,
		     -10.0, 8.8,   0.0, std::numeric_limits<type>::quiet_NaN()};

	type b[8] = {2.28,
		     54.6,
		     0.0,
		     std::numeric_limits<type>::max(),
		     std::numeric_limits<type>::min(),
		     99099.9,
		     -0.0,
		     0.5f};

	printf("a: ");
	print_array(std::span{a, 8});
	printf("b: ");
	print_array(std::span{b, 8});

	auto vec_a = _mm512_load_pd(a);
	auto vec_b = _mm512_load_pd(b);
	auto vec_c = _mm512_mul_pd(vec_a, vec_b);
	_mm512_store_pd(c, vec_c);

	printf("c: ");
	print_array(std::span{c, 8});
}

static void avx512_f32_div()
{
	using type = f32;
	puts("Задание 2. f32 C = A / B");
	type a[16] = {1.1f,
		      13.37f,
		      3.5f,
		      1.0f,
		      3.5,
		      111.0,
		      -std::numeric_limits<type>::infinity(),
		      -10.0,
		      -10.0f,
		      8.8f,
		      0.5f,
		      std::numeric_limits<type>::min(),
		      -0.1f,
		      12.3f,
		      0.0f,
		      std::numeric_limits<type>::quiet_NaN()};

	type b[16] = {2.28f,
		      std::numeric_limits<type>::infinity(),
		      54.6f,
		      74.8f,
		      360000000.44f,
		      0.0f,
		      21.19f,
		      123.456f,
		      789.012f,
		      11.09f,
		      2025.1f,
		      99099.9f,
		      -0.0f,
		      std::numeric_limits<type>::max(),
		      std::numeric_limits<type>::min(),
		      0.5f};
	type c[16] = {};

	printf("a: ");
	print_array(std::span{a, 16});
	printf("b: ");
	print_array(std::span{b, 16});

	auto vec_a = _mm512_load_ps(a);
	auto vec_b = _mm512_load_ps(b);
	auto vec_c = _mm512_div_ps(vec_a, vec_b);
	_mm512_store_ps(c, vec_c);

	printf("c: ");
	print_array(std::span{c, 16});
}

static void avx512_i32_sub()
{
	using type = i32;
	puts("Задание 3. i32 C = A - B");
	type a[16] = {0, 1, std::numeric_limits<type>::min(), 11, 256, 4, 99, 0, 1, 38, 4, 211, 0, 2, 19, std::numeric_limits<type>::max()};
	type b[16] = {0, -1, 2, -3, 4, -5, 6, -7, 8, -9, 10, -11, 12, -13, 14, -15};
	type c[16] = {};

	printf("a: ");
	print_array(std::span{a, 16});
	printf("b: ");
	print_array(std::span{b, 16});

	auto vec_a = _mm512_load_si512((__m256i *)a);
	auto vec_b = _mm512_load_si512((__m256i *)b);
	auto vec_res = _mm512_sub_epi32(vec_a, vec_b);
	_mm512_store_si512((__m256i *)c, vec_res);

	printf("c: ");
	print_array(std::span{c, 16});
}

static void avx512_i8_sum()
{
	using type = i8;
	puts("Задание 5. i8 C = A + B");
	type a[32] = "Этот текст из 32 Б.";
	type b[32] = "This string has just 2^5 bytes.";
	type c[32] = {};

	printf("a: ");
	print_array(std::span{a, 32});
	printf("b: ");
	print_array(std::span{b, 32});

	auto vec_a = _mm256_load_si256((__m256i *)a);
	auto vec_b = _mm256_load_si256((__m256i *)b);
	auto vec_res = _mm256_add_epi8(vec_a, vec_b);
	_mm256_store_si256((__m256i *)c, vec_res);

	printf("c: ");
	print_array(std::span{c, 32});
}

static void avx512_u16_sum()
{
	using type = u16;
	puts("Задание 4. u16 C = A + B");
	type a[16] = {0,   1,	std::numeric_limits<type>::max(),
		      11,  220, 4,
		      99,  1,	12,
		      177, 11,	12,
		      13,  14,	88};
	type b[16] = {1,  38,  4,   125,
		      0,  2,   19,  std::numeric_limits<type>::max(),
		      99, 100, 111, 112,
		      26, 128, 66};
	type c[16] = {};

	printf("a: ");
	print_array(std::span{a, 16});
	printf("b: ");
	print_array(std::span{b, 16});

	auto vec_a = _mm256_load_si256((__m256i *)a);
	auto vec_b = _mm256_load_si256((__m256i *)b);
	auto vec_res = _mm256_adds_epu8(vec_a, vec_b);
	_mm256_store_si256((__m256i *)c, vec_res);

	printf("c: ");
	print_array(std::span{c, 16});
}

int main()
{
	avx512_f64_mult();
	std::println();

	avx512_f32_div();
	std::println();

	avx512_i32_sub();
	std::println();

	avx512_u16_sum();
	std::println();

	avx512_i8_sum();

	puts("Нажмите любую кнопку для завершения");
	(void)getchar();
	return 0;
}
