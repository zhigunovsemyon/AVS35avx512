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

static void avx512_i32_sub()
{
	using type = i32;
	puts("Задание 1. i32 C = A - B");
	type a[8] = {0, 1, std::numeric_limits<type>::min(), 11, 256, 4, 99, 0};
	type b[8] = {1, 38, 4, 211, 0, 2, 19, std::numeric_limits<type>::max()};
	type c[8] = {};

	printf("a: ");
	print_array(std::span{a, 8});
	printf("b: ");
	print_array(std::span{b, 8});

	auto vec_a = _mm256_load_si256((__m256i *)a);
	auto vec_b = _mm256_load_si256((__m256i *)b);
	auto vec_res = _mm256_sub_epi32(vec_a, vec_b);
	_mm256_store_si256((__m256i *)c, vec_res);

	printf("c: ");
	print_array(std::span{c, 8});
}

static void avx512_i8_sum()
{
	using type = i8;
	puts("Задание 3. i8 C = A + B");
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
	puts("Задание 2. u16 C = A + B");
	type a[16] = {0,   1,	 std::numeric_limits<type>::max(),
		      11,  220, 4,
		      99,  1,	 12,
		      177, 11,	 12,
		      13, 14,	 88};
	type b[16] = {1,   38,	4,   125,
		      0,   2,	19,  std::numeric_limits<type>::max(),
		      99, 100, 111, 112,
		      26,  128, 66};
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
	avx512_i32_sub();
	std::println();

	avx512_u16_sum();
	std::println();
	
	avx512_i8_sum();

	puts("Нажмите любую кнопку для завершения");
	(void)getchar();
	return 0;
}
