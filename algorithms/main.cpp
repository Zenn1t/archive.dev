#define SERVICE_NAME "main"

#include "pch.hpp"
#include <Log.hpp>

#include "sorting/insertion.hpp"
#include "sorting/merge.hpp"

int main() {
	lI("Start Programm");
	constexpr int l = 8;
	int i_m[] = { 2,2,2,2,1,1,3,3,4 };

	lI("Array before sort:"); for (int i : i_m) { std::cout << i << " "; }  std::cout << "\n";
		
	smerge(i_m, l);

	lI("Array after sort:"); for (int i : i_m) { std::cout << i << " "; }  std::cout << "\n";



	return 0;
}
