class Queue{
public:
    Queue(int*, int);
    ~Queue();
    void push(int);
    int pop();
    int size();
    void print();

    int front, rear, length;
    unsigned int cap;
    int* arr;
    int* buffer;
};