#include <iostream>
#include <string>

using namespace std;

struct NodeProduct {
    int id;
    string name;
    int price;
    NodeProduct *next;
};

struct NodeOrder {
    int id;
    NodeProduct product;
    NodeOrder *next;
};

// linked list product
class ProductList {
   private:
    NodeProduct *head = NULL;
    NodeProduct *tail = NULL;
    int id = 1;

   public:
    ProductList() {
    }

    void addProduct(string name, int price) {
        NodeProduct *newProduct = new NodeProduct;
        newProduct->id = id++;
        newProduct->name = name;
        newProduct->price = price;
        newProduct->next = NULL;

        if (isEmpty()) {
            head = newProduct;
            tail = newProduct;
        } else {
            tail->next = newProduct;
            tail = newProduct;
        }
    }

    bool isEmpty() {
        return head == NULL;
    }

    bool removeProduct(int id) {
        NodeProduct *current = head;
        NodeProduct *previous = NULL;

        while (current != NULL) {
            if (current->id == id) {
                if (previous == NULL) {
                    // current is head
                    head = current->next;
                } else if (current->next == NULL) {
                    // current is tail
                    tail = previous;
                    tail->next = NULL;
                } else {
                    // current is in the middle
                    previous->next = current->next;
                }
                delete current;
                return true;
            }
            previous = current;
            current = current->next;
        }
        return false;
    }

    NodeProduct getProduct(int id) {
        NodeProduct *current = head;

        while (current != NULL) {
            if (current->id == id) {
                return *current;
            }
            current = current->next;
        }
        throw runtime_error("Product not found");
    }

    void printList() {
        NodeProduct *current = head;
        while (current != NULL) {
            cout << current->id << " " << current->name << " " << current->price << endl;
            current = current->next;
        }
    }
};

class OrderQueue {
   private:
    NodeOrder *head = NULL;
    NodeOrder *tail = NULL;
    int id = 1;

   public:
    OrderQueue() {
    }

    void enqueue(NodeProduct product) {
        NodeOrder *newOrder = new NodeOrder;
        newOrder->id = id++;
        newOrder->product = product;
        newOrder->next = NULL;

        if (isEmpty()) {
            head = newOrder;
            tail = newOrder;
        } else {
            tail->next = newOrder;
            tail = newOrder;
        }
    }

    NodeOrder dequeue() {
        if (isEmpty()) {
            throw runtime_error("Queue is empty");
        }
        NodeOrder *current = head;
        head = head->next;
        return *current;
    }

    bool isEmpty() {
        return head == NULL;
    }

    void printList() {
        NodeOrder *current = head;
        while (current != NULL) {
            cout << current->id << " " << current->product.name << " " << current->product.price << endl;

            current = current->next;
        }
    }
};

// create class for shipping with stack
class OrderStack {
   private:
    NodeOrder *head = NULL;
    NodeOrder *tail = NULL;

   public:
    OrderStack() {
    }

    void push(NodeOrder *newOrder) {
        newOrder->next = NULL;
        if (isEmpty()) {
            head = newOrder;
            tail = newOrder;
        } else {
            newOrder->next = head;
            head = newOrder;
        }
    }

    NodeOrder pop() {
        if (isEmpty()) {
            throw runtime_error("Stack is empty");
        }
        NodeOrder *current = head;
        head = head->next;
        return *current;
    }

    bool isEmpty() {
        return head == NULL;
    }

    void printList() {
        NodeOrder *current = head;
        while (current != NULL) {
            cout << current->id << " "
                 << current->product.name << " " << current->product.price << endl;
            current = current->next;
        }
    }
};

// linked list headed and tailed
class OrderLinkedList {
   private:
    NodeOrder *head = (NodeOrder *)malloc(sizeof(NodeOrder));
    NodeOrder *tail = (NodeOrder *)malloc(sizeof(NodeOrder));

   public:
    OrderLinkedList() {
        head->id = -999;
        head->next = tail;
        tail->id = 999;
        tail->next = NULL;
    }

    void addOrder(NodeOrder *newOrder) {
        NodeOrder *current = head;
        newOrder->next = NULL;
        while (current->next->id < newOrder->id) {
            current = current->next;
        }
        newOrder->next = current->next;
        current->next = newOrder;
    }

    bool isEmpty() {
        return head->next == NULL;
    }

    void printList() {
        NodeOrder *current = head->next;
        while (current != tail) {
            cout << current->id << " " << current->product.name << " " << current->product.price << endl;
            current = current->next;
        }
    }
};

int main() {
    ProductList productsList;
    productsList.addProduct("Bread", 10);
    productsList.addProduct("Milk", 20);
    productsList.addProduct("Cheese", 30);
    productsList.addProduct("Apple", 40);

    productsList.addProduct("Egg", 50);
    productsList.removeProduct(5);

    cout << "List Semua Produk" << endl;
    productsList.printList();
    cout << endl;

    OrderQueue orderQueue;
    NodeProduct product = productsList.getProduct(1);
    orderQueue.enqueue(product);
    product = productsList.getProduct(2);
    orderQueue.enqueue(product);
    product = productsList.getProduct(3);
    orderQueue.enqueue(product);
    product = productsList.getProduct(4);
    orderQueue.enqueue(product);

    cout << "List Input Pemesanan" << endl;
    orderQueue.printList();
    cout << endl;

    OrderStack shipmentStack;
    NodeOrder order = orderQueue.dequeue();
    shipmentStack.push(&order);
    NodeOrder order1 = orderQueue.dequeue();
    shipmentStack.push(&order1);
    NodeOrder order2 = orderQueue.dequeue();
    shipmentStack.push(&order2);

    cout << "List Pesanan yang sudah di proses" << endl;
    shipmentStack.printList();
    cout << endl;

    cout << "List Pesanan yang belum di proses" << endl;
    orderQueue.printList();
    cout << endl;

    OrderLinkedList historyOrder;

    NodeOrder order3 = shipmentStack.pop();
    historyOrder.addOrder(&order3);
    NodeOrder order4 = shipmentStack.pop();
    historyOrder.addOrder(&order4);

    cout << "List Pesanan yang belum dikirim" << endl;
    shipmentStack.printList();
    cout << endl;

    cout << "List Pesanan yang sudah dikirim dan masuk ke riwayat order" << endl;
    historyOrder.printList();
    cout << endl;

    return 0;
}
