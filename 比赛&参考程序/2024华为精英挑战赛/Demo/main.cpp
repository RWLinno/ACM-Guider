#include <bits/stdc++.h>
#pragma GCC optimize("Ofast,no-stack-protector,fast-math",3)
#pragma GCC optimization("unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,popcnt,lzcnt")
#define mk make_pair
inline int md(int x,int y) { return x*200+y;}
inline int get_x(int x) { return (x/200);} 
inline int get_y(int x) { return (x%200);}
using namespace std;
const int n = 200;
const int robot_num = 10;
const int berth_num = 10;
const int boat_num = 5;
const int N = 201;
const int beta_value = 100;
int money, boat_capacity, ID;  // id表示帧号，money表示当前帧钱数，boat_capacity表示船的容量
char ch[N][N];                 // 地图，'.'空地  '*'海洋  '#'障碍  'A'机器人起始位置  'B'大小4*4泊位坐标 '$'货物
int arrive[N][N], value[N][N]; // 货物到达时间,货物价值
int dist[N*N];                // 空白格到最近泊位的距离
bool canReach[N*N] = {0};     // 地图上标记每个空白点能否到达港口
char occupy[N*N][15005];

const int dx[4] = {0, 0, -1, 1};
const int dy[4] = {1, -1, 0, 0};

struct action { // 动作
	string command; // 命令
	int para;       // 参数
	int x, y;       // 动作发生时的坐标
};

struct Robot {
	int xy, goods;        // goods = 1携带物品/0未携带
	int status;             // 1正常运行，0恢复停止
	int mbx = -1, mby = -1; // 目标地址
	queue<action> act_list; // 搜索行动序列
	int id;
	Robot() {}
	Robot(int startX, int startY) {
		xy = md(startX,startY);
	}
} robot[robot_num + 10];

struct good { // 货物
	int xy, val, id; // 货物坐标，价值，生成的时间
	bool operator<(const good &other) const {
		if (val * dist[other.xy] == other.val * dist[xy])
			return id < other.id;
		return val * dist[other.xy] == other.val * dist[xy];
	}
};

struct Berth { // 泊位
	int xy;
	int transport_time;
	int loading_speed;
	int boatid;       // 停靠的船id
	int num, berthid; // 存放的货物数量，自身id
	Berth() {}
	Berth(int x, int y, int transport_time, int loading_speed) {
		this->xy = md(x,y);
		this->transport_time = transport_time;
		this->loading_speed = loading_speed;
	}
} berth[berth_num + 10];

struct bfs_trace { // bfs每一步状态
	int xy, last_index, has_good, val, id, index;
	bool operator<(const bfs_trace &tmp) const { // 拓展节点排序，先按照有无货物，再按照(价值/(已花时间+估计时间))
		if (has_good != tmp.has_good)
			return has_good < tmp.has_good;
		if (has_good == 1)
			return (id+dist[xy])*(tmp.val+beta_value) > (val+beta_value)*(tmp.id+dist[tmp.xy]);
		else
			return id > tmp.id;
	}
};

struct Boat {
	int pos, status, num;
	int stayid; // 停靠在泊位id
	action act;
} boat[10];

vector<good> goods_list; // 待运输的货物列表
priority_queue<good> goods_queue;

void Init() { // 初始化输入地图，泊位位置，船的容量
	for (int i = 0; i < n; i++) {
		scanf("%s", ch[i]);
		for (int j = 0; j < n; ++j)
			if (ch[i][j] == 'A')
				ch[i][j] = '.';
	}

	for (int i = 0, id, x, y; i < berth_num; i++) {
		scanf("%d", &id);
		scanf("%d%d%d%d", &x, &y, &berth[id].transport_time, &berth[id].loading_speed);
		berth[id].xy = md(x,y);
		berth[id].berthid = id;
	}

    sort(berth, berth + berth_num, [](const Berth &a, const Berth &b) {
        return a.transport_time != b.transport_time ? a.transport_time < b.transport_time : a.loading_speed > b.loading_speed;
    }); // 泊位按照运输时长从小到大排序

	scanf("%d", &boat_capacity);
	char okk[100];
	scanf("%s", okk);
	printf("OK\n");
	fflush(stdout);
}

inline int Input() { // 每一帧输入新增商品坐标价值，机器人坐标状态，船的状态坐标，返回帧id
	scanf("%d%d", &ID, &money);
	int num;
	scanf("%d", &num);
	for (int i = 1; i <= num; i++) {
		int x, y, val;
		scanf("%d%d%d", &x, &y, &val);
		ch[x][y] = '$';
		arrive[x][y] = ID;
		value[x][y] = val;
	}

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			if (ch[i][j] == '$' && arrive[i][j] + 1000 <= ID)
				ch[i][j] = '.';

	for (int i = 0, x, y; i < robot_num; ++i) {
		scanf("%d%d%d%d", &robot[i].goods, &x, &y, &robot[i].status);
		robot[i].xy = md(x,y);
		if(ID) occupy[md(x,y)][1] = i;
	}

    for (int i = 0; i < boat_num; ++i) {
        scanf("%d%d", &boat[i].status, &boat[i].pos);
        boat[i].act.command = "";
    }
	char okk[100];
	scanf("%s", okk);
	return ID;
}
inline bool checkHit(int prexy, int xy, int preid) { // 判断碰撞
	if (occupy[xy][preid + 1] || occupy[xy][preid] == occupy[prexy][preid + 1] && occupy[xy][preid])
		return false;
	return true;
}

inline int bfs(Robot &robot, int endxy, int id) { // 搜索
	priority_queue<bfs_trace> q;
	vector<bfs_trace> v;

	bool vis[40005][2] = {0};
	q.push({robot.xy, -1, robot.goods, 0, id, 0});
	vis[robot.xy][robot.goods] = 1;
	int flag = 1;
	while (q.size() && flag) {
		bfs_trace now = q.top();
		q.pop();
		now.index = v.size();
		v.push_back(now);
		for (int i = 0, x, y, nxy; i < 4; ++i) {
			x = dx[i] + get_x(now.xy), y = dy[i] + get_y(now.xy);
			nxy=md(x,y);
			if (x < 0 || y < 0 || x >= 200 || y >= 200 || ch[x][y] == '#' || ch[x][y] == '*'||!checkHit(now.xy, nxy, now.id)) continue; 
            if (vis[nxy][now.has_good]) {
                continue;
            }
            vis[nxy][now.has_good] = 1;
            if (now.has_good && ch[x][y] == 'B') {
                flag = 0;
                v.push_back({nxy, now.index, 1, now.val, now.id + 1, 0});
                break;
            }

            if (!now.has_good && ch[x][y] == '$' && arrive[x][y] + 1000 > now.id + 1) {
                q.push({nxy, now.index, 1, value[x][y], now.id + 1, 0});
                ch[x][y] = '.';
            } else {
                q.push({nxy, now.index, now.has_good, now.val, now.id + 1, 0});
            }
		}
	}
	bfs_trace head = v[v.size() - 1];
	stack<action> st;
	st.push({"pull", 0, get_x(head.xy), get_y(head.xy) });
	while (head.last_index != -1) { // 递归回去找路径
		bfs_trace Next = v[head.last_index];
		int headx = get_x(head.xy), heady = get_y(head.xy);
		int nextx = get_x(Next.xy), nexty=get_y(Next.xy);
		if (head.has_good ^ Next.has_good)
			st.push({"get", 0, headx, heady});
		for (int i = 0; i < 4; ++i)
			if (nextx + dx[i] == headx && nexty + dy[i] == heady) {
				st.push({"move", i, nextx, nexty});
				break;
			}
		head = Next;
	}
	if (st.size() < robot.act_list.size() || robot.act_list.size() == 0) {
		while (!robot.act_list.empty())
			robot.act_list.pop();
		while (st.size()) {
			action top = st.top();
			robot.act_list.push(top);
			st.pop();
		}
	}
	return 0;
}
void update_record(Robot robot, int i, int id) {
	int x = get_x(robot.xy), y = get_y(robot.xy);
	while (robot.act_list.size()) {
		action act = robot.act_list.front();
		robot.act_list.pop();
		if (act.command == "move") {
			x += dx[act.para], y += dy[act.para];
			id++;
		}
		occupy[md(x,y)][id] = i + 1; // 0表示为没有被占用，故将robot编号+1
	}
}

inline void task() {
	for (int i = 0; i < robot_num; ++i){
		Robot& rob = robot[i];
		if (rob.status) {
			if (rob.act_list.empty()) { // 如果机器人未规划路径
				bfs(rob, berth[i].xy, ID);
				update_record(rob, i, ID);
			} else if (rob.act_list.front().x != get_x(rob.xy) || rob.act_list.front().y != get_y(rob.xy)) { // 机器人的实际位置与规划不同，则删除重开
				int id = ID;
				while (rob.act_list.size()) {
					action act = rob.act_list.front();
					rob.act_list.pop();
					occupy[md(act.x,act.y)][id] = 0;
					id++;
				}
				bfs(rob, berth[i].xy, ID);
				update_record(rob, i, ID);
			}
		}
	}
	for (int i = 0; i < boat_num; ++i) {
		if (boat[i].status == 1 && boat[i].pos == -1) { // 在虚拟点则开出到泊位
			boat[i].act = {"ship", berth[i].berthid};
			boat[i].num = 0;
		} else if (boat[i].status == 1 && (boat[i].num == boat_capacity || berth[i].transport_time*2+ID>=14900)) { // 在泊位且船上货物大于5，则开走
			boat[i].act = {"go", 0};
		} else if (boat[i].status == 0)
			boat[i].act.command = "";
		else if (boat[i].status == 1) { // 装货
			int cnt = min(min(berth[i].num, boat_capacity - boat[i].num), berth[i].loading_speed);
			boat[i].num += cnt;
			berth[i].num -= cnt;
		}
	}
}

inline void search_all_reach() { // Find all reachable blank points from the ports
    deque<pair<int, int>> q; // Using deque instead of queue
    for (int i = 0; i < 5; ++i) {
        q.emplace_back(berth[i].xy, 0); // More concise with emplace_back and make_pair
        canReach[berth[i].xy] = 1;
        dist[berth[i].xy] = 0;
    }
    while (!q.empty()) { // More idiomatic check for empty queue
        auto [xy, step] = q.front();
        q.pop_front();
        for (int i = 0,newX,newY,newxy; i < 4; ++i) {
            newX = get_x(xy) + dx[i],newY = get_y(xy) + dy[i],newxy = md(newX,newY);
            if (newX < 0 || newY < 0 || newX >= 200 || newY >= 200 || 
                ch[newX][newY] == '#' || canReach[newxy] || ch[newX][newY] == '*') {
                continue;
            }
            int newStep = ch[newX][newY] == 'B' ? 0 : step + 1;
            q.emplace_back(newxy, newStep); // More concise with emplace_back
            dist[newxy] = newStep;
            canReach[newxy] = 1;
        }
    }
}

int main() {
	Init();
	search_all_reach();
	for (int zhen = 1; zhen <= 15000; zhen++) {
		int id = Input();
		task();
		for (int i = 0; i < robot_num; i++) {
			if (robot[i].act_list.size() && robot[i].act_list.front().command != "") {
				cout << robot[i].act_list.front().command << ' ' << i; // 输出move指令
				if (robot[i].act_list.front().command == "move")
					cout << ' ' << robot[i].act_list.front().para;
				cout << "\n";
				robot[i].act_list.pop();
				if (robot[i].act_list.size())
					if (robot[i].act_list.front().command == "pull" || robot[i].act_list.front().command == "get") { // 输出pull和get指令
						cout << robot[i].act_list.front().command << ' ' << i << "\n";
						if (robot[i].act_list.front().command == "pull") {
							for (int j = 0,x,y; j < berth_num; ++j){
								x = get_x(berth[j].xy),y = get_y(berth[j].xy);
								if (robot[i].act_list.front().x >= x && robot[i].act_list.front().y >= y && robot[i].act_list.front().x < x + 4 && robot[i].act_list.front().y <y + 4) {
									berth[j].num++;
									break;
								}
							}
						}
						robot[i].act_list.pop();
					}
			}
		}
		for (int i = 0; i < boat_num; i++) {
			if (ID + berth[i].transport_time > 14990) {
				cout << "go " << i << "\n";
				continue;
			}
			if (boat[i].act.command != "") {
				cout << boat[i].act.command << ' ' << i;
				if (boat[i].act.command == "ship")
					cout << ' ' << boat[i].act.para;
				cout << "\n";
			}
		}
		puts("OK");
		fflush(stdout);
	}
	return 0;
}
