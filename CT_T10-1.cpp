#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int d) : data(d), next(0) {}
};

void insertNode(Node*& head, int data) {
    Node* newNode = new Node(data);
    if (head == 0) { 
        head = newNode;
        return;
    }
    Node* current = head;
    while (current->next != 0) { 
        current = current->next;
    }
    current->next = newNode; 
}

void printList(Node* head) {
    if (head == 0) {
        cout << "Danh sach rong" << endl;
        return;
    }
    Node* t = head;
    while (t != 0) {
    	cout << t->data << " ";
        t = t->next;
    }
    cout << "NULL" << endl;
}

// Xoa dau danh sach
void deleteAtHead(Node*& head) {
    if (head == 0) {
        cout << "Danh sach khong the xoa" << endl;
        return;
    }
    Node* t = head;
    head = head->next;
    delete t;
}

// Xoa cuoi sanh sach
void deleteAtTail(Node*& head) {
    if (head == 0) {
        cout << "Danh sach khong the xoa" << endl;
        return;
    }
    if (head->next == 0) {
        delete head;
        head = 0;
        return;
    }
    Node* temp = head;
    while (temp->next->next != 0) {
        temp = temp->next;
    }
    delete temp->next;
    temp->next = 0;
}

// Xoa node cho truoc
void deleteAfterNode(Node* pNode) {
    if (pNode == 0 || pNode->next == 0) {
        cout << "Khong co node cho truoc" << endl;
        return;
    }
    Node* temp = pNode->next;
    pNode->next = temp->next;
    delete temp;
}

// Hàm chính
int main() {
    Node* head = 0;
	
	int n,d;
	cout << "So node duoc nhap: "; cin >> n;
	for (int i=0; i<n; i++)
	{
		cout << "node thu " << i+1 << " :";
		cin >> d;
		insertNode(head, d);
	}

    cout << "Danh sach ban dau: ";
    printList(head);

    cout << "\nXoa node dau danh sach\n";
    deleteAtHead(head);
    printList(head);

    cout << "\nXoa node cuoi danh sach\n";
    deleteAtTail(head);
    printList(head);

    cout << "\nXoa node cho truoc\n";
    int k;
    cout << "Data Node muon xoa: "; cin >> k;
    Node* current = head;
    int kt=0;
    while (current != 0) 
	{
		if (current->data == k)
		{
			kt=1;
			break;
		}
		current = current->next;
	}
	if (kt==0) {
        cout << "Khong tim thay node co gia tri: " << k << endl;
    } else if (current->next == 0) {
        cout << "Node co gia tri " << k << " la node cuoi khong the xoa nod sau no" << endl;
    } else {
        deleteAfterNode(current);
        cout << "Danh sach sau khi xoa node sau node co gia tri " << k << ": ";
        printList(head);
    }

    return 0;
}

