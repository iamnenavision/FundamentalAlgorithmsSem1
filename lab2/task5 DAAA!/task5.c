#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

enum errors {
	INVALID_COUNT_ARG,
	INVALID_OPTION,
	REFERENCE,
	OK
};

int check_args(int argc, char *argv[]);
int my_rand(int a, int b);
void generate(int *arr, int size, int begin, int end);
void output(int *arr, int size);
void swap_max_min(int *arr, int size);
void swap(int *frst, int *sec);
int count_meet(int *arr, int size, int number, int j);
int *generate_unique(int *arr, int size, int *new_size);

int main(int argc, char *argv[]) {
	srand(time(NULL));

	int check = check_args(argc, argv);
	
	if (check == OK) {
		int begin = 0;
		int end = 0;
		int size = my_rand(1, 20);
		int arr[size];

		printf("Put borders: ");
		scanf("%d%d", &begin, &end);
		generate(arr, size, begin, end);
		output(arr, size);

		if (strcmp("s", argv[1]) == 0) {
			swap_max_min(arr, size);
			output(arr, size);
		}
		if (strcmp("g", argv[1]) == 0) {
			int new_size = 0;
			int *generate_arr = generate_unique(arr, size, &new_size);
			output(generate_arr, new_size);
			free(generate_arr);
		}
	} else {
		if (check == REFERENCE) {
			printf("s - swap max and min\n");
			printf("g - generate array\n");
		}
		if (check == INVALID_OPTION) {
			fprintf(stderr, "%s\n", "Invalid option");
		}
		if (check == INVALID_COUNT_ARG) {
			fprintf(stderr, "%s\n", "Invalid count of arguments");
		}
	}

	return 0;
}

int check_args(int argc, char *argv[]) {
	if (argc == 2) {
		if (strcmp("s", argv[1]) == 0 ||
			strcmp("g", argv[1]) == 0) {
			return OK;
		} else {
			if (strcmp("?", argv[1]) == 0) {
				return REFERENCE;
			}
		}
		return INVALID_OPTION;
	}

	return INVALID_COUNT_ARG;
}

int my_rand(int a, int b) {
	return a > 0 ? a + rand() % (b - a) : a + rand() % (abs(a) + b);
}

void generate(int *arr, int size, int begin, int end) {
	for (int i = 0; i < size; i++) {
		arr[i] = my_rand(begin, end);
	}
}

void output(int *arr, int size) {
	for (int i = 0; i < size; i++) {
		printf("%d ", arr[i]);
	}

	printf("\n");
}

void swap_max_min(int *arr, int size) {
	int index_max = 0;
	int index_min = 0;

	for (int i = 1; i < size; i++) {
		index_min = arr[i] < arr[index_min] ? i : index_min;
		index_max = arr[i] > arr[index_max] ? i : index_max;
	}

	swap(&arr[index_min], &arr[index_max]);
}

void swap(int *frst, int *sec) {
	int temp = *frst;
	*frst = *sec;
	*sec = temp;
}

int count_meet(int *arr, int size, int number, int j) {
	int meet = 1;

	for (int i = 0; i <= j; i++) {
		if (arr[i] == number)
		{
		meet += 1;}
	}

	return meet;
}

int *generate_unique(int *arr, int size, int *new_size) {
	int meet_arr[size];
	int it = 0;
	int *new_arr = (int *) malloc(sizeof(int) * size);
	if (NULL == new_arr)
	{
		return NULL;
	}

	for (int i = 0; i < size; i++) {
		meet_arr[i] = count_meet(arr, size, arr[i], i);
		if (meet_arr[i] == 2) {
			*(new_arr + it++) = *(arr + i);
			// it++;

		}



	} 

	int *ptr = realloc(new_arr, sizeof(int) * it);
	if (NULL == ptr)
	{
		return NULL;
	}
	new_arr = ptr;


	*new_size = it;


	return new_arr;
}
