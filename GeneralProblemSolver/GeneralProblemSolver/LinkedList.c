#include "LinkedList.h"

_Must_inspect_result_
LPNODE_LINKED_LIST
CreateNodeLinkedList
(
	_In_ LPVOID lpData
)
{
	LPNODE_LINKED_LIST lpResult = (LPNODE_LINKED_LIST)VirtualAlloc
	(
		NULL,
		sizeof(LINKED_LIST),
		MEM_COMMIT,
		PAGE_READWRITE
	);
	if (NULL == lpResult) 
	{
		return NULL;
	}

	lpResult->Data = lpData;
	lpResult->Next = NULL;

	return lpResult;
}

VOID
UpdateNodeLinkedList
(
	_Inout_ LPNODE_LINKED_LIST lpNode,
	_In_ LPVOID lpData
)
{
	lpNode->Data = lpData;
}

VOID
DestroyNodeLinkedList
(
	_Inout_ LPNODE_LINKED_LIST* lpNode
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
LPLINKED_LIST
CreateLinkedList()
{
	LPLINKED_LIST lpResult = (LPLINKED_LIST)VirtualAlloc
	(
		NULL,
		sizeof(LINKED_LIST),
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

VOID
AddFirstLinkedList
(
	_Inout_ LPLINKED_LIST lpLinkedList,
	_In_ LPVOID lpData
)
{
	LPNODE_LINKED_LIST lpNode = CreateNodeLinkedList
	(
		lpData
	);
	if (NULL == lpNode)
	{
		return;
	}

	if (NULL == lpLinkedList->Head)
	{
		lpLinkedList->Head = lpNode;
		lpLinkedList->Tail = lpNode;
	}
	else
	{
		lpNode->Next = lpLinkedList->Head;
		lpLinkedList->Head = lpNode;
	}

	lpLinkedList->Size = lpLinkedList->Size + 1;
}

VOID
AddLastLinkedList
(
	_Inout_ LPLINKED_LIST lpLinkedList,
	_In_ LPVOID lpData
)
{
	LPNODE_LINKED_LIST lpNode = CreateNodeLinkedList
	(
		lpData
	);
	if (NULL == lpNode)
	{
		return;
	}

	if (NULL == lpLinkedList->Tail)
	{
		lpLinkedList->Head = lpNode;
		lpLinkedList->Tail = lpNode;
	}
	else
	{
		lpLinkedList->Tail->Next = lpNode;
		lpLinkedList->Tail = lpNode;
	}

	lpLinkedList->Size = lpLinkedList->Size + 1;
}

VOID
AddAtLinkedList
(
	_Inout_ LPLINKED_LIST lpLinkedList,
	_In_ LPVOID lpData,
	_In_ DWORD dwPosition
)
{
	LPNODE_LINKED_LIST lpNode = NULL;
	LPNODE_LINKED_LIST lpCurrentNode = NULL;

	if (dwPosition > lpLinkedList->Size)
	{
		return;
	}

	if (0 == dwPosition)
	{
		AddFirstLinkedList(lpLinkedList, lpData);
	}
	else if (dwPosition == lpLinkedList->Size)
	{
		AddLastLinkedList(lpLinkedList, lpData);
	}
	else
	{
		lpNode = CreateNodeLinkedList
		(
			lpData
		);
		if (NULL == lpNode)
		{
			return;
		}

		lpCurrentNode = lpLinkedList->Head;
		for (DWORD i = 0; i < dwPosition - 1; i++)
		{
			lpCurrentNode = lpCurrentNode->Next;
		}

		lpNode->Next = lpCurrentNode->Next;
		lpCurrentNode->Next = lpNode;

		lpLinkedList->Size = lpLinkedList->Size + 1;
	}
}

LPVOID
GetFirstLinkedList
(
	_Inout_ LPLINKED_LIST lpLinkedList
)
{
	if (NULL != lpLinkedList->Head)
	{
		return lpLinkedList->Head->Data;
	}
	return NULL;
}

LPVOID
GetLastLinkedList
(
	_Inout_ LPLINKED_LIST lpLinkedList
)
{
	if (NULL != lpLinkedList->Tail)
	{
		return lpLinkedList->Tail->Data;
	}
	return NULL;
}

LPVOID
GetAtLinkedList
(
	_Inout_ LPLINKED_LIST lpLinkedList,
	_In_ DWORD dwPosition
)
{
	LPNODE_LINKED_LIST lpCurrentNode = NULL;
	if (dwPosition >= lpLinkedList->Size)
	{
		return NULL;
	}
	if (dwPosition == lpLinkedList->Size - 1)
	{
		return GetLastLinkedList(lpLinkedList);
	}

	lpCurrentNode = lpLinkedList->Head;
	for (DWORD i = 0; i < dwPosition; i++)
	{
		lpCurrentNode = lpCurrentNode->Next;
	}

	return lpCurrentNode->Data;
}

VOID
UpdateFirstLinkedList
(
	_Inout_ LPLINKED_LIST lpLinkedList,
	_In_ LPVOID lpData
)
{
	if (NULL != lpLinkedList->Head)
	{
		UpdateNodeLinkedList(lpLinkedList->Head, lpData);
	}
}

VOID
UpdateLastLinkedList
(
	_Inout_ LPLINKED_LIST lpLinkedList,
	_In_ LPVOID lpData
)
{
	if (NULL != lpLinkedList->Tail)
	{
		UpdateNodeLinkedList(lpLinkedList->Tail, lpData);
	}
}

VOID
UpdateAtLinkedList
(
	_Inout_ LPLINKED_LIST lpLinkedList,
	_In_ LPVOID lpData,
	_In_ DWORD dwPosition
)
{
	LPNODE_LINKED_LIST lpCurrentNode = NULL;

	if (dwPosition >= lpLinkedList->Size)
	{
		return;
	}

	lpCurrentNode = lpLinkedList->Head;
	for (DWORD i = 0; i < dwPosition; i++)
	{
		lpCurrentNode = lpCurrentNode->Next;
	}

	UpdateNodeLinkedList(lpCurrentNode, lpData);
}

VOID
DeleteFirstLinkedList
(
	_Inout_ LPLINKED_LIST lpLinkedList
)
{
	if (0 == lpLinkedList->Size)
	{
		return;
	}

	LPNODE_LINKED_LIST lpNode = lpLinkedList->Head;
	lpLinkedList->Head = lpLinkedList->Head->Next;
	DestroyNodeLinkedList(&lpNode);
	lpLinkedList->Size = lpLinkedList->Size - 1;

	if (0 == lpLinkedList->Size)
	{
		lpLinkedList->Head = NULL;
		lpLinkedList->Tail = NULL;
	}
}

VOID
DeleteLastLinkedList
(
	_Inout_ LPLINKED_LIST lpLinkedList
)
{
	LPNODE_LINKED_LIST lpCurrentNode = NULL;
	if (0 == lpLinkedList->Size)
	{
		return;
	}

	if (1 == lpLinkedList->Size)
	{
		DeleteFirstLinkedList(lpLinkedList);
	}
	else
	{
		lpCurrentNode = lpLinkedList->Head;
		for (DWORD i = 0; i < lpLinkedList->Size - 2; i++)
		{
			lpCurrentNode = lpCurrentNode->Next;
		}

		lpLinkedList->Tail = lpCurrentNode;
		lpCurrentNode = lpCurrentNode->Next;
		lpLinkedList->Tail->Next = NULL;
		DestroyNodeLinkedList(&lpCurrentNode);
		lpLinkedList->Size = lpLinkedList->Size - 1;
	}
}

VOID
DeleteAtLinkedList
(
	_Inout_ LPLINKED_LIST lpLinkedList,
	_In_ DWORD dwPosition
)
{
	LPNODE_LINKED_LIST lpCurrentNode = NULL;
	LPNODE_LINKED_LIST lpNode = NULL;
	if (dwPosition >= lpLinkedList->Size)
	{
		return;
	}

	if (0 == dwPosition)
	{
		DeleteFirstLinkedList(lpLinkedList);
	}
	else if (lpLinkedList->Size == dwPosition + 1)
	{
		DeleteLastLinkedList(lpLinkedList);
	}
	else
	{
		lpCurrentNode = lpLinkedList->Head;
		for (DWORD i = 0; i < dwPosition - 1; i++)
		{
			lpCurrentNode = lpCurrentNode->Next;
		}

		lpNode = lpCurrentNode->Next;
		lpCurrentNode->Next = lpCurrentNode->Next->Next;
		DestroyNodeLinkedList(&lpNode);
		lpLinkedList->Size = lpLinkedList->Size - 1;
	}
}

VOID
DestroyLinkedList
(
	_Inout_ LPLINKED_LIST* lpLinkedList
)
{
	LPNODE_LINKED_LIST lpNode = NULL;
	LPNODE_LINKED_LIST lpCurrentNode = (*lpLinkedList)->Head;
	while (NULL != lpCurrentNode)
	{
		lpNode = lpCurrentNode;
		lpCurrentNode = lpCurrentNode->Next;
		DestroyNodeLinkedList(&lpNode);
	}

	VirtualFree
	(
		*lpLinkedList, 
		0,
		MEM_RELEASE
	);
	*lpLinkedList = NULL;
}