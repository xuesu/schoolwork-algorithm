#include <cstdio>
#include <iostream>
#include <bitset>
#include <cstring>
#include <algorithm>
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
int path[32],pi;
int a[32];
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
    return np + (m - nw)*(g[ind].c/(double)g[ind].w);
}
/*
 * ������������,�����ȫ�ֱ���maxp��a������
 * s: Ŀǰ���ڿ��ǵ���Ʒ���
 * nw: Ŀǰ�Ѿ����������
 * np: Ŀǰ�Ѿ�����ļ�ֵ
 */
void dfs(int s,int nw,int np){
    //������Ʒs
    if(g[s].w + nw <= m){
        int e = (int)ex(nw,np,s);
        //������ޱ�Ŀǰ���Ž�С,��û�б�Ҫ��������
        if(e <= maxp)return;
        else{
            int sub = np + g[s].c;
            //����Ʒ���м�����Ʒs
            path[pi++] = g[s].id;
            //ȡ���Ž�
            if(sub > maxp){
                maxp = sub;
                copy(path,path + n,a);
            }
            dfs(s+1,nw + g[s].w, sub);
            //�ָ�·��״̬
            pi--;
            path[pi] = 0;
        }
    }
    //������Ʒs
    if(s + 1 < n){
        int e = (int)ex(nw,np,s + 1);
        if(e <= maxp)return;
        else{
            dfs(s+1,nw, np);
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
    dfs(0,0,0);
    cout<<"����ֵ"<<maxp<<endl;
    cout<<"��ȡ��Ʒ"<<endl;
    for(int i = 0;a[i];i++){
        cout<<a[i]<<endl;
    }
    return 0;
}
