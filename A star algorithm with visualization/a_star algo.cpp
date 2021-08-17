#include <bits/stdc++.h>
using namespace std;
#define F first
#define S second
const int row = 10;
const int col = 10;

class Node
{
public:
    int parent_x;
    int parent_y;
    int f;
    int g;
    int h;

    Node()
    {
        parent_x = -1;
        parent_y = -1;
        f = INT_MAX;
        g = INT_MAX;
        h = INT_MAX;
    }
};

bool is_destination(int x, int y, pair<int, int> dest)
{
    return (dest.F == x && dest.S == y);
}

int getH(int x, int y, pair<int, int> dest)
{
    return abs(x - dest.F) + abs(y - dest.S);
}

bool isvalid(int x, int y)
{
    return (x >= 0 && x < row && y >= 0 && y < col);
}

void printGrid(int grid[][col])
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

void tracePath(int grid[][col], Node nodes[][col], pair<int, int> src, pair<int, int> dest)
{
    pair<int, int> curNode = dest;

    while (curNode != src)
    {
        grid[curNode.F][curNode.S] = 2;
        pair<int, int> parent = make_pair(nodes[curNode.F][curNode.S].parent_x, nodes[curNode.F][curNode.S].parent_y);
        curNode = parent;
    }
    grid[src.F][src.S] = 2;

    printGrid(grid);
}

void aStarSearch(int grid[][col], pair<int, int> src, pair<int, int> dest)
{
    Node nodes[row][col];
    int closedList[row][col];   //visited array
    memset(closedList, 0, sizeof(closedList));
    set<pair<int, pair<int, int>>> openList; // (f_score,(x,y))

    if (!isvalid(src.F, src.S))
    {
        cout << "src not valid" << endl;
        return;
    }
    if (!isvalid(dest.F, dest.S))
    {
        cout << "dest not valid" << endl;
        return;
    }
    if (grid[src.F][src.S] == 1)
    {
        cout << "src is blocked" << endl;
        return;
    }
    if (grid[dest.F][dest.S] == 1)
    {
        cout << "dest is blocked" << endl;
        return;
    }
    if (is_destination(src.F, src.S, dest))
    {
        cout << "src is destination" << endl;
        return;
    }

    nodes[src.F][src.S].f = 0;
    nodes[src.F][src.S].g = 0;
    nodes[src.F][src.S].h = 0;

    openList.insert({0, {src.F, src.S}});

    while (!openList.empty())
    {
        pair<int, pair<int, int>> cur = *openList.begin();
        openList.erase(openList.begin());
        int cur_f = cur.F;
        int cur_x = cur.S.F;
        int cur_y = cur.S.S;
        closedList[cur_x][cur_y] = 1; //visited 

        int dx[4] = {1, -1, 0, 0};
        int dy[4] = {0, 0, 1, -1};

        for (int k = 0; k < 4; k++)
        {
            int new_x = cur_x + dx[k];
            int new_y = cur_y + dy[k];
            //is it valid node?
            if (!isvalid(new_x, new_y))
                continue;

            //is it destination?
            if (is_destination(new_x, new_y, dest))
            {
                nodes[new_x][new_y].parent_x = cur_x;
                nodes[new_x][new_y].parent_y = cur_y;
                tracePath(grid, nodes, src, dest);
                cout << "Reached destination" << endl;
                return;
            }

            //is it closed/visited or blocked?
            if (closedList[new_x][new_y] == 0 && grid[new_x][new_y] == 0)
            {
                int new_g = nodes[cur_x][cur_y].g + 1;
                int new_h = getH(new_x, new_y, dest);
                int new_f = new_g + new_h;

                if (nodes[new_x][new_y].f > new_f)
                {
                    openList.insert({new_f, {new_x, new_y}});
                    nodes[new_x][new_y].f = new_f;
                    nodes[new_x][new_y].g = new_g;
                    nodes[new_x][new_y].h = new_h;
                    nodes[new_x][new_y].parent_x = cur_x;
                    nodes[new_x][new_y].parent_y = cur_y;
                }
            }
        }
    }
}

int main()
{
    int grid[row][col] = {
                        {1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
                        {1, 1, 1, 0, 1, 1, 1, 0, 1, 1},
                        {1, 1, 1, 0, 1, 1, 0, 1, 0, 1},
                        {0, 0, 1, 0, 1, 0, 0, 0, 0, 1},
                        {1, 1, 1, 0, 1, 1, 1, 0, 1, 0},
                        {1, 0, 1, 1, 1, 1, 0, 1, 0, 0},
                        {1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
                        {1, 0, 1, 1, 1, 1, 0, 1, 1, 1},
                        {1, 1, 1, 0, 0, 0, 1, 0, 0, 1}
                        };

    pair<int, int> src = make_pair(8, 3);
    pair<int, int> dest = make_pair(9, 9);

    aStarSearch(grid, src, dest);

    return 0;
}