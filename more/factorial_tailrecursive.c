// 尾递归，《算法精解》page 35
		   / a 如果 n = 0, n = 1
F(n, a) = |
		   \ F(n - 1, a) 如果 n > 1


// 如果一个函数中所有递归形式的调用都出现在函数的末尾，我们称这个递归函数是尾递归的
// 当递归调用是整个函数体中最后执行的语句，且它的返回值不属于表达式的一部分时，
// 这个递归调用就是尾递归

int facttail(int n, int a){
	if(n < 0)
		return 0;
	else if(n == 0)
		return 1;
	else if(n == 1)
		return a;
	else
		return facttail(n - 1, na);
}