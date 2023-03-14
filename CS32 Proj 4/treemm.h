#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED

#include <iostream>
#include <vector>

template <typename KeyType, typename ValueType>
class TreeMultimap
{
public:
    struct Node;

    class Iterator
    {
    public:
        Iterator()
        {
            m_size = 0;
            m_loc = 1;
        }

        Iterator(std::vector<ValueType>& values)
            : m_values(values)
        {
            m_v = &m_values.front();
            m_size = m_values.size();
            m_loc = 1;
        }

        ValueType& get_value() const
        {
            return *m_v;
        }

        bool is_valid() const
        {
            if (m_loc > m_size)
                return false;
            else
                return true;
        }

        void advance()
        {
            if (!is_valid())
                return;

            m_v++;
            m_loc++;
        }

    private:
        std::vector<ValueType> m_values;
        ValueType* m_v;
        int m_size;
        int m_loc;
    };

    TreeMultimap()
    {
        m_root = nullptr;
    }

    ~TreeMultimap()
    {
        FreeTree(m_root);
    }

    void insert(const KeyType& key, const ValueType& value)
    {
        if (m_root == nullptr)
        {
            m_root = new Node(key, value);
            return;
        }

        Node* cur = m_root;
        for (;;)
        {
            if (key == cur->key)
            {
                cur->values.push_back(value); // if key is the same, add value to vector
                return;
            }
            if (key < cur->key)
            {
                if (cur->left != nullptr)
                    cur = cur->left;
                else
                {
                    cur->left = new Node(key, value);
                    cur->left->parent = cur;
                    return;
                }
            }
            else if (key > cur->key)
            {
                if (cur->right != nullptr)
                    cur = cur->right;
                else
                {
                    cur->right = new Node(key, value);
                    cur->right->parent = cur;
                    return;
                }
            }
        }
    }

    Iterator find(const KeyType& key) const // making the assumption that find won't be called on an empty treemm 
    {
        Node* cur = m_root;

        while (cur != nullptr)
        {
            if (key == cur->key)
            {
                Iterator it(cur->values);
                return it;
            }
            else if (key < cur->key)
                cur = cur->left;
            else
                cur = cur->right;
        }
        Iterator it;
        return it;
    }

private:
    struct Node
    {
        Node(const KeyType& myKey, const ValueType& myValue) // USER NO APPROPRIATE DEFAULT CONSTRUCTOR
        {
            key = myKey;
            values.push_back(myValue);
            parent = left = right = nullptr;
        }

        KeyType key;
        std::vector<ValueType> values;
        Node* parent;
        Node* left;
        Node* right;
    };

    void FreeTree(Node* cur)
    {
        if (cur == nullptr)
            return;

        FreeTree(cur->left);
        FreeTree(cur->right);

        delete cur;
    }

    Node* m_root;
};

#endif // TREEMULTIMAP_INCLUDED