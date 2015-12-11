#include <cstdio>
#include <iostream>
#include <bitset>
#include <cstring>
#include <algorithm>
using namespace std;
/*
 * int n: 节点数
 * int m: 无向边数
 * int nc: 颜色数
 * int[] c: 物品所取颜色集
 */
int n,m,nc;
int c[32];

/* 邻接链表
 * first: 头结点
 * nxt: 指向下一个节点的偏移量
 * to: 弧尾
 * ind: 目前已经加入的弧数
 */
int first[32];
int nxt[1024],ind;
int to[1024];

//添加弧,from f to t
void addedge(int f,int t){
    to[ind] = t;
    nxt[ind] = first[f];
    first[f] = ind;
    ind++;
}

//具体搜索过程,s为起点
bool dfs(int s){
    for(int p = first[s];p!=-1;p=nxt[p]){
        int t = to[p];
        if(c[t]!=0){
            if(c[t]==c[s])return false;
        }
        else{
            //最优策略为s点的颜色序号最小,所以从小向大搜索
            for(int i = 1;i <= nc;i++){
                if(i == c[s])continue;
                c[t] = i;
                //已经搜到最优解
                if(dfs(t))break;
                c[t] = 0;
            }
            if(c[t]==0)return false;
        }
    }
    return true;
}

int main(){
    cout<<"Please input the nodes number:(less than 32)";
    cin>>n;
    cout<<"Please input the edge number:(no duplication,no direct)";
    cin>>m;
    cout<<"Please input the color available:(less than element number)(from 0 to n-1)";
    cin>>nc;
    //初始化邻接矩阵,-1 为NULL标记
    memset(first,-1,sizeof first);
    for(int i = 0;i < m;i++){
        cout<<"Please input the"<<i+1<<"th edge's nodes(gap by space)"<<endl;
        int tmpf,tmpt;
        cin>>tmpf>>tmpt;
        addedge(tmpf,tmpt);
        addedge(tmpt,tmpf);
    }
    bool fl = true;
    for(int i = 0;i < n;i++){
        if(c[i]!=0)continue;
        c[i] = 1;
        if(!dfs(i)){
            fl = false;
            cout<<"CANT DYE IT!!"<<endl;
            break;
        }
    }
    if(fl){
        for(int i = 0;i < n;i++){
            cout<<"The "<<i+1<<"th element is "<<c[i]<<"color"<<endl;
        }
    }
    return 0;
}
