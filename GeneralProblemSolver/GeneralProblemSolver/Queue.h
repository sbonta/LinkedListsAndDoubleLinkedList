#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "DoubleLinkedList.h"

typedef struct _QUEUE
{
	LPDOUBLE_LINKED_LIST List;
}QUEUE,
*LPQUEUE;

LPQUEUE
CreateQueue();

VOID
PushQueue
(
	_Inout_ LPQUEUE lpQueue,
	_In_ LPVOID lpData
);

LPVOID
PeekQueue
(
	_In_ LPQUEUE lpQueue
);

VOID
PopQueue
(
	_Inout_ LPQUEUE lpQueue
);

BOOL
IsEmptyQueue
(
	_In_ LPQUEUE lpQueue
);

VOID
DestroyQueue
(
	_Inout_ LPQUEUE* lpQueue
);

#endif // !_QUEUE_H_
