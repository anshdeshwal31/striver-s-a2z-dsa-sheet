#include <bits/stdc++.h>
using namespace std;

double fractionalKnapsack(vector<int>& val, vector<int>& wt, int capacity) {
    map<int,int>rate;
    for(int i = 0 ; i <val.size();i++){
        int perKgPrice = val[i]/wt[i];
        rate[perKgPrice] = i;
    }

    double ans = 0;
    for(auto r:rate){
        if(!capacity) return ans;

        if(capacity>=wt[r.second]){
            ans+=val[r.first];
            capacity-=wt[r.second];
        }
        else{
            ans+=(r.first*capacity);
        }
    }

}


// LC - 678. Valid Parenthesis String
bool checkValidString(string s) {
    int low = 0, high = 0;

    for (char ch : s) {
        if (ch == '(') {
            low++;
            high++;
        } else if (ch == ')') {
            low--;
            high--;
        } else { // ch == '*'
            low--;      // if * is ')'
            high++;     // if * is '('
        }

        if (high < 0) return false; // too many ')'
        if (low < 0) low = 0;       // we can't have negative open brackets
    }

    return low == 0;
}



// LC 55 - jump game

// using recursion
bool solve(int i , vector<int>& nums){
    if(i==nums.size()-1) return true;
    
    int currentValue = nums[i];
    for(int  j = 1; j <= currentValue; j++){
        if(solve(i+j,nums)) return true;
    }
    return false;
}

bool canJump(vector<int>& nums) {
    return solve(0,nums);
}


// using greedy approach 
bool canJump(vector<int>& nums) {
    int maxReach = 0;
    int n = nums.size();
    
    for (int i = 0; i < n; i++) {
        if (i > maxReach) return false; // if unreachable
        maxReach = max(maxReach, i + nums[i]); // update farthest reachable index
    }
    return true;
}


// LC 45 - jump game 2

// using recursion
int jumpFrom(int i, vector<int>& nums) {
    int n = nums.size();
    if (i >= n - 1) return 0; // reached or passed the last index

    int minJumps = INT_MAX;
    for (int j = 1; j <= nums[i]; j++) {
        int nextJumps = jumpFrom(i + j, nums);
        if (nextJumps != INT_MAX)
            minJumps = min(minJumps, 1 + nextJumps);
    }

    return minJumps;
}

int jump(vector<int>& nums) {
    return jumpFrom(0, nums);
}

// using greedy approach
int jump(vector<int>& nums) {
    int res = 0;
    int l = 0, r = 0;

    int farthest = 0;
    while (r < nums.size() - 1) {
        for (int i = l; i <= r; i++) {
            farthest = max(farthest, i + nums[i]);
        }
        l = r + 1;
        r = farthest;
        res++;
    }
    return res;
}



// activity selection - https://www.geeksforgeeks.org/problems/activity-selection-1587115620/1

static bool helpSort(pair<int,int>& a, pair<int,int>& b) {
    return a.second < b.second;  // sort by finish time ascending
}

int activitySelection(vector<int>& start, vector<int>& finish) {
    vector<pair<int, int>> activity;
    for (int i = 0; i < start.size(); i++) 
        activity.push_back({start[i], finish[i]});

    sort(activity.begin(), activity.end(), helpSort);

    int ans = 0;
    int endTime = -1;

    for (int i = 0; i < activity.size(); i++) {
        int startTime = activity[i].first;
        if (startTime > endTime) {
            endTime = activity[i].second;
            ans++;
        }
    }

    return ans;
}


// minimum platforms - http://geeksforgeeks.org/problems/minimum-platforms-1587115620/1

int findPlatform(vector<int>& arr, vector<int>& dep) {
    int n = arr.size();
    sort(arr.begin(), arr.end());
    sort(dep.begin(), dep.end());

    int plat_needed = 1, max_platforms = 1;
    int i = 1, j = 0;

    while (i < n && j < n) {
        if (arr[i] <= dep[j]) {
            plat_needed++;
            i++;
        } else {
            plat_needed--;
            j++;
        }
        max_platforms = max(max_platforms, plat_needed);
    }

    return max_platforms;
}



// job sequencing - https://www.geeksforgeeks.org/problems/job-sequencing-problem-1587115620/1

vector<int> jobSequencing(vector<int> &deadline, vector<int> &profit) {
    int n = deadline.size();

    // Pair profit with deadline
    vector<pair<int, int>> jobs;
    for (int i = 0; i < n; i++) {
        jobs.push_back({profit[i], deadline[i]});
    }

    // Sort jobs by profit descending
    sort(jobs.rbegin(), jobs.rend());

    // Find max deadline
    int maxDeadline = 0;
    for (auto &job : jobs) {
        maxDeadline = max(maxDeadline, job.second);
    }

    // Time slots array, initialized to -1
    vector<int> slot(maxDeadline + 1, -1);

    int countJobs = 0, totalProfit = 0;

    for (auto &job : jobs) {
        int p = job.first;
        int d = job.second;

        // Find free slot from d to 1
        for (int j = d; j >= 1; j--) {
            if (slot[j] == -1) {
                slot[j] = p;   // Occupy slot
                countJobs++;
                totalProfit += p;
                break;
            }
        }
    }

    return {countJobs, totalProfit};
}





















