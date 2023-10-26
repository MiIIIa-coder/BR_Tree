#include <iostream>

namespace tree {

    enum colour_t { BLACK, RED };

    template <typename key_t = int>
    class tree_RB {
        
        //key1 > key2 ?
        bool (*comp_)(key_t key1, key_t key2);

        struct Node_RB {
            key_t key_;
            colour_t colour_;
            Node_RB *parent_, *left_, *right_;

            Node_RB(key_t key, colour_t colour = RED) : key_(key), colour_(colour) { 
                parent_ = nullptr;
                left_   = nullptr; 
                right_  = nullptr;  
            }

        };
        using iterator = Node_RB*;
        Node_RB *root_;

        //if didn't find returns nullptr
        iterator searh_node(key_t key) const {
            iterator node;

            node = root_;
            while (node != nullptr) {
                if (comp_(node->key_, key))
                    node = node->left_;
                else if (comp_(key, node->key_)) 
                    node = node->right_;
                else return node;
            }

            return nullptr;
        }

        public: //selectors
            bool exist() const { return !(root_ == nullptr); }
            void print(key_t key) const { std::cout << searh_node(key)->key_ << std::endl; }
        
        public:
            tree_RB(bool (*comp_func)(key_t key1, key_t key2), iterator root = nullptr) : comp_(comp_func), root_(root) {}

            void insert(key_t key) {
                iterator add_node = new Node_RB{key};
                iterator node(root_);
                iterator parent_node = nullptr;

                while (node != nullptr) {
                    parent_node = node;
                    if (comp_(node->key_, key))
                        node = node->left_;
                    else node = node->right_;
                }
                add_node->parent_ = parent_node;
                
                if (parent_node == nullptr) {
                    root_ = add_node;
                    root_->colour_ = BLACK;
                    return;
                }
                else if (comp_(parent_node->key_, key)) {
                    parent_node->left_ = add_node;
                } else parent_node->right_ = add_node; 

                //rebuild features of Red_Black tree
                RB_insert_fixup(add_node);
            }

            void RB_insert_fixup(iterator add_node) {
                while (add_node->parent_->colour_ == RED) {
                    iterator node_uncle;
                    if (add_node->parent_ == add_node->parent_->parent_->left_) {
                        node_uncle = add_node->parent_->parent_->right_;
                        if (node_uncle->colour_ == RED) {
                            add_node->parent_->colour_ = BLACK;
                            node_uncle->colour_ = BLACK;
                            add_node->parent_->parent_->colour_ = RED;
                            add_node = add_node->parent_->parent_;
                            if (add_node == root_)
                                break;
                        } else { 
                            if (add_node == add_node->parent_->right_) {
                                add_node = add_node->parent_;
                                left_rotate(add_node);
                            }
                            add_node->parent_->colour_ = BLACK;
                            add_node->parent_->parent_->colour_ = RED;
                            right_rotate(add_node->parent_->parent_);
                        }
                    } else {
                        node_uncle = add_node->parent_->parent_->left_;
                        if (node_uncle->colour_ == RED) {
                            add_node->parent_->colour_ = BLACK;
                            node_uncle->colour_ = BLACK;
                            add_node->parent_->parent_->colour_ = RED;
                            add_node = add_node->parent_->parent_;
                        } else {
                            if (add_node == add_node->parent_->left_) {
                                add_node = add_node->parent_;
                                right_rotate(add_node);
                            }
                            add_node->parent_->colour_ = BLACK;
                            add_node->parent_->parent_->colour_ = RED;
                            left_rotate(add_node->parent_->parent_);
                        }
                    }
                }

                root_->colour_ = BLACK;
            }

            void left_rotate(iterator node_x) {
                if (node_x->right_ == nullptr)
                    return;
                iterator node_y = node_x->right_;
                node_x->right_ = node_y->left_;

                if (node_y->left_ != nullptr)
                    node_y->left_->parent_ = node_x;
                node_y->parent_ = node_x->parent_;
                if (node_x->parent_ == nullptr)
                    root_ = node_y;
                else if (node_x == node_x->parent_->left_)
                    node_x->parent_->left_ = node_y;
                else node_x->parent_->right_ = node_y;
                node_y->left_ = node_x;
                node_x->parent_ = node_y;
            }

            void right_rotate(iterator node_x) {
                if (node_x->left_ == nullptr)
                    return;
                iterator node_y = node_x->left_;
                node_x->left_ = node_y->right_;

                if (node_y->right_ != nullptr)
                    node_y->right_->parent_ = node_x;
                node_y->parent_ = node_x->parent_;
                if (node_x->parent_ == nullptr)
                    root_ = node_y;
                else if (node_x == node_x->parent_->left_)
                    node_x->parent_->left_ = node_y;
                else node_x->parent_->right_ = node_y;
                node_y->right_ = node_x;
                node_x->parent_ = node_y;
            }

    };



}