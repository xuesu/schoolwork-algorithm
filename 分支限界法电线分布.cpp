#include <cstdio>
#include <iostream>
#include <bitset>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;
/*
 * int n: �ڵ���
 * int a: ���
 * int ax,ay: ��������a
 * int b: �յ�
 * int bx,by:��������b
 */
int n,a,b,ax,ay,bx,by;

/*
 * c[i][j]:cost ����i�ڵ���4�����������������
 * dx[4],dy[4]:�����ĸ�����,x��ʾ��ֱ����,y��ʾˮƽ����,
 * ����ֱ���:0:���� 1:���� 2:���� 3:����
 */
int c[36][4];
const int dx[4]={1,-1,0,0};
const int dy[4]={0,0,1,-1};

/*
 * int dp[]: �洢����õ�����Ž��
 * int now[]: �洢����õ�����Ž��
 * int ans[]: �洢����ý��
 * int minc: ��С�ı�����ֵ,������������
 */
int dp[36];
int pt[36],minc;
int now[36];
bool in(int i,int j){
    return i>=0 && i < n && j >=0 && j < n;
}
int ind(int i,int j){
    return i*n+j;
}
int calpt(int x,int y,int np){
    return np + minc * (abs(bx - x) + abs(by - y));
}
struct p{
    int x,y;
    p(int x,int y){
        this->x = x;
        this->y = y;
    }
    bool operator >(const p& p2)const{
        return pt[ind(x,y)] > pt[ind(p2.x,p2.y)];
    }
};

void bfs(int sx,int sy){
    priority_queue<p,vector<p>,greater<p> >que;
    que.push(p(sx,sy));
    //��־�Ƿ��ڶ�����
    bool used[36];
    memset(used,0,sizeof used);
    while(!que.empty()){
        p tp = que.top();que.pop();
        sx = tp.x;sy = tp.y;
        int s = ind(sx,sy);
        used[ind(sx,sy)] = false;
        for(int di = 0;di < 4;di++){
            int tx = sx + dx[di],ty = sy + dy[di];
            if(!in(tx,ty))continue;
            int t = ind(tx,ty);
            if(calpt(tx,ty,dp[s] + c[s][di]) < dp[b] &&  dp[t]>dp[s] + c[s][di]){
                dp[t] = dp[s] + c[s][di];
                now[t] = di;
                pt[t] = calpt(tx,ty,dp[s] + c[s][di]);
                if(!used[t]){
                    used[t] = true;
                    que.push(p(tx,ty));
                }
            }
        }
    }
}

int main(){
    cout<<"Please input n:(no more than 6)";
    cin>>n;
    for(int i = 0;i < n * n;i++){
        dp[i] = 0x3f3f3f3f;
        memset(c[i],0x3f,sizeof c[i]);
    }
    minc = 0x7fffffff;

    cout<<"Please input the cost matrix(vertically)"<<endl;
    for(int i = 0;i < n - 1;i++){
        for(int j = 0;j < n;j++){
            int tmp;
            cin>>tmp;
            minc = min(minc,tmp);
            c[ind(i,j)][0]=tmp;
            c[ind(i + 1,j)][1]=tmp;
        }
    }
    cout<<"Please input the cost matrix(horizontally)"<<endl;
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n - 1;j++){
            int tmp;
            cin>>tmp;
            minc = min(minc,tmp);
            c[ind(i,j)][2]=tmp;
            c[ind(i,j + 1)][3]=tmp;
        }
    }
    cout<<"Please input ax,ay:";
    cin>>ax>>ay;
    a=ind(ax,ay);
    dp[a] = 0;
    cout<<"Please input bx,by:";
    cin>>bx>>by;
    b=ind(bx,by);
    bfs(ax,ay);
    cout<<"Consume:"<<dp[b]<<endl;

    //�������Ϣ
    int tmpx = bx,tmpy = by,tmp = b;
    //�洢���շ�����,m�ǲ���
    int ans[36],m = 0;
    for(m = 0;m < n * n && tmp != a;m ++){
        ans[m] = now[tmp];
        tmpx -= dx[now[tmp]];
        tmpy -= dy[now[tmp]];
        tmp = ind(tmpx,tmpy);
    }
    cout<<"Direction is:";
    for(int i = m - 1;i >= 0;i--)cout<<ans[i]<<" ";
    cout<<endl;
    return 0;
}
