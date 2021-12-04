#include <fstream>
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

class ProductList {
   private:
    NodeProduct *head = NULL;
    NodeProduct *tail = NULL;
    string FILENAME = "products.txt";
    int id = 1;

   public:
    ProductList() {
        importProduct(FILENAME);
    }

    void importProduct(string filename) {
        ifstream file;
        int importId;
        string name;
        int price;
        file.open(filename);
        while (file >> importId >> ws >> name >> ws >> price) {
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
        file.close();
    }

    void saveToFile(string filename) {
        ofstream file;
        file.open(filename);
        NodeProduct *current = head;
        while (current != NULL) {
            file << current->id << " " << current->name << " " << current->price << endl;
            current = current->next;
        }
        file.close();
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

        saveToFile(FILENAME);
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
                saveToFile(FILENAME);
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
            cout << current->id << ". " << current->name << " (" << current->price << ") " << endl;
            current = current->next;
        }
    }
};

class OrderQueue {
   private:
    NodeOrder *front = NULL;
    NodeOrder *rear = NULL;
    string FILENAME = "orders.txt";
    int id = 1;

   public:
    OrderQueue() {
        importOrder(FILENAME);
    }

    void importOrder(string filename) {
        ifstream file;
        int importId;
        int importProductId;
        string name;
        int price;
        file.open(filename);
        while (file >> importId >> ws >> importProductId >> ws >> name >> ws >> price) {
            NodeOrder *newOrder = new NodeOrder;
            newOrder->id = id++;
            newOrder->product.id = importProductId;
            newOrder->product.name = name;
            newOrder->product.price = price;
            newOrder->next = NULL;

            if (isEmpty()) {
                front = newOrder;
                rear = newOrder;
            } else {
                rear->next = newOrder;
                rear = newOrder;
            }
        }
        file.close();
    }

    void saveToFile(string filename) {
        ofstream file;
        file.open(filename);
        NodeOrder *current = front;
        while (current != NULL) {
            file << current->id << " " << current->product.id << " " << current->product.name << " " << current->product.price << endl;
            current = current->next;
        }
        file.close();
    }

    void enqueue(NodeProduct product) {
        NodeOrder *newOrder = new NodeOrder;
        newOrder->id = id++;
        newOrder->product = product;
        newOrder->next = NULL;

        if (isEmpty()) {
            front = newOrder;
            rear = newOrder;
        } else {
            rear->next = newOrder;
            rear = newOrder;
        }

        saveToFile(FILENAME);
    }

    NodeOrder dequeue() {
        if (isEmpty()) {
            throw runtime_error("Queue is empty");
        }
        NodeOrder *current = front;
        front = front->next;
        saveToFile(FILENAME);
        return *current;
    }

    NodeOrder peek() {
        if (isEmpty()) {
            throw runtime_error("Queue is empty");
        }
        return *front;
    }

    bool isEmpty() {
        return front == NULL;
    }

    void printList() {
        NodeOrder *current = front;
        while (current != NULL) {
            cout << current->id << ". " << current->product.name << " (" << current->product.price << ")" << endl;
            current = current->next;
        }
    }
};

class OrderStack {
   private:
    NodeOrder *top = NULL;
    string FILENAME = "shipments.txt";

   public:
    OrderStack() {
        importOrder(FILENAME);
    }

    void importOrder(string filename) {
        ifstream file;
        int importId;
        int importProductId;
        string name;
        int price;
        file.open(filename);
        while (file >> importId >> ws >> importProductId >> ws >> name >> ws >> price) {
            NodeOrder *newOrder = new NodeOrder;
            newOrder->id = importId;
            newOrder->product.id = importProductId;
            newOrder->product.name = name;
            newOrder->product.price = price;
            newOrder->next = top;
            top = newOrder;
        }
        file.close();
        reverseStack();
    }

    void saveToFile(string filename) {
        ofstream file;
        file.open(filename);
        NodeOrder *current = top;
        while (current != NULL) {
            file << current->id << " " << current->product.id << " " << current->product.name << " " << current->product.price << endl;
            current = current->next;
        }
        file.close();
    }

    void push(int id, NodeProduct product) {
        NodeOrder *newOrder = new NodeOrder;
        newOrder->id = id;
        newOrder->product = product;
        newOrder->next = top;
        top = newOrder;
        saveToFile(FILENAME);
    }

    NodeOrder pop() {
        if (isEmpty()) {
            throw runtime_error("Stack is empty");
        }
        NodeOrder *current = top;
        top = top->next;
        saveToFile(FILENAME);
        return *current;
    }

    NodeOrder peek() {
        if (isEmpty()) {
            throw runtime_error("Stack is empty");
        }
        return *top;
    }

    bool isEmpty() {
        return top == NULL;
    }

    void printList() {
        NodeOrder *current = top;
        while (current != NULL) {
            cout << current->id << ". " << current->product.name << " (" << current->product.price << ") " << endl;
            current = current->next;
        }
    }

    void reverseStack() {
        NodeOrder *current = top;
        NodeOrder *previous = NULL;
        NodeOrder *next = NULL;
        while (current != NULL) {
            next = current->next;
            current->next = previous;
            previous = current;
            current = next;
        }
        top = previous;
    }
};

// linked list headed and tailed
class OrderLinkedList {
   private:
    NodeOrder *head = (NodeOrder *)malloc(sizeof(NodeOrder));
    NodeOrder *tail = (NodeOrder *)malloc(sizeof(NodeOrder));
    string FILENAME = "history.txt";

   public:
    OrderLinkedList() {
        head->id = -999;
        head->next = tail;
        tail->id = 999;
        tail->next = NULL;

        importFromFile(FILENAME);
    }

    void importFromFile(string filename) {
        ifstream file;
        int importId;
        int importProductId;
        string name;
        int price;
        file.open(filename);
        while (file >> importId >> ws >> importProductId >> ws >> name >> ws >> price) {
            NodeOrder *newOrder = new NodeOrder;
            newOrder->id = importId;
            newOrder->product.id = importProductId;
            newOrder->product.name = name;
            newOrder->product.price = price;
            newOrder->next = NULL;

            NodeOrder *current = head;
            newOrder->next = NULL;
            while (current->next->id < newOrder->id) {
                current = current->next;
            }
            newOrder->next = current->next;
            current->next = newOrder;
        }
        file.close();
    }

    void saveToFile(string filename) {
        ofstream file;
        file.open(filename);
        NodeOrder *current = head->next;
        while (current != tail) {
            file << current->id << " " << current->product.id << " " << current->product.name << " " << current->product.price << endl;
            current = current->next;
        }
        file.close();
    }

    void addOrder(int id, NodeProduct product) {
        NodeOrder *current = head;
        NodeOrder *newOrder = new NodeOrder;
        newOrder->id = id;
        newOrder->product = product;
        newOrder->next = NULL;
        while (current->next->id < newOrder->id) {
            current = current->next;
        }
        newOrder->next = current->next;
        current->next = newOrder;
        saveToFile(FILENAME);
    }

    bool isEmpty() {
        return head->next == NULL;
    }

    void printList() {
        NodeOrder *current = head->next;
        while (current != tail) {
            cout << current->id << ". " << current->product.name << " (" << current->product.price << ") " << endl;
            current = current->next;
        }
    }
};

int menu() {
    int choice;
    cout << "==== Toko Elektronik ====" << endl;
    cout << "1. Input Produk" << endl;
    cout << "2. Hapus Produk" << endl;
    cout << "3. List Produk" << endl;
    cout << "4. Input Order" << endl;
    cout << "5. Proses Order" << endl;
    cout << "6. Kirim Order" << endl;
    cout << "7. Lihat Status Order" << endl;
    cout << "8. Lihat Riwayat Order" << endl;
    cout << "9. Exit" << endl;
    cout << "Silahkan Pilih Menu : ";
    cin >> choice;
    return choice;
}

int main() {
    int choice;
    ProductList productsList;
    OrderQueue processQueue;
    OrderStack shipmentStack;
    OrderLinkedList historyOrderList;

    while (true) {
        choice = menu();
        if (choice == 1) {
            // input product
            int jumlah;
            cout << "Silahkan Masukkan jumlah input : ";
            cin >> jumlah;
            for (int i = 1; i <= jumlah; i++) {
                string name;
                int price;
                cout << "Nama barang : ";
                cin >> name;
                cout << "Harga Barang : ";
                cin >> price;
                productsList.addProduct(name, price);
            }
        } else if (choice == 2) {
            // remove product
            int id;
            productsList.printList();
            cout << "Silahkan Masukkan Produk yang ingin dihapus : ";
            cin >> id;
            bool isDeleted = productsList.removeProduct(id);
            if (isDeleted) {
                cout << "Produk berhasil dihapus" << endl;
            } else {
                cout << "Produk tidak ditemukan" << endl;
            }
        } else if (choice == 3) {
            // list product
            cout << "List Semua Produk : " << endl;
            productsList.printList();
            cout << endl;
        } else if (choice == 4) {
            // input order
            int jumlah;
            cout << "Silahkan Masukkan jumlah input : ";
            cin >> jumlah;
            for (int i = 1; i <= jumlah; i++) {
                int id;
                productsList.printList();
                cout << "Masukkan ID Produk : ";
                cin >> id;
                try {
                    NodeProduct product = productsList.getProduct(id);
                    processQueue.enqueue(product);
                } catch (runtime_error e) {
                    cout << e.what() << endl;
                }
            }
        } else if (choice == 5) {
            // proses order
            string answer;
            if (processQueue.isEmpty()) {
                cout << "Queue is empty" << endl;
            } else {
                NodeOrder order = processQueue.peek();
                cout << "Proses Order : " << endl;
                cout << "ID Produk : " << order.id << endl;
                cout << "Nama Produk : " << order.product.name << endl;
                cout << "Harga Produk : " << order.product.price << endl;

                cout << "Apakah anda ingin memproses order ini ? (y/n) : ";
                cin >> answer;

                if (toupper(answer[0]) == 'Y') {
                    cout << "Order berhasil diproses" << endl;
                    NodeOrder order = processQueue.dequeue();
                    shipmentStack.push(order.id, order.product);
                }
            }
        } else if (choice == 6) {
            // kirim order
            string answer;
            if (shipmentStack.isEmpty()) {
                cout << "Stack is empty" << endl;
            } else {
                NodeOrder order = shipmentStack.peek();
                cout << "Kirim Order : " << endl;
                cout << "ID Produk : " << order.id << endl;
                cout << "Nama Produk : " << order.product.name << endl;
                cout << "Harga Produk : " << order.product.price << endl;

                cout << "Apakah anda ingin mengirim order ini ? (y/n) : ";
                cin >> answer;

                if (toupper(answer[0]) == 'Y') {
                    NodeOrder order = shipmentStack.pop();
                    historyOrderList.addOrder(order.id, order.product);
                }
            }
        } else if (choice == 7) {
            // Lihat Status Order
            cout << "Order Menunggu Diproses : " << endl;
            processQueue.printList();
            cout << endl;
            cout << "Order Menunngu Dikirim : " << endl;
            shipmentStack.printList();
            cout << endl;

        } else if (choice == 8) {
            // lihat riwayat order
            cout << "Riwayat Order : " << endl;
            historyOrderList.printList();
            cout << endl;
        } else if (choice == 9) {
            // exit
            cout << "Terima Kasih Telah Menggunakan Toko Elektronik" << endl;
            break;
        } else {
            cout << "Menu tidak ditemukan" << endl;
        }
    };
}
