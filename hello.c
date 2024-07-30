
#include <stdio.h>
void func(/*....*/) { // ....
}
int main() {
int arr[5] = {1, 2, 3, 4, 5}; func(arr, 5);
for (int i = 0; i < 5; i++)
printf("%d ", arr[i]+1); return 0;
}