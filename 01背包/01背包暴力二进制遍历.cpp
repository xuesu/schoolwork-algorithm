#include <cstdio>
#include <iostream>
#include <bitset>
#include <cstring>
using namespace std;
int n,m;
int ans,a,answ;
int c[32],w[32];
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
    cout<<"����ֵ"<<ans<<endl;
    cout<<"��ռ����"<<answ<<endl;
    cout<<"��ȡ��Ʒ"<<endl;
    for(int i = 0;i<n;i++){
        if((a&(1<<i))!=0)cout<<i+1<<endl;
    }
    return 0;
}
