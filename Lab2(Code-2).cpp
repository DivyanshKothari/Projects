#include<iostream>
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
ListNode* rotateByK(ListNode* head, int k) {
        if(head == nullptr || head->next == nullptr || k == 0)
            return head;
        ListNode*temp=head;
        int count=1;
        ListNode*tail=head;
        while(tail->next) {
            count++;
            tail=tail->next;
        }
        k%=count;
        if(k==0) return head;
        count=count-k;
        
        while(--count){
            temp=temp->next;
        }
        tail->next=head;
        head=temp->next;
        temp->next=nullptr;
        
    return head;}

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
    cout<<"Before Rotating:";
    print(head);
    int k;
    cout<<"Enter k:";
    cin>>k;
    head=rotateByK(head,k);
    cout<<"After Rotating:";
    print(head);
    return 0;
}