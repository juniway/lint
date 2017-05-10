/*
n prisoners are standing on a circle, sequentially numbered from 0 to n − 1.
An executioner walks along the circle, starting from prisoner 0, removing every k-th prisoner and killing him.
As the process goes on, the circle becomes smaller and smaller, until only one prisoner remains, who is then freed.

For example, if there are n = 5 prisoners and k = 2,
the order the prisoners are killed in (let's call it the "killing sequence")
will be 1, 3, 0, and 4, and the survivor will be #2.

Task Given any n,k > 0, find out which prisoner will be the final survivor.
In one such incident, there were 41 prisoners and every 3rd prisoner was being killed (k = 3).
Among them was a clever chap name Josephus who worked out the problem, stood at the surviving position,
and lived on to tell the tale. Which number was he?
*/
// http://www.geeksforgeeks.org/josephus-problem-set-1-a-on-solution/

#include <stdio.h>

int josephus(int n, int k) {
  if (n == 1)
    return 1;
  else
    /* The position returned by josephus(n - 1, k) is adjusted because the
       recursive call josephus(n - 1, k) considers the original position
       k%n + 1 as position 1 */
    return (josephus(n - 1, k) + k-1) % n + 1;

	// =========================
	// iterative method
    /*int a = 0;
	for(int i = 2; i <= n; i++) {
		a = (a + k) % i + 1;
		cout << a << endl;
	}
	return a + 1;*/
	// =========================

}

// Driver Program to test above function
int main() {
  int n = 14;
  int k = 2;
  printf("The chosen place is %d", josephus(n, k));
  return 0;
}