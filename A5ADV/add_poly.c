#include <stdio.h>
#include <stdlib.h>

struct Node {
    int coeff;
    int exp;
    struct Node* next;
};

struct Node* newNode(int coeff, int exp) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    if (node == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }
    node->coeff = coeff;
    node->exp = exp;
    node->next = NULL;
    return node;
}

void printPoly(struct Node* poly) {
    if (poly == NULL) {
        printf("0");
        return;
    }

    while (poly != NULL) {
        if (poly->coeff != 0) {
            if (poly->exp == 0) {
                printf("%d", poly->coeff);
            } else {
                printf("%dx", poly->coeff);
                if (poly->exp > 1) {
                    printf("^%d", poly->exp);
                }
            }
            if (poly->next != NULL && poly->next->coeff != 0) {
                printf(" + ");
            }
        }
        poly = poly->next;
    }
}

struct Node* add(struct Node* poly1, struct Node* poly2) {
    struct Node* result = NULL;
    struct Node* temp, * prev = NULL;

    while (poly1 != NULL && poly2 != NULL) {
        if (poly1->exp > poly2->exp) {
            temp = newNode(poly1->coeff, poly1->exp);
            poly1 = poly1->next;
        } else if (poly2->exp > poly1->exp) {
            temp = newNode(poly2->coeff, poly2->exp);
            poly2 = poly2->next;
        } else {
            temp = newNode(poly1->coeff + poly2->coeff, poly1->exp);
            poly1 = poly1->next;
            poly2 = poly2->next;
        }

        if (result == NULL) {
            result = temp;
        } else {
            prev->next = temp;
        }
        prev = temp;
    }

    while (poly1 != NULL) {
        prev->next = newNode(poly1->coeff, poly1->exp);
        poly1 = poly1->next;
        prev = prev->next;
    }

    while (poly2 != NULL) {
        prev->next = newNode(poly2->coeff, poly2->exp);
        poly2 = poly2->next;
        prev = prev->next;
    }

    return result;
}

struct Node* subtract(struct Node* poly1, struct Node* poly2) {
    struct Node* result = NULL;
    struct Node* temp, * prev = NULL;

    while (poly1 != NULL && poly2 != NULL) {
        if (poly1->exp > poly2->exp) {
            temp = newNode(poly1->coeff, poly1->exp);
            poly1 = poly1->next;
        } else if (poly2->exp > poly1->exp) {
            temp = newNode(-poly2->coeff, poly2->exp);
            poly2 = poly2->next;
        } else {
            temp = newNode(poly1->coeff - poly2->coeff, poly1->exp);
            poly1 = poly1->next;
            poly2 = poly2->next;
        }

        if (result == NULL) {
            result = temp;
        } else {
            prev->next = temp;
        }
        prev = temp;
    }

    while (poly1 != NULL) {
        prev->next = newNode(poly1->coeff, poly1->exp);
        poly1 = poly1->next;
        prev = prev->next;
    }

    while (poly2 != NULL) {
        prev->next = newNode(-poly2->coeff, poly2->exp);
        poly2 = poly2->next;
        prev = prev->next;
    }

    return result;
}

void freePoly(struct Node* poly) {
    struct Node* current = poly;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    struct Node* poly1 = NULL;
    struct Node* poly2 = NULL;
    struct Node* sum = NULL;
    struct Node* diff = NULL;

    poly1 = newNode(5, 2);
    poly1->next = newNode(4, 1);
    poly1->next->next = newNode(2, 0);

    poly2 = newNode(5, 1);
    poly2->next = newNode(3, 0);

    printf("First polynomial: ");
    printPoly(poly1);
    printf("\n");

    printf("Second polynomial: ");
    printPoly(poly2);
    printf("\n");

    sum = add(poly1, poly2);
    printf("Added polynomial: ");
    printPoly(sum);
    printf("\n");

    diff = subtract(poly1, poly2);
    printf("Subtracted polynomial: ");
    printPoly(diff);
    printf("\n");

    freePoly(poly1);
    freePoly(poly2);
    freePoly(sum);
    freePoly(diff);

    return 0;
}
