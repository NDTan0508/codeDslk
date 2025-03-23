#include <iostream>
using namespace std;

// =======================
//  DANH SACH LIEN KET DON
// =======================
struct NodeSingly {//tạo node mới
    int data;
    NodeSingly* next;
};

struct SinglyLinkedList {//tạo dslk đơn
    NodeSingly* head;
    SinglyLinkedList() { head = NULL; }
};

void insertSingly(SinglyLinkedList &list, int value, int position = -1) {//hàm chèn một node vào sau vị trí k
    NodeSingly* newNode = new NodeSingly{value, NULL};//tạo node mới
    if (position == 1 || !list.head) {//nếu pos=1 hoặc list.head=NULL thì chèn newnode vào đầu ds
        newNode->next = list.head;
        list.head = newNode;
        return;
    }
    NodeSingly* temp = list.head;
    if (position == -1) {
        while (temp->next) temp = temp->next;//nếu pos=-1 lặp đến khi nào temp->next=NULL thì dừng, khi đó temp là node cuối ds
    } else {
        for (int i = 1; temp->next && i < position; i++) temp = temp->next;//lặp cho temp chạy đến vị trí thứ pos
    }
    newNode->next = temp->next;//chèn temp vào sau vị trí pos
    temp->next = newNode;
}
//in ds
void printListSingly(SinglyLinkedList list) {
    NodeSingly* temp = list.head;
    while (temp) {
        cout<< temp->data << "->";
        temp = temp->next;
    }
    cout << "NULL\n";
}
// xoa theo gia tri (khong toi uu vi neu 1 danh sach co 2 phan tu trung nhau thi chi xoa ptu dau tien
    void deleteByValueSingly(SinglyLinkedList &list, int value) {
    if (!list.head) return;
    if (list.head->data == value) {
        NodeSingly* temp = list.head;
        list.head = list.head->next;
        delete temp;
        return;
    }
    NodeSingly* temp = list.head;
    while (temp->next && temp->next->data != value) temp = temp->next;
    if (!temp->next) return;
    NodeSingly* toDelete = temp->next;
    temp->next = temp->next->next;
    delete toDelete;
    }

//xoa theo vi tri
void deleteByValueSingly(SinglyLinkedList &list, int position) {
    if (!list.head) return;//nếu ds head=Null thì dừng
    NodeSingly* temp = list.head;
    if (position == 1) {//pos=1 xóa node đầu ds
        list.head = temp->next;
        delete temp;
        return;
    }
    for (int i = 1; temp->next && i < position-1; i++) temp = temp->next;//cho temp chạy đến trước node pos
    if (!temp->next) return;
    NodeSingly* toDelete = temp->next;//gán node cần xóa cho todelete
    temp->next = temp->next->next;//trỏ node trước todelete đến node sau todelete rồi xóa todelete
    delete toDelete;
}
//đếm
int countNodesSingly(SinglyLinkedList list) {
    int count = 0;
    NodeSingly* temp = list.head;
    while (temp) {//lặp đến khi nào temp=null dừng
        count++;
        temp = temp->next;
    }
    return count;
}

// =======================
//  DANH SACH LIEN KET KEP
// =======================
struct NodeDoubly {
    int data;
    NodeDoubly* prev;
    NodeDoubly* next;
};

struct DoublyLinkedList {
    NodeDoubly* head;
    DoublyLinkedList() { head = NULL; }
};

void insertDoubly(DoublyLinkedList &list, int value, int position = -1) {
    NodeDoubly* newNode = new NodeDoubly{value, NULL, NULL};
    if (position == 1 || !list.head) {//nếu pos=1 hoặc list.head=NULL thì chèn newnode vào đầu ds
        newNode->next = list.head;
        if (list.head) list.head->prev = newNode;//nếu list.head khác rỗng thì gán head->pre cho newnode
        list.head = newNode;
        return;
    }
    NodeDoubly* temp = list.head;
    if (position == -1) {//nếu không điền pos tương đương pos=-1 thì chèn vào cuối ds
        while (temp->next) temp = temp->next;
    } else {
        for (int i = 1; temp->next && i < position; i++) temp = temp->next;//lặp để temp đến vị trí pos
    }
    newNode->next = temp->next;
    newNode->prev = temp;
    if (temp->next) temp->next->prev = newNode;
    temp->next = newNode;
}
//in
void printListDoubly(DoublyLinkedList list) {
    NodeDoubly* temp = list.head;
    while (temp) {
        cout << temp->data << " <-> ";
        temp = temp->next;
    }
    cout << "NULL\n";
    }

    void deleteByValueDoubly(DoublyLinkedList &list, int value) {
    if (!list.head) return;
    NodeDoubly* temp = list.head;
    while (temp && temp->data != value) temp = temp->next;
    if (!temp) return;
    if (temp->prev) temp->prev->next = temp->next;
    if (temp->next) temp->next->prev = temp->prev;
    if (temp == list.head) list.head = temp->next;
    delete temp;
    }

//xóa 1 phần tử vị trí thứ pos
//vì dslk kép có 2 chiều nên để ý phải có tới có lui
void deleteByValueDoubly(DoublyLinkedList &list, int position) {
    if (!list.head) return;
    NodeDoubly* temp = list.head;
    if (position == 1) {//nếu pos=1 xóa phần tử đầu ds
        list.head = temp->next;//đẩy head qua node thứ 2
        if (list.head) list.head->prev = NULL;
        delete temp;
        return;
    }
    for (int i = 1; temp->next && i < position-1; i++) temp = temp->next;//lặp để temp đến vị trí pos-1
    if (!temp->next) return;
    NodeDoubly* toDelete = temp->next;//cho todelete ở vị trí temp+1 tức là vị trí pos
    temp->next = toDelete->next;
    if (toDelete->next) toDelete->next->prev = temp;
    delete toDelete;
}
//đếm
int countNodesDoubly(DoublyLinkedList list) {
    int count = 0;
    NodeDoubly* temp = list.head;
    while (temp) {
        count++;
        temp = temp->next;
    }
    return count;
}

// =======================
//  STACK (NGAN XEP)
// =======================
struct Stack {
    NodeSingly* top;
    Stack() { top = NULL; }
};

//đẩy 1 giá trị vào ds
void push(Stack &s, int value) {
    NodeSingly* newNode = new NodeSingly{value, s.top};
    s.top = newNode;
}
//lấy giá trị đươc đưa vào cuối cùng ra trước
void pop(Stack &s) {
    if (!s.top) return;
    NodeSingly* temp = s.top;
    s.top = s.top->next;
    delete temp;
}

void printStack(Stack s) {
    NodeSingly* temp = s.top;
    while (temp) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << "\n";
}

int countStack(Stack s) {
    int count = 0;
    NodeSingly* temp = s.top;
    while (temp) {
        count++;
        temp = temp->next;
    }
    return count;
}

// =======================
//  QUEUE (HANG DOI)
// =======================
struct Queue {
    NodeSingly* front;
    NodeSingly* rear;
    Queue() { front = rear = NULL; }
};

void enqueue(Queue &q, int value) {//thêm 1 phần từ vào cuối ds
    NodeSingly* newNode = new NodeSingly{value, NULL};
    if (!q.rear) {
        q.front = q.rear = newNode;
        return;
    }
    q.rear->next = newNode;
    q.rear = newNode;
}

void dequeue(Queue &q) {//lầy ra phần tử đầu danh sách
    if (!q.front) return;
    NodeSingly* temp = q.front;
    q.front = q.front->next;
    if (!q.front) q.rear = NULL;
    delete temp;
}

void printQueue(Queue q) {
    NodeSingly* temp = q.front;
    while (temp) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << "\n";
}

int countQueue(Queue q) {
    int count = 0;
    NodeSingly* temp = q.front;
    while (temp) {
        count++;
        temp = temp->next;
    }
    return count;
}

// =======================
//  HAM MAIN DE TEST CAC CHUC NANG
// =======================
int main() {
    int n, value,position;
    //  DANH SACH LIEN KET DON
    //tao dslk don
    SinglyLinkedList sList;
    cout << "Nhap so luong phan tu danh sach lien ket don: ";
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cout << "Nhap gia tri thu " << i << ": ";
        cin >> value;
        insertSingly(sList, value); //chen moi gia tri nhap tu ban phim vao cuoi danh sach (vi khong nhap position nen mac dinh no la -1)
    }
    //in dslk vua tao ra man hinh
    printListSingly(sList);
    
    //chen mot gia tri vao vi tri bat ki trong dslk don
    cout << "Nhap gia tri va vi tri muon chen vao danh sach lien ket don: ";
    cin >> value >> position;
    insertSingly(sList, value, position);
    printListSingly(sList);

    //xoa mot gia tri trong dslk don
    cout << "Nhap vi tri muon xoa khoi danh sach lien ket don: ";
    cin >> position;
    deleteByValueSingly(sList, position);
    printListSingly(sList);

    //đếm số phần tử của dslk đơn
    cout<<"So phan tu cua danh sach lien ket don: "<<countNodesSingly(sList)<<"\n";
    
    //tao danh sach lien ket kep
    DoublyLinkedList dList;
    cout << "Nhap so luong phan tu danh sach lien ket kep: ";
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cout << "Nhap gia tri thu " << i << ": ";
        cin >> value;
        insertDoubly(dList, value);
    }
    printListDoubly(dList);
    
    //chèn một giá trị vào vị trí bất kì vào ds
    cout << "Nhap gia tri va vi tri muon chen vao danh sach lien ket kep: ";
    cin >> value >> position;
    insertDoubly(dList, value, position);
    printListDoubly(dList);
    
    //xóa phần tử vị trí X của danh sách
    cout << "Nhap vi tri muon xoa khoi danh sach lien ket kep: ";
    cin >> position;
    deleteByValueDoubly(dList, position);
    printListDoubly(dList);
    
    //đếm số phần tử của danh sách
    cout<<"So phan tu cua danh sach lien ket kep: "<<countNodesDoubly(dList)<<"\n";
    
    //tạo stack
    Stack s;
    cout << "Nhap so luong phan tu stack: ";
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cout << "Nhap gia tri thu " << i << ": ";
        cin >> value;
        push(s, value);
    }
    printStack(s);
    
    //chèn 1 giá trị vào đầu danh sách 
    cout << "Nhap gia tri muon day vao stack: ";
    cin >> value;
    push(s, value);
    printStack(s);
    //lấy phần tử đầu danh sách ra (vào sau ra trước)
    cout << "danh sach sau khi lay ra 1 phan tu cua stack ";
    pop(s);
    printStack(s);
    cout<<"So phan tu cua stack: "<<countStack(s)<<"\n";//đếm số phần tử của stack
    
    //tạo queue
    Queue q;
    cout << "Nhap so luong phan tu queue: ";
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cout << "Nhap gia tri thu " << i << ": ";
        cin >> value;
        enqueue(q, value);
    }
    printQueue(q);
    //chèn 1 giá trị vào cuối ds
    cout << "Nhap gia tri muon them vao queue: ";
    cin >> value;
    enqueue(q, value);
    printQueue(q);
    //lấy phần tử đầu danh sách ra (vào trước ra trước)
    cout << "danh sach sau khi lay ra 1 phan tu cua queue ";
    dequeue(q);
    printQueue(q);
    cout<<"So phan tu cua queue: "<<countQueue(q)<<"\n"; //đếm số ptu của queue
    return 0;
}
