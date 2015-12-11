#include <cstdio>
#include <iostream>
#include <bitset>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
/*
 * int n: 节点数
 * int m: 无向边数
 */
int n,m;

/* 邻接链表
 * first: 头结点
 * nxt: 指向下一个节点的偏移量
 * to: 弧尾
 * ind: 目前已经加入的弧数
 * cost:该边花费
 * mincost:从该点出发的边的最小花费
 * maxcost:从该点出发的边的最大花费
 */
int first[32];
int nxt[1024],ind;
int to[1024];
int cost[1024];
int mincost[32];
int maxcost[32];

//status用于记录路径和pt值
class status{
public:
    vector<int> now;
    int pt;
    int s;
    status (){
        pt = 0;
        s = -1;
    }
    status(int s,int pt){
        this->pt = pt;
        this->s = s;
    }
    status(int s,int pt,vector<int> now){
        this->pt = pt;
        this->s = s;
        this->now = now;
    }
    bool operator < (const status & s2)const{
        if(pt != s2.pt)return pt > s2.pt;
        return now.size() < s2.now.size();
    }
    bool operator > (const status & s2)const{
        if(pt != s2.pt)return pt < s2.pt;
        return now.size() > s2.now.size();
    }
};


//添加弧,from f to t
void addedge(int f,int t,int c){
    to[ind] = t;
    nxt[ind] = first[f];
    first[f] = ind;
    cost[ind] = c;
    mincost[f] = min(mincost[f],c);
    mincost[t] = min(mincost[t],c);
    maxcost[f] = max(maxcost[f],c);
    maxcost[t] = max(maxcost[t],c);
    ind++;
}
//记录答案
int ans;
vector<int> a;
//在数组a中搜索指定元素
bool find(vector<int> a, int aim){
    for(int i = 0;i < a.size();i++){
        if(a[i] == aim)return true;
    }
    return false;
}

//具体搜索过程,s为起点,num已搜索数目,nc已花费时间,bound,目前最低限界,初值为所有点花费最小的边值,边集中加入一个点,就减去对应的最小边值
void bfs(int bound){
    priority_queue<status, vector<status>, greater<status> >que;
    status s(0,bound);
    s.now.push_back(0);
    que.push(s);
    while(!que.empty()){
        status tp = que.top();que.pop();
        for(int p = first[tp.s];p!=-1;p = nxt[p]){
            if(find(tp.now,to[p])){
                if(to[p] == 0 && tp.now.size() == n){
                    int tmp = tp.pt - mincost[to[p]] + cost[p];
                    if(tmp < ans){
                        ans = tmp;
                        a = tp.now;
                    }
                }
            }
            else{
                int pt = tp.pt - mincost[to[p]] + cost[p];
                if(pt < ans){
                    status t(to[p],pt,tp.now);
                    t.now.push_back(to[p]);
                    que.push(t);
                }
            }
        }
    }
}
int main(){
    cout<<"Please input the citys' number:(less than 32)";
    cin>>n;
    cout<<"Please input the edge number:(no duplication,no direct)";
    cin>>m;
    //初始化邻接矩阵,-1 为NULL标记
    memset(first,-1,sizeof first);
    for(int i = 0;i < n;i++)mincost[i] = 0x7fffffff;
    for(int i = 0;i < m;i++){
        cout<<"Please input the"<<i+1<<"th edge's nodes and cost(gap by space)"<<endl;
        int tmpf,tmpt,tmpc;
        cin>>tmpf>>tmpt>>tmpc;
        addedge(tmpf,tmpt,tmpc);
        addedge(tmpt,tmpf,tmpc);
    }
    for(int i = 0;i < n;i++){
            ans+=maxcost[i];
    }
    int bound = 0;
    for(int i = 0;i < n;i++){
        bound+=mincost[i];
    }
    bfs(bound);
    cout<<"Consume:"<<ans<<endl;
    for(int i = 0;i < n;i++)cout<<a[i]<<" ";
    cout<<endl;
    return 0;
}
