//#include<iostream>
//using namespace std;
//#include<thread>
//
//void curthread()
//{
//	std::cout << "curthread id: " << std::this_thread::get_id() << endl;
//	std::cout << "curthread  is running" << endl;
//	std::this_thread::sleep_for(std::chrono::milliseconds(100));
//	std::cout << "curthread finished" << endl;
//}
//
//void add(int a, int b)
//{
//	std::cout << "add id: " << std::this_thread::get_id() << endl;
//	cout << a + b << endl;
//
//	std::this_thread::sleep_for(std::chrono::milliseconds(100));
//}
//
//int main()
//{
//	cout << "main thread id: " << std::this_thread::get_id() << endl;
//
//	std::thread t1(curthread);
//
//	if(t1.joinable())
//		t1.join();
//	/*if (t1.joinable())
//		t1.detach();*/
//
//	//std::thread t2(std::move(t1));
//	std::thread t3(add, 3, 5);
//	if (t3.joinable())
//		t3.detach(); //如果主线程跑完了，子线程未结束时，打印不了，自动释放
//
//	//swap
//	//t1.swap(t3);
//	//swap(t1, t3);
//
//	system("pause");
//	return 0 ;
//}