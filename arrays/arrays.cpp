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