#include<iostream>
#include<thread>
#include<mutex>
#include<vector>
#include<future>
#include<random>

using namespace std;

int object;
bool flag = false;
bool work1 = true;
bool work2 = true;
vector<int> v1, v2;

mt19937 mt;
uniform_int_distribution<int> r(0, 100'000);

mutex m;

void factory()
{
	while (work1==true)
	{
		if (flag==true)
		{
			this_thread::sleep_for(100ms);
		}
		else
		{
			object = r(mt);
			v1.push_back(object);
			flag = true;
		}
	}
}
void consumer()
{
	while (work2==true)
	{
		if (flag==false)
		{
			this_thread::sleep_for(100ms);
		}
		else
		{
			v2.push_back(object);
			flag = false;
		}
	}
}
void check_all()
{
	thread f1(factory);
	thread f2(factory);

	thread c1(consumer);
	thread c2(consumer);
	thread c3(consumer);

	this_thread::sleep_for(1s);

	work1 = false;
	f1.join();
	f2.join();
	work2 = false;
	c1.join();
	c2.join();
	c3.join();

	for (int i = 0; i < v1.size(); ++i)
	{
		cout << v1[i] << ' ';
	}
	cout << endl;
	for (int i = 0; i < v2.size(); ++i)
	{
		cout << v2[i] << ' ';
	}
	cout << endl;
}

void factory_m()
{
	while (work1)
	{
		m.lock();
		if (flag)
		{
			m.unlock();
			this_thread::sleep_for(100ms);
		}
		else
		{
			object = r(mt);
			v1.push_back(object);
			flag = true;
			m.unlock();
		}
	}
}
void consumer_m()
{
	while (work2)
	{
		m.lock();
		if (!flag)
		{
			m.unlock();
			this_thread::sleep_for(100ms);
		}
		else
		{
			v2.push_back(object);
			flag = false;
			m.unlock();
		}
	}
}
void check_all_m()
{
	thread f1(factory_m);
	thread f2(factory_m);

	thread c1(consumer_m);
	thread c2(consumer_m);
	thread c3(consumer_m);

	this_thread::sleep_for(1s);

	work1 = false;
	f1.join();
	f2.join();
	work2 = false;
	c1.join();
	c2.join();
	c3.join();

	for (int i = 0; i < v1.size(); ++i)
	{
		cout << v1[i] << ' ';
	}
	cout << endl;
	for (int i = 0; i < v2.size(); ++i)
	{
		cout << v2[i] << ' ';
	}
	cout << endl;
}

int main()
{
	//check_all();
	check_all_m();

	return 0;
}