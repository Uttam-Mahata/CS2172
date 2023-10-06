#include <stdio.h>
#include <stdlib.h>

struct ByteNode {
    char data;
    struct ByteNode* next;
};

struct intADT {
    struct ByteNode* head;
    int size; 
    int sign; 
};

struct intADT* initializeInt() {
    struct intADT* integer = (struct intADT*)malloc(sizeof(struct intADT));
    if (integer == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }
    integer->head = NULL;
    integer->size = 0;
    integer->sign = 0;
    return integer;
}

void appendByte(struct intADT* integer, char byte) {
    struct ByteNode* newNode = (struct ByteNode*)malloc(sizeof(struct ByteNode));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }
    newNode->data = byte;
    newNode->next = NULL;

    if (integer->head == NULL) {
        integer->head = newNode;
    } else {
        struct ByteNode* current = integer->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }

    integer->size++;
}

void printDecimal(struct intADT* integer) {
    if (integer->sign == 1) {
        printf("-");
    }

    struct ByteNode* current = integer->head;
    while (current != NULL) {
        printf("%d", current->data);
        current = current->next;
    }

    printf("\n");
}

void printHexadecimal(struct intADT* integer) {
    printf("0x");
    struct ByteNode* current = integer->head;
    while (current != NULL) {
        printf("%02X", (unsigned char)current->data);
        current = current->next;
    }
    printf("\n");
}

struct intADT* addIntegers(struct intADT* integer1, struct intADT* integer2) {
    struct intADT* result = initializeInt();
    char carry = 0;

    struct ByteNode* node1 = integer1->head;
    struct ByteNode* node2 = integer2->head;

    while (node1 != NULL || node2 != NULL || carry) {
        char value1 = (node1 != NULL) ? node1->data : 0;
        char value2 = (node2 != NULL) ? node2->data : 0;

        char sum = value1 + value2 + carry;
        carry = sum / 10;

        appendByte(result, sum % 10);

        if (node1 != NULL) node1 = node1->next;
        if (node2 != NULL) node2 = node2->next;
    }

    return result;
}

struct intADT* subtractIntegers(struct intADT* integer1, struct intADT* integer2) {
    struct intADT* result = initializeInt();
    char borrow = 0;

    struct ByteNode* node1 = integer1->head;
    struct ByteNode* node2 = integer2->head;

    while (node1 != NULL || node2 != NULL) {
        char value1 = (node1 != NULL) ? node1->data : 0;
        char value2 = (node2 != NULL) ? node2->data : 0;

        char diff = value1 - value2 - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        appendByte(result, diff);

        if (node1 != NULL) node1 = node1->next;
        if (node2 != NULL) node2 = node2->next;
    }

    while (result->size > 1 && result->head->data == 0) {
        struct ByteNode* temp = result->head;
        result->head = result->head->next;
        free(temp);
        result->size--;
    }

    return result;
}

void freeInt(struct intADT* integer) {
    struct ByteNode* current = integer->head;
    while (current != NULL) {
        struct ByteNode* temp = current;
        current = current->next;
        free(temp);
    }
    free(integer);
}

int main() {
    struct intADT* num1 = initializeInt();
    struct intADT* num2 = initializeInt();

    appendByte(num1, 7);
    appendByte(num1, 5);
    appendByte(num1, 3);

    appendByte(num2, 2);
    appendByte(num2, 9);

    printf("num1 in decimal: ");
    printDecimal(num1);
    printf("num1 in hexadecimal: ");
    printHexadecimal(num1);

    printf("num2 in decimal: ");
    printDecimal(num2);
    printf("num2 in hexadecimal: ");
    printHexadecimal(num2);

    struct intADT* sum = addIntegers(num1, num2);
    printf("Sum in decimal: ");
    printDecimal(sum);

    struct intADT* diff = subtractIntegers(num1, num2);
    printf("difference in decimal: ");
    printDecimal(diff);

    freeInt(num1);
    freeInt(num2);
    freeInt(sum);
    freeInt(diff);

    return 0;
}
