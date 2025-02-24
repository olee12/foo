//============================================================================
// Search a 2D Matrix
// Write an efficient algorithm that searches for a value in an m x n matrix.
// This matrix has the following properties:
//
// Integers in each row are sorted from left to right.
// The first integer of each row is greater than the last integer of the previous row.
// For example,
//
// Consider the following matrix:
//
// [
//  [1,   3,  5,  7],
//  [10, 11, 16, 20],
//  [23, 30, 34, 50]
// ]
//Given target = 3, return true.
//============================================================================

#include <iostream>
#include <vector>
using namespace std;

// dhu note: this solution is not the best because it takes O(m + n). 
// The best solution should be a binary search variant.
class Solution {
public:
  bool searchMatrix(vector<vector<int> > &matrix, int target) {
    int M = matrix.size();
    if (M == 0) return false;
    int N = matrix[0].size();
    if (N == 0) return false;
    if (target < matrix[0][0] || target > matrix[M-1][N-1]) return false;
    int i = 0, j = N - 1;
    while (i < M && j >= 0) {
      if (matrix[i][j] < target) i++;
      else if (matrix[i][j] > target) j--;
      else return true;
    }
    return false;
  }
};

int main() {
  return 0;
}
