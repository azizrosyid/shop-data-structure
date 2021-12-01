#include <iostream>
#include <string>
#include <malloc.h>

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
	int menu;
	ProductList productsList;
	do{
    cout << "==== Toko Elektronik ====" << endl;
    cout << "1.Input Produk" << endl;
    cout << "2.Hapus Produk" << endl;
    cout << "3.List Produk" << endl;
    cout << "4.Input Order" << endl;
    cout << "5.Proses Order" << endl;
    cout << "6.Kirim Order" << endl;
    cout << "7.Lihat Riwayat Order" << endl;
    cout <<"8.Exit" << endl;
    cout << "Silahkan Pilih Menu : " << endl; cin>>menu;
    cout <<endl;
    
    if(menu == 1){
	
		int jumlah;
		int i;
		cout << "Silahkan Masukkan jumlah input : " <<endl; cin>>jumlah;
		for(i=1; i<=jumlah; i++)
		{
			string name;
			int price;
			cout << "Nama barang : " ; cin>>name;
			cout <<endl;
			cout << "Harga BarangL "; cin>>price;
    productsList.addProduct(name, price);
   }
}else if(menu == 2){
	int id;
	cout << "Silahkan Masukkan Produk yang ingin dihapus : "; cin>>id;
	cout <<endl;
    productsList.removeProduct(id);
}else if(menu == 3){
    cout << "List Semua Produk" << endl;
    productsList.printList();
    cout << endl;
}
}while(menu !=8);
}
