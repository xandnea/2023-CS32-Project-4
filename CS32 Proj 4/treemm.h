#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED

#include <map>

template <typename KeyType, typename ValueType>
class TreeMultimap
{
public:
    class Iterator
    {
    public:
        Iterator()
        {
            // Replace this line with correct code.
        }

        ValueType& get_value() const
        {
            return m_map[it];  // Replace this line with correct code.
        }

        bool is_valid() const
        {
            // Replace this line with correct code.
            if (it == m_map.end())
                return false;
            else
                return true;
        }

        void advance()
        {
            it++; // Replace this line with correct code.
        }

    private:
    };

    TreeMultimap()
    {
        it = m_map.begin()  // Replace this line with correct code.
    }

    ~TreeMultimap()
    {
        // Replace this line with correct code.
    }

    void insert(const KeyType& key, const ValueType& value)
    {
        m_map[key] = value; // Replace this line with correct code.
    }

    Iterator find(const KeyType& key) const
    {
        return Iterator();  // Replace this line with correct code.
    }

private:
    map<KeyType, ValueType> m_map;
    map<KeyType, ValueType>::iterator it;
};

#endif // TREEMULTIMAP_INCLUDED

// show content:
//for (std::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
//std::cout << it->first << " => " << it->second << '\n';