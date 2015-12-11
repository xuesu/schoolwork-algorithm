#include <cstdio>
#include <iostream>
#include <bitset>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
/*
 * int n: ��Ʒ����
 * int m: �����������
 * int[] path: ��¼�Ѿ�ȡ�˵���Ʒ��,Ҳ����¼dfs��·��
 * int pi: the index of path, Ŀǰpath�����¼��ȡ������Ʒ
 * int[] a: ��¼������Ʒ��
 * int maxp: ��¼����ֵ
 */

int n,m;
vector<int> a;
int maxp;

/* good:
 * w: ��Ʒ����
 * c: ��Ʒ��ֵ
 * id: ��Ʒ���
 * good[] g: ��¼������Ʒ��Ϣ
 */
struct good{
    int w,c,id;
}g[32];

//status���ڼ�¼·����ptֵ
//s��ǰ��δ����ı����Сֵ,nw:Ŀǰ�Ѽ�������,np:Ŀǰ�Ѽ����ֵ
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
 * ���յ�λ��ֵ�Ӵ�С����
*/
bool cmp(good g1,good g2){
    if(g1.c/g1.w!=g2.c/g2.w)return g1.c/g1.w > g2.c/g2.w;
    if(g1.w!=g2.w)return g1.w < g2.w;
    return g1.id < g2.id;
}
/*
 * ����Ŀǰ������
 * nw: Ŀǰ�Ѿ����������
 * np: Ŀǰ�Ѿ�����ļ�ֵ
 * ind: Ŀǰ���ڿ��ǵ���Ʒ���
 */
double ex(int nw,int np,int ind){
    if(ind == n)return np;
    return np + (m - nw)*(g[ind].c/(double)g[ind].w);
}
/*
 * ������������,�����ȫ�ֱ���maxp��a������
 */
void bfs(){
    status s(0,m * g[0].c/g[0].w,0,0);
    priority_queue<status, vector<status>, less<status> >que;
    que.push(s);
    while(!que.empty()){
        status tp = que.top();que.pop();
        int s = tp.s,nw = tp.nw,np = tp.np;

        //������Ʒs
        if(g[s].w + nw <= m){
            int e = (int)ex(nw + g[s].w,np + g[s].c,s + 1);
            //������ޱ�Ŀǰ���Ž�С,��û�б�Ҫ��������
            if(e <= maxp)return;
            else{
                int sub = np + g[s].c;
                //ȡ���Ž�
                if(sub > maxp){
                    maxp = sub;
                    a = tp.now;
                    a.push_back(s);
                }
                if(s < n - 1){
                    //����Ʒ���м�����Ʒs
                    status t(s + 1,e,nw + g[s].w,sub,tp.now);
                    t.now.push_back(s);
                    que.push(t);
                }
            }
        }
        //������Ʒs
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
    cout<<"�����뱳������"<<endl;
    cin>>m;
    cout<<"�������������"<<endl;
    cin>>n;
    for(int i = 0;i < n;i++){
        cout<<"�������"<<i+1<<"�����������"<<endl;
        cin>>g[i].w;
        cout<<"�������"<<i+1<<"������ļ۸�"<<endl;
        cin>>g[i].c;
        g[i].id = i + 1;
    }
    sort(g,g+n,cmp);
    bfs();
    cout<<"����ֵ"<<maxp<<endl;
    cout<<"��ȡ��Ʒ"<<endl;
    for(int i = 0;i < a.size();i++){
        cout<<a[i]<<endl;
    }
    return 0;
}
