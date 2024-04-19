#include<iostream>
#include<bits/stdc++.h>
using namespace std;

vector<int[10]>visitedRow(9);
vector<int[10]>visitedColumn(9);
vector<int[10]>visitedSection(9);
vector<pair<int ,int>>zeroPositions;
vector<pair<int , pair<int ,int>>>result;    // value ---> position of this value

int grid[9][9];

bool isSolved = false ;
int GetSection(int i ,int j)
{
    if(i<3 && j<3)
        return 0;
    else if(i<3 && j>2 &&j<6)
        return 1 ;
    else if(i<3 && j>5)
        return 2;
//
    if(i>2 && i<6 && j<3)
        return 3;
    else if(i>2 && i<6 && j>2 &&j<6)
        return 4 ;
    else if(i>2 && i<6 && j>5)
        return 5;
//
    if(i>5 && j<3)
        return 6;
    else if(i>5 && j>2 &&j<6)
        return 7 ;
    else if(i>5 && j>5)
        return 8;
}
void printGrid()
{

    for(pair<int ,pair<int,int>> value : result)
    {
        int num = value.first;
        int r = value.second.first;
        int c = value.second.second;
        grid[r][c]=num;
    }
    cout<<endl<<"#--------> result of this sudoku <----------#"<<endl<<endl;;
    for(int i =0 ;i<9 ;i++)
    {
        for(int j =0 ;j<9 ;j++)
        {
            cout<<grid[i][j]<<" ";
            if(j==2 || j==5)
                cout<<"| ";
        }
        cout<<endl;
        if(i==2 || i==5)
        cout<<"----------------------"<<endl;
    }
   cout<<endl<<"---------------------------------------------"<<endl;
}
void SolveSudoku(int index)
{
    if(isSolved)
        return ;
    if(index>=zeroPositions.size())
    { 
        isSolved = true ;      
        printGrid();
        return ;
    }
    for(int i = 1 ;i<=9 ;i++)
    {
        pair<int ,int>cell = zeroPositions[index];
        int r = cell.first , c = cell.second;
        int section = GetSection(r,c);
        if(visitedRow[r][i]==0 && visitedColumn[c][i]==0 && visitedSection[section][i]==0)
        {
            visitedRow[r][i] = visitedColumn[c][i] = visitedSection[section][i] = 1;
            result.push_back({i , {r,c}});
            SolveSudoku(index+1);
            result.pop_back();
            visitedRow[r][i] = visitedColumn[c][i] = visitedSection[section][i] = 0;
        }
    }
}
int main()
{
   cout<<"#----------------  welcome to sudoku solver -----------------------#"<<endl<<endl;
   cout<<"note : if the number exist enter it  ,  if not exist enter zero ( 0 )\nenter the numbers :  "<<endl<<endl;
    int num =0 ;
    for(int i=0 ;i<9 ;i++)
    {
        for(int j =0 ;j<9 ;j++)
        {
            cin>>num;
            grid[i][j]=num;
            if(num==0)
            {
                zeroPositions.push_back({i,j});
            }
            else
            {
                int section = GetSection(i ,j);
                visitedRow[i][num] = 1;
                visitedColumn[j][num]=1;
                visitedSection[section][num]=1;
            }
        }
    }
    SolveSudoku(0);
}