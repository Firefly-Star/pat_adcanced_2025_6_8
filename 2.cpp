#include <iostream>
#include <map>
#include <unordered_set>
#include <set>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

struct Time
{
	int day;
	int hour;
	int minute;
	int second;

	pair<bool, int> is_late()
	{
		if (hour >= 23 && (minute >= 1 || second >= 1))
		{
			return { true, day };
		}
		else if (hour <= 2 && minute <= 59 && second <= 59)
		{
			return { true, day - 1 };
		}
		else
		{
			return { false, -1 };
		}
	}
};

Time parse(string s)
{
	for (auto& c : s)
	{
		c -= '0';
	}
	Time res;
	string day = { s[0], s[1], s[2] };
	string hour = { s[4],s[5] };
	string minute = { s[7],s[8] };
	string second = { s[10],s[11] };
	res.day = 100 * s[0] + 10 * s[1] + s[2];
	res.hour = 10 * s[4] + s[5];
	res.minute = 10 * s[7] + s[8];
	res.second = 10 * s[10] + s[11];
	return res;
}

int main()
{
	// input
	int n;
	std::cin >> n;
	if (n == 0)
	{
		cout << "0\n#";
		return 0;
	}
	map<int, vector<Time>> inputs;
	for (int i = 0; i < n; ++i)
	{
		int index;
		std::cin >> index;
		Time time;
		string str_time;
		cin >> str_time;
		
		time = parse(str_time);
		bool b = false;
		for (auto t : inputs[index])
		{
			if (t.day == time.day && t.hour == time.hour && t.minute == time.minute && t.second == time.second)
				b = true;
		}
		if (!b)
		{
			inputs[index].push_back(time);
		}
		inputs[index].push_back(time);
	}
	// cnt
	unordered_set<int> late_days;
	map<int, int> final_cnts;
	for (auto& [index, times] : inputs)
	{
		for (auto time : times)
		{
			auto [b, day] = time.is_late();
			if (b)
			{
				++final_cnts[index];
				late_days.insert(day);
			}
		}
	}
	// output
	std::cout << late_days.size() << "\n";
	if (late_days.size() == 0)
	{
		std::cout << "#";
	}
	else
	{
		int max_cnt = 0;
		for (auto [index, late_cnt] : final_cnts)
		{
			max_cnt = max(max_cnt, late_cnt);
		}
		set<int> max_indices;
		for (auto [index, late_cnt] : final_cnts)
		{
			if (late_cnt == max_cnt)
			{
				max_indices.insert(index);
			}
		}
		bool is_first = true;
		for (auto index : max_indices)
		{
			if (is_first)
			{
				if (index == 0)
				{
					std::cout << "000";
				}
				else if (index > 0 && index <= 9)
				{
					std::cout << "00" << index;
				}
				else if (index <= 99)
				{
					std::cout << "0" << index;
				}
				else
				{
					std::cout << index;
				}
				is_first = false;
			}
			else
			{
				if (index == 0)
				{
					cout << " 000";
				}
				else if (index >= 0 && index <= 9)
				{
					std::cout << " 00" << index;
				}
				else if (index <= 99)
				{
					std::cout << " 0" << index;
				}
				else
				{
					std::cout << " " << index;
				}
			}
		}
	}
}