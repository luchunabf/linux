#include<stdio.h>
void Swap(int*a, int*b)
{
  int tmp = 0;
  tmp = *a;
  *a = *b;
  *b = tmp;
}
void Bubblesort( int*arr, int size )
{
  int i = 0;
  for(i = 0; i < size-1; i++)
  {
    int Flag = 0;
    int j = 0;
    for(j = 0;j < size-1-i; j++)
    {
        if(arr[j] > arr[j+1])
        {
          Swap(&arr[j],&arr[j+1]);
          Flag = 1;
        }
    }
    if(Flag == 0)
      return;
  }
}
int main()
{


  int arr[9] = { 87, 94, 66, 78, 45, 39, 76, 8, 10 };
  int size = 9;
  Bubblesort(arr,size);
  int i = 0;
  for(i = 0; i < size; i++)
  {
    printf("%d ", arr[i]);
  }
  printf("\n");
  return 0;
}
