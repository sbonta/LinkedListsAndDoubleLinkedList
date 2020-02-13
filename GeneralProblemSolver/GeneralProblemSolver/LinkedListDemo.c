#include <stdio.h>

#include "Demo.h"
#include "LinkedList.h"

VOID
PrintElementLinkedList
(
	LPVOID lpData
)
{
	LONGLONG* llData = (LONGLONG*)lpData;
	printf("%lld ", *llData);
}

VOID
PrintLinkedList
(
	LPLINKED_LIST lpList
)
{
	for (DWORD i = 0; i < lpList->Size; i++)
	{
		PrintElementLinkedList(GetAtLinkedList(lpList, i));
	}
	printf("\n");
}

VOID
LinkedListDemo()
{
	LONGLONG dataSet[1000] = { 0 };
	LPLINKED_LIST lpList = CreateLinkedList();
	if (NULL == lpList)
	{
		printf("Linked List Demo Failed, memory allocation failure");
		goto Cleanup;
	}

	for (DWORD i = 0; i < 1000; i++)
	{
		dataSet[i] = i;
	}

	printf("\n\nStarting Linked List Demo\n");
	printf("Adding 10 values in list\n");
	for (DWORD i = 0; i < 10; i++)
	{
		AddLastLinkedList(lpList, &dataSet[i]);
	}
	PrintLinkedList(lpList);

	printf("Adding 101 on the third position\n");
	AddAtLinkedList(lpList, &dataSet[101], 2);
	PrintLinkedList(lpList);

	printf("Updating the value of the sixth element to 201\n");
	UpdateAtLinkedList(lpList, &dataSet[201], 5);
	PrintLinkedList(lpList);

	printf("Deleting the seventh element\n");
	DeleteAtLinkedList(lpList, 6);
	PrintLinkedList(lpList);

Cleanup:
	if (NULL != lpList)
	{
		DestroyLinkedList(&lpList);
	}
}