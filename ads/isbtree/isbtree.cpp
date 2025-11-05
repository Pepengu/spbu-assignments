#include <cstring>
#include <cctype>
#include <iostream>
#include <fstream>

template<typename T>
class Stack{
private:
    T* arr;
    size_t size;
    size_t top;

public:
    Stack(): size(100), arr(new T[100]), top(-1){}
    Stack(size_t s): size(s), arr(new T[s]), top(-1){}
    ~Stack(){delete[] arr;}
    void resize(int new_size){
        delete[] arr;
        arr = new T[new_size];
        size = new_size;
    }

    bool isEmpty() const{
        return top==-1;
    }

    bool isFull() const{
        return top == size-1;
    }
    
    void push(T n){
        if (isFull()){
            return;
        }
        arr[++top] = n;
    }

    T pop(){
        if (isEmpty()){
            return 0;
        }
        return arr[top--];
    }
};


template<typename T>
class Queue {
private:
    Stack<T> inside;
    Stack<T> out;
    size_t size;
public:

    Queue(int s): size(0), inside(s), out(s){}

    bool empty(){
        return inside.isEmpty() && out.isEmpty();
    }

    void enqueue(T n){
        if (inside.isFull())
        {
            std::cout << "overflow!" << std::endl;
            return;
        }
        ++size;
        inside.push(n);
    }

    T dequeue(){
        if (out.isEmpty()){
            while (!inside.isEmpty()){
                out.push(inside.pop());
            }
            size--;
            return out.pop();
        }
        size--;
        return out.pop();
    }

    int getSize() const{
        return size;
    }
};

struct NodeInfo {
    bool isLeaf;
    int nodeNumber;
    int usingsCounter;
    int keyCount;
    int* keys;
    int childCount;
    int* children_nums;

    NodeInfo():
        isLeaf(false),
        nodeNumber(0),
        usingsCounter(0),
        keyCount(0),
        keys(nullptr),
        childCount(0),
        children_nums(nullptr){}
};


class BTree{
private:
    static int search(const NodeInfo* nodesInfo, int size, int target) {
        int low = 0;
        int high = size - 1;
        while (low <= high){
            int mid = low + (high - low) / 2;

            if (nodesInfo[mid].nodeNumber == target){
                return mid;
            }
            if (nodesInfo[mid].nodeNumber < target){
                low = mid + 1;
            }
            else{
                high = mid - 1;
            }
        }

        return -1;
    }

    struct BTreeNode{
        NodeInfo info;
        BTreeNode** child; 

        BTreeNode(bool leaf, int nodeNum, int numKeys, const int* arrOfkeys, int numChilds){
            info.isLeaf = leaf;
            info.nodeNumber = nodeNum;
            info.keyCount = numKeys;
            info.keys = new int[numKeys];
            for (size_t i = 0; i < numKeys; i++){
                info.keys[i] = arrOfkeys[i];
            }
            info.childCount = numChilds;
            if (info.childCount == 0){
                child = nullptr;
            }
            else{
                child = new BTreeNode * [numChilds] {nullptr};
            }
        }
    };

    bool trash;
    int N;
    int t;
    int level;
    BTreeNode* root;
    
    
public:
    BTree():
        N(0),
        t(2),
        root(nullptr),
        level(0),
        trash(true){}

    void kill(BTreeNode* startNode){
        if (startNode != nullptr){
            for (int i = 0; i < startNode->info.childCount; i++){
                kill(startNode->child[i]);
            }
            delete[] startNode->info.keys;
            delete[] startNode->child; 
            delete startNode;
        }

    }

    BTree(NodeInfo* nodesInfo, int amStrN, int t, int root_num):
        N(amStrN),
        t(t),
        level(0),
        trash(false),
        root(nullptr){

        Queue<BTreeNode*> queue(amStrN);
        int rootNodeIndex = search(nodesInfo, amStrN, root_num);
        if (rootNodeIndex == -1){
            trash = true;
            for (size_t i = 0; i < amStrN; i++){
                delete[] nodesInfo[i].keys;
                nodesInfo[i].keys = nullptr;
                delete[] nodesInfo[i].children_nums;
                nodesInfo[i].children_nums = nullptr;
            }
            delete[] nodesInfo;
            return;
        }

        ++nodesInfo[rootNodeIndex].usingsCounter;
        root = new BTreeNode(nodesInfo[rootNodeIndex].isLeaf, 
                            nodesInfo[rootNodeIndex].nodeNumber, 
                            nodesInfo[rootNodeIndex].keyCount, 
                            nodesInfo[rootNodeIndex].keys, 
                            nodesInfo[rootNodeIndex].childCount);
        
        for (size_t i = 0; i < root->info.childCount; i++){
            int childNodeNumber = search(nodesInfo, amStrN, nodesInfo[rootNodeIndex].children_nums[i]);
            if (childNodeNumber == -1){
                trash = true;
                for (size_t i = 0; i < amStrN; i++){
                    delete[] nodesInfo[i].keys;
                    nodesInfo[i].keys = nullptr;
                    delete[] nodesInfo[i].children_nums;
                    nodesInfo[i].children_nums = nullptr;
                }
                delete[] nodesInfo;
                return;
            }

            ++nodesInfo[childNodeNumber].usingsCounter;

            if (nodesInfo[childNodeNumber].usingsCounter > 1){
                trash = true;
                for (size_t i = 0; i < amStrN; i++){
                    delete[] nodesInfo[i].keys;
                    nodesInfo[i].keys = nullptr;
                    delete[] nodesInfo[i].children_nums;
                    nodesInfo[i].children_nums = nullptr;
                }
                delete[] nodesInfo;
                return;
            }

            root->child[i] = new BTreeNode(nodesInfo[childNodeNumber].isLeaf,
                                        nodesInfo[childNodeNumber].nodeNumber,
                                        nodesInfo[childNodeNumber].keyCount,
                                        nodesInfo[childNodeNumber].keys,
                                        nodesInfo[childNodeNumber].childCount);


            queue.enqueue(root->child[i]);
        }

        while (!queue.empty()){
            int qSize = queue.getSize();
            for (size_t i = 0; i < qSize; i++){
                BTreeNode* node = queue.dequeue();
                int currNodeIndex = search(nodesInfo, amStrN, node->info.nodeNumber);
                if (currNodeIndex == -1){
                    trash = true;
                    for (size_t i = 0; i < amStrN; i++){
                        delete[] nodesInfo[i].keys;
                        nodesInfo[i].keys = nullptr;
                        delete[] nodesInfo[i].children_nums;
                        nodesInfo[i].children_nums = nullptr;
                    }
                    delete[] nodesInfo;
                    return;
                }
                for (size_t j = 0; j < nodesInfo[currNodeIndex].childCount; j++){
                    int childNodeIndex = search(nodesInfo, amStrN, nodesInfo[currNodeIndex].children_nums[j]);
                    if (childNodeIndex == -1){
                        trash = true;
                        for (size_t i = 0; i < amStrN; i++){
                            delete[] nodesInfo[i].keys;
                            nodesInfo[i].keys = nullptr;
                            delete[] nodesInfo[i].children_nums;
                            nodesInfo[i].children_nums = nullptr;
                        }

                        delete[] nodesInfo;
                        return;
                    }
                    ++nodesInfo[childNodeIndex].usingsCounter; 
                    if (nodesInfo[childNodeIndex].usingsCounter > 1){
                        trash = true;
                        for (size_t i = 0; i < amStrN; i++){
                            delete[] nodesInfo[i].keys;
                            nodesInfo[i].keys = nullptr;
                            delete[] nodesInfo[i].children_nums;
                            nodesInfo[i].children_nums = nullptr;
                        }
                        delete[] nodesInfo;
                        return;
                    }

                    if (node->child != nullptr){
                        node->child[j] = new BTreeNode(nodesInfo[childNodeIndex].isLeaf,
                                                            nodesInfo[childNodeIndex].nodeNumber,
                                                            nodesInfo[childNodeIndex].keyCount,
                                                            nodesInfo[childNodeIndex].keys,
                                                            nodesInfo[childNodeIndex].childCount);
                        queue.enqueue(node->child[j]);
                    }

                }

            }
            ++level;
        }

        for (size_t i = 0; i < amStrN; i++){
            delete[] nodesInfo[i].children_nums;
            delete[] nodesInfo[i].keys;
        }
        delete[] nodesInfo;
    }

    ~BTree(){
        kill(root);
    }

    bool search(int key) const{
        BTreeNode* currentNode = root;
        while (currentNode != nullptr) {
            BTreeNode* next_node = nullptr;
            int i = 0;
            int j = 0;
            bool checked = false;
            for (; j < currentNode->info.childCount; ++j){
                if (key == currentNode->info.keys[i]) {
                    return true;
                }

                if (i == 0 && !checked) {
                    if (key < currentNode->info.keys[i]) {
                        next_node = currentNode->child[0];
                        break;
                    }
                    checked = true;
                }

                else if (i == currentNode->info.keyCount - 1 && j == currentNode->info.childCount - 1) {
                    next_node = currentNode->child[j];
                }
                else if (key > currentNode->info.keys[i - 1] && key < currentNode->info.keys[i]) {
                    next_node = currentNode->child[j];
                    break;
                }
                

                if (i != currentNode->info.keyCount - 1) {
                    ++i;
                }
            }

            if (currentNode->info.isLeaf){
                for (int i = 0; i < currentNode->info.keyCount; ++i) {
                    if (currentNode->info.keys[i] == key) {
                        return true;
                    }
                }
            }

            currentNode = next_node;
        }

        return false;
    }

    bool isValid() const{
        if (trash){
            return false;
        }
    
        if (root != nullptr){
            if (!((root->info.keyCount >= 1 && root->info.keyCount <= 2 * t - 1)
                        && (!(root->info.isLeaf && (root->info.childCount == root->info.keyCount + 1))
                            || root->info.isLeaf))){
                return false;
            }

            int prev;
            if (root->info.keyCount > 0){
                prev = root->info.keys[0];
                for (size_t i = 0; i < root->info.keyCount; i++) {
                    if (root->info.keys[i] < prev){
                        return false;
                    }
                    prev = root->info.keys[i];
                }
            }
            
            bool checkVal = false;
            
            for (size_t currBranchKey = 0, childIdx = 0; childIdx < root->info.childCount; childIdx++){
                for (size_t extKeysIdx = 0; extKeysIdx < root->child[childIdx]->info.keyCount; extKeysIdx++){
                    if (currBranchKey == 0 && !checkVal){
                        if (root->child[childIdx]->info.keys[extKeysIdx] >= root->info.keys[currBranchKey]){
                            return false;
                        }
                    }
                    else if ((currBranchKey == root->info.keyCount - 1) && (childIdx == root->info.childCount - 1)){
                        if (root->child[childIdx]->info.keys[extKeysIdx] <= root->info.keys[currBranchKey]){
                            return false;
                        }
                    }
                    else{
                        if (root->child[childIdx]->info.keys[extKeysIdx] <= root->info.keys[currBranchKey - 1]
                            || root->child[childIdx]->info.keys[extKeysIdx] >= root->info.keys[currBranchKey]){
                            return false;
                        }
                    }
                }
                checkVal = true;
                if (currBranchKey != root->info.keyCount - 1){
                    currBranchKey++;
                }
            }
            Queue<BTreeNode*> queue(N + 1);

            for (size_t i = 0; i < root->info.childCount; i++){
                queue.enqueue(root->child[i]);
            }
            while (!queue.empty()){
                bool oneLevelCheck = false;
                int qSize = queue.getSize();
                for (size_t i = 0; i < qSize; i++){
                    BTreeNode* currChildNode = queue.dequeue();

                    if (i == 0){
                        oneLevelCheck = currChildNode->info.isLeaf;
                    }

                    if (!(currChildNode->info.keyCount >= t - 1 && currChildNode->info.keyCount <= 2 * t - 1
                        && ((!currChildNode->info.isLeaf && currChildNode->info.childCount == currChildNode->info.keyCount + 1) || currChildNode->info.isLeaf)
                        && currChildNode->info.isLeaf == oneLevelCheck)){
                        
                        return false;
                    }

                    int tmp;
                    if (currChildNode->info.keyCount > 0){
                        tmp = currChildNode->info.keys[0];
                        for (size_t i = 0; i < currChildNode->info.keyCount; i++){
                            if (currChildNode->info.keys[i] < tmp) {
                                return false;
                            }
                            if (!search(currChildNode->info.keys[i])){
                                return false;
                            }
                            tmp = currChildNode->info.keys[i];
                        }
                    }

                    bool checkVal = false;

                    for (size_t currBranchKey = 0, childIdx = 0; childIdx < currChildNode->info.childCount; childIdx++){
                        for (size_t extKeysIdx = 0; extKeysIdx < currChildNode->child[childIdx]->info.keyCount; ++extKeysIdx){
                            if (currBranchKey == 0 && !checkVal){
                                if (currChildNode->child[childIdx]->info.keys[extKeysIdx] >= currChildNode->info.keys[currBranchKey]){
                                    return false;
                                }
                            }
                            else if ((currBranchKey == currChildNode->info.keyCount - 1) && (childIdx == currChildNode->info.childCount - 1)){
                                if (currChildNode->child[childIdx]->info.keys[extKeysIdx] <= currChildNode->info.keys[currBranchKey]){
                                    return false;
                                }
                            }
                            else{
                                if (currChildNode->child[childIdx]->info.keys[extKeysIdx] <= currChildNode->info.keys[currBranchKey - 1]
                                    || currChildNode->child[childIdx]->info.keys[extKeysIdx] >= currChildNode->info.keys[currBranchKey]){
                                    return false;
                                }
                            }
                        }
                        checkVal = true;
                        if (currBranchKey != currChildNode->info.keyCount - 1){
                            currBranchKey++;
                        }
                    }
                    for (size_t i = 0; i < currChildNode->info.childCount; i++){
                        queue.enqueue(currChildNode->child[i]);
                    }
                }
            }
        }
        return true;
    }
};

int partition(NodeInfo* nodesInfo, int low, int high) {
    int pivot = nodesInfo[high].nodeNumber;
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (nodesInfo[j].nodeNumber < pivot) {
            i++;
            std::swap(nodesInfo[i], nodesInfo[j]);
        }
    }

    std::swap(nodesInfo[i + 1], nodesInfo[high]);
    return (i + 1);
}

void quickSort(NodeInfo* nodesInfo, int low, int high) {
    if (low < high) {
        int pivot = partition(nodesInfo, low, high);
        quickSort(nodesInfo, low, pivot - 1);
        quickSort(nodesInfo, pivot + 1, high);
    }
}

int parseNum(char*& str, char delimiter) {
    int num = 0;
    int sign = 1;

    for (;*str != 0 && *str == ' '; ++str){}

    if (*str == '-') {
        sign = -1;
        str++;
    }

    while (*str != 0 && *str != delimiter) {
        if(std::isdigit(*str) == 0){
            break;
        }
        num = num * 10 + (*str - '0');
        ++str;
    }

    return num * sign;
}

NodeInfo* fillBtreeInfo(const char* filename, int& nodeCount, int& t, int& root) {
    std::ifstream file(filename);
    file >> nodeCount >> t >> root;
    file.ignore();
    char line[2048];
    NodeInfo* nodesInfo = new NodeInfo[nodeCount];
    for (size_t i = 0; i < nodeCount; i++){
        file.getline(line, sizeof(line));
        char* pos = line;
        if (strncmp(pos, "leaf", 4) == 0) {
            nodesInfo[i].isLeaf = true;
            pos += 8;
            nodesInfo[i].nodeNumber = parseNum(pos, ' ');
            pos += 2;
            nodesInfo[i].keyCount = parseNum(pos, ':');
            nodesInfo[i].keys = new int[nodesInfo[i].keyCount];
            pos += 2;
            for (size_t extKeysIdx = 0; extKeysIdx < nodesInfo[i].keyCount; extKeysIdx++){
                if (extKeysIdx == nodesInfo[i].keyCount - 1){
                    nodesInfo[i].keys[extKeysIdx] = parseNum(pos, ')');
                }
                else{
                    nodesInfo[i].keys[extKeysIdx] = parseNum(pos, ' ');
                }
            }
        }
        else {
            nodesInfo[i].isLeaf = false;
            pos += 10;
            nodesInfo[i].nodeNumber = parseNum(pos, ' ');
            pos += 2;
            nodesInfo[i].keyCount = parseNum(pos, ':');
            nodesInfo[i].keys = new int[nodesInfo[i].keyCount];
            pos += 2;
            for (size_t extKeysIdx = 0; extKeysIdx < nodesInfo[i].keyCount; extKeysIdx++){
                if (extKeysIdx == nodesInfo[i].keyCount - 1){
                    nodesInfo[i].keys[extKeysIdx] = parseNum(pos, ')');
                }
                else{
                    nodesInfo[i].keys[extKeysIdx] = parseNum(pos, ' ');
                }
            }
            pos += 3;
            nodesInfo[i].childCount = parseNum(pos, ':');
            nodesInfo[i].children_nums = new int[nodesInfo[i].childCount];
            pos += 2;
            for (size_t extKeysIdx = 0; extKeysIdx < nodesInfo[i].childCount; extKeysIdx++){
                if (extKeysIdx == nodesInfo[i].childCount - 1){
                    nodesInfo[i].children_nums[extKeysIdx] = parseNum(pos, ')');
                }
                else{
                    nodesInfo[i].children_nums[extKeysIdx] = parseNum(pos, ' ');
                }
            }
        }
    }
    
    file.close();

    return nodesInfo;
}


int main(int argc, char* argv[]){
    const char* filename = argv[1];

    int N;
    int root;
    int t;
    NodeInfo* nodesInfo = fillBtreeInfo(filename, N, t, root);

    quickSort(nodesInfo, 0, N - 1);

    BTree tree(nodesInfo, N, t, root);

    std::cout << (tree.isValid() ? "yes" : "no");

    return 0;
}
