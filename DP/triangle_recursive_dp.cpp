int n, triangle[100][100];
int cache2[100][100];
int path2(int y, int x){
	if(y == n -1) return triangle[y][x];
	cache2[y][x] = max(cache2[y - 1][x], cache2[y - 1][x - 1]) + triangle[y][x];
	return cache2[y][x] = path2(y);
}