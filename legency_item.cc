#include <iostream>
#include <math.h>
#include <vector>
#include <stdio.h>


using namespace std;

struct TreeNode{
    int num;
    int lp;
    int rp;
    int pp;
    TreeNode* left;
    TreeNode* right;
    TreeNode* pre;
    TreeNode(int n,int lp_v, int rp_v, int pp_v):num(n),lp(lp_v), rp(rp_v),pp(pp_v),left(NULL), right(NULL), pre(NULL){}
};


TreeNode* preOrder(TreeNode* node){
    if(node){
        cout << node->num << endl;
        cout << node->pp<< endl;
        preOrder(node->left);
        preOrder(node->right);
    }
}

vector<TreeNode*> leafs;
int n, p, q;
TreeNode* getNextNode(TreeNode* pre_node, bool getted){
    int lp;
    int pp;
    int this_num = pre_node->num;
    if(getted){
        this_num += 1; 
        pp = pre_node->lp;
        lp = p / (pow(2,this_num));
    }else{
        pp = pre_node->rp;
        lp = pre_node->lp + q;
        if(lp > 100) lp = 100;
    }

    TreeNode* node = new TreeNode(this_num, lp, 100 - lp, pp);
    node->pre = pre_node;
    if(this_num == n){
        leafs.push_back(node);
    }
    else{
        node->left = getNextNode(node, true); 
        if(lp != 100){
            node->right = getNextNode(node , false); 
        }
    }
    return node;
}

vector<float> getPath(TreeNode* node){
    vector<float> path_probs;
    while(node->pre){
        path_probs.push_back((float)node->pp/100);
        node = node->pre;
    } 
    return path_probs;
}

int main(){
    while(cin >> p >> q >> n){
        TreeNode* root = new TreeNode(0, p ,100 - p, 100);
        root->left =  getNextNode(root, true);
        if(p != 100){
            root->right = getNextNode(root, false);
        }
        vector<TreeNode*>::iterator iter = leafs.begin();
        float pray = 0;
        for(iter; iter != leafs.end(); ++iter){
            TreeNode* leaf = *iter;

            vector<float> path_probs = getPath(leaf);
            int plen = path_probs.size(); 
            float pmul = 1;
            vector<float>::iterator piter = path_probs.begin();
            for(piter; piter != path_probs.end(); ++piter){
                pmul *= (*piter);
            }
            
            pray += plen*pmul;
        }
        printf("%.2f\n", pray);
    }
}
