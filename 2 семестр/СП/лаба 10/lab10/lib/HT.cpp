#include "HT.h";
using namespace std;
namespace HT {
	int HashFunction(const Element* element, int size, int p);
	int Next_hash(int hash, int size, int p);
	DWORD WINAPI SnapShotCycle(HTHANDLE* ht);
	wchar_t* GetWC(char* c);
	wchar_t* GenerateMutexName(const wchar_t* pathToHT);
	BOOL CheckParmLength(HTHANDLE* ht, Element* element);
	BOOL CheckParmLength(HTHANDLE* ht, int payloadLength);

	const int DELETED = -1;
	Element* GetElementFromHT(HTHANDLE* ht, int n);
	BOOL SetElementToHT(HTHANDLE* ht, Element* element, int n);
	BOOL IsDeleted(Element* ptr);
	void SetDeletedFlag(Element* ptr);
	BOOL EqualElementKeys(Element* el1, Element* el2);
	void SetErrorMessage(HTHANDLE* ht, const char* message, int messageLen);
	void UpdateElement(HTHANDLE* ht, Element* el, void* newpayload, int newpayloadlength);

	Element::Element() {
		this->key = nullptr;
		this->keylength = NULL;
		this->payload = nullptr;
		this->payloadlength = NULL;
	}
	Element::Element(const void* key, int keylength) {
		Element();
		this->key = (void*)key;
		this->keylength = keylength;
	}
	Element::Element(const void* key, int keylength, const void* payload, int  payloadlength) {
		this->key = (void*)key;
		this->keylength = keylength;
		this->payload = (void*)payload;
		this->payloadlength = payloadlength;
	}
	Element::Element(Element* oldelement, const void* newpayload, int  newpayloadlength) {
		this->key = oldelement->key;
		this->keylength = oldelement->keylength;
		this->payload = (void*)payload;
		this->payloadlength = payloadlength;
	}

	HTHANDLE::HTHANDLE() {
	}
	HTHANDLE::HTHANDLE(
		int Capacity,
		int SecSnapshotInterval,
		int MaxKeyLength,
		int MaxPayloadLength,
		const wchar_t FileName[512]
	) {
		this->Capacity = Capacity;
		this->SecSnapshotInterval = SecSnapshotInterval;
		this->MaxKeyLength = MaxKeyLength;
		this->MaxPayloadLength = MaxPayloadLength;
		this->N = 0;
		memcpy(this->FileName, FileName, sizeof(this->FileName));
	}

	HTHANDLE* Create(
		int	  Capacity,					   
		int   SecSnapshotInterval,		   
		int   MaxKeyLength,       
		int   MaxPayloadLength,      
		const wchar_t  FileName[512]
	) {
		HANDLE hf = CreateFile(
			FileName,//path
			GENERIC_WRITE | GENERIC_READ,
			NULL,
			NULL,
			CREATE_NEW, 
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);
		if (hf == INVALID_HANDLE_VALUE) return NULL;
		DWORD HTsize = sizeof(HTHANDLE) + Capacity * (MaxKeyLength + MaxPayloadLength + 2 * sizeof(int));
		HANDLE hm = CreateFileMapping(
			hf,
			NULL,
			PAGE_READWRITE,
			0, HTsize, NULL);
		if (!hm)return NULL;

		LPVOID lp = MapViewOfFile(
			hm,
			FILE_MAP_ALL_ACCESS,
			0, 0, 0);
		if (!lp)return NULL;

		ZeroMemory(lp, HTsize);
		HTHANDLE* ht = new(lp) HTHANDLE(
			Capacity,
			SecSnapshotInterval,
			MaxKeyLength,
			MaxPayloadLength,
			FileName);

		ht->File = hf;
		ht->FileMapping = hm;
		ht->Addr = lp;
		ht->lastsnaptime = time(NULL);
		ht->Mutex = CreateMutex(
			NULL,
			FALSE,
			GenerateMutexName(FileName));//MAX_PATH LIMIT

		DWORD SnapShotThread = NULL;
		if (!(ht->SnapshotThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)SnapShotCycle, ht, 0, &SnapShotThread))) return NULL;
		return ht;
	}

	HTHANDLE* Open(const wchar_t FileName[512]) {
		HANDLE hf = CreateFile(
			FileName,//path
			GENERIC_WRITE | GENERIC_READ,
			NULL,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);
		if (hf == INVALID_HANDLE_VALUE)return NULL;
		HANDLE hm = CreateFileMapping(
			hf,
			NULL,
			PAGE_READWRITE,
			0, 0, NULL);
		if (!hm)return NULL;

		LPVOID lp = MapViewOfFile(
			hm,
			FILE_MAP_ALL_ACCESS,
			0, 0, 0);
		if (!lp)return NULL;

		HTHANDLE* ht = (HTHANDLE*)lp;
		ht->File = hf;
		ht->FileMapping = hm;
		ht->Addr = lp;
		ht->Mutex = CreateMutex(
			NULL,
			FALSE,
			GenerateMutexName(FileName));

		DWORD SnapShotThread = NULL;
		if (!(ht->SnapshotThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)SnapShotCycle, ht, 0, &SnapShotThread))) return NULL;
		return ht;
	}

	BOOL HT::Snap
	(
		HTHANDLE* hthandle
	) {
		bool result = true;
		WaitForSingleObject(hthandle->Mutex, INFINITE);
		int totalHtSize = sizeof(HTHANDLE);
		totalHtSize += hthandle->Capacity * (sizeof(Element) + hthandle->MaxKeyLength + hthandle->MaxPayloadLength);
		if (FlushViewOfFile(hthandle, totalHtSize)) {
			time(&(((HTHANDLE*)hthandle)->lastsnaptime));
			char* buffer = new char[250];
			ctime_s(buffer, 250, &(((HTHANDLE*)hthandle)->lastsnaptime));

			std::tm* ptm = new tm();
			localtime_s(ptm, &(((HTHANDLE*)hthandle)->lastsnaptime));
			strftime(buffer, 32, "_%d_%m_%Y__%H_%M_%S", ptm);
			delete ptm;

			wstring newFile = wstring((wchar_t*)hthandle->FileName);
			newFile.replace(newFile.find('.'), 0, GetWC(buffer));
			delete[] buffer;

			HANDLE hf = NULL;
			hf = CreateFile(newFile.c_str(), GENERIC_READ | GENERIC_WRITE, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if (hf == INVALID_HANDLE_VALUE) {
				result = false;
				SetErrorMessage(hthandle, "fail with snap file opening", 28);
			}
			else {
				DWORD written = -1;
				int totalHtSize = sizeof(HTHANDLE);
				totalHtSize += hthandle->Capacity * (sizeof(Element) + hthandle->MaxKeyLength + hthandle->MaxPayloadLength);
				if (WriteFile(hf, hthandle, totalHtSize, &written, NULL))
				{
					CloseHandle(hf);
					cout << "Snapshot is done" << endl;
				}
				else SetErrorMessage(hthandle, "fail with snap file opening", 28);
			}
			ReleaseMutex(hthandle->Mutex);
			return result;
		}
		else {
			ReleaseMutex(hthandle->Mutex);
			return false;
		}
	}

	BOOL Close(const HTHANDLE* hthandle) {
		HANDLE mapping, file, mutex;

		memcpy(&mapping, &hthandle->FileMapping, sizeof(HANDLE));
		memcpy(&file, &hthandle->File, sizeof(HANDLE));
		memcpy(&mutex, &hthandle->Mutex, sizeof(HANDLE));
		TerminateThread(hthandle->SnapshotThread, 0);
		if (!UnmapViewOfFile(hthandle->Addr)) return FALSE;
		if (!CloseHandle(mapping))return FALSE;
		if (!CloseHandle(file))return FALSE;
		if (!CloseHandle(mutex))return FALSE;
		return TRUE;
	}
	BOOL Insert      
	(
		HTHANDLE* hthandle,            
		Element* element              
	) {
		if (!CheckParmLength(hthandle, element))
			return FALSE;
		WaitForSingleObject(hthandle->Mutex, INFINITE);
		bool inserted = false;
		if (hthandle->N != hthandle->Capacity)
		{
			for (int i = 0, j = HashFunction(element, hthandle->Capacity, 0);
				i != hthandle->Capacity && !inserted;  j = Next_hash(j, hthandle->Capacity, ++i)) {
				Element* elFromHT = GetElementFromHT(hthandle, j);
				if (elFromHT == NULL || IsDeleted(elFromHT))
				{
					SetElementToHT(hthandle, element, j);
					hthandle->N++;
					inserted = true;
				}
				if (elFromHT != NULL && EqualElementKeys(elFromHT, element)) {
					SetErrorMessage(hthandle, "Repeat key\n", 12);
					ReleaseMutex(hthandle->Mutex);
					return FALSE;
				}
			}
		}
		ReleaseMutex(hthandle->Mutex);
		return inserted;
	}
	Element* Get     
	(
		HTHANDLE* hthandle,            
		Element* element              
	) 	
	{
		if (!CheckParmLength(hthandle, element))
			return NULL;
		WaitForSingleObject(hthandle->Mutex, INFINITE);
		int indexInHT = -1;
		bool found = false;
		if (hthandle->N != 0)
			for (int i = 0, j = HashFunction(element, hthandle->Capacity, 0);
				GetElementFromHT(hthandle, j) != NULL && i != hthandle->Capacity && !found;
				j = Next_hash(j, hthandle->Capacity, ++i)) {
			Element* elFromHT = GetElementFromHT(hthandle, j);
			if (!IsDeleted(elFromHT)) {
				if (EqualElementKeys(elFromHT, element)) {
					indexInHT = j; found = true;
				}
			}
		}
		if (indexInHT < 0) {
			SetErrorMessage(hthandle, "Not found key\n", 15);
			ReleaseMutex(hthandle->Mutex);
			return NULL;
		}
		ReleaseMutex(hthandle->Mutex);
		return GetElementFromHT(hthandle, indexInHT);
	}
	BOOL Delete      
	(
		HTHANDLE* hthandle,            
		Element* element              
	)	
	{
		if (!CheckParmLength(hthandle, element))
			return FALSE;
		WaitForSingleObject(hthandle->Mutex, INFINITE);
		int indexInHT = -1;
		bool deleted = false;
		if (hthandle->N != 0)
			for (int i = 0, j = HashFunction(element, hthandle->Capacity, 0);
				GetElementFromHT(hthandle, j) != NULL && i != hthandle->Capacity && !deleted;
				j = Next_hash(j, hthandle->Capacity, ++i)) {
			Element* elFromHT = GetElementFromHT(hthandle, j);
			if (!IsDeleted(elFromHT)) {
				if (EqualElementKeys(elFromHT, element)) {
					indexInHT = j; deleted = true;
				}
			}
		}
		if (indexInHT < 0) {
			SetErrorMessage(hthandle, "Not found key\n", 15);
			ReleaseMutex(hthandle->Mutex);
			return FALSE;
		}

		SetDeletedFlag(GetElementFromHT(hthandle, indexInHT));
		hthandle->N--;
		ReleaseMutex(hthandle->Mutex);
		return TRUE;
	}
	BOOL Update     
	(
		HTHANDLE* hthandle,            
		Element* oldelement,          
		void* newpayload,          
		int             newpayloadlength     
	) {
		if (!CheckParmLength(hthandle, oldelement) || !CheckParmLength(hthandle, newpayloadlength))
			return FALSE;
		WaitForSingleObject(hthandle->Mutex, INFINITE);
		int indexInHT = -1;
		bool updated = false;
		if (hthandle->N != 0)
			for (int i = 0, j = HashFunction(oldelement, hthandle->Capacity, 0);
				GetElementFromHT(hthandle, j) != NULL && i != hthandle->Capacity && !updated;
				j = Next_hash(j, hthandle->Capacity, ++i)) {
			Element* elFromHT = GetElementFromHT(hthandle, j);
			if (!IsDeleted(elFromHT)) {
				if (EqualElementKeys(elFromHT, oldelement)) {
					indexInHT = j; updated = true;
				}
			}
		}
		if (indexInHT < 0) {
			SetErrorMessage(hthandle, "Not found key\n", 15);
			ReleaseMutex(hthandle->Mutex);
			return FALSE;
		}

		UpdateElement(hthandle, GetElementFromHT(hthandle, indexInHT), newpayload, newpayloadlength);
		ReleaseMutex(hthandle->Mutex);
		return TRUE;
	}

	char* GetLastError(HTHANDLE* ht) {
		return ht->LastErrorMessage;
	}

	void print(const Element* element) {
		char* key = (char*)element->key;
		std::cout << std::right << std::setfill('=') << std::setw(30) << '|' << std::endl;
		std::cout << std::left << std::setfill(' ') << std::setw(10) << "KEY";
		for (int i = 0; i < element->keylength; i++) {
			std::cout << key[i];
		}
		std::cout << std::endl << std::right << std::setfill('-') << std::setw(6) << '|' << std::endl;
		std::cout << std::left << std::setfill(' ') << std::setw(10) << "VALUE";
		char* payload = (char*)element->payload;
		for (int i = 0; i < element->payloadlength; i++) {
			std::cout << payload[i];
		}
		std::cout << std::endl;
		std::cout << std::right << std::setfill('=') << std::setw(30) << '|' << std::endl;
	}

	Element* GetElementFromHT(HTHANDLE* ht, int n) {
		void* elementsAddr = ht + 1;
		int defaultElementSize = ht->MaxKeyLength + ht->MaxPayloadLength + 2 * sizeof(int);
		void* elementAddr = (char*)elementsAddr + defaultElementSize * n;
		Element* element = new Element();
		element->key = elementAddr;
		element->keylength = *(int*)((char*)elementAddr + ht->MaxKeyLength);
		element->payload = ((char*)elementAddr + ht->MaxKeyLength + sizeof(int));
		element->payloadlength = *(int*)((char*)elementAddr + ht->MaxKeyLength + sizeof(int) + ht->MaxPayloadLength);
		if (element->keylength == 0) {
			delete element;
			return NULL;
		}
		return element;
	}
	BOOL SetElementToHT(HTHANDLE* ht, Element* element, int n) {
		void* elementsAddr = ht + 1;
		int defaultElementSize = ht->MaxKeyLength + ht->MaxPayloadLength + 2 * sizeof(int);
		void* elementAddr = (char*)elementsAddr + defaultElementSize * n;

		memcpy(elementAddr, element->key, element->keylength);
		memcpy(((char*)elementAddr + ht->MaxKeyLength), &element->keylength, sizeof(int));
		memcpy(((char*)elementAddr + ht->MaxKeyLength + sizeof(int)), element->payload, element->payloadlength);
		memcpy(((char*)elementAddr + ht->MaxKeyLength + sizeof(int) + +ht->MaxPayloadLength), &element->payloadlength, sizeof(int));
		return TRUE;
	}
	BOOL IsDeleted(Element* ptr) {
		if (*(int*)ptr->key == -1) {
			return TRUE;
		}
		return FALSE;
	}
	BOOL EqualElementKeys(Element* el1, Element* el2) {
		return !memcmp(el1->key, el2->key, el2->keylength) ? TRUE : FALSE;
	}
	void SetErrorMessage(HTHANDLE* ht, const char* message, int messageLen) {
		char* err = (char*)message;
		memcpy(ht->LastErrorMessage, err, messageLen);
	}
	void SetDeletedFlag(Element* ptr) {
		memcpy(ptr->key, &DELETED, sizeof(DELETED));
	}
	void UpdateElement(HTHANDLE* ht, Element* el, void* newpayload, int newpayloadlength) {
		ZeroMemory(el->payload, ht->MaxPayloadLength + sizeof(int));
		memcpy(el->payload, newpayload, newpayloadlength);
		memcpy((char*)el->payload + ht->MaxPayloadLength, &newpayloadlength, sizeof(int));
	}

	int HashFunction(const Element* element, int size, int p)
	{
		char* arrKeyBytes = new char[element->keylength];
		memcpy(arrKeyBytes, element->key, element->keylength);
		int sumBytes = 0;
		for (int i = 0; i < element->keylength; i++) {
			sumBytes += arrKeyBytes[i];
		}
		double key2 = 5 * ((0.6180339887499 * sumBytes) - int((0.6180339887499 * sumBytes)));
		delete[] arrKeyBytes;
		return (p + sumBytes) % size;
	}
	int Next_hash(int hash, int size, int p)
	{
		return (hash + 5 * p + 3 * p * p) % size;
	}
	DWORD WINAPI SnapShotCycle(HTHANDLE* ht) {
		while (true)
		{
			if (ht) {
				if (time(NULL) >= ht->lastsnaptime + ht->SecSnapshotInterval)
				{
					WaitForSingleObject(ht->Mutex, INFINITE);
					if (!FlushViewOfFile(ht->Addr, NULL)) {
						SetErrorMessage(ht, "Snapshot error", 15);
						return FALSE;
					}
					else ht->lastsnaptime = time(NULL);
					ReleaseMutex(ht->Mutex);
				}
			}
			else break;
		}
		return TRUE;
	}
	wchar_t* GetWC(char* c)
	{
		size_t cSize = strlen(c) + 1;
		wchar_t* wc = new wchar_t[cSize];
		size_t outSize;
		mbstowcs_s(&outSize, wc, cSize, c, cSize - 1);

		return wc;
	}
	wchar_t* GenerateMutexName(const wchar_t* pathToHT) {
		wchar_t mutexName[MAX_PATH];
		ZeroMemory(mutexName, sizeof(mutexName));
		int j = 0;
		for (int i = 0; i < wcslen(pathToHT); i++) {
			if (pathToHT[i] == L'\\') {
				continue;
			}
			else {
				mutexName[j++] = pathToHT[i];
			}
		}
		return mutexName;
	}
	BOOL CheckParmLength(HTHANDLE* ht, Element* element) {
		if (element->keylength > ht->MaxKeyLength) {
			SetErrorMessage(ht, "KeyLength > maxKeyLength\n", strlen("KeyLength > maxKeyLength\n") + 1);
			return FALSE;
		}
		else if (element->payloadlength > ht->MaxPayloadLength) {
			SetErrorMessage(ht, "PayloadLength > maxPayloadLength\n", strlen("PayloadLength > maxPayloadLength\n") + 1);
			return FALSE;
		}
		return TRUE;
	}
	BOOL CheckParmLength(HTHANDLE* ht, int payloadLength) {
		if (payloadLength > ht->MaxPayloadLength) {
			SetErrorMessage(ht, "PayloadLength > maxPayloadLength\n", strlen("PayloadLength > maxPayloadLength\n") + 1);
			return FALSE;
		}
		return TRUE;
	}
}
