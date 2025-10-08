
//1. Linear Search with Count

#include <stdio.h>

int main() {
    int n, num, count = 0;
    printf("Enter size of array: ");
    scanf("%d", &n);
    int a[n];
    printf("Enter elements: ");
    for(int i = 0; i < n; i++) scanf("%d", &a[i]);

    printf("Enter number to search: ");
    scanf("%d", &num);

    printf("Found at positions: ");
    for(int i = 0; i < n; i++)
        if(a[i] == num) {
            printf("%d ", i);
            count++;
        }
    printf("\nTotal Count = %d", count);
}


//2. Binary Search (Iterative)

#include <stdio.h>

int main() {
    int n, key, mid, low = 0, high;
    printf("Enter size of sorted array: ");
    scanf("%d", &n);
    int a[n];
    printf("Enter sorted elements: ");
    for(int i = 0; i < n; i++) scanf("%d", &a[i]);
    high = n - 1;

    printf("Enter number to search: ");
    scanf("%d", &key);

    while(low <= high) {
        mid = (low + high) / 2;
        printf("low=%d high=%d mid=%d\n", low, high, mid);
        if(a[mid] == key) { printf("Found at index %d", mid); return 0; }
        else if(a[mid] < key) low = mid + 1;
        else high = mid - 1;
    }
    printf("Not found");
}


//3. Jump Search vs Linear Search (Time Comparison)

#include <stdio.h>
#include <math.h>
#include <time.h>

int linearSearch(int a[], int n, int x) {
    for(int i = 0; i < n; i++)
        if(a[i] == x) return i;
    return -1;
}

int jumpSearch(int a[], int n, int x) {
    int step = sqrt(n), prev = 0;
    while(a[(step < n ? step : n) - 1] < x) {
        prev = step; step += sqrt(n);
        if(prev >= n) return -1;
    }
    for(int i = prev; i < step && i < n; i++)
        if(a[i] == x) return i;
    return -1;
}

int main() {
    int n, x;
    printf("Enter size of sorted array: ");
    scanf("%d", &n);
    int a[n]; for(int i=0;i<n;i++) a[i]=i+1;
    printf("Enter number to search: "); scanf("%d",&x);

    clock_t t1=clock();
    linearSearch(a,n,x);
    clock_t t2=clock();
    jumpSearch(a,n,x);
    clock_t t3=clock();

    printf("Linear Search Time: %.6f\n", (double)(t2-t1)/CLOCKS_PER_SEC);
    printf("Jump Search Time: %.6f\n", (double)(t3-t2)/CLOCKS_PER_SEC);
}


//4. Interpolation vs Binary Search (Step Count)

#include <stdio.h>

int interpolationSearch(int a[], int n, int x) {
    int low = 0, high = n - 1, steps = 0;
    while(low <= high && x >= a[low] && x <= a[high]) {
        steps++;
        int pos = low + ((x - a[low]) * (high - low)) / (a[high] - a[low]);
        if(a[pos] == x) return steps;
        if(a[pos] < x) low = pos + 1;
        else high = pos - 1;
    }
    return steps;
}

int binarySearch(int a[], int n, int x) {
    int low = 0, high = n - 1, steps = 0;
    while(low <= high) {
        steps++;
        int mid = (low + high)/2;
        if(a[mid] == x) return steps;
        if(a[mid] < x) low = mid + 1;
        else high = mid - 1;
    }
    return steps;
}

int main() {
    int n, x;
    printf("Enter array size: ");
    scanf("%d", &n);
    int a[n];
    for(int i = 0; i < n; i++) a[i] = i + 1;
    printf("Enter number to search: ");
    scanf("%d", &x);

    printf("Binary Steps: %d\n", binarySearch(a,n,x));
    printf("Interpolation Steps: %d", interpolationSearch(a,n,x));
}


//5. Exponential Search

#include <stdio.h>

int binarySearch(int a[], int l, int r, int x) {
    while(l <= r) {
        int mid = (l + r) / 2;
        if(a[mid] == x) return mid;
        if(a[mid] < x) l = mid + 1;
        else r = mid - 1;
    }
    return -1;
}

int exponentialSearch(int a[], int n, int x) {
    if(a[0] == x) return 0;
    int i = 1;
    while(i < n && a[i] <= x) i *= 2;
    return binarySearch(a, i/2, (i < n ? i : n-1), x);
}

int main() {
    int n, x;
    printf("Enter size of sorted array: ");
    scanf("%d", &n);
    int a[n]; for(int i = 0; i < n; i++) a[i] = i + 1;
    printf("Enter number to search: ");
    scanf("%d", &x);

    int idx = exponentialSearch(a, n, x);
    if(idx != -1) printf("Found at index %d", idx);
    else printf("Not found");
}


//6. Bubble Sort with Optimization

#include <stdio.h>

void bubbleSort(int a[], int n) {
    int passes = 0;
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++)
            if(a[j] > a[j+1]) {
                int t=a[j]; a[j]=a[j+1]; a[j+1]=t;
            }
        passes++;
    }
    printf("Normal Bubble Passes: %d\n", passes);
}

void optimizedBubble(int a[], int n) {
    int passes = 0, swapped;
    for(int i = 0; i < n-1; i++) {
        swapped = 0;
        for(int j = 0; j < n-i-1; j++)
            if(a[j] > a[j+1]) {
                int t=a[j]; a[j]=a[j+1]; a[j+1]=t;
                swapped = 1;
            }
        passes++;
        if(!swapped) break;
    }
    printf("Optimized Bubble Passes: %d\n", passes);
}

int main() {
    int a[] = {5, 2, 9, 1, 5, 6}, n = 6;
    bubbleSort(a, n);
    int b[] = {5, 2, 9, 1, 5, 6};
    optimizedBubble(b, n);
}


//7. Selection Sort and Stability Check

#include <stdio.h>

struct Student { int roll, marks; };

void selectionSort(struct Student s[], int n) {
    for(int i=0;i<n-1;i++){
        int min=i;
        for(int j=i+1;j<n;j++)
            if(s[j].marks < s[min].marks)
                min=j;
        if(min!=i){
            struct Student t=s[i]; s[i]=s[min]; s[min]=t;
        }
    }
}

int main(){
    struct Student s[4]={{1,80},{2,70},{3,70},{4,90}};
    selectionSort(s,4);
    printf("After Sorting (roll, marks):\n");
    for(int i=0;i<4;i++)
        printf("%d %d\n",s[i].roll,s[i].marks);
    printf("\nNote: Order of same marks changed → Selection Sort is not stable.");
}


//8. Insertion Sort (Card Analogy)

#include <stdio.h>

int main(){
    int a[]={5,3,4,1,2},n=5;
    for(int i=1;i<n;i++){
        int key=a[i],j=i-1;
        while(j>=0 && a[j]>key){
            a[j+1]=a[j];
            j--;
        }
        a[j+1]=key;
        printf("Step %d: ",i);
        for(int k=0;k<n;k++) printf("%d ",a[k]);
        printf("\n");
    }
}


//9. Merge Sort with Divide-and-Conquer

#include <stdio.h>

void merge(int a[], int l, int m, int r) {
    int n1=m-l+1, n2=r-m, L[n1], R[n2];
    for(int i=0;i<n1;i++) L[i]=a[l+i];
    for(int j=0;j<n2;j++) R[j]=a[m+1+j];
    int i=0,j=0,k=l;
    while(i<n1 && j<n2) a[k++]=(L[i]<=R[j])?L[i++]:R[j++];
    while(i<n1) a[k++]=L[i++];
    while(j<n2) a[k++]=R[j++];
    printf("Merged [%d..%d]\n", l, r);
}

void mergeSort(int a[], int l, int r){
    if(l<r){
        int m=(l+r)/2;
        mergeSort(a,l,m);
        mergeSort(a,m+1,r);
        merge(a,l,m,r);
    }
}

int main(){
    int a[]={9,4,7,3,1,6},n=6;
    mergeSort(a,0,n-1);
    printf("Sorted: ");
    for(int i=0;i<n;i++) printf("%d ",a[i]);
}


//10. Quick Sort and Worst-Case Comparison

#include <stdio.h>

int count = 0;

int partition(int a[], int low, int high) {
    int pivot = a[low], i = low + 1, j = high, t;
    while (i <= j) {
        while (i <= high && a[i] <= pivot) { i++; count++; }
        while (a[j] > pivot) { j--; count++; }
        if (i < j) { t = a[i]; a[i] = a[j]; a[j] = t; }
    }
    t = a[low]; a[low] = a[j]; a[j] = t;
    return j;
}

void quickSort(int a[], int low, int high) {
    if (low < high) {
        int p = partition(a, low, high);
        quickSort(a, low, p - 1);
        quickSort(a, p + 1, high);
    }
}

int main() {
    int a1[] = {3, 6, 2, 7, 1, 9}, n = 6;
    count = 0;
    quickSort(a1, 0, n - 1);
    printf("Random array comparisons: %d\n", count);

    int a2[] = {1, 2, 3, 4, 5, 6};
    count = 0;
    quickSort(a2, 0, n - 1);
    printf("Sorted array comparisons: %d\n", count);
    printf("\nExplanation: Sorted array causes unbalanced partitions → worst case O(n²).");
}


//11. Fixed-Size Stack – Function Call Simulation

#include <stdio.h>
#define SIZE 5

int stack[SIZE], top = -1;

void push(int addr) {
    if (top == SIZE - 1) { printf("Stack Overflow!\n"); return; }
    stack[++top] = addr;
    printf("Pushed return address %d\n", addr);
}

void pop() {
    if (top == -1) { printf("Stack Underflow!\n"); return; }
    printf("Returned from address %d\n", stack[top--]);
}

void display() {
    printf("Stack: ");
    for (int i = top; i >= 0; i--) printf("%d ", stack[i]);
    printf("\n");
}

int main() {
    push(100); display();
    push(200); display();
    pop(); display();
    pop(); display();
    pop();
}


//12. Dynamic Stack – Browser History Tracker

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char url[50];
    struct Node* next;
};
struct Node* top = NULL;

void push(char* site) {
    struct Node* new = malloc(sizeof(struct Node));
    strcpy(new->url, site);
    new->next = top;
    top = new;
    printf("Visited: %s\n", site);
}

void pop() {
    if (!top) { printf("No more history to go back!\n"); return; }
    printf("Back from: %s\n", top->url);
    struct Node* temp = top;
    top = top->next;
    free(temp);
}

void show() {
    printf("History Stack: ");
    for (struct Node* p = top; p; p = p->next)
        printf("%s ", p->url);
    printf("\n");
}

int main() {
    push("google.com"); show();
    push("youtube.com"); show();
    push("github.com"); show();
    pop(); show();
    pop(); show();
    pop(); pop();
}


//13. Circular Buffer Stack – Memory-Efficient Stack

#include <stdio.h>
#define SIZE 5

int stack[SIZE], top = -1;

void push(int x) {
    top = (top + 1) % SIZE;
    stack[top] = x;
    printf("Pushed %d (Top=%d)\n", x, top);
}

void show() {
    printf("Buffer: ");
    for (int i = 0; i < SIZE; i++) printf("%d ", stack[i]);
    printf("\n");
}

int main() {
    for (int i = 1; i <= 7; i++) {
        push(i);
        show();
        if (i > SIZE) printf("** Overwriting oldest data **\n");
    }
}


//14. Priority Stack – Task Scheduler

#include <stdio.h>
#include <stdlib.h>

struct Task {
    int id, priority;
    struct Task* next;
};
struct Task* top = NULL;

void push(int id, int p) {
    struct Task* t = malloc(sizeof(struct Task));
    t->id = id; t->priority = p; t->next = top;
    top = t;
    printf("Task %d (Priority %d) added.\n", id, p);
}

void pop() {
    if (!top) { printf("No tasks left!\n"); return; }
    struct Task *maxPrev = NULL, *maxNode = top, *prev = NULL, *curr = top;
    while (curr) {
        if (curr->priority > maxNode->priority)
            maxNode = curr, maxPrev = prev;
        prev = curr;
        curr = curr->next;
    }
    if (maxPrev) maxPrev->next = maxNode->next;
    else top = top->next;
    printf("Executed Task %d (Priority %d)\n", maxNode->id, maxNode->priority);
    free(maxNode);
}

void show() {
    printf("Tasks: ");
    for (struct Task* p = top; p; p = p->next)
        printf("[%d:%d] ", p->id, p->priority);
    printf("\n");
}

int main() {
    push(1,2); push(2,5); push(3,3);
    show(); pop(); show(); pop(); pop(); pop();
}


//15. Undo Stack – Text Editor Feature

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char text[100];
    struct Node* next;
};
struct Node* top = NULL;

void save(char* doc) {
    struct Node* n = malloc(sizeof(struct Node));
    strcpy(n->text, doc);
    n->next = top;
    top = n;
    printf("Saved: %s\n", doc);
}

void undo() {
    if (!top) { printf("Nothing to undo!\n"); return; }
    printf("Undo: Restored previous version: %s\n", top->text);
    struct Node* temp = top;
    top = top->next;
    free(temp);
}

int main() {
    save("Hello");
    save("Hello World");
    save("Hello World!!!");
    undo();
    undo();
    undo();
    undo();
}


//16. Double Stack – Two Stacks in One Array

#include <stdio.h>
#define SIZE 10

int arr[SIZE], top1 = -1, top2 = SIZE;

void push1(int x) {
    if (top1 + 1 == top2) { printf("Overflow!\n"); return; }
    arr[++top1] = x;
}

void push2(int x) {
    if (top2 - 1 == top1) { printf("Overflow!\n"); return; }
    arr[--top2] = x;
}

void pop1() {
    if (top1 == -1) { printf("Stack1 Underflow!\n"); return; }
    printf("Popped from Stack1: %d\n", arr[top1--]);
}

void pop2() {
    if (top2 == SIZE) { printf("Stack2 Underflow!\n"); return; }
    printf("Popped from Stack2: %d\n", arr[top2++]);
}

void show() {
    printf("Array: ");
    for (int i = 0; i < SIZE; i++) printf("%d ", arr[i]);
    printf("\nTop1=%d Top2=%d\n", top1, top2);
}

int main() {
    push1(10); push1(20);
    push2(99); push2(88);
    show();
    pop1(); pop2(); show();
}


