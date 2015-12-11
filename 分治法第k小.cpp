#include <cstdio>
#include <iostream>
#include <algorithm>


using namespace std;

const int maxn  = 1e4+4;
//record the number
int c[maxn];
//the number of number
int n;

typedef pair<int,int> P;
//get the kth element between s and e
int getkth(int s,int e,int k){
    if(s >=e)cout<<"ERROR"<<endl;
    int i = s + 1;
    int j = e - 1;
//quicksork, make [s+1,i) just contain elements that smaller or equal than c[s], meanwhile [i,j) greater
    while(i <= j){
        if(c[i] > c[s]){
            swap(c[i],c[j]);
            j--;
        }
        else{
            i++;
        }
    }
//make the array in that format <=c[s],c[s],>c[s]
    swap(c[s],c[i - 1]);
    if(i - s - 1== k)return c[i - 1];
    else if(i - s - 1 < k){
        return getkth(i,e,k - i - s);
    }
    else return getkth(s,i,k);
    return 0;
}

int main(){
    cout<<"Please input the length"<<endl;
    cin>>n;
    cout<<"Please input the numbers,gaped by blank"<<endl;
    for(int i = 0;i < n;i++){
        cin>>c[i];
    }
    cout<<"Please input k"<<endl;
    int k;
    cin>>k;
    k--;
    cout<<"ans:"<<getkth(0,n,k);
    return 0;
}
