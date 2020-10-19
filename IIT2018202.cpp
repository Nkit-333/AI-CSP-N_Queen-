#include<bits/stdc++.h>
using namespace std;
bool complete(vector<int> state,int N){
    //bool h=true;
    for(int i=0;i<N;i++)
    {
        if(state[i]==-1)
            return false;
    }
    return true;
}
void show(vector<int> v){
for(int k=0;k<v.size();k++){
    for(int i=0;i<v.size();i++)
    {
       if(i==v[k])
        cout<<"Q"<<" ";
       else
        cout<<"*"<<" ";
    }
    cout<<"\n";
}
}
void show_domain(vector<set<int>> domain)
{
    for(int i=0;i<domain.size();i++)
        {
            for(auto j=domain[i].begin();j!=domain[i].end();j++)
                cout<<*j<<" ";
            cout<<endl;
        }
}
int mrv_heristic(vector<int> temp, vector<set<int>>&domain,int N){
    vector<pair<int,int>> vape;
   int min=INT_MAX;
   int select;
   for(int i=0;i<domain.size();i++)
   {
      if(domain[i].size()!=0&&temp[i]==-1)
      {
        vape.push_back({domain[i].size(),i});
      }      
   }
   sort(vape.begin(),vape.end());
   //cout<<"showing sizes"<<endl;
   //for(auto itr=vape.begin();itr!=vape.end();itr++)
        //cout<<"size"<<itr->first<<" index "<<itr->second<<" ";
   //cout<<endl;
   return vape.begin()->second;

}
void forward_checking(vector<set<int>> &domain,int n,int ind,int q) //ind ==> pth
{
    for(int j=0;j<n;j++)
    {
        if(j!=q)
        {
            if(domain[j].find(ind)!=domain[j].end())
            {
                domain[j].erase(ind);
            }
            if((ind+(q-j))<n&&(ind+(q-j))>=0&&domain[j].find(ind+(q-j))!=domain[j].end())
                domain[j].erase(ind+(q-j));
           if((ind+(j-q))<n&&(ind+(j-q))>=0&&domain[j].find(ind+(j-q))!=domain[j].end())
                domain[j].erase(ind+(j-q));

        }
    }        
}   
bool check_empty(vector<int> s,vector<set<int>> domains){
    //cout<<endl;
    for(int i=0;i<domains.size();i++){
        if(domains[i].size()==0&&s[i]==-1)
            return true;
    }
    return false;
}
int count_forward(vector<set<int>> domain,int ind,int q)
{
    int n=domain.size();
    int count=0;
    for(int j=0;j<domain.size();j++){
   
    if(j!=q){
    
        if(domain[j].find(ind)!=domain[j].end())
            count++;
        if((ind+(q-j))<n&&(ind+(q-j))>=0&&domain[j].find(ind+(q-j))!=domain[j].end())
            count++;
        if((ind+(j-q))<n&&(ind+(j-q))>=0&&domain[j].find(ind+(j-q))!=domain[j].end())
            count++;}
    }
    return count;

}
vector<int> Lcv_heuristic(vector<set<int>> domains,int queen,set<int> &v)
{
    vector<int> temp;
    vector<set<int>> d=domains;
    vector<pair<int,int>> map;
    for(auto i=d[queen].begin();i!=d[queen].end();i++){
        int count= count_forward(d,*i,queen);
        map.push_back({count,*i});   
    }  
    sort(map.begin(),map.end());   
    for(auto itr=map.begin();itr!=map.end();itr++)
    {
        //v.insert(itr->second);
        temp.push_back(itr->second);
    }

    return temp;
}
bool maintain(set<int> &q1,set<int> &q2,int queen1,int queen2,int n){
    bool change=false;
    
    set<int> tq1 = q1;
    
    for(auto i=tq1.begin();i!=tq1.end();i++)
    {
        int count=0;
        if(q2.find(*i)!=q2.end())
            count++;
        if((*i+(queen1-queen2))<n&&(*i+(queen1-queen2))>=0&&q2.find(*i+(queen1-queen2))!=q2.end())
            count++;
        if((*i+(queen2-queen1))<n&&(*i+(queen2-queen1))>=0&&q2.find(*i+(queen2-queen1))!=q2.end())
            count++;   
        if(count==q2.size())
        {
            q1.erase(*i);
            change=true;
        }
    }
    return change;
}
void arc_consistency(vector<set<int>> &domains,int N,vector<int> state){
    
    
    queue<pair<int,int>> q;
    for(int i=0;i<N;i++)
    {
        if(find(state.begin(), state.end(), i) == state.end()){
            for(int j =0;j<N;j++){
                if(find(state.begin(), state.end(), j) == state.end()){
                    if(i!=j)
                        q.push({i,j});
                }
            }
        }
    }
    while(!q.empty()){
        pair<int,int> curr=q.front();
        q.pop();
        if(domains[curr.first].size() == 0){
            return;
        }
        if(maintain(domains[curr.first],domains[curr.second],curr.first,curr.second,N))
        {
            //cout<<"y1"<<endl;
            for(int i=0; i<domains.size(); i++){
                if(domains[i].size() == 0){
                    return;
                }
                for(auto itr = domains[i].begin(); itr!=domains[i].end(); itr++){
                    //cout<<*itr<<" ";
                }
                //cout<<endl;
            }
            //if(domains[curr.second].size()!=0){
             for(int i=0;i<N;i++){
                if(find(state.begin(), state.end(), i) == state.end()){
                    if(i!=curr.first)
                        q.push({i,curr.first});
                } 
             }
        }
    }
}
void solve_nqueen(vector<int> state,vector<set<int>> domains,int N){
    //show(state);
    if(complete(state,N)){
        cout<<"Placed at\n";
         show(state);
        exit(0);
    }
    arc_consistency(domains,N,state);
    /*if(check_empty(state,domains)){
           //cout<<"BT";
            return ;
    }*/
   int queen=mrv_heristic(state,domains,N);
   set<int> queen_domain=domains[queen];
   vector<int> queen_dom=Lcv_heuristic(domains,queen,queen_domain); 
   //cout<<"Queen Selected"<<queen<<endl;
   for(auto i=queen_dom.begin();i!=queen_dom.end();i++){
        //cout<<"Round "<<*i<<endl;
        vector<set<int>> copydomain=domains;
        state[queen]=*i;
        //cout<<endl;
        copydomain[queen].erase(*i); 
        domains[queen].erase(*i);    
        forward_checking(copydomain,N,*i,queen);
        //show_domain(copydomain);
        //cout<<endl;
        if(check_empty(state,copydomain)){
           //cout<<"BT";
            return ;
        }
       solve_nqueen(state,copydomain,N);
    }
}
void dfssolver(int N)
{
    vector<int> state(N,-1);
    vector<set<int>> domains;
    for(int i=0;i<N;i++)
    {
        set<int>v;
        for(int j=0;j<N;j++){
            v.insert(j);
        }
            
    domains.push_back(v);
    }
   
    solve_nqueen(state,domains,N);
    
}
int main()
{
    int N;
    cin>>N;
    dfssolver(N);
}