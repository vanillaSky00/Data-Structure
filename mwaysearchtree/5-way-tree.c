#include <stdio.h>
#include <stdlib.h>

/**
 * a multiway tree has more than two children
 * max element: m^(tree_height + 1) - 1
 */
#define MAX 4 //max key

typedef struct node{
    unsigned int count;           //number of key
    int value[MAX];               //keys
    struct node* child[MAX + 1];  //children
} node;

int searchnode(int val, node* n, unsigned int* pos);
node* search(int val, node* root, unsigned int* pos);
node* insert(int val, node* root);
int insert_recursive(int val, node* n, unsigned int* pos, node** position_node);
//del()
node* create_node(int val);
void insertion_sort(int* a, unsigned int n);



//search between nodes
node* search(int val, node* root, unsigned int* pos){
    if(root == NULL) return NULL;


    if (searchnode(val, root, pos)) {
        return root;  
    } else {
        if (*pos <= root->count && root->child[*pos] != NULL) {
            return search(val, root->child[*pos], pos);
        } else {
            return NULL;  // Not found and no child to continue
        }
    }
 }


//search within a node
int searchnode(int val, node* n, unsigned int* pos){

    //if less than first key, go left of 1st key
    if (n->count == 0 || val < n->value[0]) {
        *pos = 0;
        return 0;
    }

    //search from the rightes key within a node
    for (*pos = 0; *pos < n->count; (*pos)++) {
        if (val == n->value[*pos]) {
            return 1; // found
        }
        if (val < n->value[*pos]) {
            break;
        }
    }

    return 0; // not found
}

node* insert(int val, node* root){
    if(root == NULL){
        return create_node(val);
    }

    // Check for duplicate
    unsigned int dummy;
    if (search(val, root, &dummy)) {
        return root;
    }

    unsigned int pos;
    node* position_node = NULL;
    insert_recursive(val, root, &pos, &position_node);
    if(position_node->count < MAX){
            position_node->value[position_node->count++] = val;
            insertion_sort(position_node->value, position_node->count);
    }
    else{
        //because 0 based
        //printf("add one more :%d, post: %d", val, pos);
        position_node->child[pos] = create_node(val);
    }

    return root;
}

int insert_recursive(int val, node* n, unsigned int* pos, node** position_node){
    *pos = 0;

    while(*pos < n->count && val > n->value[*pos]){
        (*pos)++;
    }

    //if the field is no node, then is where we wanna insert 
    if(n->child[*pos] == NULL){
        *position_node = n;
        return 1;
    }

    return insert_recursive(val, n->child[*pos], pos, position_node);
}

void insertion_sort(int* a, unsigned int n){
    int temp, j;
    for(int i=1; i<n; i++){
        temp = a[i];
        for(j=i-1; j>=0 && (a[j] > temp); j--){
            a[j+1] = a[j];
        }
        a[j+1] = temp;
    }
}

node* create_node(int val){
    node* n = (node*) malloc(sizeof(node));
    if (n == NULL) return NULL;
    n->count = 1;
    n->value[0] = val;
    int t = MAX + 1;
    for (int i = 0; i < t; i++) n->child[i] = NULL;
    return n;
}

/**
 * 4 cases for del
 * 1. del key with no subtree
 * 2. del key with right subtree
 * 3. del key with left subtree
 * 4. del key with both right/left subtrees
 */

 void printnode(node* n){
    printf("count: %d\n", n->count);
    for(int i=0; i<MAX; i++){
        printf("   %d", n->value[i]);
    }
    printf("\n");
    for(int i=0; i<MAX+1; i++){
        printf("%p ", (void*)n->child[i]);
    }
    printf("\n");
 }

 void printAll(node* root){
    node* q[100] = {NULL};
    int front = 0, rear = 0;

    q[rear++] = root;

    while(front < rear){
        node* curr = q[front++];
        printnode(curr);

        for(int i=0; i<= curr->count; i++){
            if(curr->child[i] != NULL){
                q[rear++] = curr->child[i];
            }
        }
    }
 }

 int main(){
    node* head = create_node(10);
    for(int i=0; i<20; i++){
        insert(i*2+3, head);
    }
    insert(34, head);
    insert(30, head);
    insert(20, head);
    insert(14, head);

    printAll(head);
    return 0;
 }