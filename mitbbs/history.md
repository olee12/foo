1. permuation with duplicate
<br>http://www.mitbbs.com/article_t/JobHunting/32603015.html

2. MInimize cash flow among lenders and borrowers
<br>http://www.geeksforgeeks.org/minimize-cash-flow-among-given-set-friends-borrowed-money/

3. Validate BST: variant
<br>http://www.mitbbs.com/article_t/JobHunting/32605903.html

4. һ����ά���飬Ԫ����0��1���ҳ�������1���ɵ�"X"��״ (done)
<br>http://www.mitbbs.com/article_t/JobHunting/32620157.html
<br>�����κ�һ���� i,j,��4������ֱ��ʾ�Ըõ�Ϊ����,����,����,����б�ŵ�������1�ĸ���(���Լ�). ��ô�õ�Ϊ���ĵ����X��1�ĸ���Ϊmin(4���������)*4-3.���ֵ����dp��ϵ,������Ϊ��:
<br>dp[i][j][0] = dp[i-1][j-1][0]+1;  if A[i][j]==1
<br>dp[i][j][0] = 0;                  if A[i][j]==0
<br>�ĸ��������һ��,�������dp[i][j][0..3], ���˾Ϳ��Եó������Ǹ���.

5. �������飬��������ֶ���0 to n-1, and no duplicate. ʹ��swap_with_zero�ѵڶ�����ɵ�һ��.
<br>http://www.mitbbs.com/article_t/JobHunting/32620793.html
<br>http://cs.stackexchange.com/questions/13930/rearrange-an-array-using-swap-with-0

6. Rocket Fuel: (#1: Deque without pop_front; #3: Auto Racers)
<br>http://www.mitbbs.com/article_t/JobHunting/32613553.html
<br>http://get-that-job-at-google.blogspot.com/2013/02/rocketfuel-codesprint-at-iit-bombay.html
<br>Solution to "Auto Racers":
<br>Divide n races into sqrn(n) buckets. Each bucket will have sqrt(n) racers' starting times.
Then scan the racers either by ending time in incremental order, or by starting time in decreasing orders.
If we scan ending time in incremental order, find the number of racers whose starting times are later than
the current racer. This number will be the score that we are looking for. Each scan takes O(sqrn(n)) time.
Thus the total time complexity is O(n * sqrn(n)), aka. O(n^1.5), which is better than O(n^2). 

