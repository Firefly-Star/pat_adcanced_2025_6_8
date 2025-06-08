#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

int main()
{
	int n;
	cin >> n;
	int m;
	cin >> m;
	vector<unordered_set<int>> edges(n + 1);
	for (int i = 0; i < m; ++i)
	{
		int a, b;
		cin >> a >> b;

		edges[a].insert(b);
		edges[b].insert(a);
	}
	vector<vector<int>> dsus;
	vector<bool> visited(n + 1, false);
	for (int i = 1; i <= n; ++i)
	{
		if (!visited[i])
		{
			vector<int> component;
			queue<int> q;
			q.push(i);
			visited[i] = true;
			while (!q.empty())
			{
				int cur = q.front();
				q.pop();
				component.push_back(cur);
				for (auto next : edges[cur])
				{
					if (!visited[next])
					{
						visited[next] = true;
						q.push(next);
					}
				}
			}
			dsus.push_back(component);
		}
	}
	int cnt_linear_comp = 0;
	int max_edge = -1;
	for (auto& dsu : dsus)
	{
		if (dsu.size() == 1)
		{
			if (edges[dsu[0]].size() == 0)
			{
				++cnt_linear_comp;
				int edge_cnt = dsu.size() - 1;
				if (edge_cnt > max_edge)
				{
					max_edge = edge_cnt;
				}
			}
		}
		int cnt_1 = 0;
		bool is_linear = true;
		for (auto v : dsu)
		{
			if (edges[v].size() == 1)
			{
				++cnt_1;
			}
			else if (edges[v].size() > 2)
			{
				is_linear = false;
				break;
			}
		}
		if (cnt_1 == 2)
		{
			++cnt_linear_comp;
			int edge_cnt = dsu.size() - 1;
			if (edge_cnt > max_edge)
			{
				max_edge = edge_cnt;
			}
		}
	}
	cout << cnt_linear_comp << " " << max_edge;
}