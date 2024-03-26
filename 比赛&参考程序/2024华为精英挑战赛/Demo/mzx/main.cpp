#include <bits/stdc++.h>
using namespace std;

const int n = 200;
const int robot_num = 10;
const int berth_num = 10;
const int boat_num = 5;
const int N = 210;
int money, boat_capacity, ID;  // id表示帧号，money表示当前帧钱数，boat_capacity表示船的容量
char ch[N][N];                 // 地图，'.'空地  '*'海洋  '#'障碍  'A'机器人起始位置  'B'大小4*4泊位坐标 '$'货物
int arrive[N][N], value[N][N]; // 货物到达时间,货物价值
int dist[N][N];                // 空白格到最近泊位的距离
bool canReach[N][N] = {0};     // 地图上标记每个空白点能否到达港口
char occupy[N][N][15005];

const int dx[4] = {0, 0, -1, 1};
const int dy[4] = {1, -1, 0, 0};
// set<pair<int, int>> record[N][N];

struct action // 动作
{
    string command; // 命令
    int para;       // 参数
    int x, y;       // 动作发生时的坐标
};

struct Robot
{
    int x, y, goods;        // goods = 1携带物品/0未携带
    int status;             // 1正常运行，0恢复停止
    int mbx = -1, mby = -1; // 目标地址
    queue<action> act_list; // 搜索行动序列
    int id;
    Robot() {}
    Robot(int startX, int startY)
    {
        x = startX;
        y = startY;
    }
} robot[robot_num + 10];

struct good // 货物
{
    int x, y, val, id; // 货物坐标，价值，生成的时间
    bool operator<(const good &other) const
    {
        if (val * dist[other.x][other.y] == other.val * dist[x][y])
            return id < other.id;
        return val * dist[other.x][other.y] == other.val * dist[x][y];
    }
};

struct Berth // 泊位
{
    int x;
    int y;
    int transport_time;
    int loading_speed;
    int boatid;       // 停靠的船id
    int num, berthid; // 存放的货物数量，自身id
    Berth() {}
    Berth(int x, int y, int transport_time, int loading_speed)
    {
        this->x = x;
        this->y = y;
        this->transport_time = transport_time;
        this->loading_speed = loading_speed;
    }
} berth[berth_num + 10];

struct bfs_trace // bfs每一步状态
{
    int x, y, last_index, has_good, val, id, index;
    bool operator<(const bfs_trace &tmp) const // 拓展节点排序，先按照有无货物，再按照(价值/(已花时间+估计时间))
    {
        if (has_good != tmp.has_good)
            return has_good < tmp.has_good;
        if (has_good == 1)
            // return val * (tmp.id - ID + dist[tmp.x][tmp.y]) < tmp.val * (id - ID + dist[x][y]);
            return dist[x][y] > dist[tmp.x][tmp.y];
        else
            return id > tmp.id;
    }
};

struct Boat
{
    int pos, status, num;
    int stayid; // 停靠在泊位id
    action act;
} boat[10];

vector<good> goods_list; // 待运输的货物列表
priority_queue<good> goods_queue;

void Init() // 初始化输入地图，泊位位置，船的容量
{
    for (int i = 0; i < n; i++)
    {
        scanf("%s", ch[i]);
        for (int j = 0; j < n; ++j)
            if (ch[i][j] == 'A')
                ch[i][j] = '.';

        // cerr<<ch[i]<<"\n";
    }

    for (int i = 0; i < berth_num; i++)
    {
        int id;
        scanf("%d", &id);
        scanf("%d%d%d%d", &berth[id].x, &berth[id].y, &berth[id].transport_time, &berth[id].loading_speed);
        berth[id].berthid = id;
        // cerr << id <<' '<< berth[id].x <<' '<<berth[id].y<<' '<<berth[i].transport_time<<' '<<berth[i].loading_speed<<"\n";
    }
    
    sort(berth, berth + berth_num, [](Berth &a, Berth &b)
         {
        if (a.transport_time != b.transport_time) return a.transport_time < b.transport_time;
        return a.loading_speed > b.loading_speed; }); // 泊位按照运输时长从小到大排序
        
    scanf("%d", &boat_capacity);
    // cerr << boat_capacity <<"\n";
    char okk[100];
    scanf("%s", okk);
    // cerr<<okk<<"\n";
    printf("OK\n");
    fflush(stdout);
}

int Input() // 每一帧输入新增商品坐标价值，机器人坐标状态，船的状态坐标，返回帧id
{
    scanf("%d%d", &ID, &money);
    // cerr<<ID<<' '<<money<<"\n";
    int num;
    scanf("%d", &num);
    // cerr<<num<<"\n";
    for (int i = 1; i <= num; i++)
    {
        int x, y, val;
        scanf("%d%d%d", &x, &y, &val);
        // cerr<<x<<' '<<y<<' '<<val<<"\n";
        good new_good = {x, y, val, ID};
        // if (canReach[x][y]) // 判断该点能否到达港口
        {
            // goods_list.push_back(new_good);
            // goods_queue.push(new_good);
            // cerr << "New goods: x=" << x << " y=" << y << " val=" << val << "\n";
            ch[x][y] = '$';
            arrive[x][y] = ID;
            value[x][y] = val;
        }
    }

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (ch[i][j] == '$' && arrive[i][j] + 1000 <= ID)
                ch[i][j] = '.';

    for (int i = 0; i < robot_num; i++)
    {
        scanf("%d%d%d%d", &robot[i].goods, &robot[i].x, &robot[i].y, &robot[i].status);
        if (ID == 1)
            occupy[robot[i].x][robot[i].y][1] = i;
        // cerr<<robot[i].goods<<' '<<robot[i].x<<' '<<robot[i].y<<' '<<robot[i].status<<"\n";
    }
    // cerr<<"Read:\n";
    for (int i = 0; i < boat_num; i++)
    {
        scanf("%d%d\n", &boat[i].status, &boat[i].pos);
        // cerr<<boat[i].status<<' '<<boat[i].pos<<"\n";
        boat[i].act.command = "";
        // cerr<<"Boat "<<i<<" statu="<<boat[i].status<<" pos="<<boat[i].pos<<"\n";
    }
    char okk[100];
    scanf("%s", okk);
    return ID;
}
bool checkHit(int prex, int prey, int x, int y, int preid) // 判断碰撞
{
    if (occupy[x][y][preid + 1] || occupy[x][y][preid] == occupy[prex][prey][preid + 1] && occupy[x][y][preid])
        return false;
    /*
    if (record[x][y].find({i, preid + 1}) != record[x][y].end())
            return false;
    else if (record[x][y].find({i, preid}) != record[x][y].end() && record[prex][prey].find({i, preid + 1}) != record[prex][prex].end())
            return false;*/
    return true;
}

int bfs(Robot &robot, int endx, int endy, int id) // 搜索
{
    priority_queue<bfs_trace> q;
    vector<bfs_trace> v;

    bool vis[205][205][2] = {0};
    q.push({robot.x, robot.y, -1, robot.goods, 0, id, 0});
    vis[robot.x][robot.y][robot.goods] = 1;
    int flag = 1, times = 0;
    while (q.size() && flag)
    {
        times++;
        bfs_trace now = q.top();
        q.pop();
        now.index = v.size();
        v.push_back(now);
        // if (now.has_good) cerr << now.x<<' '<<now.y<<' '<<now.has_good<<' '<<now.id<<' '<<now.val<<"\n";
        for (int i = 0; i < 4; ++i)
        {
            int x = dx[i] + now.x;
            int y = dy[i] + now.y;
            if (x < 0 || y < 0 || x >= 200 || y >= 200 || ch[x][y] == '#' || ch[x][y] == '*')
                continue;
            if (!checkHit(now.x, now.y, x, y, now.id)) // 判断是否碰撞
                continue;
            if (now.has_good) // 判断当前状态是否有货物
            {
                if (vis[x][y][1])
                    continue;
                vis[x][y][1] = 1;
                if (ch[x][y] == 'B') // && x >= endx && y >= endy && x < endx + 4 && y < endy + 4)  // 判断是否在指定泊位
                {
                    flag = 0;
                    v.push_back({x, y, now.index, 1, now.val, now.id + 1, 0});
                    break;
                }
                q.push({x, y, now.index, 1, now.val, now.id + 1, 0});
            }
            else
            {
                if (ch[x][y] == '$' && arrive[x][y] + 1000 > now.id + 1) // 判断是否在货物位置，货物还没消失
                {
                    q.push({x, y, now.index, 1, value[x][y], now.id + 1, 0});
                    vis[x][y][1] = 1;
                    ch[x][y] = '.';
                }
                else
                {
                    if (vis[x][y][0])
                        continue;
                    vis[x][y][0] = 1;
                    q.push({x, y, now.index, 0, 0, now.id + 1, 0});
                }
            }
        }
    }
    // cerr << times<<"\n";
    bfs_trace head = v[v.size() - 1];
    stack<action> st;
    st.push({"pull", 0, head.x, head.y});
    while (head.last_index != -1) // 递归回去找路径
    {
        bfs_trace Next = v[head.last_index];
        if (head.has_good ^ Next.has_good)
            st.push({"get", 0, head.x, head.y});
        for (int i = 0; i < 4; ++i)
            if (Next.x + dx[i] == head.x && Next.y + dy[i] == head.y)
            {
                st.push({"move", i, Next.x, Next.y});
                break;
            }
        head = Next;
    }
    if (st.size() < robot.act_list.size() || robot.act_list.size() == 0)
    {
        while (!robot.act_list.empty())
            robot.act_list.pop();
        while (st.size())
        {
            action top = st.top();
            robot.act_list.push(top);
            st.pop();
        }
    }
    return 0;
}
void update_record(Robot robot, int i, int id)
{
    int x = robot.x, y = robot.y;
    while (robot.act_list.size())
    {
        action act = robot.act_list.front();
        // cerr <<"Robot " << i <<' '<< act.command << ' ' << act.para << ' ' << act.x << ' ' << act.y<<"\n";
        robot.act_list.pop();
        if (act.command == "move")
        {
            x += dx[act.para], y += dy[act.para];
            id++;
        }
        occupy[x][y][id] = i + 1; // 0表示为没有被占用，故将robot编号+1
    }
}

void task()
{
    for (int i = 0; i < robot_num; ++i)
        if (robot[i].status)
        {
            if (robot[i].act_list.empty()) // 如果机器人未规划路径
            {
                // for (int j = 0; j < 5; ++j)
                bfs(robot[i], berth[i].x, berth[i].y, ID);
                update_record(robot[i], i, ID);
            }
            else if (robot[i].act_list.front().x != robot[i].x || robot[i].act_list.front().y != robot[i].y) // 机器人的实际位置与规划不同，则删除重开
            {
                int id = ID;
                while (robot[i].act_list.size())
                {
                    action act = robot[i].act_list.front();
                    robot[i].act_list.pop();
                    occupy[act.x][act.y][id] = 0;
                    id++;
                }
                bfs(robot[i], berth[i].x, berth[i].y, ID);
                update_record(robot[i], i, ID);
            }
        } /*
         else
         {
             while (robot[i].act_list.size())
                 robot[i].act_list.pop();
         }*/
    for (int i = 0; i < boat_num; ++i)
    {
        if (boat[i].status == 1 && boat[i].pos == -1) // 在虚拟点则开出到泊位
        {
            boat[i].act = {"ship", berth[i].berthid};
            boat[i].num = 0;
            // cerr<<id<<" Boat "<<i<<" ship\n";
        }
        else if (boat[i].status == 1 && (boat[i].num == boat_capacity || berth[i].transport_time*2+ID>=14900)) // 在泊位且船上货物大于5，则开走
        {
            boat[i].act = {"go", 0};
            // cerr<<id<<" Boat "<<i<<" go\n";
        }
        else if (boat[i].status == 0)
            boat[i].act.command = "";
        else if (boat[i].status == 1) // 装货
        {
            int cnt = min(min(berth[i].num, boat_capacity - boat[i].num), berth[i].loading_speed);
            boat[i].num += cnt;
            berth[i].num -= cnt;
            // cerr<<id<<" Boat "<<i<<" add="<<cnt<<" num="<<boat[i].num<<" statu="<<boat[i].status<<"\n";
        }
    }
}

void search_all_reach() // 找到所有能到达港口的空白点
{
    queue<pair<pair<int, int>, int>> q;
    for (int i = 0; i < 5; ++i)
    {
        q.push({{berth[i].x, berth[i].y}, 0});
        canReach[berth[i].x][berth[i].y] = 1;
        dist[berth[i].x][berth[i].y] = 0;
    }
    while (q.size())
    {
        auto now = q.front();
        q.pop();
        for (int i = 0; i < 4; ++i)
        {
            int x = now.first.first + dx[i];
            int y = now.first.second + dy[i];
            // cerr<<x<<' '<<y<<' '<<ch[x][y]<<"\n";
            if (x < 0 || y < 0 || x >= 200 || y >= 200 || ch[x][y] == '#' || canReach[x][y] || ch[x][y] == '*')
                continue;
            int step = now.second + 1;
            if (ch[x][y] == 'B')
                step = 0;
            q.push({{x, y}, step});
            dist[x][y] = step;
            canReach[x][y] = 1;
        }
    }
}

int main()
{
    // freopen("map.in","r",stdin);
    Init();
    search_all_reach();
    /*
    for (int i=1;i<=n;++i,cerr<<"\n")
    for (int j=1;j<=n;++j)
    cerr<<dist[i][j]<<' ';
    //if (canReach[i][j]) cerr<<1;
    //else cerr<<0;
    return 0;*/
    for (int zhen = 1; zhen <= 15000; zhen++)
    {
        int id = Input();
        //if (zhen <= 50) { puts("OK"); fflush(stdout); continue; }
        task();
        for (int i = 0; i < robot_num; i++)
        {
            if (robot[i].act_list.size() && robot[i].act_list.front().command != "")
            {
                cout << robot[i].act_list.front().command << ' ' << i; // 输出move指令
                if (robot[i].act_list.front().command == "move")
                    cout << ' ' << robot[i].act_list.front().para;
                cout << "\n";
                // cerr << robot[i].act_list.front().command << ' ' << i<< ' ' << robot[i].act_list.front().para;
                robot[i].act_list.pop();
                if (robot[i].act_list.size())
                    if (robot[i].act_list.front().command == "pull" || robot[i].act_list.front().command == "get") // 输出pull和get指令
                    {
                        cout << robot[i].act_list.front().command << ' ' << i << "\n";
                        // cerr << robot[i].act_list.front().command << ' ' << i << ' ' << robot[i].x << ' ' << robot[i].y << ch[robot[i].x][robot[i].y] << "\n";
                        if (robot[i].act_list.front().command == "pull")
                        {
                            for (int j = 0; j < berth_num; ++j)
                                if (robot[i].act_list.front().x >= berth[j].x && robot[i].act_list.front().y >= berth[j].y && robot[i].act_list.front().x < berth[j].x + 4 && robot[i].act_list.front().y < berth[j].y + 4)
                                {
                                    berth[j].num++;
                                    break;
                                }
                        }
                        // cerr << "Robot " << i << ' '<< robot[i].x<<' '<<robot[i].y<<"\n";
                        // cerr << robot[i].act_list.front().command << ' ' << i<< ' ' << robot[i].act_list.front().para<<"\n";
                        robot[i].act_list.pop();
                    }
            }
        }
        for (int i = 0; i < boat_num; i++)
        {
            if (ID + berth[i].transport_time > 14990)
            {
                cout << "go " << i << "\n";
                continue;
            }
            if (boat[i].act.command != "")
            {
                cout << boat[i].act.command << ' ' << i;
                if (boat[i].act.command == "ship")
                    cout << ' ' << boat[i].act.para;
                // else cerr << ID <<"Boat "<<i<<" go\n";
                cout << "\n";
            }
        }
        puts("OK");
        fflush(stdout);
    }
    return 0;
}
