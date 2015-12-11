#include <cstdio>
#include <iostream>
#include <bitset>
#include <cstring>
using namespace std;
int n,m;
int w[32],c[32];
int tmp[32],a[32],ans,answ;
int res[32][1001],path[32][1001][32];
int dfs(int i,int j){
    if(res[i][j] > 0)return res[i][j];
    int resw = j;
    for(int ii = i;ii < n;ii++){
        if(w[ii] + j <= m){
            int subw = dfs(ii+1,j +w[ii]);
            if(res[i][j]<res[ii + 1][j + w[ii]] + c[ii]){
                res[i][j]=res[ii + 1][j + w[ii]] + c[ii];
                copy(path[ii+1][j+w[ii]],path[ii+1][j+w[ii]]+31,path[i][j]+1);
                path[i][j][0] = ii + 1;
                resw = subw;
            }
            if(res[i][j] > ans){
                copy(path[i][j],path[i][j] + 32,a);
                ans = res[i][j];
                answ = resw;
            }
        }
    }
    return resw;
}
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
    dfs(0,0);
    cout<<"最大价值"<<ans<<endl;
    cout<<"所占质量"<<answ<<endl;
    cout<<"所取物品"<<endl;
    for(int i = 0;a[i];i++){
        cout<<a[i]<<endl;
    }
    return 0;
}
