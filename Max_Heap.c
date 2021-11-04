//author Ertuğrul Demir - ID: 260201059

#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <math.h>
#include <string.h>

struct node {
    int data;
    struct node* left;
    struct node* right;
} ;

void maxheapify(int a[], int i, int heapsize)  //https://www.sanfoundry.com/c-program-to-implement-binary-heap/
{
    int temp, largest, left, right, k;
    left = (2*i+1);
    right = ((2*i)+2);
    if (left >= heapsize)
        return;
    else {
        if (left < (heapsize) && a[left] > a[i])
            largest = left;
        else
            largest = i;
        if (right < (heapsize) && a[right] > a[largest])
            largest = right;
        if (largest != i) {
            temp = a[i];
            a[i] = a[largest];
            a[largest] = temp;
            maxheapify(a, largest, heapsize);
        }
    }
}
int* buildmaxheap(int a[], int n)
{
    int heapsize = n;
    int j;
    for (j = n/2; j >= 0; j--) {
        maxheapify(a, j, heapsize);
    }
    return a;
}
struct node * connect_node (int index, struct node* x, int arr[], int arraySize){ //by myself

    struct node *newNodeRight = malloc(sizeof (struct node));  //create new node
    struct node *newNodeLeft = malloc(sizeof (struct node));
    x->right =malloc(sizeof (struct node));
    x->left = malloc(sizeof (struct node));
    x->data = arr[index];
    if (index*2+1 < arraySize){ //connect children to their parent recursively
        x->right = connect_node(index*2+1,newNodeRight,arr,arraySize);}
    if (index*2+2 < arraySize){
        x->left = connect_node(index*2+2,newNodeLeft,arr,arraySize);}

    return x; //return itself
}

void printCurrentLevel(struct node* root, int level,FILE* writeFile); //https://www.geeksforgeeks.org/level-order-tree-traversal/
int height(struct node* node);
struct node* newNode(int data);

/* Function to print level order traversal a tree*/
void printLevelOrder(struct node* root,FILE* writeFile)
{
    int h = height(root);
    int i;
    for (i = 1; i <= h; i++)
        printCurrentLevel(root, i,writeFile);
}

/* Print nodes at a current level */
void printCurrentLevel(struct node* root, int level,FILE* writeFile)
{
    if (root == NULL)
        return;
    if (level == 1)
        fprintf(writeFile,"%d ", root->data);
    else if (level > 1) {
        printCurrentLevel(root->left, level - 1,writeFile);
        printCurrentLevel(root->right, level - 1,writeFile);
    }
}

/* Compute the "height" of a tree -- the number of
    nodes along the longest path from the root node
    down to the farthest leaf node.*/
int height(struct node* node)
{

    if (node == NULL || node->data > 10000 || node->data == 0)
        return 0;
    else {
        /* compute the height of each subtree */
        return height(node->right) + 1;

    }
}


int main() {
    //Initialization part
    int size = pow(2,24) ;
    int digit_of_number_plus_space = 5; //ex 1000_2001_1234   -> _ means space
    //int size = 20;
    int * array = malloc(size * sizeof(int));
    int * maxHeapArray = malloc(size * sizeof(int));
    struct node *num =malloc( sizeof (struct node));


    //File read then store it in array
    FILE * fp;
    fp = fopen ("C:\\Users\\Ertugrul Demir\\Desktop\\Desktop\\CLion_Project\\list(1).txt", "r");

    if(fp == NULL) {
        printf("error in opening file\n");
    }
    char *line = malloc(size * digit_of_number_plus_space);
    while( fgets ( line, size * digit_of_number_plus_space, fp ) != NULL ){}
    char *token = strtok(line, " ");
    array[0] = atoi(token);
    int j = 1;
    while (token != NULL)
    {
        token = strtok(NULL, " ");
        array[j] = atoi(token);
        j++;
    }

    fclose(fp);

    //Build Max Heap and time calculation
    //clock
    clock_t t;
    t = clock();
    maxHeapArray = buildmaxheap(array,size);
    t = clock()-t;
    double time_taken = ((double )t)/CLOCKS_PER_SEC;
    printf("This process took %f seconds!",time_taken);
    //clock

    //Connect Node
    num = connect_node(0,num,maxHeapArray,size);

    //Traverse with BFS and write a file
    FILE *writeF;
    writeF = fopen("C:\\Users\\Ertugrul Demir\\Desktop\\Desktop\\CLion_Project\\write_list.txt","w+");

    printLevelOrder(num,writeF);


    //close and free
    fclose(writeF);
    free(array);
    free(num);

    return 0;
}
