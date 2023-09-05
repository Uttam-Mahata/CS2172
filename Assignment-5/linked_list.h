struct intNode {
    int element;              
    struct intNode* next;
};
// Function Prototypes
struct intNode* addIntNodeSorted(struct intNode*, int elem);
int isPresentIntNodeSorted(struct intNode*, int elem);
struct intNode* deleteIntNodeSorted(struct intNode*, int elem);
void printLL(struct intNode*);


