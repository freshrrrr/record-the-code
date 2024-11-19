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

    // ��ӽڵ㵽����β��
    bool addNode(int value)
    {
        if (!isValid(value))
        {   //�Ϸ�����֤
            std::cerr << "Invalid node data: " << value << std::endl;
            return false;
        }

        Node* newNode = new Node(value);
        if (tail == nullptr)
        {
            // ����Ϊ�գ��½ڵ�ͬʱ��Ϊͷ����β��
            head = newNode;
            tail = newNode;
        }
        else {
            // ���½ڵ���ӵ�β��
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        return true;
    }

    // ɾ������β���ڵ�
    bool delNode() {
        if (head == nullptr)
        {   //�Ϸ�����֤
            std::cerr << "The list is empty. Cannot delete a node." << std::endl;
            return false;
        }

        // �ҵ�Ҫɾ����β���ڵ�
        Node* nodeToDelete = tail;

        if (nodeToDelete->prev == nullptr) {
            // �������ֻ��һ���ڵ�
            head = nullptr;
            tail = nullptr;
        }
        else {
            // ����β��ָ��
            tail = nodeToDelete->prev;
            tail->next = nullptr;
        }

        delete nodeToDelete;
        return true;
    }

    // ����������ӡ�ڵ�ֵ
    void traverse(int nDir)
    {
        if (nDir != 0 && nDir != 1)
        {
            std::cerr << "Invalid traversal direction: " << nDir << std::endl;
            return;
        }
        //�Ϸ�����֤
        if (head == nullptr) {
            std::cout << "The list is empty." << std::endl;
            return;
        }

        if (nDir == 0) {
            // �������
            Node* current = head;
            while (current != nullptr)
            {
                std::cout << current->data << " -> ";
                current = current->next;
            }
        }
        else {
            // �������
            Node* current = tail;
            while (current != nullptr) {
                std::cout << current->data << " -> ";
                current = current->prev;
            }
        }

        std::cout << "nullptr" << std::endl;
    }
};

// ������������ڵ�ֵ���ļ�
void savelist(Node* head)
{
    const std::string filename = "data.txt";
    std::ofstream outFile(filename);
    //�Ϸ�����֤
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



// �������ļ��ж�ȡ���ݲ���������
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
        // ʹ�ô���� LinkedList ������� addNode ����
        list.addNode(value);
    }

    inFile.close();
    std::cout << "Linked list created from file: " << filename << std::endl;
}

int main() {
    LinkedList myList;
    Node* head = nullptr;
    Node* tail = nullptr;

    // ���ɲ����ʮ���������������
    for (int i = 0; i < 10; ++i) {
        int randomValue = rand() % 100;  // ����0��99֮����������
        myList.addNode(randomValue);

    }
    std::cout << "ʮ������������Ϊ" << std::endl;
    // ��ӡ�������ݣ����������
    std::cout << "�������:" << std::endl;
    myList.traverse(0);



    // ɾ������β���ڵ�
    if (myList.delNode()) {
        std::cout << "ɾ�����һ���ڵ�." << std::endl;
    }
    else {
        std::cout << "ɾ�����һ���ڵ�ʧ��." << std::endl;
    }

    // ��ӡ�������ݣ����������
    std::cout << "�������:" << std::endl;
    myList.traverse(0);

    // ����һ���µ������������ӵ�����
    int newRandomValue = rand() % 100;  // �����µ��������
    myList.addNode(newRandomValue);
    std::cout << "׷�ӽڵ��" << std::endl;

    // ��ӡ�������ݣ����������
    std::cout << "�������:" << std::endl;
    myList.traverse(0);

    // ��ӡ�������ݣ����������
    std::cout << "�������:" << std::endl;
    myList.traverse(1);


    // ����˫�����ļ�
    savelist(head);

    // ���ļ��ж�ȡ���ݲ���������
    readlist(myList);

    // ��ӡ�������ݣ����������
    std::cout << "�������:" << std::endl;
    myList.traverse(0);
    return 0;
}
