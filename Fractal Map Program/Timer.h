#pragma once

#include <chrono>
#include <iostream>
#include <functional>

struct timer {

	template<typename F>
	static void function_timer(F func, string message) {
		std::cout << message;
		auto start = std::chrono::high_resolution_clock::now();
		func();
		auto stop = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = stop - start;
	
		std::cout << " Elapsed time: " << elapsed.count() << std::endl;
		
	}

};