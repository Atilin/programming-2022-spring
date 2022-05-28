#include<iostream>
#include<thread>
#include<mutex>
#include<vector>
#include<future>
#include<random>
#include<queue>
#include<condition_variable>

using namespace std;

queue<int> q;
bool work1 = true;
bool work2 = true;
vector<int> v1, v2;

mt19937 mt;
uniform_int_distribution<int> r(0, 100'000);

mutex m;
condition_variable cv;

bool f()
{
	return !q.empty();
}

void factory()
{
	int q_rand = 0;
	while (work1)
	{
		if (f() == true)
		{
			this_thread::sleep_for(100ms);
		}
		else
		{
			q_rand = r(mt);
			q.push(q_rand);
			v1.push_back(q_rand);
		}
	}
}
void consumer()
{
	while (work2)
	{
		if (f() == false)
		{
			this_thread::sleep_for(100ms);
		}
		else
		{
			v2.push_back(q.front());
			q.pop();
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
	int q_rand = 0;
	while (work1)
	{
		m.lock();
		if (f() == true)
		{
			m.unlock();
			this_thread::sleep_for(100ms);
		}
		else
		{
			q_rand = r(mt);
			q.push(q_rand);
			v1.push_back(q_rand);
			m.unlock();
		}
	}
}
void consumer_m()
{
	while (work2)
	{
		m.lock();
		if (f() == false)
		{
			m.unlock();
			this_thread::sleep_for(100ms);
		}
		else
		{
			v2.push_back(q.front());
			q.pop();
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

void factory_cv()
{
	int q_rand = 0;
	while (work1)
	{
		if (f() == true)
		{
			m.unlock();
			this_thread::sleep_for(100ms);
		}
		else
		{
			q_rand = r(mt);
			q.push(q_rand);
			v1.push_back(q_rand);
			cv.notify_one();
		}
	}
}
void consumer_cv()
{
	while (work2)
	{
		unique_lock<mutex> l(m);
		cv.wait(l, f);
		if (f()==false)
		{
			this_thread::sleep_for(100ms);
		}
		else
		{
			v2.push_back(q.front());
			q.pop();
		}
	}
}
void check_all_cv()
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
	//check_all_m();
	check_all_cv();

	return 0;
}