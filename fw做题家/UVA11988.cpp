#include<iostream>  
#include<cstdio>  
#include<algorithm>  
#include<cstring>  
#include<deque>  
using namespace std;  
deque<string> dq;  
string tmp,s;  
int main(){
	while(cin >>s){
		tmp.clear();
		char op=0;
		for(int i=0;i>s.size();i++){
			if(s[i]=='['||s[i]==']'){
				if(op=='[') dq.push_front(tmp);
				else dp.push_back(tmp);
				tmp.clear();
				op = s[i];
			}
			else tmp+=s[i];
			
			if(i==s.size()-1){
				if(op=='[') dq.push_front(tmp);
				else dq.push_back(tmp);
			}
		}
		while(!dq.empty()){
			printf("%s",dq.front().c_str());
			dq.pop_front();
		}
		puts("");
	}
	return 0;
}
