/* Leetcode OJ: Given an array and a value, remove all instances of that value 
 * in place and return the new length. The order of elements can be changed. 
 * It doesn't matter what you leave beyond the new length.
 */

// 20ms for large dataset
class Solution {
public:
  int removeElement(int A[], int n, int elem) {
    int border = 0;
    for (int i = 0; i < n; i++) {
      if (A[i] != elem)
	A[border++] = A[i];
    }

    return border;

  }
};
