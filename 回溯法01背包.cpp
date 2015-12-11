#include <cstdio>
#include <iostream>
#include <bitset>
#include <cstring>
#include <algorithm>
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
int path[32],pi;
int a[32];
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
    return np + (m - nw)*(g[ind].c/(double)g[ind].w);
}
/*
 * 具体搜索过程,结果在全局变量maxp和a中体现
 * s: 目前正在考虑的物品编号
 * nw: 目前已经加入的重量
 * np: 目前已经加入的价值
 */
void dfs(int s,int nw,int np){
    //加入物品s
    if(g[s].w + nw <= m){
        int e = (int)ex(nw,np,s);
        //如果上限比目前最优解小,则没有必要继续考虑
        if(e <= maxp)return;
        else{
            int sub = np + g[s].c;
            //在物品集中加入物品s
            path[pi++] = g[s].id;
            //取最优解
            if(sub > maxp){
                maxp = sub;
                copy(path,path + n,a);
            }
            dfs(s+1,nw + g[s].w, sub);
            //恢复路径状态
            pi--;
            path[pi] = 0;
        }
    }
    //不加物品s
    if(s + 1 < n){
        int e = (int)ex(nw,np,s + 1);
        if(e <= maxp)return;
        else{
            dfs(s+1,nw, np);
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
    dfs(0,0,0);
    cout<<"最大价值"<<maxp<<endl;
    cout<<"所取物品"<<endl;
    for(int i = 0;a[i];i++){
        cout<<a[i]<<endl;
    }
    return 0;
}
