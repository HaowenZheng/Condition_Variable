#include<iostream>
using namespace std;
#include <thread>
#include <condition_variable>
#include <mutex>
#include <list>

condition_variable g_cond;
std::mutex g_mtx;
bool bReady = false;

void func1()
{
	cout << "func1 thread id: " << std::this_thread::get_id() << endl;
	
	int i = 0;
	while (1)
	{
		std::lock_guard<std::mutex> lck(g_mtx);
		//cout << "func1 获得锁" << i << endl;
		bReady = true;
		
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
		g_cond.notify_one();
		cout << "func1 发送信号" << i << endl;
		i++;
	}

}

void func2()
{
	cout << "func2 thread id: " << std::this_thread::get_id() << endl;
	int i = 0;
	while (1)
	{
		std::unique_lock<std::mutex> lck(g_mtx);

		g_cond.wait(lck, []() {return bReady; });

		cout << "等到信号： " << i << endl;
		i++;
		std::this_thread::sleep_for(std::chrono::seconds(2));
		cout << "完成一次信号处理" << endl;
	}
}

class ListData
{
public:
	void InsertData()
	{
		for (int i = 0; i < m_maxcount; i++)
		{
			std::lock_guard<std::mutex> lck(m_mtx);
			m_list.push_back(i);
			cout << "插入数据 " << i << endl;
			m_cond.notify_one();

		}
	}

	void PopData()
	{
		for (int i = 0; i < m_maxcount; i++)
		{
			std::unique_lock<std::mutex> lck(m_mtx);

			m_cond.wait(lck, [this]() {return !m_list.empty(); });

			int num = m_list.front();
			cout << "获取数据: " << num << endl;
			m_list.pop_front();

			std::this_thread::sleep_for(200ms);
		}
	}

	ListData(int num) :m_maxcount(num)
	{

	}

private:
	std::condition_variable m_cond;
	std::list<int> m_list;
	std::mutex m_mtx;
	int m_maxcount;
};

int main()
{
	/*std::thread t1(func1);
	std::thread t2(func2);

	t1.join();
	t2.join();*/

	ListData td(1000);

	std::thread t1(&ListData::InsertData, &td);
	std::thread t2(&ListData::PopData, &td);

	t1.join();
	t2.join();

	system("pause");
	return 0;

}