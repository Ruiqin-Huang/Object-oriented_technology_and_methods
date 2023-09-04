// using UTF-8
class CLQueue
{
private:
    struct Node
    {
        int data;
        Node *next;
    };
    Node *front;
    Node *rear;

public:
    void Add(int x);
    void Remove();
    int Get(int x);
    CLQueue()
    {
        front = nullptr;
        rear = nullptr;
    } // 初始化头指针和尾指针为空指针
};

void CLQueue::Add(int x)
{
    Node *newnode = new Node{x};
    if (rear == nullptr)
    {
        front = newnode;
    }
    else
    {
        rear->next = newnode;
    }
    rear = newnode;
    rear->next = front;
}

void CLQueue::Remove()
{
    if (front == nullptr)
    {
        cout << "queue is empty!" << endl;
        return;
    }

    Node *temp = front;
    if (front == rear) // 说明当前队列只有一个元素，则将队列置为空
    {
        front = nullptr;
        rear = nullptr;
    }
    else
    {
        front = front->next;
        rear->next = front;
    }
    delete temp; // 删除原来队首元素，释放内存
}

int CLQueue::Get(int x)
{
    Node *temp = front;
    if (front == nullptr)
    {
        cout << "queue is empty!" << endl;
        return -1;
    }
    for (int i = 0; i < x && temp != rear; i++)
        temp = temp->next;
    return temp->data;
}