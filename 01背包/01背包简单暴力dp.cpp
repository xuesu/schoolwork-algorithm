#include <cstdio>
#include <iostream>
#include <bitset>
#include <cstring>
using namespace std;
bool pre[1000][1001];
int main(){
    int n,m;
    cout<<"�����뱳������"<<endl;
    cin>>m;
    cout<<"�������������"<<endl;
    cin>>n;
    int* w = new int[n];
    int * c= new int[n];
    for(int i = 0;i < n;i++){
        cout<<"�������"<<i+1<<"�����������"<<endl;
        cin>>w[i];
        cout<<"�������"<<i+1<<"������ļ۸�"<<endl;
        cin>>c[i];
    }
    int * p = new int [m+1];
    int * tmp = new int[m + 1];
    memset(p,-1,(sizeof (int)) * (m + 1));
    p[0] = 0;
    int ans = 0;
    for(int i = 0;i < n;i++){
        memset(tmp,-1,sizeof (int) * (m + 1));
        for(int j = m;j >= 0;j--){
            pre[i][j] = false;
            if (p[j] != -1 && w[i] + j <= m && c[i] + p[j] > p[w[i] + j] && c[i] + p[j] > tmp[w[i] + j]){
                //cout<< i<<','<<j<<','<<c[i] + p[j]<<endl;
                tmp[w[i] + j] = c[i] + p[j];
                pre[i][w[i] + j] = true;
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
            ans-=w[i];
        }
    }
    delete[] w;
    delete[] c;
    delete[] p;
    delete[] tmp;
    return 0;
}
