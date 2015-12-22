#include <cstdio>
#include <iostream>
#include <bitset>
#include <cstring>
#include <algorithm>
using namespace std;
bool pre[1000][1001];
int p[1001];
int tmp[1001];
struct good{
    int w,c,id;
}g[1001];

bool cmp(good g1,good g2){
    if(g1.c/g1.w!=g2.c/g2.w)return g1.c/g1.w > g2.c/g2.w;
    if(g1.w!=g2.w)return g1.w < g2.w;
    return g1.id < g2.id;
}
int main(){
    int n,m;
    cout<<"�����뱳������"<<endl;
    cin>>m;
    cout<<"�������������"<<endl;
    cin>>n;
    for(int i = 0;i < n;i++){
        cout<<"�������"<<i+1<<"�����������"<<endl;
        cin>>g[i].w;
        cout<<"�������"<<i+1<<"������ļ۸�"<<endl;
        cin>>g[i].c;
    }
    sort(g,g+n,cmp);
    memset(p,-1,(sizeof (int)) * (m + 1));
    p[0] = 0;
    int ans = 0;
    for(int i = 0;i < n;i++){
        memset(tmp,-1,sizeof (int) * (m + 1));
        for(int j = m;j >= 0;j--){
            pre[i][j] = false;
            if (p[j] != -1 && g[i].w + j <= m && g[i].c + p[j] > p[g[i].w + j] && g[i].c + p[j] > tmp[g[i].w + j]){
                //cout<< i<<','<<j<<','<<c[i] + p[j]<<endl;
                tmp[g[i].w + j] = g[i].c + p[j];
                pre[i][g[i].w + j] = true;
            }
        }
        for(int j = 0;j < m;j++){
            if(tmp[j] != -1){
                p[j] = tmp[j];
                if(p[ans] < p[j]){
                    ans = j;
                }
            }
        }
    }
    cout<<"����ֵ"<<p[ans]<<endl;
    cout<<"��ռ����"<<ans<<endl;
    cout<<"��ȡ��Ʒ"<<endl;
    for(int i = n-1;i >= 0;i--){
        if(pre[i][ans]){
            cout<<i+1<<endl;
            ans-=g[i].w;
        }
    }
    return 0;
}
