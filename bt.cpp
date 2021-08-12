#include <iostream>
#include "bt.h"
#include <queue>
#include <queue>
#define null NULL;
using namespace std;

binaryTreeNode<int>* takeInputLevelwise(){
    int rootData;
    cout << "Enter rootData: " << endl;
    cin >> rootData;
    if(rootData == -1){
        return NULL;
    }

    binaryTreeNode<int>* root = new binaryTreeNode<int>(rootData);
    queue<binaryTreeNode<int>*> pendingNodes;
    pendingNodes.push(root);
    while(pendingNodes.size()!=0){
        binaryTreeNode<int>* front = pendingNodes.front();
        pendingNodes.pop();
        cout << "Enter left child of " << front -> data << endl;
        int leftChild;
        cin>>leftChild;
        if(leftChild!= -1){
            binaryTreeNode<int>* leftnode = new binaryTreeNode<int>(leftChild);
            front->left = leftnode;
            pendingNodes.push(leftnode);
        }
        cout << "Enter right child of " << front -> data << endl;
        int rightChild;
        cin>>rightChild;
        if(rightChild!= -1){
            binaryTreeNode<int>* rightnode = new binaryTreeNode<int>(rightChild);
            front -> right = rightnode;
            pendingNodes.push(rightnode);
        }
    }
    return root;
}

int numNodes(binaryTreeNode<int>* root){
    if(root==NULL){
        return 0;
    }
    return 1 + numNodes(root->left) + numNodes(root->right);
}

binaryTreeNode<int>* takeInput(){
    int rootData;
    cout << "Enter root data: " << endl;
    cin >> rootData;
    if(rootData == -1){
        return NULL;
    }

    binaryTreeNode<int>* root = new binaryTreeNode<int>(rootData);
    binaryTreeNode<int>* leftChild =takeInput();
    binaryTreeNode<int>* rightChild = takeInput();
    root->left = leftChild;
    root->right = rightChild;

    return root;
}
bool findNode(binaryTreeNode<int>* root, int x){
    if(root == NULL){
        return false;
    }
    if(root -> data == x){
        return true;
    }
    bool l = findNode(root->left, x);
    if(l){
        return true;
    }
    bool r = findNode(root->right, x);
    if(r){
        return true;
    }
    return false;
}

int heightOfBinaryTree(binaryTreeNode<int>* root){
    if(root == NULL){
        return 0;
    }
    if(root->left == NULL && root -> right == NULL){
        return 1;
    }

    int l = heightOfBinaryTree(root -> left);
    int r = heightOfBinaryTree(root->right);
    if(l>r){
        return l +1;
    }else{
        return r + 1;
    }
}

pair<int, int> heightDiameter(binaryTreeNode<int>* root){
    if(root == NULL){
        pair<int, int> p;
        p.first = 0;
        p.second = 0;
        return p;
    }

    pair<int, int> leftAns = heightDiameter(root->left);
    pair<int, int> rightAns = heightDiameter(root -> right);
    int ld = leftAns.second;
    int lh = leftAns.first;
    int rd = rightAns.second;
    int rh = rightAns.first;

    int height = 1 + max(lh, rh);
    int diameter = max(lh + rh, max(rd, ld));
    pair<int, int> p;
    p.first = height;
    p.second = diameter;
    return p;
}


void mirror(binaryTreeNode<int>* root){
    if(root == NULL){
        return;
    }
    if(root -> left!= NULL or root -> right!= NULL){
        binaryTreeNode<int>* temp = root -> right;
        root -> right = root -> left;
        root->left = temp;

        mirror(root -> left);
        mirror(root -> right);
    }
    return;
}

void inorder(binaryTreeNode<int>* root){
    if(root == NULL){
        return;
    }
    inorder(root->left);
    cout << root->data << " ";
    inorder (root->right);
}

void preorder(binaryTreeNode<int>* root){
    if(root == NULL){
        return;
    }
    cout << root -> data << " ";
    preorder(root -> left);
    preorder(root-> right);
}

binaryTreeNode<int>* builTreeHelper(int* in, int* pre, int inS, int inE, int preS, int preE){
    if(inS > inE){
        return NULL;
    }

    int rootData = pre[preS];
    int rootIndex = -1;
    for(int i = inS; i <= inE; i++){
        if(in[i] == rootData){
            rootIndex = i;
            break;
        }
    }

    int linS = inS;
    int linE = rootIndex - 1;
    int lpreS = preS + 1;
    int lpreE = linE - linS + lpreS;
    int rpreS = lpreE + 1;
    int rpreE = preE;
    int rinS = rootIndex + 1;
    int rinE = inE; 

    binaryTreeNode<int>* root = new binaryTreeNode<int>(rootData);
    root -> left = builTreeHelper(in, pre, linS, linE, lpreS, lpreE);
    root -> right = builTreeHelper(in, pre, rinS, rinE, rpreS, rpreE);

    return root;
}

binaryTreeNode<int>* buildTree(int* in, int* pre, int size){
    return builTreeHelper(in, pre, 0, size-1, 0, size-1);
}

void postorder(binaryTreeNode<int>* root){
    if(root == NULL){
        return;
    }
    postorder(root -> left);
    postorder(root -> right);

    cout << root -> data << " ";
}

int summOfNodes(binaryTreeNode<int>* root){
    if(root == NULL){
        return 0;
    }

    int sum = 0;

    sum += summOfNodes(root -> left);
    sum += summOfNodes(root -> right);

    return root->data + sum;
}

pair<bool, int> depth(binaryTreeNode<int>* root){
    if(root == NULL){
        pair<bool, int> p;
        p.first = true;
        p.second = 0;
        return p;
    }

    pair<bool, int> l = depth(root->left);
    pair<bool, int> r = depth(root->right);

    pair<bool, int> ans;
    if(abs(l.second - r.second) > 1){
        ans.first = false;
        ans.second = 1 + max(l.second, r.second);
        return ans;
    }
    else if (l.second and r.second)
    {
        ans.first = true;
        ans.second = 1 + max(l.second, r.second);
        return ans;
    }else{
        ans.first = false;
        ans.second = 1 + max(l.second, r.second);
        return ans;
    }
    
}

void levelOrderTravasal(binaryTreeNode<int>* root){
    if(root == NULL){
        return;
    }

    queue<binaryTreeNode<int>*> pending;
    pending.push(root);
    pending.push(NULL);

    while(pending.size() != 0){
        if(pending.size() == 1){
            if(pending.front() == NULL){
                break;
            }
        }
        binaryTreeNode<int>* front = pending.front();
        if(front!= NULL){
            if(front->left!=NULL){
                pending.push(front->left);
            }
            if(front->right != NULL){
                pending.push(front->right);
            }
            cout << front -> data << " ";
            pending.pop();
        }
        else if(front == NULL){
            cout << endl;
            pending.pop();
            pending.push(NULL);
        }else{
            break;
        }
    }
}

bool checkBalanced(binaryTreeNode<int>* root){
    pair<bool, int> p = depth(root);
    return p.first;
}

void printBT(binaryTreeNode<int>* root){
    if(root == NULL){
        return;
    }
    cout << root->data << ":";
    if(root -> left != NULL){
        cout << "L" << root ->left -> data  << ",";
    }
    if(root -> right != NULL){
        cout << "R" << root ->right -> data;
    }
    cout << endl;
    printBT(root->left);
    printBT(root->right);
}

binaryTreeNode<int>* removeLeafNode(binaryTreeNode<int>* root){
    if(root == NULL){
        return NULL;
    }
    if(root -> left == NULL and root -> right == NULL){
        root = NULL;
        return root;
    }
    binaryTreeNode<int>* l = removeLeafNode(root -> left);
    binaryTreeNode<int>* r = removeLeafNode(root -> right);
    
    root -> left = l;
    root -> right = r;

    return root;
}

void nodeWithoutSibling(binaryTreeNode<int>* root){
    if(root == NULL){
        return;
    }
    if(root -> left == NULL and root -> right == NULL){
        return;
    }
    if(root -> left == NULL and root -> right != NULL){
        cout << root->right-> data << " ";
    }
    if(root -> left != NULL and root -> right == NULL){
        cout << root->left-> data << " ";
    }

     nodeWithoutSibling(root -> left);
     nodeWithoutSibling(root -> right);
}

int maxi(binaryTreeNode<int>* root){
    if(root == NULL){
        return INT32_MIN;
    }
    return max(root->data, max(maxi(root->left), maxi(root->right)));
}
int mini(binaryTreeNode<int>* root){
    if(root == NULL){
        return INT32_MAX;
    }
    return min(root->data, min(mini(root->left), mini(root->right)));
}

bool isBST(binaryTreeNode<int>* root){
    if(root == NULL){
        return true;
    }
    int leftmax = maxi(root -> left);
    int rightmin = mini(root -> right);
    bool output = (root -> data > leftmax) && (root -> data <= rightmin) && isBST(root->left ) && isBST(root -> right);
    return output;
}


binaryTreeNode<int>* searchBST(binaryTreeNode<int>* root, int k){
    if(root == NULL){
        return NULL;
    }
    if(root -> data == k){
        return root;
    }
    binaryTreeNode<int>* ans;
    if(k > root->data){
        ans = searchBST(root -> right, k);
    }else{
        ans = searchBST(root ->left, k);
    }

    return ans;
}

//1 2 3 4 5 6 7 -1 -1 -1 -1 8 9 -1 -1 -1 -1 -1 -1
int main(){
    // binaryTreeNode<int>* root = new binaryTreeNode<int>(1);
    // binaryTreeNode<int>* node1 = new binaryTreeNode<int>(2);
    // binaryTreeNode<int>* node2 = new binaryTreeNode<int>(3);
    // root->left = node1;
    // root->right = node2;

    binaryTreeNode<int>* root = takeInputLevelwise();
    cout << isBST(root) << endl;
    // binaryTreeNode<int>* ans = searchBST(root, 2);
    // if(ans){
    //     cout << "true" << endl;
    // }else{
    //     cout << "false";
    // }
    // nodeWithoutSibling(root);

    // binaryTreeNode<int>* root2 = removeLeafNode(root);
    
    // levelOrderTravasal(root2);
    // int ans = summOfNodes(root);
    // cout << ans << endl;
    // pair<int, int> ans = heightDiameter(root);
    // cout << " Height: " << ans.first;
    // cout << "diameter: " << ans.second;
    // printBT(root);
    // cout << endl;
    // inorder(root);
    // cout << endl;
    // preorder(root);
    // cout << endl;
    // postorder(root);
    
    // int ans = heightOfBinaryTree(root);
    // cout << ans;


    // int in[] = {4, 2, 5, 1, 8, 6, 9, 3, 7};
    // int pre[] = {1, 2, 4, 5, 3, 6, 8, 9, 7};

    // binaryTreeNode<int>* root = buildTree(in, pre, 9);
    // printBT(root);

}