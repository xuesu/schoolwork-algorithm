#include <cstdio>
#include <iostream>
#include <algorithm>
#include <assert.h>
#include <iomanip>

using namespace std;
const int maxn = 100;
int maz[maxn][maxn];
int n,cnt;

struct p{
    int x,y;
    p(){
        x = y = 0;
    }
    p(int x,int y){
        this->x = x;
        this->y = y;
    }
    bool operator == (p p2)const{
        return x == p2.x && y == p2.y;
    }
    bool operator != (p p2)const{
        return !(*this == p2);
    }
    void fill(int i){
        maz[x][y] = i;
    }
    bool filled(){
        return maz[x][y] != 0;
    }
}st;
struct cube{
    p s,e;
    cube(p s,p e){
        this->s = s;
        this->e = e;
    }
    int getlength(){
        assert(e.x - s.x == e.y - s.y);
        assert(e.x > s.x);
        return e.x - s.x;
    }
    cube getll(){
        assert(s!=e);
        return cube(s,p((s.x + e.x)/2,(s.y + e.y)/2));
    }
    cube getlr(){
        assert(s!=e);
        return cube(p((s.x + e.x)/2,s.y),p(e.x,(s.y + e.y)/2));
    }
    cube getrl(){
        assert(s!=e);
        return cube(p(s.x,(s.y + e.y)/2),p((s.x + e.x)/2,e.y));
    }
    cube getrr(){
        assert(s!=e);
        return cube(p((s.x + e.x)/2,(s.y + e.y)/2),p(e.x,e.y));
    }

/*
ll|lr
rl|rr
*/
    p getllp(){
        return s;
    }
    p getlrp(){
        return p(e.x - 1,s.y);
    }
    p getrlp(){
        return p(s.x,e.y - 1);
    }
    p getrrp(){
        return p(e.x - 1,e.y - 1);
    }
    bool filled()
    {
        for(int i = s.x;i < e.x;i++){
            for(int j = s.y;j < e.y;j++){
                if(p(i,j).filled())return true;
            }
        }
        return false;
    }
    bool in(p p1){
        return p1.x >= s.x && p1.x < e.x && p1.y >= s.y && p1.y < e.y;
    }
    bool fill(){
        cube c = * this;
        int l = c.getlength();
        if(l == 1){
            return c.s.filled() || c.s == st;
        }
        cube ll = c.getll(),lr = c.getlr(),rl = c.getrl(),rr= c.getrr();
        ++cnt;
        bool fl = false;
        if(!ll.in(st)&&!ll.filled()){
            ll.getrrp().fill(cnt);
        }else {
            if(fl){
                return false;
            }
            fl = true;
        }
        if(!lr.in(st)&&!lr.filled()){
            lr.getrlp().fill(cnt);
        }else {
            if(fl){
                return false;
            }
            fl = true;
        }
        if(!rl.in(st)&&!rl.filled()){
            rl.getlrp().fill(cnt);
        }else {
            if(fl){
                return false;
            }
            fl = true;
        }
        if(!rr.in(st)&&!rr.filled()){
            rr.getllp().fill(cnt);
        }else {
            if(fl){
                return false;
            }
            fl = true;
        }
        return ll.fill() && lr.fill() && rr.fill() && rl.fill();
    }
};

int main(){
    cout<<"Please input the length(the lab is 2^length * 2^length)"<<endl;
    cin>>n;
    n = (1<<n);
    cout<<"Please input the coordinate:(example: 0 0)"<<endl;
    cin>>st.x>>st.y;
    cube c(p(0,0),p(n,n));
    cout<<"FILL:"<<c.fill()<<endl;
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++)cout<<setw(3)<<maz[i][j]<<" ";
        cout<<endl;
    }
    return 0;
}
