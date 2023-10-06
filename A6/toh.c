#include <stdio.h>

void towerOfHanoi(int n, char src, char aux, char dest) {
    if (n == 1) {
        printf("Move disk 1 from %c to %c\n", src, dest);
        return;
    }
    
    towerOfHanoi(n - 1, src, dest, aux);
    printf("Move disk %d from %c to %c\n", n, src, dest);
    towerOfHanoi(n - 1, aux, src, dest);
}

int main() {
    int numofDisks;
    printf("Enter the number of disks: ");
    scanf("%d", &numofDisks);

    printf("Steps to solve the Tower of Hanoi with %d disks:\n", numofDisks);
    towerOfHanoi(numofDisks, 'A', 'B', 'C');

    return 0;
}
