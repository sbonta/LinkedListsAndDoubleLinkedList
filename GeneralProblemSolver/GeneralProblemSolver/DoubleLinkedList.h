#ifndef _DOUBLE_LINKED_LIST_H_
#define _DOUBLE_LINKED_LIST_H_

#include <Windows.h>

typedef struct _NODE_DOUBLE_LINKED_LIST
{

	LPVOID Data;
	ULONGLONG XorAddresses;

}NODE_DOUBLE_LINKED_LIST,
*LPNODE_DOUBLE_LINKED_LIST;

_Must_inspect_result_
LPNODE_DOUBLE_LINKED_LIST
CreateNodeDoubleLinkedList
(
	_In_ LPVOID lpData
);

VOID
UpdateNodeDoubleLinkedList
(
	_In_ LPNODE_DOUBLE_LINKED_LIST lpNode,
	_In_ LPVOID lpData
);

VOID
DestroyNodeDoubleLinkedList
(
	_Inout_ LPNODE_DOUBLE_LINKED_LIST* lpNode
);

typedef struct _DOUBLE_LINKED_LIST
{
	LPNODE_DOUBLE_LINKED_LIST Head;
	LPNODE_DOUBLE_LINKED_LIST Tail;
	DWORD Size;
}DOUBLE_LINKED_LIST,
*LPDOUBLE_LINKED_LIST;

_Must_inspect_result_
LPDOUBLE_LINKED_LIST
CreateDoubleLinkedList();

VOID
AddFirstDoubleLinkedList
(
	_Inout_ LPDOUBLE_LINKED_LIST lpDoubleLinkedList,
	_In_ LPVOID lpData
);

VOID
AddLastDoubleLinkedList
(
	_Inout_ LPDOUBLE_LINKED_LIST lpDoubleLinkedList,
	_In_ LPVOID lpData
);

VOID
AddAtDoubleLinkedList
(
	_Inout_ LPDOUBLE_LINKED_LIST lpDoubleLinkedList,
	_In_ LPVOID lpData,
	_In_ DWORD dwPosition
);

LPVOID
GetFirstDoubleLinkedList
(
	_Inout_ LPDOUBLE_LINKED_LIST lpDoubleLinkedList
);

LPVOID
GetLastDoubleLinkedList
(
	_Inout_ LPDOUBLE_LINKED_LIST lpDoubleLinkedList
);

LPVOID
GetAtDoubleLinkedList
(
	_Inout_ LPDOUBLE_LINKED_LIST lpDoubleLinkedList,
	_In_ DWORD dwPosition
);

VOID
UpdateFirstDoubleLinkedList
(
	_Inout_ LPDOUBLE_LINKED_LIST lpDoubleLinkedList,
	_In_ LPVOID lpData
);

VOID
UpdateLastDoubleLinkedList
(
	_Inout_ LPDOUBLE_LINKED_LIST lpDoubleLinkedList,
	_In_ LPVOID lpData
);

VOID
UpdateAtDoubleLinkedList
(
	_Inout_ LPDOUBLE_LINKED_LIST lpDoubleLinkedList,
	_In_ LPVOID lpData,
	_In_ DWORD dwPosition
);

VOID
DeleteFirstDoubleLinkedList
(
	_Inout_ LPDOUBLE_LINKED_LIST lpDoubleLinkedList
);

VOID
DeleteLastDoubleLinkedList
(
	_Inout_ LPDOUBLE_LINKED_LIST lpDoubleLinkedList
);

VOID
DeleteAtDoubleLinkedList
(
	_Inout_ LPDOUBLE_LINKED_LIST lpDoubleLinkedList,
	_In_ DWORD dwPosition
);

VOID
DestroyDoubleLinkedList
(
	_Inout_ LPDOUBLE_LINKED_LIST* lpDoubleLinkedList
);

DWORD
SizeDoubleLinkedList
(
	_In_ LPDOUBLE_LINKED_LIST lpDoubleLinkedList
);

#endif // !_DOUBLE_LINKED_LIST_H_
