#pragma once
#include <cstdint>
#include <random>
#include <iostream>
#include <algorithm>

typedef int64_t i64;
typedef uint64_t ui64;
typedef uint32_t ui;
typedef unsigned char uchar;
#define FOR(i, n, k)	for (ui64 i = 0; i < (n); i += (k))

namespace datagen {

	template <typename Item>
	void random_writer(Item* A, ui64 n) {
		std::default_random_engine g;
		if constexpr (std::is_same<Item, char>::value || std::is_same<Item, uchar>::value) {		// handle char type separately
			std::uniform_int_distribution<ui> d(0, 25);
			FOR(i, n, 1) A[i] = 'a' + d(g);
		}
		else {
			typedef std::conditional<std::is_integral<Item>::value,
				std::uniform_int_distribution<Item>,
				std::uniform_real_distribution<Item>>::type dist;
			dist d;
			FOR(i, n, 1) A[i] = d(g);
		}
	}

	template <typename Item>
	void pareto_writer(Item* A, ui64 n) {
		ui64 a = 6364136223846793005, c = 1442695040888963407, x = 1;
		double ED = 20;
		double alpha = 1, beta = 7;
		ui64 sum = 0, keys = 0, y = 889;
		ui64 maxF = 0;
		ui64 ceiling = 100000;
		FOR(i, n, 1) {
			x = x * a + c;
			y = y * a + c;
			// generate frequency from the Pareto distribution with alpha=1; otherwise, the generator gets slow
			double u = (double)y / ((double)(1LLU << 63) * 2);				// uniform [0,1]
			ui64 f = std::min<double>(ceil(beta * (1 / (1 - u) - 1)), ceiling);		// rounded-up Pareto
			
			if constexpr (std::is_same<Item, char>::value || std::is_same<Item, uchar>::value)
				A[i] = 'a' + (f % 26);
			else A[i] = f;
		}
	}

	template <typename Item>
	void print_arr(Item* A, ui64 n) {
		FOR(i, n, 1) {
			if constexpr (std::is_same<Item, ui>::value)
				printf("%12lu ", A[i]);
			else if constexpr (std::is_same<Item, int>::value)
				printf("%12lu ", A[i]);
			else if constexpr (std::is_same<Item, i64>::value || std::is_same<Item, ui64>::value)
				printf("%12llX ", A[i]);
			else if constexpr (std::is_same<Item, float>::value)
				printf("%12lf ", A[i]);
			else if constexpr (std::is_same<Item, double>::value)
				printf("%12llf ", A[i]);
			else if constexpr (std::is_same<Item, char>::value)
				printf("%c ", A[i]);
		}
		printf("\n");
	}
}
