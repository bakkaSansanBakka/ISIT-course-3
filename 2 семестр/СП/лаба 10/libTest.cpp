#include <iostream>
//#pragma comment(lib,"E:\\3 курс\\2 семестр\\Системное программирование\\лаба 10\\lab10\\x64\\Debug\\libTest.obj")
#include "../lib/HT.h"

int main()
{
	//try {
	//	HT::HTHANDLE* HT = HT::Create(10, 3, 5, 10, L"C:\\Users\\dmitr\\Documents\\Labs\\ОСиСП\\Lab10\\lab10\\storage.ht");
	//	//HT::HTHANDLE* HT = HT::Open(L"C:\\Users\\dmitr\\Documents\\Labs\\ОСиСП\\Lab10\\lab10\\storage.ht");
	//	if (HT == NULL) throw "Invalid handle";

	//	HT::Element* el1 = new HT::Element("str", 4, "polina", 7);
	//	HT::Element* el2 = new HT::Element("key", 4, "value", 6);

	//	if (!HT::Insert(HT, el1)) throw HT::GetLastError(HT);
	//	if (!HT::Insert(HT, el2)) throw HT::GetLastError(HT);

	//	HT::Element* el;
	//	if ((el = HT::Get(HT, el1)) == NULL) throw HT::GetLastError(HT);
	//	HT::print(el);
	//	if ((el = HT::Get(HT, el2)) == NULL) throw HT::GetLastError(HT);
	//	HT::print(el);

	//	std::cout << std::endl << std::endl;

	//	if (!HT::Update(HT, el1, (void*)"payload", 8)) throw HT::GetLastError(HT);
	//	if (!HT::Delete(HT, el2)) throw HT::GetLastError(HT);

	//	if ((el = HT::Get(HT, el1)) == NULL) throw HT::GetLastError(HT);
	//	HT::print(el);
	//	/*if ((el = HT::Get(HT, el2)) == NULL) throw HT::GetLastError(HT);
	//	HT::print(el);*/

	//	if (!HT::Snap(HT)) throw HT::GetLastError(HT);

	//	HT::Close(HT);
	//}
	//catch (const char* err) {
	//	std::cout << err << std::endl;
	//}
}