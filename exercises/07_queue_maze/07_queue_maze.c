#include <stdio.h>
#include <stdlib.h>

#define MAX_ROW 5
#define MAX_COL 5

int maze[MAX_ROW][MAX_COL] = {
	0, 1, 0, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 1, 0,
};

int visited[MAX_ROW][MAX_COL];
int prev_row[MAX_ROW][MAX_COL];
int prev_col[MAX_ROW][MAX_COL];

int directions[4][2] = {
	{-1, 0},
	{1, 0},
	{0, -1},
	{0, 1},
};

int in_bounds(int row, int col)
{
	return row >= 0 && row < MAX_ROW && col >= 0 && col < MAX_COL;
}

int main(void)
{
	int queue_row[MAX_ROW * MAX_COL];
	int queue_col[MAX_ROW * MAX_COL];
	int head = 0;
	int tail = 0;

	for (int i = 0; i < MAX_ROW; i++) {
		for (int j = 0; j < MAX_COL; j++) {
			visited[i][j] = 0;
			prev_row[i][j] = -1;
			prev_col[i][j] = -1;
		}
	}

	queue_row[tail] = 0;
	queue_col[tail] = 0;
	tail++;
	visited[0][0] = 1;

	int found = 0;

	while (head < tail) {
		int r = queue_row[head];
		int c = queue_col[head];
		head++;

		if (r == MAX_ROW - 1 && c == MAX_COL - 1) {
			found = 1;
			break;
		}

		for (int k = 0; k < 4; k++) {
			int nr = r + directions[k][0];
			int nc = c + directions[k][1];

			if (!in_bounds(nr, nc)) {
				continue;
			}

			if (visited[nr][nc]) {
				continue;
			}

			if (maze[nr][nc] != 0) {
				continue;
			}

			visited[nr][nc] = 1;
			prev_row[nr][nc] = r;
			prev_col[nr][nc] = c;
			queue_row[tail] = nr;
			queue_col[tail] = nc;
			tail++;
		}
	}

	if (!found) {
		printf("No path!\n");
		return 0;
	}

	int path_row[MAX_ROW * MAX_COL];
	int path_col[MAX_ROW * MAX_COL];
	int count = 0;
	int cr = MAX_ROW - 1;
	int cc = MAX_COL - 1;

	while (cr != -1 && cc != -1) {
		path_row[count] = cr;
		path_col[count] = cc;
		count++;

		int pr = prev_row[cr][cc];
		int pc = prev_col[cr][cc];
		cr = pr;
		cc = pc;
	}

	for (int i = 0; i < count; i++) {
		printf("(%d, %d)\n", path_row[i], path_col[i]);
	}

	return 0;
}
