#ifndef _ARRAY_H_
#define _ARRAY_H_

#include <Windows.h>

#define DEFAULT_CAPACITY 10

typedef struct _ARRAY
{
	LPVOID* Data;
	DWORD Capacity;
	DWORD Size;
}ARRAY,
*LPARRAY;

_Must_inspect_result_
LPARRAY
CreateArray
(
	_In_ DWORD dwCapacity
);

VOID
AddAtArray
(
	_Inout_ LPARRAY lpArray,
	_In_ LPVOID lpData,
	_In_ DWORD dwPosition
);

LPVOID
GetAtArray
(
	_In_ LPARRAY lpArray,
	_In_ DWORD dwPosition
);

VOID
UpdateAtArray
(
	_Inout_ LPARRAY lpArray,
	_In_ LPVOID lpData,
	_In_ DWORD dwPosition
);

VOID
RemoveAtArray
(
	_In_ LPARRAY lpArray,
	_In_ DWORD dwPosition
);

VOID
DestroyArray
(
	_Inout_ LPARRAY* lpArray
);

#endif // !_ARRAY_H_
