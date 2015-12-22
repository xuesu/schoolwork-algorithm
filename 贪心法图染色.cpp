#include <cstdio>
#include <iostream>
#include <bitset>
#include <cstring>
#include <algorithm>
using namespace std;
/*
 * int n: �ڵ���
 * int m: �������
 * int nc: ��ɫ��
 * int[] c: ��Ʒ��ȡ��ɫ��
 */
int n,m,nc;
int c[32];

/* �ڽ�����
 * first: ͷ���
 * nxt: ָ����һ���ڵ��ƫ����
 * to: ��β
 * ind: Ŀǰ�Ѿ�����Ļ���
 */
int first[32];
int nxt[1024],ind;
int to[1024];

//��ӻ�,from f to t
void addedge(int f,int t){
    to[ind] = t;
    nxt[ind] = first[f];
    first[f] = ind;
    ind++;
}

//������������,sΪ���
bool dfs(int s){
    for(int p = first[s];p!=-1;p=nxt[p]){
        int t = to[p];
        if(c[t]!=0){
            if(c[t]==c[s])return false;
        }
        else{
            //���Ų���Ϊs�����ɫ�����С,���Դ�С�������
            for(int i = 1;i <= nc;i++){
                if(i == c[s])continue;
                c[t] = i;
                //�Ѿ��ѵ����Ž�
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
    //��ʼ���ڽӾ���,-1 ΪNULL���
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
