#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int sudoku[9][9];

int available_values[9];
int available_indexes[9];

/* map array index to matrix */
void convert_array_index_to_matrix(int index, int *m_row, int *m_col) {
    *m_row = index / 3;
    *m_col = index % 3;
}

/* initialize matrix */
void setup_matrix() {
	int i, j;
	for(i = 0; i < 9; i++) {
		for(j = 0; j < 9; j++) {
			sudoku[i][j] = 0;
		}
	}
}

/* print sudoku board */
void print_sudoku() {
	int i, j;
	printf("\n+-----+-----+-----+\n");
        for(i=1; i<10; ++i)
        {
            for(j=1; j<10; ++j) printf("|%d", sudoku[i-1][j-1]);
            printf("|\n");
            if (i%3 == 0) printf("+-----+-----+-----+\n");
        }
}

/* initialize arrays */
void setup_arrays() {
    int i;
	for(i = 0; i < 9; i++) {
		available_values[i] = i + 1;
		available_indexes[i] = i;
	}
}

/* set an index on available_indexes so it wont be used again on the same sudoku block */
void set_index_not_available(int index, int array_size) {
	if(index != (array_size - 1)) {
		available_indexes[index] = available_indexes[array_size - 1];
	}
}

/* set an index on available_values so it wont be used again on the same sudoku block */
void set_value_not_available(int index, int array_size) {
	if(index != (array_size - 1)) {
		available_values[index] = available_values[array_size - 1];
	}
}

/* verify if the value on sudoku[row][col] is valid */
int check_row_column(int value, int row, int col) {
	int i;

	/* check row */ 
	for(i = 0; i < 9; i++) {
		if(i == col) continue;
		if(sudoku[row][i] == value) return 0;
	}
	/* check column */ 
	for(i = 0; i < 9; i++) {
		if(i == row) continue;
		if(sudoku[i][col] == value) return 0;
	}

	return 1;
}

/* fill sudoku block */
void fill_grid(int ini_row, int ini_col) {
	setup_arrays();

    int cont = rand() % 4;

	int value_index, array_index, array_size = 9;
	int m_row = 0, m_col = 0;

	while(cont > 0) {
		/* Choose random position */
		array_index = rand() % array_size;
		convert_array_index_to_matrix(available_indexes[array_index], &m_row, &m_col);

		m_row = m_row + ini_row;
		m_col = m_col + ini_col;

		/* Choose random value */
		value_index = rand() % array_size;

		if(check_row_column(available_values[value_index], m_row, m_col) == 1) {
			sudoku[m_row][m_col] = available_values[value_index];
			set_index_not_available(array_index, array_size);
			set_value_not_available(array_index, array_size);
			array_size--;
			cont--;
		}
	}

}

/* generate sudoku board */
void fill_board() {
	int i;
	int aux = 0;

	setup_matrix();

	for(i = 0; i < 9; i = i+3) {
		fill_grid(i, aux);
		fill_grid(i, aux + 3);
		fill_grid(i, aux + 6);
	}
}

main() {
	srand(time(NULL));
	fill_board();
	print_sudoku();
}
