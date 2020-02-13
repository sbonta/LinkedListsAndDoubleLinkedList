#include "Queue.h"

LPQUEUE
CreateQueue()
{
	LPQUEUE lpResult = (LPQUEUE)VirtualAlloc
	(
		NULL,
		sizeof(QUEUE),
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
PushQueue
(
	_Inout_ LPQUEUE lpQueue,
	_In_ LPVOID lpData
)
{
	AddLastDoubleLinkedList(lpQueue->List, lpData);
}

LPVOID
PeekQueue
(
	_In_ LPQUEUE lpQueue
)
{
	return GetLastDoubleLinkedList(lpQueue->List);
}

VOID
PopQueue
(
	_Inout_ LPQUEUE lpQueue
)
{
	DeleteLastDoubleLinkedList(lpQueue->List);
}

BOOL
IsEmptyQueue
(
	_In_ LPQUEUE lpQueue
)
{
	return SizeDoubleLinkedList(lpQueue->List) == 0;
}

VOID
DestroyQueue
(
	_Inout_ LPQUEUE* lpQueue
)
{
	DestroyDoubleLinkedList(&(*lpQueue)->List);
	VirtualFree
	(
		*lpQueue,
		0,
		MEM_RELEASE
	);
	*lpQueue = NULL;
}