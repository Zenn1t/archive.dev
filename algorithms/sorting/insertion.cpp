#define SERVICE_NAME "sort-insertion"

#include "Log.hpp"

#include "insertion.hpp"

// todo: alle Typen - use templates 

void swap(int* arr, int pos1, int pos2) {
	int t = arr[pos1];
	arr[pos1] = arr[pos2];
	arr[pos2] = t;
}

void insertion_sort(int* arr, const int s_arr) {
	for (int i = 1; i < s_arr; ++i) {

		for (int j = i; j != 0; j--) {

			if (arr[j - 1] <= arr[j]) {
				break;
			}

			swap(arr, j - 1, j);
		}
	}
}
