#ifndef _STACK_H_
#define _STACK_H_

#include "DoubleLinkedList.h"

typedef struct _STACK
{
	LPDOUBLE_LINKED_LIST List;
}STACK,
*LPSTACK;

LPSTACK
CreateStack();

VOID
PushStack
(
	_Inout_ LPSTACK lpStack,
	_In_ LPVOID lpData
);

LPVOID
PeekStack
(
	_In_ LPSTACK lpStack
);

VOID
PopStack
(
	_Inout_ LPSTACK lpStack
);

BOOL
IsEmptyStack
(
	_In_ LPSTACK lpStack
);

VOID
DestroyStack
(
	_Inout_ LPSTACK* lpStack
);

#endif // !_STACK_H_
