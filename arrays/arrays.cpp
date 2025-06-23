#include<bits/stdc++.h>
using namespace std;


// check if an array is sorted and rotated
bool check(vector<int>& nums) {
    int i = 0;
    int j = 1;
    int n = nums.size();
    while(j<n){
        if(nums[i]<=nums[j]){
            i++;
            j++;
        }
        else{
            if(nums[i]>=nums[j]){
                j++;
            }
            else{
                return false;
            }
        }
    }
    return true;
}


// remove duplicates from a sorted array
int removeDuplicates(vector<int>& nums) {
    int n = nums.size();
    int i = 1; 
    for(int j=1;j<n;j++){
        if(nums[i] != nums[j]){
            i++;
            nums[i] = nums[j];
        }
    }
    return i+1;
}



// maximum consecutive ones
int findMaxConsecutiveOnes(vector<int>& nums) {
    int maxi = 0;
    int count = 0;
    for(int i = 0;i<nums.size();i++){
        if(nums[i] == 1){
            count++;
        }
        else{
            maxi = max(maxi,count);
            count = 0;
        }
    }
    maxi = max(maxi,count);
    return maxi;
}



// maximum subarray  -  kadane's algo 
int maxSubArray(vector<int>& arr) {
    int sum = 0;
    int maxSum = INT_MIN;
    for(int num:arr){
        if(sum<0)sum = 0;

        sum+=num;
        maxSum = max(maxSum,sum);
    }
    return maxSum;
}



int pairWithMaxSum(vector<int>& arr) {
    sort(arr.begin(), arr.end());
    int maxSum = 0;
    for(int i = 0; i<arr.size()-1; i++){
        for(int j = i+1 ; j<arr.size()-1; j++ ){
            maxSum = max(maxSum,arr[i]+arr[i+1]);
        }
    }
    return maxSum;
}




// LC - 2149. Rearrange Array Elements by Sign
vector<int> rearrangeArray(vector<int>& nums) {
    queue<int> positives;
    queue<int> negatives;
    for(int num: nums){
        if(num>=0)positives.push(num);
        else negatives.push(num);
    }

    vector<int> ans;
    while(!positives.empty() || !negatives.empty()){
        int positive = positives.front();
        int negative = negatives.front();
        positives.pop();
        negatives.pop();
        ans.push_back(positive);
        ans.push_back(negative);
    }
    return ans;
}



// LC - 2149. Rearrange Array Elements by Sign
// more optimal solution 
vector<int> rearrangeArray(vector<int>& nums) {
    int n = nums.size();
    int negPointer = 0;
    int posPointer = 0;

    vector<int> ans;
    while(negPointer<n || posPointer<n){
        while(posPointer<n && nums[posPointer]<0){
            posPointer++;
        }
        while(negPointer<n && nums[negPointer]>=0){
            negPointer++;
        }
        
        if(posPointer<n) ans.push_back(nums[posPointer]);
        if(negPointer<n) ans.push_back(nums[negPointer]);
        
        posPointer++;
        negPointer++;
    }

    return ans;
}




// LC - 128 - longest consecutive subsequence
int longestConsecutive(vector<int>& nums) {
    if(nums.empty()) return 0;

    sort(nums.begin(), nums.end());
    int maxi  = 1 ;
    int temp = 1;
    for(int i = 1 ; i<nums.size(); i++){
        if(nums[i]==nums[i-1]) continue;

        else if(nums[i]==nums[i-1]+1){
            temp++;
        }
        else{
            maxi = max(temp , maxi);
            temp = 1;
        }
    }
    maxi = max(temp,maxi);
    return maxi;
}


// LC 73 - set matrix zeroes

void solve(vector<vector<int>> & matrix, int row  , int col){
    for(int  c = 0 ; c<matrix[0].size();c++){
        matrix[row][c] = 0;
    }
    for(int  r = 0 ; r<matrix.size();r++){
        matrix[r][col] = 0;
    }
}
void setZeroes(vector<vector<int>>& matrix) {
    vector<vector<int>> visited(matrix.size(),vector<int>(matrix[0].size(),1));

    for(int i = 0; i<matrix.size();i++){
        for(int j = 0 ; j< matrix[0].size() ; j++){
            if(matrix[i][j] == 0) visited[i][j] = 0;
        }
    }

    for(int i = 0; i<matrix.size();i++){
        for(int j = 0 ; j< matrix[0].size() ; j++){
            if(visited[i][j] == 0){
                solve(matrix, i , j);
            }
        }
    }
    
}



// LC 48 - rotate image
void rotate(vector<vector<int>>& matrix) {
    int rowSize = matrix.size();
    int colSize = matrix[0].size();

    // updating the last row
    for(int col = 0 ; col<colSize; col++){
        matrix[rowSize-1][col] = matrix[rowSize-col-1][rowSize-1];
    }

    // updating the last column
    for(int row = rowSize-2; row>=0; row--){
        matrix[row][colSize-1] = matrix[0][colSize-row-1];
    }
}



// LC 54 - spiral matrix
vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int numElements  = matrix.size()*matrix[0].size();
        int startRow = 0;
        int endRow = matrix.size()-1;
        int startCol = 0;
        int endCol = matrix[0].size()-1;
        vector<int> result;

        int count = 0;
        while(count<numElements){
            // for the top row 
            for(int col = startCol ; col<=endCol; col++) {
                count++;
                result.push_back(matrix[startRow][col]);
            }
            startRow++;

            // for the last col 
            for(int row = startRow; row<=endRow; row++) {
                count++;
                result.push_back(matrix[row][endCol]);
            }
            endCol--;

            // for the bottom row
            for(int col = endCol; col>=startCol;col--) {
                count++;
                result.push_back(matrix[endRow][col]);
            }
            endRow--;

            // for the initial col
            for(int row = endRow; row>=startRow; row--) {
                count++;
                result.push_back(matrix[row][startCol]);
            }
            startCol++;

        }
        // result.pop_back();
        return result;
    }



// LC 59 - spiral matrix 2
vector<vector<int>> generateMatrix(int n) {
    vector<vector<int>> result(n, vector<int>(n,0));
    int startRow = 0;
    int endRow = result.size()-1;
    int startCol = 0;
    int endCol = result[0].size()-1;

    int index = 1;
    while(index<=n*n){

        // for the top row 
        for(int col = startCol ; col<=endCol; col++) {
            if(index<=n*n){
                result[startRow][col] = index;
                index++;
            }
        }
        startRow++;

        // for the last col 
        for(int row = startRow; row<=endRow; row++) {
            if(index<=n*n){
                result[row][endCol] = index;
                index++;
            }
        }
        endCol--;

        // for the bottom row
        for(int col = endCol; col>=startCol;col--) {
            if(index<=n*n){
                result[endRow][col] = index;
                index++;
            }
        }
        endRow--;

        // for the initial col
        for(int row = endRow; row>=startRow; row--) {
            if(index<=n*n){
                result[row][startCol] = index;
                index++;
            }
        }
        startCol++;

    }
    // result.pop_back();
    return result;
}





// LC 560 - subarray sum equals k 

// wrong  code
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int , bool> mp;
        int count = 0;
        int sum = 0;
        for(int &num:nums){
            sum += num;
            if(mp[sum-k])count++;
            else if(sum==k) count++;
            mp[sum] = true;
        }
        return count;
    }

};



class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> mp;  // sum -> frequency
        int count = 0;
        int sum = 0;
        mp[0] = 1;  // Initialize for subarrays starting from index 0
        
        for(int num : nums) {
            sum += num;
            count += mp[sum - k];  // Add all previous occurrences
            mp[sum]++;  // Increment frequency
        }
        return count;
    }
};



// LC 118
void solve(int num , vector<vector<int>> &ans){
    if(num ==1){
        vector<int> temp = {1};
        ans.push_back(temp);
        return;
    }

    solve(num-1,ans);
    int len = ans.size();
    vector<int> temp;
    temp.push_back(1);

    for(int i = 0; i<=ans[len-1].size()-2;i++){
        temp.push_back(ans[len-1][i]+ans[len-1][i+1]);
    }
    temp.push_back(1);
    ans.push_back(temp);
}

vector<vector<int>> generate(int numRows) {
    vector<vector<int>> ans;
    solve(numRows,ans);
    return ans;
}



// LC - 167. Two Sum II - Input Array Is Sorted

vector<int> twoSum(vector<int>& numbers, int target) {
    int l = 0;
    int r = numbers.size() - 1;

    while (l < r) {
        int curSum = numbers[l] + numbers[r];
        if (curSum > target) {
            r--;
        }
        else if (curSum < target) {
            l++;
        }
        else { // found the match
            return {l + 1, r + 1}; // 1-based indexing
        }
    }
    return {};

}



// LC 15 - 3sum

vector<vector<int>> threeSum(vector<int>& nums) {
    sort(nums.begin(), nums.end()); // Sort first
    vector<vector<int>> result;

    for(int i = 0; i < nums.size(); i++) {
        if (i > 0 && nums[i] == nums[i-1]) continue; // Skip duplicates

        int left = i + 1;
        int right = nums.size() - 1;

        while (left < right) {
            int sum = nums[i] + nums[left] + nums[right];
            if (sum == 0) {
                result.push_back({nums[i], nums[left], nums[right]});

                left++;
                right--;
                
                // Skip duplicates
                while (left < right && nums[left] == nums[left-1]) left++;
                while (left < right && nums[right] == nums[right+1]) right--;
            }
            else if (sum < 0) left++;
            else right--;
        }
    }
    return result;
}



// LC 18 - 4sum

vector<vector<int>> fourSum(vector<int>& nums, int target) {
    int n = nums.size();
    vector<vector<int>> res;
    if (n < 4) return res;

    sort(nums.begin(), nums.end());

    for (int i = 0; i < n - 3; ++i) {
        if (i > 0 && nums[i] == nums[i - 1]) continue;  // skip duplicate i

        for (int j = i + 1; j < n - 2; ++j) {
            if (j > i + 1 && nums[j] == nums[j - 1]) continue;  // skip duplicate j

            long long remain = (long long)target - nums[i] - nums[j];
            int left = j + 1, right = n - 1;

            while (left < right) {
                long long sum2 = (long long)nums[left] + nums[right];
                if (sum2 < remain) {
                    ++left;
                } else if (sum2 > remain) {
                    --right;
                } else {
                    res.push_back({nums[i], nums[j], nums[left], nums[right]});
                    ++left; --right;

                    while (left < right && nums[left] == nums[left - 1]) ++left;    // skip duplicate left
                    while (left < right && nums[right] == nums[right + 1]) --right; // skip duplicate right
                }
            }
        }
    }

    return res;
}



// largest subarray with 0 sum - https://www.geeksforgeeks.org/problems/largest-subarray-with-0-sum/1

int maxLen(vector<int>& arr) {
    unordered_map<int, int> prefixSumIndex;
    int maxLength = 0;
    int prefixSum = 0;

    for (int i = 0; i < arr.size(); ++i) {
        prefixSum += arr[i];

        // Case 1: subarray from beginning has sum 0
        if (prefixSum == 0) {
            maxLength = i + 1;
        }

        // Case 2: if prefixSum seen before
        if (prefixSumIndex.find(prefixSum) != prefixSumIndex.end()) {
            int length = i - prefixSumIndex[prefixSum];
            maxLength = max(maxLength, length);
        } else {
            // Store first occurrence of this prefixSum
            prefixSumIndex[prefixSum] = i;
        }
    }

    return maxLength;
}



// count subarrays with given XOR

long subarrayXor(vector<int> &arr, int k) {
    // code here
    unordered_map<int, int> freq;
    int count = 0;
    int xorSum = 0;

    for (int num : arr) {
        xorSum ^= num;

        // If prefix XOR itself is equal to k
        if (xorSum == k) count++;

        // If xorSum ^ k exists in map, add its frequency
        if (freq.find(xorSum ^ k) != freq.end()) {
            count += freq[xorSum ^ k];
        }

        // Store current prefix XOR in map
        freq[xorSum]++;
    }

    return count;
}


// missing and repeating - https://www.geeksforgeeks.org/problems/find-missing-and-repeating2512/1

//   using maths
    vector<int> findTwoElement(vector<int>& a) {
    long long n = a.size(); // size of the array

    // Find Sn and S2n:
    long long SN = (n * (n + 1)) / 2;
    long long S2N = (n * (n + 1) * (2 * n + 1)) / 6;

    // Calculate S and S2:
    long long S = 0, S2 = 0;
    for (int i = 0; i < n; i++) {
        S += a[i];
        S2 += (long long)a[i] * (long long)a[i];
    }

    //S-Sn = X-Y:
    long long val1 = S - SN;

    // S2-S2n = X^2-Y^2:
    long long val2 = S2 - S2N;

    //Find X+Y = (X^2-Y^2)/(X-Y):
    val2 = val2 / val1;

    //Find X and Y: X = ((X+Y)+(X-Y))/2 and Y = X-(X-Y),
    // Here, X-Y = val1 and X+Y = val2:
    long long x = (val1 + val2) / 2;
    long long y = x - val1;

    return {(int)x, (int)y};
}



// count inversions - https://www.geeksforgeeks.org/problems/inversion-of-array-1587115620/1

  int merge(vector<int> &arr, int low, int mid, int high) {
    vector<int> temp; // temporary array
    int left = low;      // starting index of left half of arr
    int right = mid + 1;   // starting index of right half of arr

    //Modification 1: cnt variable to count the pairs:
    int cnt = 0;

    //storing elements in the temporary array in a sorted manner//

    while (left <= mid && right <= high) {
        if (arr[left] <= arr[right]) {
            temp.push_back(arr[left]);
            left++;
        }
        else {
            temp.push_back(arr[right]);
            cnt += (mid - left + 1); //Modification 2
            right++;
        }
    }

    // if elements on the left half are still left //

    while (left <= mid) {
        temp.push_back(arr[left]);
        left++;
    }

    //  if elements on the right half are still left //
    while (right <= high) {
        temp.push_back(arr[right]);
        right++;
    }

    // transfering all elements from temporary to arr //
    for (int i = low; i <= high; i++) {
        arr[i] = temp[i - low];
    }

    return cnt; // Modification 3
}

int mergeSort(vector<int> &arr, int low, int high) {
    int cnt = 0;
    if (low >= high) return cnt;
    int mid = (low + high) / 2 ;
    cnt += mergeSort(arr, low, mid);  // left half
    cnt += mergeSort(arr, mid + 1, high); // right half
    cnt += merge(arr, low, mid, high);  // merging sorted halves
    return cnt;
}

    // Function to count inversions in the array.
    int inversionCount(vector<int> &arr) {
        // Your Code Here
        return mergeSort(arr,0,arr.size()-1);
    }


// LC 493 - reverse pairs

int merge(vector<int> &arr, int low, int mid, int high) {
    vector<int> temp; // temporary array
    int left = low;      // starting index of left half of arr
    int right = mid + 1;   // starting index of right half of arr

    //Modification 1: cnt variable to count the pairs:
    int cnt = 0;

    //storing elements in the temporary array in a sorted manner//

    while (left <= mid && right <= high) {
        if (arr[left] <= 2*arr[right]+1) {
            left++;
        }
        else {
            cnt += (mid - left + 1); //Modification 2
            right++;
        }
    }

    left = low;
    right = mid+1;
    while(left <= mid && right<=high){
        if(arr[left]<=arr[right]){
            temp.push_back(arr[left]);
            left++;
        }
        else{
            temp.push_back(arr[right]);
            right++;
        }
    }

    // if elements on the left half are still left //

    while (left <= mid) {
        temp.push_back(arr[left]);
        left++;
    }

    //  if elements on the right half are still left //
    while (right <= high) {
        temp.push_back(arr[right]);
        right++;
    }

    // transfering all elements from temporary to arr //
    for (int i = low; i <= high; i++) {
        arr[i] = temp[i - low];
    }

    return cnt; // Modification 3
}


int mergeSort(vector<int>& nums , int left , int right ){
    if(left>=right) return 0;

    int count = 0;
    int mid = left+(right-left)/2;

    count+=mergeSort(nums, left,mid);
    count += mergeSort(nums , mid+1,right);
    count += merge(nums , left , mid , right);

    return count;
}

int reversePairs(vector<int>& nums) {
    return mergeSort(nums ,0,nums.size()-1);
}



// LC 152 - maximum product subarray

  int maxProduct(vector<int> &arr) {
    int n = arr.size();

    int pre = 1, suff = 1;
    int ans = INT_MIN;
    for (int i = 0; i < n; i++) {
        if (pre == 0) pre = 1;
        if (suff == 0) suff = 1;
        pre *= arr[i];
        suff *= arr[n - i - 1];
        ans = max(ans, max(pre, suff));
    }
    return ans;
}



// M - coloring problem - https://www.geeksforgeeks.org/problems/m-coloring-problem-1587115620/1

    // Function to check if it is safe to color the current node with color 'col'
    bool isSafe(int node, vector<int>& color, vector<vector<int>>& edges, int col, int n) {
    for (auto adjNode : edges[node]) {
        if (color[adjNode] == col)
            return false;
    }
    return true;
}


    // Backtracking function to try coloring the graph
    bool solve(int node, vector<int>& color, int m, int n, vector<vector<int>>& edges) {
        if (node == n) return true;  // all nodes colored successfully

        for (int col = 1; col <= m; col++) {
            if (isSafe(node, color, edges, col, n)) {
                color[node] = col;
                if (solve(node + 1, color, m, n, edges))
                    return true;
                color[node] = 0;  // backtrack
            }
        }
        return false;
    }

    // Main function called by the platform
    bool graphColoring(int n, vector<vector<int>>& edges, int m) {
    // Convert edge list to adjacency list
    vector<vector<int>> adj(n);
    for (auto& edge : edges) {
        adj[edge[0]].push_back(edge[1]);
        adj[edge[1]].push_back(edge[0]);
    }

    vector<int> color(n, 0);
    return solve(0, color, m, n, adj);
}



// LC 37 - sudoku solver

bool isValid(vector < vector < char >> & board, int row, int col, char c) {
  for (int i = 0; i < 9; i++) {
    if (board[i][col] == c)
      return false;

    if (board[row][i] == c)
      return false;

    if (board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == c)
      return false;
  }
  return true;
}

bool solveSudoku(vector < vector < char >> & board) {
  for (int i = 0; i < board.size(); i++) {
    for (int j = 0; j < board[0].size(); j++) {
      if (board[i][j] == '.') {
        for (char c = '1'; c <= '9'; c++) {
          if (isValid(board, i, j, c)) {
            board[i][j] = c;

            if (solveSudoku(board))
              return true;
            else
              board[i][j] = '.';
          }
        }

        return false;
      }
    }
  }
  return true;
}