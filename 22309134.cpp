#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>


class Node {
public:
    int data;
    Node* next;
    Node* prev;

    Node(int value) : data(value), next(nullptr), prev(nullptr) {}
};

class LinkedList {
private:
    Node* head;
    Node* tail;

public:
    LinkedList() : head(nullptr), tail(nullptr) {}

    bool isValid(int value)
    {
        return value >= 0;
    }

    // 添加节点到链表尾部
    bool addNode(int value)
    {
        if (!isValid(value))
        {   //合法性验证
            std::cerr << "Invalid node data: " << value << std::endl;
            return false;
        }

        Node* newNode = new Node(value);
        if (tail == nullptr)
        {
            // 链表为空，新节点同时成为头部和尾部
            head = newNode;
            tail = newNode;
        }
        else {
            // 将新节点添加到尾部
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        return true;
    }

    // 删除链表尾部节点
    bool delNode() {
        if (head == nullptr)
        {   //合法性验证
            std::cerr << "The list is empty. Cannot delete a node." << std::endl;
            return false;
        }

        // 找到要删除的尾部节点
        Node* nodeToDelete = tail;

        if (nodeToDelete->prev == nullptr) {
            // 如果链表只有一个节点
            head = nullptr;
            tail = nullptr;
        }
        else {
            // 更新尾部指针
            tail = nodeToDelete->prev;
            tail->next = nullptr;
        }

        delete nodeToDelete;
        return true;
    }

    // 遍历链表并打印节点值
    void traverse(int nDir)
    {
        if (nDir != 0 && nDir != 1)
        {
            std::cerr << "Invalid traversal direction: " << nDir << std::endl;
            return;
        }
        //合法性验证
        if (head == nullptr) {
            std::cout << "The list is empty." << std::endl;
            return;
        }

        if (nDir == 0) {
            // 正向遍历
            Node* current = head;
            while (current != nullptr)
            {
                std::cout << current->data << " -> ";
                current = current->next;
            }
        }
        else {
            // 反向遍历
            Node* current = tail;
            while (current != nullptr) {
                std::cout << current->data << " -> ";
                current = current->prev;
            }
        }

        std::cout << "nullptr" << std::endl;
    }
};

// 遍历链表并保存节点值到文件
void savelist(Node* head)
{
    const std::string filename = "data.txt";
    std::ofstream outFile(filename);
    //合法性验证
    if (!outFile) {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
        return;
    }

    Node* current = head;
    while (current != nullptr) {
        outFile << current->data << std::endl;
        current = current->next;
    }

    outFile.close();
    std::cout << "Linked list values saved to file: " << filename << std::endl;
}



// 从数据文件中读取数据并创建链表
void readlist(LinkedList& list) {
    const std::string filename = "data.txt";
    std::ifstream inFile(filename);
    if (!inFile)
    {
        std::cerr << "Failed to open file for reading: " << filename << std::endl;
        return;
    }

    int value;
    while (inFile >> value) {
        // 使用传入的 LinkedList 对象调用 addNode 方法
        list.addNode(value);
    }

    inFile.close();
    std::cout << "Linked list created from file: " << filename << std::endl;
}

int main() {
    LinkedList myList;
    Node* head = nullptr;
    Node* tail = nullptr;

    // 生成并添加十个随机整数到链表
    for (int i = 0; i < 10; ++i) {
        int randomValue = rand() % 100;  // 生成0到99之间的随机整数
        myList.addNode(randomValue);

    }
    std::cout << "十个整型数链表为" << std::endl;
    // 打印链表内容（正向遍历）
    std::cout << "正向遍历:" << std::endl;
    myList.traverse(0);



    // 删除链表尾部节点
    if (myList.delNode()) {
        std::cout << "删除最后一个节点." << std::endl;
    }
    else {
        std::cout << "删除最后一个节点失败." << std::endl;
    }

    // 打印链表内容（正向遍历）
    std::cout << "正向遍历:" << std::endl;
    myList.traverse(0);

    // 生成一个新的随机整数并添加到链表
    int newRandomValue = rand() % 100;  // 生成新的随机整数
    myList.addNode(newRandomValue);
    std::cout << "追加节点后" << std::endl;

    // 打印链表内容（正向遍历）
    std::cout << "正向遍历:" << std::endl;
    myList.traverse(0);

    // 打印链表内容（反向遍历）
    std::cout << "反向遍历:" << std::endl;
    myList.traverse(1);


    // 保存双链表到文件
    savelist(head);

    // 从文件中读取数据并创建链表
    readlist(myList);

    // 打印链表内容（正向遍历）
    std::cout << "正向遍历:" << std::endl;
    myList.traverse(0);
    return 0;
}
