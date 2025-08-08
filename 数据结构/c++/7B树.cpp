#include <iostream>
#include<vector>
using namespace std;

typedef int KEY_VALUE;

/* 节点数据结构 */
struct btree_node {
    KEY_VALUE *keys;    // 节点中的关键字数组
    struct btree_node **children;   // 指向子节点的数组
    int num;    // 节点中关键字个数
    int leaf;   // 是否是叶子节点
};

struct btree {
    struct btree_node *root;    // 指向B树的根节点
    int dgree;  // B树的阶数的一半， 如此设置方便之后判断节点是否需要操作
};


/* 创建B树节点 */
btree_node* btree_node_create(int dgree, int leaf) {
    btree_node *node = (btree_node*)calloc(1, sizeof(btree_node));
    if (node == nullptr) {
        printf("btree_node_create failed!\n");
        return nullptr;
    }

    node->leaf = leaf;
    node->keys = (KEY_VALUE*)calloc(1, (dgree * 2 - 1) * sizeof(KEY_VALUE));
    node->children = (btree_node**)calloc(1, (dgree * 2) * sizeof   (btree_node));
    node->num = 0;
    return node;
}

/* 释放B树节点 */
void btree_node_destory(btree_node *node){
    if (node == nullptr) return;
    free(node->children);
    free(node->keys);
    free(node);
}

/* 创建B树 */
btree* btree_create(int dgree) {
    btree *T = new btree;

    T->dgree = dgree;
    btree_node *node = btree_node_create(dgree, 1);
    T->root = node;

    return T;
}

/* 分裂B树节点 */
void btree_node_split(btree *T, btree_node *x, int index) {
    int dgree = T->dgree;
    btree_node * y = x->children[index];

    /* 新建节点z,将待分裂节点的后一半关键字放入新节点z */
    btree_node *z = btree_node_create(dgree, y->leaf); // 创建节点，传入参数为：节点的阶数+是否叶子节点
    z->num = dgree - 1; // 设置新节点z的关键字个数
    for (int k = dgree; k < 2 * dgree - 1; ++k) z->keys[k - dgree] = y->keys[k];
    if (y->leaf == 0) for (int k = dgree; k < 2 * dgree; ++k ) z->children[k - dgree] = y->children[k];   // 若待分裂节点为非叶子节点，则拥有的子树也需要复制到新节点z

    /* 将分裂出的关键字放入父节点x */
    for (int k = x->num - 1; k >= index; k--) x->keys[k + 1] = x->keys[k]; // 将后半关键字往后移动，腾出空间，以便存放分裂节点的中间关键字
    x->keys[index] = y->keys[dgree - 1]; 
    x->num += 1;
    y->num = dgree - 1;

    /* 将新建节点z作为子树插入到x节点 */
    for (int k = x->num; k > index; --k) x->children[k + 1] = x->children[k];// 将父节点中部分子树往后移动一个单位，以便插入新建节点z
    x->children[index + 1] = z;
}

/* 插入关键字---根节点非满 */
void btree_insert_key_nodeNonFull(btree *T, btree_node *x, KEY_VALUE key) {
    int index = x->num - 1;

    if (x->leaf == 1) {
        while (index >= 0 && x->keys[index] > key ) {
            x->keys[index + 1] = x->keys[index];
            index--;
        }
        x->keys[index + 1] = key;
        x->num += 1;
    }
    else {// 非叶子节点，则该节点必然不会是待插入节点，继续往下探索，探索过程中判断即将探索的下层节点关键字是否满，满了需要分裂
        while (index >= 0 && x->keys[index] > key) index--;

        if (x->children[index + 1]->num == (2 * T->dgree - 1)) {
            btree_node_split(T, x, index + 1);
            if (x->keys[index + 1] < key) index++; // 更新待探索的子节点索引，因为 分裂节点会向x节点插入新的关键字，所以要重新判断该关键字是否小于key
        }

        btree_insert_key_nodeNonFull(T, x->children[index + 1], key);
    }
}

/* 插入关键字 */
void btree_insert_key(btree *T, KEY_VALUE key) {
    btree_node *r = T->root;

    if (r->num == 2 * T->dgree - 1) { // 特殊情况，根节点关键字满，需要分裂并且重新设置根节点
        btree_node *node = btree_node_create(T->dgree, 0);
        T->root = node;
        node->children[0] = r;
        btree_node_split(T, node, 0);

        int i = 0;
        if (node->keys[0] < key) ++i;// 判断节点插入的位置        
        btree_insert_key_nodeNonFull(T, node->children[i], key);
    }
    else btree_insert_key_nodeNonFull(T, r, key);
}

/* 合并节点 */
void btree_node_merge(btree *T, btree_node *node, int index) {
    btree_node *left = node->children[index];   // 合并的左子节点
    btree_node *right = node->children[index + 1];  // 合并的右子节点

    /* 将父节点关键字以及右子节点都存入左子节点中 */
    left->keys[T->dgree - 1] = node->keys[index];
    for (int i = 0; i < right->num; ++i) left->keys[T->dgree + i] = right->keys[i];// 移动right中的关键字
    if (left->leaf == 0) for (int i = 0; i <= right->num; ++i) left->children[T->dgree + i] = right->children[i];// 移动right中的子节点指针
    left->num += right->num + 1;

    btree_node_destory(right);  // 释放右子节点

    for (int i = index + 1; i < node->num; ++i) {// 更新父节点关键字和指向子 节点的指针位置
        node->keys[i - 1] = node->keys[i];
        node->children[i] = node->children[i + 1];
    }
    node->children[node->num + 1] = nullptr;
    node->num -= 1;

    if (node->num == 0) {// 如果父节点个数为0,这种情况只可能是父节点为根节点
        T->root = left;
        btree_node_destory(node);
    }
}

/* 删除节点中关键字 */
void btree_node_delete_key(btree *T, btree_node *node, KEY_VALUE key) {
    if (node == nullptr) return;

    int index = 0;
    // 找到节点中第一个大于等于key的关键字
    while (index < node->num && key > node->keys[index]) index++;

    if (index < node->num && node->keys[index] == key) {    // 在该节点中找 到等于key的关键字, 考虑具体的删除操作
        if (node->leaf == 1) {// 该节点为叶子节点
            for (int i = index; i < node->num - 1; ++i) node->keys[i] = node->keys[i + 1];
            node->keys[node->num - 1] = 0;
            node->num -= 1;

            if (node->num == 0) {
                free(node);
                T->root = nullptr;
            }
        } 
        else if (node->children[index]->num >= T->dgree) {    // 借用左   子节点的关键字进行覆盖
            btree_node * left = node->children[index];
            node->keys[index] = left->keys[left->num - 1];

            btree_node_delete_key(T, left, left->keys[left->num - 1]);  // 递归删除子节点中用来覆盖上层节点的关键字
        } 
        else if (node->children[index + 1]->num >= T->dgree) {    // 借   用左子节点的关键字进行覆盖
            btree_node *right = node->children[index + 1];
            node->keys[index] = right->keys[0];

            btree_node_delete_key(T, right, right->keys[0]);    // 递归删   除子节点中用来覆盖上层节点的关键字
        } 
        else {
            btree_node_merge(T, node, index);
            btree_node_delete_key(T, node->children[index], key);
        }

    } 
    else {    // 继续往children[index]子节点找

        btree_node *child = node->children[index];
        if (child == nullptr) {
            printf("Cannot find key : %d\n", key);
            return;
        }

        /* 找关键字所在的节点过程中，遇到关键字个数==dgree-1的节点，进行丰满处  理 */
        if (child->num == T->dgree - 1) {
            btree_node *left = nullptr, *right = nullptr;
            if (index > 0) left = node->children[index - 1];
            if (index < node->num) right = node->children[index + 1];

            if ((left && left->num >= T->dgree) || (right && right->num     >= T->dgree)) {
                int select = 0;
                if (left && right) select = (right->num > left->num) ? 1 : 0;

                if (select) {   // 选右子树
                    /* 将父节点node的第一个大于key的关键字移给child */
                    child->keys[child->num] = node->keys[index];
                    child->num += 1;
                    child->children[child->num] = right->children[0];

                    /* 将child右兄弟节点的第一个关键字移给父节点node */
                    node->keys[index] = right->keys[0];

                    /* 更新child右兄弟节点中关键字和子节点指针的位置 */
                    for (int i = 0; i < right->num - 1; ++i) {
                        right->keys[i] = right->keys[i + 1];
                        right->children[i] = right->children[i + 1];
                    }
                    right->keys[right->num - 1] = 0;
                    right->children[right->num - 1] = right->children   [right->num];
                    right->children[right->num] = nullptr;
                    right->num -= 1;

                } 
                else {    // 选左子树

                    child->num++;
                    child->children[child->num] = child->children   [child->num - 1];
                    for (int i = child->num - 2; i >= 0; --i) {
                        child->keys[i + 1] = child->keys[i];
                        child->children[i + 1] = child->children[i];
                    }
                    child->keys[0] = node->keys[index - 1];
                    child->children[0] = left->children[left->num];

                    node->keys[index - 1] = left->keys[left->num - 1];

                    left->keys[left->num - 1] = 0;
                    left->children[left->num] = nullptr;
                    left->num -= 1;
                }
            } 
            else {
                if (left && left->num == T->dgree - 1) {
                    btree_node_merge(T, node, index - 1);
                    child = left;
                } 
                else if (right && right->num == T->dgree - 1) {
                    btree_node_merge(T, node, index);
                }
            }
        }
        btree_node_delete_key(T, child, key);
    }
}


/* 删除B树关键字 */
void btree_delete_key(btree *T, KEY_VALUE key) {
    if (T->root == nullptr) return ;
    btree_node_delete_key(T, T->root, key);
}

void btree_print(btree *T, btree_node *node, int layer) {
    btree_node *p = node;

    if (p) {
        printf("\nlayer = %d keynum = %d is_leaf = %d\n", layer, p->num, p->leaf);
        for(int i = 0; i < node->num; i++) printf("%C ", p->keys[i]);
        printf("\n");

        layer++;
        for(int i = 0; i <= p->num; i++) if(p->children[i]) btree_print(T, p->children[i], layer);
    }
    else printf("the tree is empty\n");
}

int main() {
    btree *T = btree_create(3);

    char key[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < 26; i++) {
        printf("%C ", key[i]);
        btree_insert_key(T, key[i]);
        btree_print(T, T->root, 0);
    }

    btree_print(T, T->root, 0);

    for (int i = 0; i < 26; i++) {
        btree_delete_key(T, key[25-i]);
        btree_print(T, T->root, 0);
    }

    return 0;
}
