#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include <Windows.h>

typedef struct _NODE_LINKED_LIST
{
	LPVOID Data;
	struct _NODE_LINKED_LIST* Next;
}NODE_LINKED_LIST,
* LPNODE_LINKED_LIST;

_Must_inspect_result_
LPNODE_LINKED_LIST
CreateNodeLinkedList
(
	_In_ LPVOID lpData
);

VOID
UpdateNodeLinkedList
(
	_Inout_ LPNODE_LINKED_LIST lpNodeLinkedList,
	_In_ LPVOID lpData
);

VOID
DestroyNodeLinkedList
(
	_Inout_ LPNODE_LINKED_LIST* lpNode
);


typedef struct _LINKED_LIST
{
	LPNODE_LINKED_LIST Head;
	LPNODE_LINKED_LIST Tail;
	DWORD Size;
}LINKED_LIST,
*LPLINKED_LIST;

_Must_inspect_result_
LPLINKED_LIST
CreateLinkedList();

VOID
AddFirstLinkedList
(
	_Inout_ LPLINKED_LIST lpLinkedList,
	_In_ LPVOID lpData
);

VOID
AddLastLinkedList
(
	_Inout_ LPLINKED_LIST lpLinkedList,
	_In_ LPVOID lpData
);

VOID
AddAtLinkedList
(
	_Inout_ LPLINKED_LIST lpLinkedList,
	_In_ LPVOID lpData,
	_In_ DWORD dwPosition
);

LPVOID
GetFirstLinkedList
(
	_Inout_ LPLINKED_LIST lpLinkedList
);

LPVOID
GetLastLinkedList
(
	_Inout_ LPLINKED_LIST lpLinkedList
);

LPVOID
GetAtLinkedList
(
	_Inout_ LPLINKED_LIST lpLinkedList,
	_In_ DWORD dwPosition
);

VOID
UpdateFirstLinkedList
(
	_Inout_ LPLINKED_LIST lpLinkedList,
	_In_ LPVOID lpData
);

VOID
UpdateLastLinkedList
(
	_Inout_ LPLINKED_LIST lpLinkedList,
	_In_ LPVOID lpData
);

VOID
UpdateAtLinkedList
(
	_Inout_ LPLINKED_LIST lpLinkedList,
	_In_ LPVOID lpData,
	_In_ DWORD dwPosition
);

VOID
DeleteFirstLinkedList
(
	_Inout_ LPLINKED_LIST lpLinkedList
);

VOID
DeleteLastLinkedList
(
	_Inout_ LPLINKED_LIST lpLinkedList
);

VOID
DeleteAtLinkedList
(
	_Inout_ LPLINKED_LIST lpLinkedList,
	_In_ DWORD dwPosition
);

VOID
DestroyLinkedList
(
	_Inout_ LPLINKED_LIST* lpLinkedList
);

#endif // !_LINKED_LIST_H_
