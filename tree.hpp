#include <iostream>

namespace tree {

    enum colour_t { BLACK, RED };

    template <typename key_t>
    class tree_RB {

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
                if (key < node->key_)
                    node = node->left_;
                else if (key > node->key_) 
                    node = node->right_;
                else return node;
            }

            return nullptr;
        }

        public: //selectors
            tree_RB() { root_ = nullptr; }
            bool exist() const { return !(root_ == nullptr); }
            void print(key_t key) const { std::cout << searh_node(key)->key_ << std::endl; }
        
        public:
            void add_node(key_t key) {
                iterator add_node = new Node_RB{key};
                iterator node(root_);
                iterator parent_node = nullptr;

                while (node != nullptr) {
                    parent_node = node;
                    if (key < node->key_)
                        node = node->left_;
                    else node = node->right_;
                }
                add_node->parent_ = parent_node;
                
                if (parent_node == nullptr) 
                    root_ = add_node;
                else if (key < parent_node->key_) {
                    parent_node->left_ = add_node;
                } else parent_node->right_ = add_node; 
            }

    };



}