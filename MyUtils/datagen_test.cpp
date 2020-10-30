#pragma once
#include "datagen.h"

int main() {
	using T = ui;
	const ui n = 100;
	T* d = new T[n];
	
	//datagen::random_writer<T>(d, n);
	datagen::pareto_writer<T>(d, n);
	datagen::print_arr<T>(d, n);

	delete[] d;
}