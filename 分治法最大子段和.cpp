#include <cstdio>
#include <iostream>
#include <algorithm>


using namespace std;

const int maxn  = 1e4+4;
//recode the array
int c[maxn];
//recode the sum from c[0] to c[i]
int s[maxn];
//the length of array
int n;

int lsum(int i){// get the sum [0,i]
    return s[i];
}
int rsum(int i){//[i,n-1]
    return s[n - 1] - (i == 0?0:s[i - 1]);
}
//get the sum of [b,e)
int msum(int b,int e){
    return (e>0?s[e-1]:0) - (b == 0?0:s[b - 1]);
}

typedef pair<int,int> P;

//get the max lans in the [a,b), get the x for all other y in [a,b),sum[x,b) > sum[y,b)
P getlans(int a,int b){//[x,b)
    if(b - a <= 0)cout<<"ERROR"<<endl;
    if(b - a == 1){
        return P(a,b);
    }
    int m = (a + b)/2;
    P tmp = getlans(a,m);
    P ans;
    if(msum(tmp.first,tmp.second) > 0)ans = P(tmp.first,b);
    else ans = P(m,b);
    tmp = getlans(m,b);
    if(msum(ans.first,ans.second) < msum(tmp.first,tmp.second)){
        ans = tmp;
    }
    //cout<<"getlans:("<<a<<","<<b<<") is ("<<ans.first<<","<<ans.second<<")"<<endl;
    return ans;
}
//get the max rans in the [a,b), get the x for all other y in [a,b),sum[a,x] > sum[a,y]
P getrans(int a,int b){//[a,x]
    if(b - a == 1){
        return P(a,b);
    }
    int m = (a + b)/2;
    P tmp = getrans(m,b);
    P ans;
    if(msum(tmp.first,tmp.second) > 0)ans = P(a,tmp.second);
    else ans = P(a,m);
    tmp = getrans(a,m);
    if(msum(ans.first,ans.second) < msum(tmp.first,tmp.second)){
        ans = tmp;
    }
    //cout<<"getrans:("<<a<<","<<b<<") is ("<<ans.first<<","<<ans.second<<")"<<endl;
    return ans;
}

//get the max subsequence
P getans(int a,int b){
    if(b - a == 1){
        return P(a,b);
    }
    int m = (a + b)/2;
    P ans = getans(a,m);
    P tmp = getans(m,b);
    if(msum(ans.first,ans.second) < msum(tmp.first,tmp.second)){
        ans = tmp;
    }
    tmp = P(getlans(a,m).first,getrans(m,b).second);
    if(msum(ans.first,ans.second) < msum(tmp.first,tmp.second)){
        ans = tmp;
    }
    //cout<<"getans:("<<a<<","<<b<<") is ("<<ans.first<<","<<ans.second<<")"<<endl;
    return ans;
}

int main(){
    cout<<"Please input the length"<<endl;
    cin>>n;
    cout<<"Please input the numbers,gaped by blank"<<endl;
    for(int i = 0;i < n;i++){
        cin>>c[i];
        s[i] = (i == 0?0:s[i - 1]) + c[i];
    }
    P ans = getans(0,n);
    int a = ans.first,b = ans.second;
    cout<<"The max sum is "<<msum(a,b)<<endl;
    for(int i = a;i < b;i++){
        cout<<c[i]<<" ";
    }
    cout<<endl;
    return 0;
}
