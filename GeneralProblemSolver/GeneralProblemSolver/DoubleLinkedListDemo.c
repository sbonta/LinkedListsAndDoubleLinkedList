#include <stdio.h>

#include "Demo.h"
#include "DoubleLinkedList.h"


VOID
PrintElementDoubleLinkedList
(
	LPVOID lpData
)
{
	LONGLONG* llData = (LONGLONG*)lpData;
	printf("%lld ", *llData);
}

VOID
PrintDoubleLinkedList
(
	LPDOUBLE_LINKED_LIST lpList
)
{
	for (DWORD i = 0; i < lpList->Size; i++)
	{
		PrintElementDoubleLinkedList(GetAtDoubleLinkedList(lpList, i));
	}
	printf("\n");
}

VOID
DoubleLinkedListDemo()
{
	LONGLONG dataSet[1000] = { 0 };
	LPDOUBLE_LINKED_LIST lpList = CreateDoubleLinkedList();
	if (NULL == lpList)
	{
		printf("Double Linked List Demo Failed, memory allocation failure !\n");
		goto Cleanup;
	}
	

	for (DWORD i = 0; i < 1000; i++)
	{
		dataSet[i] = i;
	}

	printf("\n\nStarting Double Linked List Demo \n");
	printf("Adding 10 values in list\n");
	for (DWORD i = 0; i < 10; i++)
	{
		AddLastDoubleLinkedList(lpList, &dataSet[i]);
	}
	PrintDoubleLinkedList(lpList);

	printf("Adding 101 on the third position\n");
	AddAtDoubleLinkedList(lpList, &dataSet[101], 2);
	PrintDoubleLinkedList(lpList);

	printf("Updating the value of the sixth element to 201\n");
	UpdateAtDoubleLinkedList(lpList, &dataSet[201], 5);
	PrintDoubleLinkedList(lpList);

	printf("Deleting the seventh element\n");
	DeleteAtDoubleLinkedList(lpList, 6);
	PrintDoubleLinkedList(lpList);

Cleanup:
	if (NULL != lpList)
	{
		DestroyDoubleLinkedList(&lpList);
	}
}