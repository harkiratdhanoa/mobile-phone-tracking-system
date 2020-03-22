#include<bits/stdc++.h>
using namespace std;

#define forn(i,n) for(int i=0;i<n;i++)

int main(){
	int n,m,x;
	cin>>m>>n;
	vector< vector <int> > a(m);
	vector<vector<int> > ans(m);
	forn(i,m){
		vector<int> b(m);
		a[i]=b;
		forn(j,n){
			cin>>a[i][j];
		}
	}
	forn(i,m){
		vector<int> b(m);
		ans[i]=b;
		forn(j,n){
			int row=0,col=0;
			forn(ii,i)
				if(a[ii][j]<a[i][j])
					col++;
			forn(jj,j)
				if(a[i][jj]<a[i][j])
					row++;
			ans[i][j]=max(row,col);
		}
	}
	forn(i,m){
		forn(j,n){
			cout<<ans[i][j]<<" ";
		}
		cout<<"\n";
	}
	return 0;
}