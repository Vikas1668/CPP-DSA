#include <bits/stdc++.h>
#include <stdexcept>
using namespace std;

template <class T>
class BinaryTreeNode {
    private:
        T data;
        BinaryTreeNode<T> *left;
        BinaryTreeNode<T> *right;

    public:
        BinaryTreeNode<T> (T data) {
            this->data = data;
            this->left = nullptr;
            this->right = nullptr;
        }

        BinaryTreeNode<T> (T data, BinaryTreeNode<T> *left, BinaryTreeNode<T> *right) {
            this(data);
            this->left = left;
            this->right = right;
        }

        T getData() {
            return this->data;
        }

        void setData(T data) {
            this->data = data;
        }

        BinaryTreeNode<T>* getLeftChild() {
            return this->left;
        }

        void setLeftChild(BinaryTreeNode<T> *left) {
            this->left = left;
        }

        BinaryTreeNode<T>* getRightChild() {
            return this->right;
        }

        void setRightChild(BinaryTreeNode<T> *right) {
            this->right = right;
        }
};

template <class T>
class BinaryTree {
    private:
        BinaryTreeNode<T> *root;
        T null;

        BinaryTreeNode<T>* constructBinaryTreeFromCompleteRepresentation (const vector<T> &elements, int idx) {

            int n = elements.size();

            if(!((n&(n+1)) == 0)) {
                throw invalid_argument("Constructor expected a complete binary representation of binary tree");
            }

            if(idx >= n) {
                return nullptr;
            }

            if(elements[idx] == null) {
                return nullptr;
            }
            
            BinaryTreeNode<T> *node = new BinaryTreeNode<T> (elements[idx]);
            node->setLeftChild(constructBinaryTreeFromCompleteRepresentation(elements, 2 * idx + 1));
            node->setRightChild(constructBinaryTreeFromCompleteRepresentation(elements, 2 * idx + 2));

            return node;
        }

        BinaryTreeNode<T> *createNode(T data) {
            if(data == null) {
                return nullptr;
            }

            return new BinaryTreeNode<T> (data);
        }

        BinaryTreeNode<T>* constructBinaryTree (const vector<T> &elements) {
            if(elements[0] == null) {
                return nullptr;
            }

            queue<BinaryTreeNode<T>*> nodes;
            
            BinaryTreeNode<T> *node = createNode(elements[0]);
            this->root = node;
            nodes.push(node);

            int idx = 1;
            while(idx < elements.size() && !nodes.empty()) {
                node = nodes.front();
                nodes.pop();

                BinaryTreeNode<T> *left;
                left = createNode(elements[idx]);
                node->setLeftChild(left);

                if(left != nullptr) {
                    nodes.push(left);
                }

                if(idx + 1 < elements.size()) {
                    BinaryTreeNode<T>* right = createNode(elements[idx + 1]);
                    node->setRightChild(right);

                     if(right != nullptr) {
                        nodes.push(right);
                    }
                }

                idx += 2;
            }

            return root;
        }

        void printNullNode(int idx) {
            cout << "Node " << idx << ": [" << null << "]" << endl; 
        }

        void printNode(BinaryTreeNode<T> *root, int idx, int left_idx, int right_idx) {
            cout << "Node " << idx << ": [data = " << root->getData() << ", left = Node " << left_idx << ", right = Node " << right_idx << "]" << endl;  
        }

        int print(BinaryTreeNode<T> *root, int idx) {
            if(root == nullptr) {
                printNullNode(idx);
                return idx + 1;
            }

            int right_idx = print(root->getLeftChild(), idx + 1);
            int return_idx = print(root->getRightChild(), right_idx);

            printNode(root, idx, idx + 1, right_idx);

            return return_idx;
        }

        int maxPathSumWithRoot(BinaryTreeNode<T> *root) {
            if(root == nullptr) {
                return INT_MIN;
            }

            int left_sum = maxPathSumWithRoot(root->getLeftChild());
            if(left_sum < 0) left_sum = 0;

            int right_sum = maxPathSumWithRoot(root->getRightChild());
            if(right_sum < 0) right_sum = 0;

            return root->getData() + max(left_sum, right_sum);
        }


        int maxPathSum (BinaryTreeNode<T> *root) {
            if(root == nullptr) {
                return INT_MIN;
            }

            int left_sum = maxPathSum(root->getLeftChild());
            int right_sum = maxPathSum(root->getRightChild());

            int left_sum_with_root = maxPathSumWithRoot(root->getLeftChild());
            if(left_sum_with_root < 0) left_sum_with_root = 0;

            int right_sum_with_root = maxPathSumWithRoot(root->getRightChild());
            if(right_sum_with_root < 0) right_sum_with_root = 0;

            int sum_with_root = root->getData() + left_sum_with_root + right_sum_with_root;

            return max({left_sum, right_sum, sum_with_root});
        }

    public:

        BinaryTree (T null) {
            this->root = nullptr;
            this->null = null;
        }

        BinaryTree (BinaryTreeNode<T> *root, T null) {
            this->null = null;
            this->root = root;
        }

        BinaryTree (const vector<T> &elements, T null) {
            this->null = null;

            int n = elements.size();
            if(n == 0) {
                return;
            }

            this->root = constructBinaryTree(elements);
        }

        BinaryTreeNode<T>* getRoot() {
            return this->root;
        }

        void setRoot(BinaryTreeNode<T> *root) {
            this->root = root;
        }

        void print() {
            print(this->root, 0);
        }

        int maxPathSum() {
            return maxPathSum(this->root);
        }
};