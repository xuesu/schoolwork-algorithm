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
    cout<<"�����뱳������"<<endl;
    cin>>m;
    cout<<"�������������"<<endl;
    cin>>n;
    for(int i = 0;i < n;i++){
        cout<<"�������"<<i+1<<"�����������"<<endl;
        cin>>w[i];
        cout<<"�������"<<i+1<<"������ļ۸�"<<endl;
        cin>>c[i];
    }
    dfs(0,0);
    cout<<"����ֵ"<<ans<<endl;
    cout<<"��ռ����"<<answ<<endl;
    cout<<"��ȡ��Ʒ"<<endl;
    for(int i = 0;a[i];i++){
        cout<<a[i]<<endl;
    }
    return 0;
}
