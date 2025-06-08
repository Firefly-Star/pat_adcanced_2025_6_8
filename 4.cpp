#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <functional>
#include <numeric>
#include <stack>
using namespace std;

int cal(string infix, vector<int> xs)
{
	stack<char> ops;
	stack<int> vals;
	auto process = [&](char cur)
		{
			int val2 = vals.top();
			vals.pop();
			int val1 = vals.top();
			vals.pop();
			switch (cur)
			{
			case '+': vals.push(val1 + val2); break;
			case '-': vals.push(val1 - val2); break;
			case '*': vals.push(val1 * val2); break;
			}
		};

	int cur_x = 0;
	for (int i = 0; i < infix.size(); ++i)
	{
		char cur = infix[i];
		switch (cur)
		{
		case '(':
		{
			ops.push('(');
			break;
		}
		case ')':
		{
			while (true)
			{
				char cur = ops.top();
				ops.pop();
				if (cur != '(')
				{
					process(cur);
				}
				else
				{
					break;
				}
			}
			break;
		}
		case '+':
		{
			ops.push('+');
			break;
		}
		case '-':
		{
			ops.push('-');
			break;
		}
		case '*':
		{
			ops.push('*');
			break;
		}
		case 'x':
		{
			vals.push(xs[cur_x]);
			++cur_x;
		}
		}
	}
	while (!ops.empty())
	{
		char cur = ops.top();
		ops.pop();
		process(cur);
	}
	return vals.top();
}

int main()
{
	int n;
	cin >> n;
	string infix;
	cin >> infix;
	vector<int> xs(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> xs[i];
	}
	vector<int> max_xs(n);
	int max_res = numeric_limits<int>::min();
	vector<bool> used(n, false);
	vector<int> cur_xs(n);
	function<void(int)> step = [&](int step_n)
		{
			if (step_n == n)
			{
				int res = cal(infix, cur_xs);
				if (res > max_res)
				{
					max_res = res;
					max_xs = cur_xs;
				}
				return;
			}
			for (int i = 0; i < n; ++i)
			{
				if (!used[i])
				{
					cur_xs[step_n] = xs[i];
					used[i] = true;
					step(step_n + 1);
					used[i] = false;
				}
			}
		};
	step(0);
	cout << max_res;
}