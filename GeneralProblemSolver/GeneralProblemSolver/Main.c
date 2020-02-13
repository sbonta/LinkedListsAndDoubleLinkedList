#include <Windows.h>

#include "Demo.h"

VOID
RunDemos()
{
	LinkedListDemo();
	DoubleLinkedListDemo();
}

INT
main
(
	_In_opt_ LPCSTR* lpArgv,
	_In_ DWORD dwArgc
)
{
	UNREFERENCED_PARAMETER(lpArgv);
	UNREFERENCED_PARAMETER(dwArgc);

	RunDemos();
	
	return 0;
}