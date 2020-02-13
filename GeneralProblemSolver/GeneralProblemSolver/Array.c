#include "Array.h"
#pragma warning( disable : 6386 )

_Must_inspect_result_
LPARRAY
CreateArray
(
	_In_ DWORD dwCapacity
)
{
	LPARRAY lpResult = (LPARRAY)VirtualAlloc
	(
		NULL,
		sizeof(ARRAY),
		MEM_COMMIT,
		PAGE_READWRITE
	);
	if (NULL == lpResult)
	{
		goto Cleanup;
	}

	if (0 == dwCapacity)
	{
		dwCapacity = DEFAULT_CAPACITY;
	}

	lpResult->Data = (LPVOID*)VirtualAlloc
	(
		NULL,
		sizeof(LPVOID),
		MEM_COMMIT,
		PAGE_READWRITE
	);
	if (NULL == lpResult->Data)
	{
		goto Cleanup;
	}
	lpResult->Capacity = dwCapacity;
	lpResult->Size = 0;

	return lpResult;

Cleanup:

	if (NULL != lpResult)
	{
		if (NULL != lpResult->Data)
		{
			VirtualFree(lpResult->Data, 0, MEM_RELEASE);
			lpResult->Data = NULL;
		}
		VirtualFree(lpResult, 0, MEM_RELEASE);
		lpResult = NULL;
	}

	return NULL;
}

_Must_inspect_result_
BOOL
ResizeArray
(
	_Inout_ LPARRAY lpArray
)
{
	LPVOID* lpNewData = (LPVOID*)VirtualAlloc
	(
		NULL,
		sizeof(LPVOID) * lpArray->Capacity * 2,
		MEM_COMMIT,
		PAGE_READWRITE
	);
	if (NULL == lpNewData)
	{
		return FALSE;
	}

	for (DWORD i = 0; i < lpArray->Capacity; i++)
	{
		lpNewData[i] = lpArray->Data[i];
	}
	VirtualFree
	(
		lpArray->Data,
		0,
		MEM_RELEASE
	);
	lpArray->Data = lpNewData;
	lpArray->Capacity = lpArray->Capacity * 2;

	return TRUE;
}

VOID
AddAtArray
(
	_Inout_ LPARRAY lpArray,
	_In_ LPVOID lpData,
	_In_ DWORD dwPosition
)
{
	if (dwPosition > lpArray->Size)
	{
		return;
	}

	if (lpArray->Size == lpArray->Capacity)
	{
		if (!ResizeArray(lpArray))
		{
			return;
		}
	}

	for (DWORD i = lpArray->Size; i >= dwPosition; i--)
	{
		lpArray->Data[i + 1] = lpArray->Data[i];
	}
	lpArray->Data[dwPosition] = lpData;
	lpArray->Size = lpArray->Size + 1;
}

LPVOID
GetAtArray
(
	_In_ LPARRAY lpArray,
	_In_ DWORD dwPosition
)
{
	if (dwPosition < lpArray->Size)
	{
		return lpArray->Data[dwPosition];
	}
	
	return NULL;
}

VOID
UpdateAtArray
(
	_Inout_ LPARRAY lpArray,
	_In_ LPVOID lpData,
	_In_ DWORD dwPosition
)
{
	if (dwPosition < lpArray->Size)
	{
		lpArray->Data[dwPosition] = lpData;
	}
}

VOID
RemoveAtArray
(
	_In_ LPARRAY lpArray,
	_In_ DWORD dwPosition
)
{
	if (dwPosition < lpArray->Size)
	{
		for (DWORD i = dwPosition; i < lpArray->Size; i++)
		{
			lpArray->Data[i] = lpArray->Data[i + 1];
		}
		lpArray->Size--;
	}
}

VOID
DestroyArray
(
	_Inout_ LPARRAY* lpArray
)
{
	VirtualFree
	(
		(*lpArray)->Data,
		0,
		MEM_RELEASE
	);
	VirtualFree
	(
		*lpArray,
		0,
		MEM_RELEASE
	);
	*lpArray = NULL;
}