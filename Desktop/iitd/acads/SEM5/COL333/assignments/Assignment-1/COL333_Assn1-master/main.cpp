# include <iostream>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <string> 
#include <climits>
using namespace std;

long cost(string s1, string s2, int **mc, unordered_map<char, int> hash)
{
	long cost=0;
	for(int i=0;i<s1.length();i++)
	{
		cost=cost+mc[hash[s1[i]]][hash[s2[i]]];
	}
	return cost;
}

class State{

	public:
	vector<string> strings;
	vector<int> positions;	// counts of characters unseen in each string

	State(vector<string> x){
		strings=x;
		for(auto xi : x){
			positions.push_back(xi.length());
		}
	}

	bool Equals(State s){
		if (s.strings != strings)
			return false;
		if(s.positions != positions)
			return false;
		return true;
	}
};

State Successor(State current, int index){

	if(index==current.strings.size())
		return current;

	if(current.positions[index]==0)
		return Successor(current,index+1);

	State dashed = current;

	dashed.strings[index].insert(dashed.strings[index].length()-dashed.positions[index],"-");
			 // dash at (str's length - unseen chars) so #unseen is unchanged

	if(totalCost(dashed.strings) < totalCost(current.strings))
		return Successor(dashed,index+1);
	current.positions[index]--; // char at (str's length - unseen chars) so #unseen decreases
	return  Successor(current,index+1);
}

State localSearch(State start){
	State next = Successor(start,0);
	if(start.Equals(next))
		return start;
	return next;
}

int main(int argc, char **argv)
{
	float t=0.0f;
	long long vocab_size;
	ifstream myfile (argv[1]);
	myfile>>t;
    myfile>>vocab_size;
    char vocab[vocab_size];
    for(long i=0;i<vocab_size;++i)
    {
    	string s;
    	myfile>>s;
    	vocab[i]=s[0];
    }
    unordered_map<char, int> vocab_index;
    for(long i=0;i<vocab_size;++i)
    {
    	vocab_index.insert(make_pair(vocab[i], i));
    }
    long long k;
    myfile>>k;
    vector<string> x (k,"");
    for(long i=0;i<k;++i)
    {
    	myfile>>x[i];
    }
    long cc=0;
    myfile>>cc;
    int mc[vocab_size+1][vocab_size+1];
    for(int i=0;i<=vocab_size;++i)
    {
    	for(int j=0;j<=vocab_size;++j)
    	{
    		mc[i][j]=-1;;
    	}
    }
    
    for(int i=0;i<=vocab_size;++i)
    {
    	for(int j=0;j<=vocab_size;++j)
    	{
    		myfile>>mc[i][j];
    	}
    }

    State initial_state(x),final_state = Successor(initial_state,0);
    for(long i=0;i<k;++i)
    {
    	cout<<x[i]<<"\n";
    }
    return 0;
}