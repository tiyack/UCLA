#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED
#include <iostream>
#include <vector>

template <typename KeyType, typename ValueType>
class TreeMultimap
{
    private:
      struct Node
      {
          KeyType key;
          std::vector<ValueType> valueVector;
          Node* left;
          Node* right;
      };
      Node* root;
      void DestructorHelper(Node* node)
      {
          if (node == nullptr)
              return;
          DestructorHelper(node->left);
          DestructorHelper(node->right);
          //std::cerr << "Desroying!\n";
          delete node;
          node = nullptr;
      }
  public:
    class Iterator
    {
      public:
        Iterator()
        :m_nodePointer(nullptr), m_valid(false)
        {
//            first = nullptr;
//            index = 0;
        }
        
//        Iterator(const std::vector<ValueType>& vectorOfValues)
//        : m_values(vectorOfValues)
//        {
            //first = &m_values.front();
//            first = &(m_values.at(0));
//            index = 0;
//        }
        Iterator(Node* node)
        :m_nodePointer(node), m_valid(true)
        {
            m_index = 0;
        }

        ValueType& get_value() const
        {
            return m_nodePointer->valueVector.at(m_index);
//            return *first;
//            return m_values.at(index);
        }

        bool is_valid() const
        {
//            if(first == nullptr)
//                return false;
//            if(m_values.empty())
//                return false;
//
//            return true;
            if(!m_valid)
                return false;
            if (m_nodePointer->valueVector.empty())
                return false;
            if(m_index >= m_nodePointer->valueVector.size())
                return false;
            return true;
        }

        void advance()
        {
//            m_values.erase(m_values.begin());
//            if(!m_values.empty())
//                first = &m_values.front();
//            else
//                first = nullptr;
            m_index++;
        }

      private:
        int m_index;
        Node* m_nodePointer;
        bool m_valid;
//        ValueType* first;
//        std::vector<ValueType> m_values;
    };

    TreeMultimap()
    {
        root = nullptr;
    }

    ~TreeMultimap()
    {
        DestructorHelper(root);
    }

    void insert(const KeyType& key, const ValueType& value)
    {
        Node* temp = root;
        Node* prev = nullptr;
        while(temp != nullptr){
            //std::cerr << "In here\n";
            if(temp->key == key){
                temp->valueVector.push_back(value);
                return;
            }
            if(temp->key > key){
                prev = temp;
                temp = temp->left;
            }
            else{
                prev = temp;
                temp = temp->right;
            }
        }
        //std::cerr << "Hee\n";
        Node* newNode = new Node;
        newNode->key = key;
        newNode->valueVector.push_back(value);
        newNode->left = nullptr;
        newNode->right = nullptr;
        
        if(root == nullptr){ //first node
            root = newNode;
//            std::cerr << "First!\n";
            return;
        }
        if (prev->key > key)
            prev->left = newNode;
        else
            prev->right = newNode;
    }

    Iterator find(const KeyType& key) const
    {
        if(root->key == key){
            //std::cerr << "Root vector: " << root->valueVector.at(0) << std::endl;
            return Iterator(root); //->valueVector);// root->value;
        }
        Node* p;
        if(root->key > key)
            p = root->left;
        else
            p = root->right;
        while(p != nullptr){
            if(p->key == key)
                break;
            if(p->key > key)
                p = p->left;
            else
                p = p->right;
        }
//        std::cerr << "Reached\n";
        if(p == nullptr) //value doesnt exist
            return Iterator(); //null iterator??
//        std::cerr << "returning iterator\n";
        return Iterator(p); //->valueVector);
    }
};

#endif // TREEMULTIMAP_INCLUDED

//void insert(Node*& root, const KeyType& key, const ValueType& value)
//{
//    if (root == nullptr) {
//        root = new Node;
//        root->key = key;
//        root->valueVector.push_back(value);
//        root->left = nullptr;
//        root->right = nullptr;
//    }
//    else if (key == root->key) {
//        root->valueVector.push_back(value);
//    }
//    else if (key < root->key) {
//        insert(root->left, key, value);
//    }
//    else {
//        insert(root->right, key, value);
//    }
//}
