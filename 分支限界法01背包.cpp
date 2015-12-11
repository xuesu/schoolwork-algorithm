#include <cstdio>
#include <iostream>
#include <bitset>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
/*
 * int n: 物品数量
 * int m: 背包最大重量
 * int[] path: 记录已经取了的物品集,也即记录dfs树路径
 * int pi: the index of path, 目前path数组记录已取多少物品
 * int[] a: 记录最终物品集
 * int maxp: 记录最大价值
 */

int n,m;
vector<int> a;
int maxp;

/* good:
 * w: 物品重量
 * c: 物品价值
 * id: 物品编号
 * good[] g: 记录所有物品信息
 */
struct good{
    int w,c,id;
}g[32];

//status用于记录路径和pt值
//s当前还未处理的编号最小值,nw:目前已加入重量,np:目前已加入价值
class status{
public:
    vector<int> now;
    int pt;
    int s;
    int nw,np;
    status (){
        pt = 0;
        s = nw = np= -1;
    }
    status(int s,int pt,int nw,int np){
        this->pt = pt;
        this->s = s;
        this->nw = nw;
        this->np = np;
    }
    status(int s,int pt,int nw,int np,vector<int> now){
        this->pt = pt;
        this->s = s;
        this->now = now;
        this->nw = nw;
        this->np = np;
    }
    bool operator < (const status & s2)const{
        if(pt != s2.pt)return pt < s2.pt;
        return nw < s2.nw;
    }
    bool operator > (const status & s2)const{
        if(pt != s2.pt)return pt > s2.pt;
        return nw > s2.nw;
    }
};



/*
 * 按照单位价值从大到小排序
*/
bool cmp(good g1,good g2){
    if(g1.c/g1.w!=g2.c/g2.w)return g1.c/g1.w > g2.c/g2.w;
    if(g1.w!=g2.w)return g1.w < g2.w;
    return g1.id < g2.id;
}
/*
 * 计算目前的上限
 * nw: 目前已经加入的重量
 * np: 目前已经加入的价值
 * ind: 目前正在考虑的物品编号
 */
double ex(int nw,int np,int ind){
    if(ind == n)return np;
    return np + (m - nw)*(g[ind].c/(double)g[ind].w);
}
/*
 * 具体搜索过程,结果在全局变量maxp和a中体现
 */
void bfs(){
    status s(0,m * g[0].c/g[0].w,0,0);
    priority_queue<status, vector<status>, less<status> >que;
    que.push(s);
    while(!que.empty()){
        status tp = que.top();que.pop();
        int s = tp.s,nw = tp.nw,np = tp.np;

        //加入物品s
        if(g[s].w + nw <= m){
            int e = (int)ex(nw + g[s].w,np + g[s].c,s + 1);
            //如果上限比目前最优解小,则没有必要继续考虑
            if(e <= maxp)return;
            else{
                int sub = np + g[s].c;
                //取最优解
                if(sub > maxp){
                    maxp = sub;
                    a = tp.now;
                    a.push_back(s);
                }
                if(s < n - 1){
                    //在物品集中加入物品s
                    status t(s + 1,e,nw + g[s].w,sub,tp.now);
                    t.now.push_back(s);
                    que.push(t);
                }
            }
        }
        //不加物品s
        if(s + 1 < n){
            int e = (int)ex(nw,np,s + 1);
            if(e <= maxp)return;
            else{
                status t(s + 1,e,nw,np,tp.now);
                que.push(t);
            }
        }
    }
}
int main(){
    cout<<"请输入背包重量"<<endl;
    cin>>m;
    cout<<"请输入重物个数"<<endl;
    cin>>n;
    for(int i = 0;i < n;i++){
        cout<<"请输入第"<<i+1<<"个重物的重量"<<endl;
        cin>>g[i].w;
        cout<<"请输入第"<<i+1<<"个重物的价格"<<endl;
        cin>>g[i].c;
        g[i].id = i + 1;
    }
    sort(g,g+n,cmp);
    bfs();
    cout<<"最大价值"<<maxp<<endl;
    cout<<"所取物品"<<endl;
    for(int i = 0;i < a.size();i++){
        cout<<a[i]<<endl;
    }
    return 0;
}
