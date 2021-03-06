//  Copyright © 2017 Dougy Ouyang. All rights reserved.

#include <iostream>
#include <queue>
#include <set>

using namespace std;
int target[2][4];
bool visited[8][8][8][8][8][8][8];

struct config{
    int body[2][4], step;
    char ans[50];
};

bool checkv(config a)
{
    return !visited[a.body[0][0]-1][a.body[0][1]-1][a.body[0][2]-1][a.body[0][3]-1][a.body[1][0]-1][a.body[1][1]-1][a.body[1][2]-1];
}

void markv(config a)
{
    visited[a.body[0][0]-1][a.body[0][1]-1][a.body[0][2]-1][a.body[0][3]-1][a.body[1][0]-1][a.body[1][1]-1][a.body[1][2]-1]=true;
}

config coma(config a)
{
    int i, tem;
    for(i=0;i<4;i++)
        tem=a.body[0][i], a.body[0][i]=a.body[1][i], a.body[1][i]=tem;
    a.ans[a.step++]='A';
    return a;
}

config comb(config a)
{
    int i, tem[2];
    tem[0]=a.body[0][3], tem[1]=a.body[1][3];
    for(i=3;i>=1;i--)
        a.body[0][i]=a.body[0][i-1], a.body[1][i]=a.body[1][i-1];
    a.body[0][0]=tem[0], a.body[1][0]=tem[1];
    a.ans[a.step++]='B';
    return a;
}

config comc(config a)
{
    int tem=a.body[0][1];
    a.body[0][1]=a.body[1][1], a.body[1][1]=a.body[1][2], a.body[1][2]=a.body[0][2], a.body[0][2]=tem;
    a.ans[a.step++]='C';
    return a;
}

bool check(config a)
{
    int i, j;
    for(i=0;i<2;i++)
        for(j=0;j<4;j++)
            if(a.body[i][j]!=target[i][j])
                return false;
    return true;
}

int main()
{
    queue<config> m;
    config in, out;
    int i, j;
    
    for(j=0;j<4;j++)
        cin >> target[0][j];
    for(j=3;j>=0;j--)
        cin >> target[1][j];
    in.body[0][0]=1, in.body[0][1]=2, in.body[0][2]=3, in.body[0][3]=4, in.body[1][3]=5, in.body[1][2]=6, in.body[1][1]=7, in.body[1][0]=8;
    in.step=0, m.push(in), markv(in);
    
    while(!m.empty()){
        out=m.front(), m.pop();
        if(check(out))
            break;
        if(checkv(coma(out)))
            m.push(coma(out)), markv(coma(out));
        if(checkv(comb(out)))
            m.push(comb(out)), markv(comb(out));
        if(checkv(comc(out)))
            m.push(comc(out)), markv(comc(out));
    }
    
    cout << out.step << endl;
    for(i=0;i<out.step;i++)
        cout << out.ans[i];
    if(out.step!=0)
        cout << endl;
    
    return 0;
}
