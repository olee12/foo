/* Leetcode OJ: Find the contiguous subarray within an array 
 * (containing at least one number) which has the largest sum.
 * For example, given the array [�|2,1,�|3,4,�|1,2,1,�|5,4],
 * the contiguous subarray [4,�|1,2,1] has the largest sum = 6.
 */

class Solution {
public:
  // 48ms for large dataset
  int maxSubArray(int A[], int n) {
    if (n == 0)
      return 0;

    int result = A[0];
    int tmp = A[0];
    for (int i = 1; i < n; i++) {
      if (tmp < 0) 
	tmp = A[i];
      else
	tmp += A[i];
      if (result < tmp)
	result = tmp;
    }

    return result;
  }
};
