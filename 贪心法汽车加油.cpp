#include <cstdio>
#include <iostream>
#include <bitset>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
class park{
public:
    int a,id;
    bool operator > (park g2)const{
        if(a!=g2.a)return a > g2.a;
        return id < g2.id;
    }
    bool operator < (park g2)const{
        if(a!=g2.a)return a < g2.a;
        return id > g2.id;
    }
}g[1001];
queue<int> sta;

int main(){
    int d,n;
    cout<<"��������������d"<<endl;
    cin>>d;
    cout<<"���������վ����"<<endl;
    cin>>n;
    for(int i = 0;i < n;i++){
        if(i>0)cout<<"�������"<<i<<"������վ����һ������վ�����"<<endl;
        else if(i == 0)cout<<"��������㵽��һ������վ�����"<<endl;
        cin>>g[i].a;
        g[i].id = i;
    }
    int cnt = d;
    int ans = 0;
    for(int i = 0;i < n;i++){
        if(cnt < g[i].a){
            if(g[i].a > d){
                cout<<"CANT REACH the ENDPOINT!"<<endl;
            }
            else{
                sta.push(i);
                cnt = d;
                ans++;
            }
        }
        cnt -= g[i].a;
    }
    cout<<"����"<<ans<<"����"<<endl;
    while(!sta.empty()){
        cout<<sta.front()<<endl;
        sta.pop();
    }
    return 0;
}
