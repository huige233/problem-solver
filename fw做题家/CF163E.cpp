#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e6+10;
struct node{
    int cnt;
    node * nxt[27];
    node * fail;
    vector<node *> num;
    int pre,ed;
}*rt;
node pool[N];
node *pos[N];
int n,idx;
void insert(string s,int x){
    node *p=rt;
    int i;
    for(i=0;i<s.size();i++){
        int sign=s[i]-'a';
        if(p->nxt[sign]==NULL)
            p->nxt[sign]=pool+(++idx);
        p=p->nxt[sign];
        if(i==(int)s.size()-1)
            pos[x]=p;
    }
}
void build(){
    int i;
    queue<node *> q;
    rt->fail=rt;
    for(i=0;i<26;i++){
        if(rt->nxt[i]){
            rt->nxt[i]->fail=rt;//第一次fail等于根
            rt->num.push_back(rt->nxt[i]);
            q.push(rt->nxt[i]);
        }
        else{
            rt->nxt[i]=rt;//不存在则指向根重新匹配
            rt->nxt[i]->fail=rt;
        }
    }
    while(q.size()){
        auto t=q.front();
        q.pop();
        for(i=0;i<26;i++){
            if(t->nxt[i]){
                t->nxt[i]->fail=t->fail->nxt[i];//存在则最长后缀就是fail指向的最长后缀，因为本身不行
                t->fail->nxt[i]->num.push_back(t->nxt[i]);//fail树的存储
                q.push(t->nxt[i]);
            }
            else{
                t->nxt[i]=t->fail->nxt[i];//Trie图,路径压缩思想，直接跳跃到答案
            }
        }
    }
}
int times;
void dfs(node * p){
    p->pre=++times;
    for(int i=0;i<p->num.size();i++){
        auto t=p->num[i];
        dfs(t);
    }
    p->ed=times;
}
int lowbit(int x){
    return x&-x;
}
int tr[N];
void add(int x,int c){
    int i;
    for(i=x;i<N;i+=lowbit(i)){
        tr[i]+=c;
    }
}
ll sum(int x){
    int i;
    ll ans=0;
    for(i=x;i;i-=lowbit(i)){
        ans+=tr[i];
    }
    return ans;
}
bool vis[N];
int main(){
    int k;
    ios::sync_with_stdio(false);
    cin>>k>>n;
    int i;
    rt=pool;
    for(i=1;i<=n;i++){
        string s;
        cin>>s;
        insert(s,i);
        vis[i]=1;
    }
    build();//没有空白位置
    dfs(rt);
    for(i=1;i<=n;i++){
        add(pos[i]->pre,1);
        add(pos[i]->ed+1,-1);
    }
    while(k--){
        char c;
        cin>>c;
        int x;
        if(c=='?'){
            string s;
            cin>>s;
            ll ans=0;
           // cout<<s<<endl;
            node *p=rt;
            for(i=0;i<s.size();i++){
                int t=s[i]-'a';
                p=p->nxt[t];
                ans+=sum(p->pre);
                //cout<<ans<<" aa"<<endl;
            }
            cout<<ans<<endl;
        }
        else if(c=='+'){
            cin>>x;
            if(vis[x])
                continue;
            vis[x]=1;
            add(pos[x]->pre,1);
            add(pos[x]->ed+1,-1);
        }
        else{
            cin>>x;
            if(!vis[x])
                continue;
            vis[x]=0;
            add(pos[x]->pre,-1);
            add(pos[x]->ed+1,1);
        }
    }
}