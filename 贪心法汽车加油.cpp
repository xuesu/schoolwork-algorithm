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
    cout<<"请输入油箱容量d"<<endl;
    cin>>d;
    cout<<"请输入加油站个数"<<endl;
    cin>>n;
    for(int i = 0;i < n;i++){
        if(i>0)cout<<"请输入第"<<i<<"个加油站到下一个加油站间距离"<<endl;
        else if(i == 0)cout<<"请输入起点到下一个加油站间距离"<<endl;
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
    cout<<"加了"<<ans<<"次油"<<endl;
    while(!sta.empty()){
        cout<<sta.front()<<endl;
        sta.pop();
    }
    return 0;
}
