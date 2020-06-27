#include "console_text_color.h"
#include <iostream>
#include <stdio.h>
#include <queue>
#include <math.h>
using namespace std;
#define maxn 100
const int mod = 1e9;
typedef long long ll;
struct Path
{
    Path() {}
    Path(int x, int y) : x(x), y(y) {}
    int x, y;
};
struct node
{
    node(int x, int y, int step, int lx, int ly) : x(x), y(y), step(step), lx(lx), ly(ly) {}
    int step, x, y, lx, ly;
    bool operator<(const node &b) const;
};
char mapp[100][100];
Path path[100][100];
int vis[100][100];
int n, m, sx, sy, ex, ey;

int g(const node &state)
{
    return state.step;
}
//欧拉函数
double f(const node &state)
{
    return sqrt((state.x - ex) * (state.x - ex) + (state.y - ey) * (state.y - ey));
}
bool node::operator<(const node &b) const
{
    //f(n)系数
    double tmp = 10;
    double val1 = g(*this) + f(*this) * tmp;
    double val2 = g(b) + f(b) * tmp;
    return val1 > val2;
}

void A()
{
    priority_queue<node> q;
    q.push(node(sx, sy, 0, sx, sy));
    path[sx][sy] = Path(sx, sy);
    while (!q.empty())
    {
        node now = q.top();
        q.pop();
        if (vis[now.x][now.y])
            continue;
        vis[now.x][now.y] = 1;
        path[now.x][now.y] = Path(now.lx, now.ly);
        if (now.x == ex && now.y == ey)
        {
            vis[now.x][now.y] = 0;
            cout << "min step : " << now.step << endl;
            int xx = now.x;
            int yy = now.y;
            while (path[xx][yy].x != xx || path[xx][yy].y != yy)
            {
                int tx = path[xx][yy].x;
                int ty = path[xx][yy].y;
                vis[tx][ty] = 3;
                xx = tx;
                yy = ty;
            }
            return;
        }
        int dx[] = {0, 0, 1, -1};
        int dy[] = {1, -1, 0, 0};
        for (int i = 0; i < 4; i++)
        {
            int x = dx[i] + now.x;
            int y = dy[i] + now.y;
            int step = now.step + 1;
            if (x < n && x >= 0 && y < m && y >= 0 && mapp[x][y] != 'x')
            {
                if (vis[x][y])
                    continue;
                q.push(node(x, y, step, now.x, now.y));
            }
        }
    }
}
void PrintOut()
{
    for (int i = 0; i < n; i++, putchar('\n'))
        for (int j = 0; j < m; j++)
        {
            if (i == sx && j == sy)
            {
                ConsoleTextColor::WHITE();
                cout << "S";
            }
            else if (i == ex && j == ey)
            {
                ConsoleTextColor::WHITE();
                cout << "E";
            }
            else if (vis[i][j] == 1)
            {
                ConsoleTextColor::BLUE();
                cout << '*';
            }
            else if (vis[i][j] == 3)
            {
                ConsoleTextColor::RED();
                cout << "-";
            }
            else
            {
                ConsoleTextColor::WHITE();
                cout << mapp[i][j];
            }
        }
}
int Build()
{
    FILE *file;
    file = fopen("map_data", "r");
    if (!file)
    {
        cout << "open file fail" << endl;
        return 1;
    }
    fscanf(file, "%d%d", &n, &m);
    for (int i = 0; i < n; i++)
        fscanf(file, "%s", mapp[i]);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (mapp[i][j] == 'S')
            {
                sx = i;
                sy = j;
            }
            else if (mapp[i][j] == 'E')
            {
                ex = i;
                ey = j;
            }
    return 0;
}
int main()
{
    if (Build())
        return 0;
    A();
    PrintOut();
    return 0;
}