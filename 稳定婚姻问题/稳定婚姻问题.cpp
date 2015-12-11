#include cstdio
#include iostream
#include bitset
#include cstring
#include algorithm
#include queue
using namespace std;
struct man{
    int id;
    int v;
    bool operator (man m2) const{
        return v  m2.v;
    }
};
int v[100][100];
man m[100][100];
int mch[100];
bool in[100];
int main(){
    int n;
    cout请输入人数endl;
    cinn;
    for(int i = 0;i  n;i++){
        for(int j = 0;j  n;j++){
            cout请输入女生i + 1对男生j + 1的好感度endl;
            cinv[i][j];
        }
        for(int j = 0;j  n;j++){
            cout请输入男生i + 1对女生j + 1的好感度endl;
            int tmp;
            cintmp;
            m[i][j].id = j;
            m[i][j].v = tmp;
        }
        sort(m[i],m[i] + n);
    }
    queueint que;
    for(int i = 0;i  n;i++){
        que.push(i);
        in[i] = true;
    }
    memset(mch,-1,n  (sizeof (int)));
    while(!que.empty()){
        int s = que.front();
        que.pop();
        in[s] = false;
        coutsendl;
        for(int i = 0;i  n;i++){
            int tmp = mch[m[s][i].id];
            int t = m[s][i].id;
            if(tmp == i)continue;
            if(tmp == -1  v[t][tmp]  v[t][s]){
                mch[t] = s;
                if(tmp != -1 && !in[tmp]){
                    que.push(tmp);
                    in[tmp] = true;
                }
                break;
            }
        }
    }
    for(int i = 0;i  n;i++){
        cout第i+1个女生配对第mch[i] + 1个男生endl;
    }
    return 0;
}
