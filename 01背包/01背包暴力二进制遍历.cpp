#include <cstdio>
#include <iostream>
#include <bitset>
#include <cstring>
using namespace std;
int n,m;
int ans,a,answ;
int c[32],w[32];
int main(){
    cout<<"请输入背包重量"<<endl;
    cin>>m;
    cout<<"请输入重物个数"<<endl;
    cin>>n;
    for(int i = 0;i < n;i++){
        cout<<"请输入第"<<i+1<<"个重物的重量"<<endl;
        cin>>w[i];
        cout<<"请输入第"<<i+1<<"个重物的价格"<<endl;
        cin>>c[i];
    }
    for(int i = 0;i < (1<<n);i++){
        int res = 0;
        int subw = 0;
        for(int j = 0;j < n;j++){
            if((i&(1<<j))!=0){
                subw+=w[j];
                res+=c[j];
            }
        }
        if(subw<=m&&ans<res){
            ans=res;
            a = i;
            answ = subw;
        }
    }
    cout<<"最大价值"<<ans<<endl;
    cout<<"所占质量"<<answ<<endl;
    cout<<"所取物品"<<endl;
    for(int i = 0;i<n;i++){
        if((a&(1<<i))!=0)cout<<i+1<<endl;
    }
    return 0;
}
