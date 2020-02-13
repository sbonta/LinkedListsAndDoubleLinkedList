#include "DoubleLinkedList.h"

_Must_inspect_result_
LPNODE_DOUBLE_LINKED_LIST
CreateNodeDoubleLinkedList
(
	_In_ LPVOID lpData
)
{
	LPNODE_DOUBLE_LINKED_LIST lpResult = (LPNODE_DOUBLE_LINKED_LIST)VirtualAlloc
	(
		NULL,
		sizeof(NODE_DOUBLE_LINKED_LIST),
		MEM_COMMIT,
		PAGE_READWRITE
	);
	if (NULL == lpResult)
	{
		return NULL;
	}

	lpResult->Data = lpData;
	lpResult->XorAddresses = 0;

	return lpResult;
}

VOID
UpdateNodeDoubleLinkedList
(
	_In_ LPNODE_DOUBLE_LINKED_LIST lpNode,
	_In_ LPVOID lpData
)
{
	lpNode->Data = lpData;
}

VOID
DestroyNodeDoubleLinkedList
(
	_Inout_ LPNODE_DOUBLE_LINKED_LIST* lpNode
)
{
	VirtualFree
	(
		*lpNode,
		0,
		MEM_RELEASE
	);
	*lpNode = NULL;
}

_Must_inspect_result_
LPDOUBLE_LINKED_LIST
CreateDoubleLinkedList()
{
	LPDOUBLE_LINKED_LIST lpResult = (LPDOUBLE_LINKED_LIST)VirtualAlloc
	(
		NULL,
		sizeof(DOUBLE_LINKED_LIST),
		MEM_COMMIT,
		PAGE_READWRITE
	);
	if (NULL == lpResult)
	{
		return NULL;
	}

	lpResult->Head = NULL;
	lpResult->Tail = NULL;
	lpResult->Size = 0;

	return lpResult;
}

LPNODE_DOUBLE_LINKED_LIST
GetNextOrPreviousNodeDoubleLinkedList
(
	LPNODE_DOUBLE_LINKED_LIST lpPreviousOrNext,
	LPNODE_DOUBLE_LINKED_LIST lpCurrent
)
{
	ULONGLONG ullPreviousOrNext = (ULONGLONG)lpPreviousOrNext;
	ULONGLONG ullNextOrPrevious = ullPreviousOrNext ^ lpCurrent->XorAddresses;
	LPNODE_DOUBLE_LINKED_LIST lpNextOrPrevious = (LPNODE_DOUBLE_LINKED_LIST)ullNextOrPrevious;

	return lpNextOrPrevious;
}

VOID
AddFirstDoubleLinkedList
(
	_Inout_ LPDOUBLE_LINKED_LIST lpDoubleLinkedList,
	_In_ LPVOID lpData
)
{
	ULONGLONG ullHead = 0;
	ULONGLONG ullNode = 0;
	LPNODE_DOUBLE_LINKED_LIST lpNode = CreateNodeDoubleLinkedList(lpData);
	if (NULL == lpNode)
	{
		return;
	}
	if (0 == lpDoubleLinkedList->Size)
	{
		lpDoubleLinkedList->Head = lpNode;
		lpDoubleLinkedList->Tail = lpNode;
		lpDoubleLinkedList->Size = lpDoubleLinkedList->Size + 1;
	}
	else
	{
		ullHead = (ULONGLONG)lpDoubleLinkedList->Head;
		ullNode = (ULONGLONG)lpNode;
		lpDoubleLinkedList->Head->XorAddresses = lpDoubleLinkedList->Head->XorAddresses ^ ullNode;
		lpNode->XorAddresses = ullHead;

		lpDoubleLinkedList->Head = lpNode;
		lpDoubleLinkedList->Size = lpDoubleLinkedList->Size + 1;
	}
}

VOID
AddLastDoubleLinkedList
(
	_Inout_ LPDOUBLE_LINKED_LIST lpDoubleLinkedList,
	_In_ LPVOID lpData
)
{
	ULONGLONG ullTail = 0;
	ULONGLONG ullNode = 0;
	LPNODE_DOUBLE_LINKED_LIST lpNode = CreateNodeDoubleLinkedList(lpData);
	if (NULL == lpNode)
	{
		return;
	}
	if (0 == lpDoubleLinkedList->Size)
	{
		lpDoubleLinkedList->Head = lpNode;
		lpDoubleLinkedList->Tail = lpNode;
		lpDoubleLinkedList->Size = lpDoubleLinkedList->Size + 1;
	}
	else
	{
		ullTail = (ULONGLONG)lpDoubleLinkedList->Tail;
		ullNode = (ULONGLONG)lpNode;
		lpDoubleLinkedList->Tail->XorAddresses = lpDoubleLinkedList->Tail->XorAddresses ^ ullNode;
		lpNode->XorAddresses = ullTail;

		lpDoubleLinkedList->Tail = lpNode;
		lpDoubleLinkedList->Size = lpDoubleLinkedList->Size + 1;
	}
}

VOID
AddAtDoubleLinkedList
(
	_Inout_ LPDOUBLE_LINKED_LIST lpDoubleLinkedList,
	_In_ LPVOID lpData,
	_In_ DWORD dwPosition
)
{
	LPNODE_DOUBLE_LINKED_LIST lpNode = NULL;
	LPNODE_DOUBLE_LINKED_LIST lpPreviousOrNext = NULL;
	LPNODE_DOUBLE_LINKED_LIST lpCurrent = NULL;
	LPNODE_DOUBLE_LINKED_LIST lpNextOrPrevious = NULL;
	LPNODE_DOUBLE_LINKED_LIST lpAuxiliary = NULL;
	DWORD dwNumberOfSteps = 0;
	ULONGLONG ullNode = 0;
	ULONGLONG ullCurrent = 0;
	ULONGLONG ullNextOrPrevious = 0;

	if (dwPosition > lpDoubleLinkedList->Size)
	{
		return;
	}

	if (0 == dwPosition)
	{
		AddFirstDoubleLinkedList(lpDoubleLinkedList, lpData);
	}
	else if (lpDoubleLinkedList->Size - 1 == dwPosition)
	{
		AddLastDoubleLinkedList(lpDoubleLinkedList, lpData);
	}
	else
	{
		lpNode = CreateNodeDoubleLinkedList(lpData);
		if (NULL == lpNode)
		{
			return;
		}

		if (dwPosition <= lpDoubleLinkedList->Size - dwPosition)
		{
			dwNumberOfSteps = dwPosition;
			lpPreviousOrNext = NULL;
			lpCurrent = lpDoubleLinkedList->Head;
		}
		else
		{
			dwNumberOfSteps = lpDoubleLinkedList->Size - dwPosition;
			lpPreviousOrNext = NULL;
			lpCurrent = lpDoubleLinkedList->Tail;
		}

		for (DWORD i = 1; i < dwNumberOfSteps; i++)
		{

			lpAuxiliary = lpCurrent;
			lpCurrent = GetNextOrPreviousNodeDoubleLinkedList(lpPreviousOrNext, lpCurrent);
			lpPreviousOrNext = lpAuxiliary;
		}

		lpNextOrPrevious = GetNextOrPreviousNodeDoubleLinkedList(lpPreviousOrNext, lpCurrent);

		ullNode = (ULONGLONG)lpNode;
		ullCurrent = (ULONGLONG)lpCurrent;
		ullNextOrPrevious = (ULONGLONG)lpNextOrPrevious;

		lpCurrent->XorAddresses = lpCurrent->XorAddresses ^ ullNextOrPrevious ^ ullNode;
		lpNextOrPrevious->XorAddresses = lpNextOrPrevious->XorAddresses ^ ullCurrent ^ ullNode;
		lpNode->XorAddresses = ullCurrent ^ ullNextOrPrevious;

		lpDoubleLinkedList->Size = lpDoubleLinkedList->Size + 1;
	}
}

LPVOID
GetFirstDoubleLinkedList
(
	_Inout_ LPDOUBLE_LINKED_LIST lpDoubleLinkedList
)
{
	if (0 != lpDoubleLinkedList->Size)
	{
		return lpDoubleLinkedList->Head->Data;
	}

	return NULL;
}

LPVOID
GetLastDoubleLinkedList
(
	_Inout_ LPDOUBLE_LINKED_LIST lpDoubleLinkedList
)
{
	if (0 != lpDoubleLinkedList)
	{
		return lpDoubleLinkedList->Tail->Data;
	}

	return NULL;
}

LPVOID
GetAtDoubleLinkedList
(
	_Inout_ LPDOUBLE_LINKED_LIST lpDoubleLinkedList,
	_In_ DWORD dwPosition
)
{
	LPNODE_DOUBLE_LINKED_LIST lpPreviousOrNext = NULL;
	LPNODE_DOUBLE_LINKED_LIST lpCurrent = NULL;
	LPNODE_DOUBLE_LINKED_LIST lpAuxiliary = NULL;
	DWORD dwNumberOfSteps = 0;

	if (dwPosition >= lpDoubleLinkedList->Size)
	{
		return NULL;
	}

	if (dwPosition <= lpDoubleLinkedList->Size - dwPosition - 1)
	{
		dwNumberOfSteps = dwPosition;
		lpPreviousOrNext = NULL;
		lpCurrent = lpDoubleLinkedList->Head;
	}
	else
	{
		dwNumberOfSteps = lpDoubleLinkedList->Size - dwPosition - 1;
		lpPreviousOrNext = NULL;
		lpCurrent = lpDoubleLinkedList->Tail;
	}

	for (DWORD i = 0; i < dwNumberOfSteps; i++)
	{
		lpAuxiliary = lpCurrent;
		lpCurrent = GetNextOrPreviousNodeDoubleLinkedList(lpPreviousOrNext, lpCurrent);
		lpPreviousOrNext = lpAuxiliary;
	}

	return lpCurrent->Data;
}

VOID
UpdateFirstDoubleLinkedList
(
	_Inout_ LPDOUBLE_LINKED_LIST lpDoubleLinkedList,
	_In_ LPVOID lpData
)
{
	if (0 != lpDoubleLinkedList->Size)
	{
		lpDoubleLinkedList->Head->Data = lpData;
	}
}

VOID
UpdateLastDoubleLinkedList
(
	_Inout_ LPDOUBLE_LINKED_LIST lpDoubleLinkedList,
	_In_ LPVOID lpData
)
{
	if (0 != lpDoubleLinkedList->Size)
	{
		lpDoubleLinkedList->Tail->Data = lpData;
	}
}

VOID
UpdateAtDoubleLinkedList
(
	_Inout_ LPDOUBLE_LINKED_LIST lpDoubleLinkedList,
	_In_ LPVOID lpData,
	_In_ DWORD dwPosition
)
{
	LPNODE_DOUBLE_LINKED_LIST lpPreviousOrNext = NULL;
	LPNODE_DOUBLE_LINKED_LIST lpCurrent = NULL;
	LPNODE_DOUBLE_LINKED_LIST lpAuxiliary = NULL;
	DWORD dwNumberOfSteps = 0;

	if (dwPosition >= lpDoubleLinkedList->Size)
	{
		return;
	}

	if (dwPosition <= lpDoubleLinkedList->Size - dwPosition - 1)
	{
		dwNumberOfSteps = dwPosition;
		lpPreviousOrNext = NULL;
		lpCurrent = lpDoubleLinkedList->Head;
	}
	else
	{
		dwNumberOfSteps = lpDoubleLinkedList->Size - dwPosition - 1;
		lpPreviousOrNext = NULL;
		lpCurrent = lpDoubleLinkedList->Tail;
	}

	for (DWORD i = 0; i < dwNumberOfSteps; i++)
	{
		lpAuxiliary = lpCurrent;
		lpCurrent = GetNextOrPreviousNodeDoubleLinkedList(lpPreviousOrNext, lpCurrent);
		lpPreviousOrNext = lpAuxiliary;
	}

	lpCurrent->Data = lpData;
}

VOID
DeleteFirstDoubleLinkedList
(
	_Inout_ LPDOUBLE_LINKED_LIST lpDoubleLinkedList
)
{
	LPNODE_DOUBLE_LINKED_LIST lpNode = NULL;
	ULONGLONG ullHead = 0;

	if (0 == lpDoubleLinkedList->Size)
	{
		return;
	}
	if (1 == lpDoubleLinkedList->Size)
	{
		DestroyNodeDoubleLinkedList(&lpDoubleLinkedList->Head);
		lpDoubleLinkedList->Head = NULL;
		lpDoubleLinkedList->Tail = NULL;
	}
	else
	{
		lpNode = GetNextOrPreviousNodeDoubleLinkedList(NULL, lpDoubleLinkedList->Head);
		ullHead = (ULONGLONG)lpDoubleLinkedList->Head;
		lpNode->XorAddresses = lpNode->XorAddresses ^ ullHead;
		DestroyNodeDoubleLinkedList(&lpDoubleLinkedList->Head);
		lpDoubleLinkedList->Head = lpNode;
	}

	lpDoubleLinkedList->Size = lpDoubleLinkedList->Size - 1;
}

VOID
DeleteLastDoubleLinkedList
(
	_Inout_ LPDOUBLE_LINKED_LIST lpDoubleLinkedList
)
{
	LPNODE_DOUBLE_LINKED_LIST lpNode = NULL;
	ULONGLONG ullTail = 0;

	if (0 == lpDoubleLinkedList->Size)
	{
		return;
	}
	if (1 == lpDoubleLinkedList->Size)
	{
		DestroyNodeDoubleLinkedList(&lpDoubleLinkedList->Tail);
		lpDoubleLinkedList->Head = NULL;
		lpDoubleLinkedList->Tail = NULL;
	}
	else
	{
		lpNode = GetNextOrPreviousNodeDoubleLinkedList(NULL, lpDoubleLinkedList->Tail);
		ullTail = (ULONGLONG)lpDoubleLinkedList->Tail;
		lpNode->XorAddresses = lpNode->XorAddresses ^ ullTail;
		DestroyNodeDoubleLinkedList(&lpDoubleLinkedList->Tail);
		lpDoubleLinkedList->Tail = lpNode;
	}

	lpDoubleLinkedList->Size = lpDoubleLinkedList->Size - 1;
}

VOID
DeleteAtDoubleLinkedList
(
	_Inout_ LPDOUBLE_LINKED_LIST lpDoubleLinkedList,
	_In_ DWORD dwPosition
)
{
	LPNODE_DOUBLE_LINKED_LIST lpPreviousOrNext = NULL;
	LPNODE_DOUBLE_LINKED_LIST lpCurrent = NULL;
	LPNODE_DOUBLE_LINKED_LIST lpNextOrPrevious = NULL;
	LPNODE_DOUBLE_LINKED_LIST lpAuxiliary = NULL;
	DWORD dwNumberOfSteps = 0;
	ULONGLONG ullPreviousOrNext = 0;
	ULONGLONG ullCurrent = 0;
	ULONGLONG ullNextOrPrevious = 0;

	if (dwPosition >= lpDoubleLinkedList->Size)
	{
		return;
	}

	if (0 == dwPosition)
	{
		DeleteFirstDoubleLinkedList(lpDoubleLinkedList);
	}
	else if(dwPosition == lpDoubleLinkedList->Size - 1)
	{
		DeleteLastDoubleLinkedList(lpDoubleLinkedList);
	}
	else
	{
		if (dwPosition <= lpDoubleLinkedList->Size - dwPosition - 1)
		{
			dwNumberOfSteps = dwPosition;
			lpPreviousOrNext = NULL;
			lpCurrent = lpDoubleLinkedList->Head;
		}
		else
		{
			dwNumberOfSteps = lpDoubleLinkedList->Size - dwPosition - 1;
			lpPreviousOrNext = NULL;
			lpCurrent = lpDoubleLinkedList->Tail;
		}

		for (DWORD i = 0; i < dwNumberOfSteps; i++)
		{
			lpAuxiliary = lpCurrent;
			lpCurrent = GetNextOrPreviousNodeDoubleLinkedList(lpPreviousOrNext, lpCurrent);
			lpPreviousOrNext = lpAuxiliary;
		}
		if (NULL == lpPreviousOrNext)
		{
			return;
		}

		lpNextOrPrevious = GetNextOrPreviousNodeDoubleLinkedList(lpPreviousOrNext, lpCurrent);

		ullPreviousOrNext = (ULONGLONG)lpPreviousOrNext;
		ullCurrent = (ULONGLONG)lpCurrent;
		ullNextOrPrevious = (ULONGLONG)lpNextOrPrevious;

		lpPreviousOrNext->XorAddresses = lpPreviousOrNext->XorAddresses ^ ullCurrent ^ ullNextOrPrevious;
		lpNextOrPrevious->XorAddresses = lpNextOrPrevious->XorAddresses ^ ullCurrent ^ ullPreviousOrNext;
		DestroyNodeDoubleLinkedList(&lpCurrent);

		lpDoubleLinkedList->Size = lpDoubleLinkedList->Size - 1;
	}

}

VOID
DestroyDoubleLinkedList
(
	_Inout_ LPDOUBLE_LINKED_LIST* lpDoubleLinkedList
)
{
	for (DWORD i = 0; i < (*lpDoubleLinkedList)->Size; i++)
	{
		DeleteFirstDoubleLinkedList(*lpDoubleLinkedList);
	}
	VirtualFree
	(
		*lpDoubleLinkedList,
		0,
		MEM_RELEASE
	);
	*lpDoubleLinkedList = NULL;
}

DWORD
SizeDoubleLinkedList
(
	_In_ LPDOUBLE_LINKED_LIST lpDoubleLinkedList
)
{
	return lpDoubleLinkedList->Size;
}