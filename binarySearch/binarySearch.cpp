#include<bits/stdc++.h>
using namespace std;


// binary search in a sorted array
int search(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;
    while(left <= right){
        int mid = left + (right - left) / 2;
        if(nums[mid] == target){
            return mid;
        }
        else if(nums[mid] < target){
            left = mid + 1;
        }
        else{
            right = mid - 1;
        }
    }
    return -1;
}


// floor in a sorted array
int findFloor(vector<int> &v, int n, int target) {
    int low = 0, high = n - 1;
    int result = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (v[mid] == target) return mid;
        else if (v[mid] < target) {
            result = mid;
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    return result;
}


// ceil in a sorted array
int ceil(int x, vector<int> &arr){
    int low = 0, high = arr.size() - 1;
    int result = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == x) return mid;
        else if (arr[mid] < x) {
            low = mid + 1;
        }
        else {
            result = mid;
            high = mid - 1;
        }
    }
    return result;
}

pair<int,int> getFloorAndCeil(int x, vector<int> &arr) {
    sort(arr.begin(), arr.end());
    int floorIndex = findFloor(arr, arr.size(), x);
    int ceilIndex = ceil(x, arr);
    if(floorIndex == -1) return {-1, arr[ceilIndex]};
    if(ceilIndex == -1) return {arr[floorIndex], -1};
    return {arr[floorIndex], arr[ceilIndex]};
}


// search insert position

// method 1
int searchInsert(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;
    while(left <= right){
        int mid = left + (right - left) / 2;
        if(nums[mid] == target){
            return mid;
        }
        else if(nums[mid] < target){
            left = mid + 1;
        }
        else{
            right = mid - 1;
        }
    }
    return left;
}


// method 2
int searchInsert(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;
    int result = -1;
    while(left <= right){
        int mid = left + (right - left) / 2;
        if(nums[mid] == target) return mid;
        else if(nums[mid] < target) {
            result = mid+1;
            left = mid + 2;
        }
        else {
            result = mid;
            right = mid - 1;
        }
    }
    return result;
}


// first and last occurence of an element in a sorted array
int firstOccurence(vector<int> &v, int n, int target) {
    int left = 0, right = n - 1;
    int result = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (v[mid] == target) {
            result = mid;
            right = mid - 1;
        }
        else if (v[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return result;
}

int lastOccurence(vector<int> &v, int n, int target) {
    int left = 0, right = n - 1;
    int result = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (v[mid] == target) {
            result = mid;
            left = mid + 1;
        }
        else if (v[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return result;
}

vector<int> searchRange(vector<int>& nums, int target) {
    int first = firstOccurence(nums, nums.size(), target);
    int last = lastOccurence(nums, nums.size(), target);
    return {first, last};   
}


// in binary search questions(like search insert position, first and last occurence of an element in a sorted, find the floor , find the ceil) , store the possible result in a variable and look for a better result (better result means the result which is closer to the target) by excluding the range in which have either already seached or by excluding the range which is not possible to have the better result. and keep updating the result until the range is valid(ie. left <= right).


// count the number of occurences of an element in a sorted array
int firstOccurence(vector<int> &v, int n, int target) {
    int left = 0, right = n - 1;
    int result = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (v[mid] == target) {
            result = mid;
            right = mid - 1;
        }
        else if (v[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return result;
}

int lastOccurence(vector<int> &v, int n, int target) {
    int left = 0, right = n - 1;
    int result = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (v[mid] == target) {
            result = mid;
            left = mid + 1;
        }
        else if (v[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return result;
}


int count(vector<int>& nums, int n, int target) {
	int first = firstOccurence(nums, n, target);
    int last = lastOccurence(nums, n, target);
    if(first == -1) return 0;
    
	return last - first +1;
}


// find the pivot element in a rotated sorted array

int findPivot(vector<int> &arr) {
    int low = 0, high = arr.size() - 1;

    // If the array is already sorted (no rotation)
    if (arr[low] <= arr[high]) {
        return low;
    }

    while (low <= high) {
        int mid = low + (high - low) / 2;

        // Check if mid is the pivot point
        if (mid < high && arr[mid] > arr[mid + 1]) {
            return mid;
        }
        if (mid > low && arr[mid] < arr[mid - 1]) {
            return mid - 1;
        }

        // Adjust the search range
        if (arr[mid] >= arr[low]) {
            low = mid + 1; // Go right
        } else {
            high = mid - 1; // Go left
        }
    }

    return -1; 
}


// search in a rotated sorted array
int search(vector<int>& nums, int target) {
    int pivot = findPivot(nums);
    int left = 0;
    int right = nums.size() - 1;
    if(pivot == -1 || pivot == 0){
        left = 0;
        right = nums.size() - 1;
    }
    else if(nums[pivot] == target){
        return pivot;
    }
    else if(nums[0] <= target){
        left = 0;
        right = pivot - 1;
    }
    else{
        left = pivot + 1;
        right = nums.size() - 1;
    }

    while(left <= right){
        int mid = left + (right - left) / 2;
        if(nums[mid] == target){
            return mid;
        }
        else if(nums[mid] < target){
            left = mid + 1;
        }
        else{
            right = mid - 1;
        }
    }

    return -1;
}



// find square root of a number
int mySqrt(int x) {
    int left = 0;
    int right = x;
    
    int ans = -1;
    while(left <= right){
        int mid = left + (right - left) / 2;
        if(mid*mid <= x){
            ans = mid;
            left = mid + 1;
        }
        else{
            right = mid - 1;
        }
    }
    return ans;
}


// koko eating bananas
long long solve(vector<int> &piles, int k){
    long long hours = 0;
    for(int i = 0; i < piles.size(); i++){
        if(piles[i] % k == 0) hours += (long long)piles[i]/k;
        else hours += (long long)piles[i]/k+1;
    }
    return hours;
}
int minEatingSpeed(vector<int>& piles, int h) {

    int maxi = *max_element(piles.begin(), piles.end());
    int left = 1;
    int right = maxi;
    int ans = -1;
    while(left <= right){
        int mid = left + (right - left) / 2;
        if(solve(piles, mid) <= (long long)h){
            ans = mid;
            right = mid - 1;
        }
        else{
            left = mid + 1;
        }
    } 
    return ans;  
}



// find the smallest divisor given a threshold
bool solve(int mid , vector<int> &nums, int threshold){
    int sum = 0;
    for(auto x : nums){
        if(x % mid == 0) sum = sum + x/mid;
        else sum  = sum + x/mid +1;
    }
    if(sum <= threshold) return true;
    return false;
}
int smallestDivisor(vector<int>& nums, int threshold) {
    int left = 1;
    int right = *max_element(nums.begin(), nums.end());
    int ans = -1;

    while(left<right){
        int mid = left + (right - left) / 2;
        if(solve(mid, nums, threshold)){
            ans = mid;
            right = mid;
        }
        else{
            left = mid + 1;
        }
    }
    return ans;
}


// capacity to ship packages within D days
int countDays(vector<int> &weights, int mid){
    int days = 1;
    int sum = 0;
    for(auto x : weights){
        sum += x;
        if(sum > mid){
            days++;
            sum = x;
        }
    }
    return days;
}
int shipWithinDays(vector<int>& weights, int days) {
    int mini = *min_element(weights.begin(), weights.end());
    int sum = accumulate(weights.begin(), weights.end(), 0);

    int left = mini;
    int right = sum;
    
    while(left < right){
        int mid = left + (right - left) / 2;
        if(countDays(weights, mid) <= days){
            right = mid;
        }
        else{
            left = mid + 1;
        }
    } 
    return left; 
}



// LC 540 - single element in a sorted array
int singleNonDuplicate(vector<int>& nums) {
    pair<int , int >p =  {0,0};
    for(int num : nums){
        if(p.second == 1){
            if(p.first == num){
                p.second = 0;
            }
            else{
                return p.first;
            }
        }
        else{
            p.second = 1;
            p.first = num;
        }
    }
}


// aggressive cows 
bool canWePlace(vector<int> &stalls, int dist, int cows) {
    int n = stalls.size(); //size of array
    int cntCows = 1; //no. of cows placed
    int last = stalls[0]; //position of last placed cow.
    for (int i = 1; i < n; i++) {
        if (stalls[i] - last >= dist) {
            cntCows++; //place next cow.
            last = stalls[i]; //update the last location.
        }
        if (cntCows >= cows) return true;
    }
    return false;
}
int aggressiveCows(vector<int> &stalls, int k) {
    int n = stalls.size(); //size of array
    //sort the stalls[]:
    sort(stalls.begin(), stalls.end());

    int low = 1, high = stalls[n - 1] - stalls[0];
    //apply binary search:
    while (low <= high) {
        int mid = (low + high) / 2;
        if (canWePlace(stalls, mid, k) == true) {
            low = mid + 1;
        }
        else high = mid - 1;
    }
    return high;
}



// Book allocation problem(min of max) 
class Solution {
private:
    // Helper function to count number of students needed for given max pages
    bool isPossible(vector<int>& arr, int maxPages, int students) {
        int currentStudent = 1;
        int currentPages = 0;
        
        for(int pages : arr) {
            // If any book has more pages than maxPages, allocation impossible
            if(pages > maxPages) return false;
            
            // If adding current book exceeds maxPages, assign to next student
            if(currentPages + pages > maxPages) {
                currentStudent++;
                currentPages = pages;
            } else {
                currentPages += pages;
            }
        }
        
        return currentStudent <= students;
    }

public:
    int findPages(vector<int>& arr, int k) {
        // If students more than books, impossible to allocate
        int n = arr.size();
        if(k > n) return -1;
        
        // Search space bounds:
        // low: maximum pages in any book (minimum possible answer)
        // high: sum of all pages (maximum possible answer)
        int low = *max_element(arr.begin(), arr.end());
        int high = accumulate(arr.begin(), arr.end(), 0);
        
        int result = -1;
        
        // Binary search on the answer space
        while(low <= high) {
            int mid = low + (high - low)/2;
            
            if(isPossible(arr, mid, k)) {
                result = mid;
                high = mid - 1;  // Try to find better (smaller) solution
            } else {
                low = mid + 1;   // Need more pages per student
            }
        }
        
        return result;
    }
};



// allocate minimum pages(book allocation problem)- http://geeksforgeeks.org/problems/allocate-minimum-number-of-pages0937/1

// brute force

int countStudents(vector<int> &arr, int pages) {
    int n = arr.size(); //size of array.
    int students = 1;
    long long pagesStudent = 0;
    for (int i = 0; i < n; i++) {
        if (pagesStudent + arr[i] <= pages) {
            //add pages to current student
            pagesStudent += arr[i];
        }
        else {
            //add pages to next student
            students++;
            pagesStudent = arr[i];
        }
    }
    return students;
}

int findPages(vector<int>& arr, int n, int m) {
    //book allocation impossible:
    if (m > n) return -1;

    int low = *max_element(arr.begin(), arr.end());
    int high = accumulate(arr.begin(), arr.end(), 0);

    for (int pages = low; pages <= high; pages++) {
        if (countStudents(arr, pages) == m) {
            return pages;
        }
    }
    return low;
}


// binary search 

int countStudents(vector<int> &arr, int pages) {
    int n = arr.size(); //size of array.
    int students = 1;
    long long pagesStudent = 0;
    for (int i = 0; i < n; i++) {
        if (pagesStudent + arr[i] <= pages) {
            //add pages to current student
            pagesStudent += arr[i];
        }
        else {
            //add pages to next student
            students++;
            pagesStudent = arr[i];
        }
    }
    return students;
}

int findPages(vector<int>& arr, int n, int m) {
    //book allocation impossible:
    if (m > n) return -1;

    int low = *max_element(arr.begin(), arr.end());
    int high = accumulate(arr.begin(), arr.end(), 0);
    while (low <= high) {
        int mid = (low + high) / 2;
        int students = countStudents(arr, mid);
        if (students > m) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    return low;
}




// LC 410 - split array largest sum

// brute force

    int countPartitions(vector<int> &a, int maxSum) {
    int n = a.size(); //size of array.
    int partitions = 1;
    long long subarraySum = 0;
    for (int i = 0; i < n; i++) {
        if (subarraySum + a[i] <= maxSum) {
            //insert element to current subarray
            subarraySum += a[i];
        }
        else {
            //insert element to next subarray
            partitions++;
            subarraySum = a[i];
        }
    }
    return partitions;
}

int splitArray(vector<int> &a, int k) {
    int low = *max_element(a.begin(), a.end());
    int high = accumulate(a.begin(), a.end(), 0);

    for (int maxSum = low; maxSum <= high; maxSum++) {
        if (countPartitions(a, maxSum) == k)
            return maxSum;
    }
    return low;
}

// binary search

int countPartitions(vector<int> &a, int maxSum) {
    int n = a.size(); //size of array.
    int partitions = 1;
    long long subarraySum = 0;
    for (int i = 0; i < n; i++) {
        if (subarraySum + a[i] <= maxSum) {
            //insert element to current subarray
            subarraySum += a[i];
        }
        else {
            //insert element to next subarray
            partitions++;
            subarraySum = a[i];
        }
    }
    return partitions;
}

int splitArray(vector<int> &a, int k) {
    int low = *max_element(a.begin(), a.end());
    int high = accumulate(a.begin(), a.end(), 0);
    //Apply binary search:
    while (low <= high) {
        int mid = (low + high) / 2;
        int partitions = countPartitions(a, mid);
        if (partitions > k) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    return low;
}



// the painter's  partition 2 - https://www.geeksforgeeks.org/problems/the-painters-partition-problem1535/1
  
//   brute force
  int countPainters(vector<int> &boards, int time) {
    int n = boards.size(); //size of array.
    int painters = 1;
    long long boardsPainter = 0;
    for (int i = 0; i < n; i++) {
        if (boardsPainter + boards[i] <= time) {
            //allocate board to current painter
            boardsPainter += boards[i];
        }
        else {
            //allocate board to next painter
            painters++;
            boardsPainter = boards[i];
        }
    }
    return painters;
}

int minTime(vector<int> &boards, int k) {
    int low = *max_element(boards.begin(), boards.end());
    int high = accumulate(boards.begin(), boards.end(), 0);

    for (int time = low; time <= high; time++) {
        if (countPainters(boards, time) <= k) {
            return time;
        }
    }
    return low;
}


// using binary search

int countPainters(vector<int> &boards, int time) {
    int n = boards.size(); //size of array.
    int painters = 1;
    long long boardsPainter = 0;
    for (int i = 0; i < n; i++) {
        if (boardsPainter + boards[i] <= time) {
            //allocate board to current painter
            boardsPainter += boards[i];
        }
        else {
            //allocate board to next painter
            painters++;
            boardsPainter = boards[i];
        }
    }
    return painters;
}

int minTime(vector<int> &boards, int k) {
    int low = *max_element(boards.begin(), boards.end());
    int high = accumulate(boards.begin(), boards.end(), 0);
    //Apply binary search:
    while (low <= high) {
        int mid = (low + high) / 2;
        int painters = countPainters(boards, mid);
        if (painters > k) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    return low;
}



// LC 2643 - row with maximum ones



// LC 74 - search a 2D matrix

bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int n = matrix.size();
    int m = matrix[0].size();

    //apply binary search:
    int low = 0, high = n * m - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        int row = mid / m, col = mid % m;
        if (matrix[row][col] == target) return true;
        else if (matrix[row][col] < target) low = mid + 1;
        else high = mid - 1;
    }
    return false;
}


// LC 240 - search in a 2D matrix 2

bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int n = matrix.size();
    int m = matrix[0].size();
    int row = 0, col = m - 1;

    //traverse the matrix from (0, m-1):
    while (row < n && col >= 0) {
        if (matrix[row][col] == target) return true;
        else if (matrix[row][col] < target) row++;
        else col--;
    }
    return false;
}



// LC 162 - find peak element 

int findPeakElement(vector<int> &arr) {
    int n = arr.size(); //Size of array.

    // Edge cases:
    if (n == 1) return 0;
    if (arr[0] > arr[1]) return 0;
    if (arr[n - 1] > arr[n - 2]) return n - 1;

    int low = 1, high = n - 2;
    while (low <= high) {
        int mid = (low + high) / 2;

        //If arr[mid] is the peak:
        if (arr[mid - 1] < arr[mid] && arr[mid] > arr[mid + 1])
            return mid;

        // If we are in the left:
        if (arr[mid] > arr[mid - 1]) low = mid + 1;

        // If we are in the right:
        // Or, arr[mid] is a common point:
        else high = mid - 1;
    }
    // Dummy return statement
    return -1;
}
