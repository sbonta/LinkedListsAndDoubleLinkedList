#include "Stack.h"

LPSTACK
CreateStack()
{
	LPSTACK lpResult = (LPSTACK)VirtualAlloc
	(
		NULL,
		sizeof(STACK),
		MEM_COMMIT,
		PAGE_READWRITE
	);
	if (NULL == lpResult)
	{
		goto Cleanup;
	}

	lpResult->List = CreateDoubleLinkedList();
	if (NULL == lpResult->List)
	{
		goto Cleanup;
	}

	return lpResult;

Cleanup:
	if (NULL != lpResult)
	{
		VirtualFree
		(
			lpResult,
			0,
			MEM_RELEASE
		);
	}

	return NULL;
}

VOID
PushStack
(
	_Inout_ LPSTACK lpStack,
	_In_ LPVOID lpData
)
{
	AddFirstDoubleLinkedList(lpStack->List, lpData);
}

LPVOID
PeekStack
(
	_In_ LPSTACK lpStack
)
{
	return GetFirstDoubleLinkedList(lpStack->List);
}

VOID
PopStack
(
	_Inout_ LPSTACK lpStack
)
{
	DeleteFirstDoubleLinkedList(lpStack->List);
}

BOOL
IsEmptyStack
(
	_In_ LPSTACK lpStack
)
{
	return SizeDoubleLinkedList(lpStack->List) == 0;
}

VOID
DestroyStack
(
	_Inout_ LPSTACK* lpStack
)
{
	DestroyDoubleLinkedList(&(*lpStack)->List);
	VirtualFree
	(
		*lpStack,
		0,
		MEM_RELEASE
	);

	*lpStack = NULL;
}