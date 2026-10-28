#include<iostream>
#include <ctime>
using namespace std;
struct ListNode {
    int data;           
    ListNode* next;       

    ListNode(int value) {
        data = value;
        next = nullptr; 
    }
};
void print(ListNode* head){
    while(head != nullptr){
        cout << head->data;
        if(head->next) cout << "->";
        head = head->next;
    }
    cout << endl;
}
void deleteNode(ListNode *x){
       if (x == nullptr || x->next == nullptr) {
        cout << "Cannot delete last node.\n";
        return;
    }
    x->data=x->next->data;
    ListNode*temp =x->next;
    x->next=x->next->next;
    temp->next=nullptr;
    delete temp;
return ;}
int main(){
    int n;
    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    cout<<"Enter number of elements:";
    cin>>n;
   for (int i = 0; i < n; i++) {
    int value;
    cout << "Enter value for element " << (i + 1) << ": ";
    cin >> value;
    ListNode* newNode = new ListNode(value);
    if(head == nullptr){
        head = tail = newNode;
    }
    else{
        tail->next = newNode;
        tail = newNode;
    }
}
    cout<<"Before Deletion:";
    print(head);
    int xValue;
    cout << "\nEnter value of node X to delete: ";
    cin >> xValue;
    
    ListNode* X = head;
    while (X != NULL && X->data != xValue)
        X = X->next;

    if (X == NULL) {
        cout << "Node not found.\n";
    } else {
        clock_t start = clock();
        deleteNode(X);
        clock_t end = clock();
        cout << "List after deletion:"<<endl;
        print(head);
        double time_taken = double(end - start) / CLOCKS_PER_SEC;
        cout << "Time taken for deletion: "
        << time_taken << " seconds" << endl;
    }   
    return 0;
}

