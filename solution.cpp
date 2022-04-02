#include<iostream>
#include<vector>
#include<cmath>
#include<cstring>
#include<fstream>

using namespace std;

vector< vector<int> > pyramid;
vector< vector< pair<int,int> > > dp; // dp is a short hand for dynamic programming
// pair, first,second --> depth, max

bool is_prime(int x)
{
    if(x == 1)
        return false;
    if(x == 2)
        return true;
    if(x % 2 == 0)
        return false;
    int lim = sqrt(x);
    for(int i = 3;i<=lim;i+=2)
    {
        if(x % i == 0)
        {
            return false;
        }
    }
    return true;
}

// dp[x] == -1, hasn't calculated yet
// dp[x] == -2, primality problem
pair<int,int> most_valuable_path(int x,int y)
{
    if(is_prime(pyramid[x][y]))
            return make_pair(x,-2);
    // if value is calculated before, return stored value
    if(dp[x][y] != make_pair(0,-1))
        return dp[x][y];
    if((int)pyramid.size()-1 == x)
    {
        return make_pair(x,pyramid[x][y]);
    }
    else
    {
        pair<int,int> left = most_valuable_path(x+1,y);
        pair<int,int> right = most_valuable_path(x+1,y+1);
        pair<int,int> best = max(left,right);
        if(best.second == -2)
        {
            return dp[x][y] = make_pair(x,pyramid[x][y]);
        }
        else
        {
            return dp[x][y] = make_pair(best.first,pyramid[x][y]+best.second);
        }

    }
    //control never reaches here
    return make_pair(-1,-1);

}

int main()
{
    ifstream in,in2;
    const string file_name = "input.txt";
    in.open(file_name);
    in2.open(file_name);

    int rows;
    string s;
    while(getline(in2,s))
        rows++;
    pyramid.resize(rows);
    for(int i = 0;i<rows;i++)
    {
        pyramid[i].resize(i+1);
        for(int j = 0;j<=i;j++)
        {
            in>>pyramid[i][j];
        }
    }
    in.close();
    dp.resize(rows);
    for(int i = 0;i < rows;i++)
    {
        dp[i].resize(i+1);
        for(int j = 0;j<=i;j++)
            dp[i][j] = make_pair(0,-1);
    }
        
    cout<< most_valuable_path(0,0).second;

    return 0;
}
