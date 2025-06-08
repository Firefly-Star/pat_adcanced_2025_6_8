#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

bool check(unsigned int n)
{
	vector<int> tmp;
	if (n == 0)
	{
		tmp = { 0 };
	}
	else
	{
		while (n != 0)
		{
			tmp.push_back(n % 2);
			n /= 2;
		}
	}
	int cnt = 1;
	int i = 1;
	while (i < tmp.size())
	{
		if (tmp[i] == tmp[i - 1])
		{
			++cnt;
		}
		else
		{
			if (cnt == 3)
			{
				return true;
			}
			cnt = 1;
		}
		++i;
	}
	return cnt == 3;
}


int main()
{
	int n;
	std::cin >> n;
	vector<unsigned int> nums(n);
	for (int i = 0; i < n; ++i)
	{
		std::cin >> nums[i];
	}
	for (auto num : nums)
	{
		if (check(num))
		{
			std::cout << "yes\n";
		}
		else
		{
			std::cout << "no\n";
		}
	}
}	