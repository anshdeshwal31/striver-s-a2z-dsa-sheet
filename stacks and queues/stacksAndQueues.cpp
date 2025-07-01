#include <bits/stdc++.h>
using namespace std;

int mod = 1e9 + 7;


// implementation of queue using stack

int solve(stack<int> &s){
    if(s.size() == 1){
        int x = s.top();
        s.pop();
        return x;
    }
    int x = s.top();
    s.pop();
    int res = solve(s);
    s.push(x);
    return res;
}


// implementing stack using linked list

class MyStack{
    private:
    StackNode* top;

    public:
    void push(int x){
        if(top == NULL){
            top = new StackNode(x);
        }
        else{
            StackNode* temp = new StackNode(x);
            temp->next = top;
            top = temp;
        }
    }

    int pop(){
    }

    MyStack(){
        top = NULL;
    }
};



// LC 496
vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {

    stack<int> st;
    int n = nums2.size();
    unordered_map<int , int > mp;
    st.push(nums2[n-1]);
    mp[nums2[n-1]] =  -1;

    for(int i = n-2;i>=0;i--){
        int element = nums2[i];
        while(!st.empty() && st.top()<=element){
            st.pop();
        } 

        if(!st.empty()){
            mp[element] = st.top();
        }
        else{
            mp[element] = -1;
        }
        st.push(element);
    }

    vector<int>ans;
    for(int el:nums1){
        ans.push_back(mp[el]);
    }
    return ans;
}



// LC 503
vector<int> nextGreaterElements(vector<int>& nums) {
    stack<int>st;
    unordered_map<int, int> mp;
    int n = nums.size()-1;

    for(int el:nums){
        if(el>nums[n-1]){
            st.push(el);
            st.push(nums[n-1]);
            mp[nums[n-1]] = el;
            break;
        }
        else{
            mp[nums[n-1]] = -1;
            break;
        }
    }
        
    for(int i = n-2;i>=0;i--){
        while(!st.empty()&&st.top()<=nums[i]){
            st.pop();
        }
        if(st.empty()){
            mp[nums[i]] = -1;
        }
        else{
            mp[nums[i]] = st.top();
        }
        st.push(nums[i]);
    }

    vector<int>ans;
    for(int el:nums){
        ans.push_back(mp[el]);
    }
    return ans;
}


vector<int> prevSmaller(vector<int> &A) {
    int n = A.size();
    stack<int>st;
    vector<int>ans;

    for (int i = 0; i < n; i++){
        while (!st.empty() && st.top()>=A[i]) st.pop();
       
        if(st.empty()) ans.push_back(-1);
        else ans.push_back(st.top());

        st.push(A[i]);
    }
    return ans;
}



// LC 907 - sum of subarray minimums

 int sumSubarrayMins(vector<int>& arr) {
    int n = arr.size();
    const int MOD = 1e9 + 7;
    stack<int> st;
    vector<int> ple(n), nle(n);  // Previous Less Element, Next Less Element

    // Find Previous Less Element (PLE)
    for (int i = 0; i < n; ++i) {
        while (!st.empty() && arr[st.top()] > arr[i])
            st.pop();
        ple[i] = st.empty() ? -1 : st.top();
        st.push(i);
    }

    // Clear stack to reuse it
    while (!st.empty()) st.pop();

    // Find Next Less Element (NLE)
    for (int i = n - 1; i >= 0; --i) {
        while (!st.empty() && arr[st.top()] >= arr[i])
            st.pop();
        nle[i] = st.empty() ? n : st.top();
        st.push(i);
    }

    // Calculate total contribution of each element
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        long long left = i - ple[i];
        long long right = nle[i] - i;
        ans = (ans + (arr[i] * left % MOD) * right % MOD) % MOD;
    }

    return ans;
}
