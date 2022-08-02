#include <iostream>
#pragma comment(lib,"E:\\3 курс\\2 семестр\\Системное программирование\\лаба 10\\lab10\\x64\\Debug\\lib.lib")
#include "../lib/HT.h"

int main()
{
	try {
		HT::HTHANDLE* HT = HT::Create(10, 3, 5, 10, L"E:\\3 курс\\2 семестр\\Системное программирование\\лаба 10\\lab10\\storage.ht");
		HT::HTHANDLE* HT2 = HT::Create(10, 3, 5, 10, L"E:\\3 курс\\2 семестр\\Системное программирование\\лаба 10\\lab10\\storageSecond.ht");

		if (HT == NULL) throw "Invalid handle";
		else std::cout << "Successful open HT\n";
		
		if (HT2 == NULL) throw "Invalid handle";
		else std::cout << "Successful open HT2\n";

		HT::Element* el1 = new HT::Element("str", 4, "polina", 7);
		HT::Element* el2 = new HT::Element("key", 4, "value", 6);

		if (!HT::Insert(HT, el1)) throw HT::GetLastError(HT);
		if (!HT::Insert(HT, el2)) throw HT::GetLastError(HT);

		std::cout << "Successful insert into HT\n";

		if (!HT::Insert(HT2, el1)) throw HT::GetLastError(HT2);
		if (!HT::Insert(HT2, el2)) throw HT::GetLastError(HT2);

		std::cout << "Successful insert into HT2\n";

		HT::Element* el;
		std::cout << "Get elements from HT\n";

		if ((el = HT::Get(HT, el1)) == NULL) throw HT::GetLastError(HT);
		HT::print(el);
		if ((el = HT::Get(HT, el2)) == NULL) throw HT::GetLastError(HT);
		HT::print(el);

		std::cout << "Get elements from HT2\n";
		if ((el = HT::Get(HT2, el1)) == NULL) throw HT::GetLastError(HT2);
		HT::print(el);
		if ((el = HT::Get(HT2, el2)) == NULL) throw HT::GetLastError(HT2);
		HT::print(el);

		std::cout << std::endl << std::endl;

		std::cout << "Update element in HT\n";
		if (!HT::Update(HT, el1, (void*)"payload", 8)) throw HT::GetLastError(HT);
		if (!HT::Delete(HT, el2)) throw HT::GetLastError(HT);

		std::cout << "Update element in HT2\n";
		if (!HT::Update(HT2, el1, (void*)"payload", 8)) throw HT::GetLastError(HT2);
		if (!HT::Delete(HT2, el2)) throw HT::GetLastError(HT2);

		if ((el = HT::Get(HT, el1)) == NULL) throw HT::GetLastError(HT);
		HT::print(el);

		if ((el = HT::Get(HT2, el1)) == NULL) throw HT::GetLastError(HT2);
		HT::print(el);
		/*if ((el = HT::Get(HT, el2)) == NULL) throw HT::GetLastError(HT);
		HT::print(el);*/

		if (!HT::Snap(HT)) throw HT::GetLastError(HT);
		if (!HT::Snap(HT2)) throw HT::GetLastError(HT2);

		HT::Close(HT);
		HT::Close(HT2);
	}
	catch (const char* err) {
		std::cout << err << std::endl;
	}
}