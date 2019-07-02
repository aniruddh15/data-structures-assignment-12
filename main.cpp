//Author: Aniruddh Kathiriya
//Assignment 12

#include "graph.h"
#include <iostream>
#include <string>
#include <cassert>
#include <list>
#include <sstream>
#include <fstream>
#include <iterator>
#include <algorithm>
using namespace std;
using namespace main_savitch_15;

void tokenize (const string& s, string& first, string& second)
{
    stringstream ss (s);
    ss >> first;
    ss >> second;
}

size_t get_index (const graph<string>& g, const string& target)
{
    size_t i = 0;
	bool found=false;
	for(size_t j=0;j<g.size();j++){
		//cout<<g[j]<<endl;
		string str1=g[j];
		string str2=target;
		if(str1.compare(str2)==0){
			i=j;
			found=true;
			break;
		}
	}
	assert(found);//target not in the vertex
	
    return i;
}


graph<string>* create_graph (const string& file_name)
{
    graph<string>* g = new graph<string>;
    ifstream input(file_name.c_str());
    size_t num;
    input >> num;
    string temp;
    getline (input, temp);
    assert (num <= g -> MAXIMUM);
    string* names = new string[num];
    for (size_t i = 0; i < num; ++i)
    {
        string s;
       getline (input, s);
        names[i] = s;
        g -> add_vertex (s);
    }
    string line;
    while (getline (input, line)>0)
    {
		
        string first, second;
        tokenize (line, first, second);
        g -> add_edge (get_index (*g, first), get_index (*g, second));
		
    }
    input.close();
    return g;
}
set<string> friends (const graph<string>& network, const string& name){
	set<string> s1;
	size_t index=get_index(network,name);
	set<size_t> s2=network.neighbors(index);
	for (std::set<size_t>::iterator it=s2.begin(); it!=s2.end(); ++it){
		s1.insert(network[*it]);
	}
	
	return s1;
}
set<string> common_friends (const graph<string>& network, const string& name1, const string& name2){
	set<string> s1;
	set<string> target1_s=friends(network,name1);
	set<string> target2_s=friends(network,name2);
	set_intersection(target1_s.begin(),target1_s.end(),target2_s.begin(),target2_s.end(),inserter(s1,s1.begin()));
	return s1;
	
	
}
set<string> friends_of_friends ( const graph<string>& network, const string& my_name){
	set<string> s1;
	set<string> neighbors=friends(network,my_name);
	set<string> friends_of_neighbors;
	for (std::set<string>::iterator it=neighbors.begin(); it!=neighbors.end(); ++it){
		friends_of_neighbors=friends(network,*it);
		for (std::set<string>::iterator itt=friends_of_neighbors.begin(); itt!=friends_of_neighbors.end(); ++itt){

			s1.insert(*itt);
			
		}
	}
	return s1;
}
void add_friend (graph<string>& network, const string& my_name, const string& new_friend){
	network.add_edge (get_index (network, my_name), get_index (network, new_friend));
}
void remove_friend (graph<string>& network, const string& my_name, const string& ex_friend){
	network.remove_edge (get_index (network, my_name), get_index (network, ex_friend));
}
bool is_friend (const graph<string>& network, const string& my_name, const string& maybe_friend){
	return network.is_edge(get_index (network, my_name), get_index (network, maybe_friend));
}
void print(const set<string> s,const string& test){
	cout<<"--------------"<<test<<"--------------"<<endl;
	if(!s.empty()){
	for (std::set<string>::iterator it=s.begin(); it!=s.end(); ++it){
		cout <<*it<<" ";
	}
	}else{
	cout<<"SET IS EMPTY";
	}
	cout<<endl;
	cout<<endl;
	
}
int main(){
	
	graph<string> *g=create_graph("assign.dat");
	set<string> s=friends(*g,"Sally");
	print(s,"Testing Friends for Sally");
	
	s=common_friends(*g,"Sally","Sally");
	print(s,"Testing Common Friends Function Sally & Sally");
	s=friends_of_friends(*g,"Sally");
	print(s,"Testing Friends of Friends for Sally");
	s=friends(*g,"William");
	print(s,"Testing Friends for William");
	s=friends_of_friends(*g,"William");
	print(s,"Testing Friends of Friends for William");
	s=friends(*g,"Eyles");
	print(s,"Testing Friends for Eyles");
	s=friends_of_friends(*g,"Eyles");
	print(s,"Testing Friends of Friends for Eyles");
	s=friends(*g,"Michelle");
	print(s,"Testing Friends for Michelle");
	s=friends_of_friends(*g,"Michelle");
	print(s,"Testing Friends of Friends for Michelle");
	add_friend(*g,"Michelle","William");
	s=friends(*g,"Michelle");
	print(s,"Testing Friends for Michelle after Adding William");
	assert(is_friend(*g,"Michelle","William"));
	remove_friend(*g,"Michelle","William");
	s=friends(*g,"Michelle");
	print(s,"Testing Friends for Michelle after Removing William");
	assert(!is_friend(*g,"Michelle","William"));
	
	
	return 0;
};
