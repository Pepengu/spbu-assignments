#include <fstream>
#include <iostream>

class AATree{
    private:
        struct node{
            int value;
            int level;
            node* left;
            node* right;

            node(int v, int lvl, node* l = nullptr, node* r = nullptr): value(v), level(lvl), left(l), right(r) {}

            ~node(){
                delete left;
                delete right;
            }

            static node* skew(node *root){
                if(root == nullptr){
                    return nullptr;
                }

                if(root->left == nullptr){
                    return root;
                }

                if(root->left->level == root->level){
                    node *new_root = root->left;
                    root->left = new_root->right;
                    new_root->right = root;
                    return new_root;
                }

                return root;
            }

            static node* split(node* root){
                if(root == nullptr){
                    return nullptr;
                }

                if(root->right == nullptr || root->right->right == nullptr){
                    return root;
                }

                if(root->level == root->right->right->level){
                    node* new_root = root->right;
                    root->right = new_root->left;
                    new_root->left = root;
                    new_root->level++;
                    return new_root;
                }

                return root;
            }

            static node* insert(int value, node* root){
                if (root == nullptr){
                    return new node(value, 1);
                }

                if (value < root->value){
                    root->left = insert(value, root->left);
                }

                if (value > root->value){
                    root->right = insert(value, root->right);
                }

                root = skew(root);
                root = split(root);
                return root;
            }

            static node* decrease_level(node *root){
                if(root == nullptr){
                    return nullptr;
                }
                int lvl = (root->left == nullptr || root->right == nullptr ? 
                        1 : std::min(root->left->level, root->right->level)+1);

                if(lvl < root->level){
                    root->level = lvl;
                    if (root->right != nullptr && root->right->level > root->level){
                        root->right->level = lvl;
                    }
                }

                return root;
            } 

            static node* next(node *root){
                if(root == nullptr){
                    return nullptr;
                }

                if(root->right == nullptr){
                    return nullptr;
                }

                root = root->right;
                while(root->left != nullptr){
                    root = root->left;
                }

                return root;
            }

            static node* remove(int value, node *root){
                if(root == nullptr){
                    return nullptr;
                }

                if(value < root->value){
                    root->left = remove(value, root->left);
                }
                else if(value > root->value){
                    root->right = remove(value, root->right);
                }
                else{
                    if (root->left == nullptr && root->right == nullptr) {
                        delete root;
                        return nullptr;
                    }

                    if (root->left == nullptr) {
                        node* tmp = root->right;
                        root->right = nullptr;
                        delete root;
                        return tmp;
                    }

                    if (root->right == nullptr) {
                        node* tmp = root->left;
                        root->left = nullptr;
                        delete root;
                        return tmp;
                    }

                    node *tmp = next(root);
                    root->value = tmp->value;
                    root->right = remove(tmp->value, root->right);
                }

                root = decrease_level(root);
                root = skew(root);
                if (root->right != nullptr){
                    root->right = skew(root->right);
                    root->right->right = skew(root->right->right);
                }

                root = split(root);
                root->right = split(root->right);

                return root;
           }
            
            static bool search(int val, node *root){
                while(root != nullptr){
                    if(root->value == val){
                        return true;
                    }

                    if(root->value > val){
                        root = root->left;
                    }
                    else{
                        root = root->right;
                    }
                }
                return false;
            }
        } *root;

    public:
        AATree(): root(nullptr){}
        ~AATree(){delete root;}

        bool search(int value){
            return node::search(value, root);
        }

        void insert(int value){
            root = node::insert(value, root);
        }

        void remove(int value){
            root = node::remove(value, root);
        }

        int getLevel(){
            if(root == nullptr){
                return 0;
            }

            return root->level;
        }
};

int main(int argc, char *argv[]){
    if(argc != 3){
        std::cerr << "Wrong command" << '\n';
        return 1;
    }

    std::ifstream fin(argv[1]);
    std::ofstream fout(argv[2]);

    if(!fin.is_open() || !fout.is_open()){
        std::cerr << "Files could not be opened" << '\n';

        fin.close();
        fout.close();

        return 1;
    }

    int n;
    char symbol;
    int value;
    AATree tree;
    fin >> n;

    for (int i = 0; i < n; i++){
        fin >> symbol;
        switch (symbol){
            case '+':
                fin >> value;
                tree.insert(value);
                fout << tree.getLevel() << '\n';
                break;
            case '-':
                fin >> value;
                tree.remove(value);
                fout << tree.getLevel() << '\n';
                break;
            case '?':
                fin >> value;
                fout << (tree.search(value) ? "true\n" : "false\n");
                break;
        }
    }

    fin.close();
    fout.close();

    return 0;
}
