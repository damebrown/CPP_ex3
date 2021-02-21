#ifndef EX3_MY_SET_HPP
#define EX3_MY_SET_HPP


#include "my_set.h"

//----------------insert implementations---------------------

template<typename T>
void my_set<T>::insertHelper(std::shared_ptr<Node> current, std::shared_ptr<Node> toAdd)
{
    if ((current->_right == nullptr) && (current->_left == nullptr))
    {
        if (current.get()->getData() < toAdd.get()->getData())
        {
            current->_right = toAdd;
        }
        else
        {
            current->_left = toAdd;
        }
        std::weak_ptr<Node> w_ptr(current);
        toAdd->_parent = w_ptr;
        return;
    }
    else
    {
        if (current.get()->getData() < toAdd.get()->getData())
        {
            if (current->_right == nullptr)
            {
                current->_right = toAdd;
                std::weak_ptr<Node> w_ptr(current);
                toAdd->_parent = w_ptr;
            }
            else
            {
                my_set<T>::insertHelper(current->_right, toAdd);
            }
        }
        else
        {
            if (current->_left == nullptr)
            {
                current->_left = toAdd;
                std::weak_ptr<Node> w_ptr(current);
                toAdd->_parent = w_ptr;
            }
            else
            {
                my_set<T>::insertHelper(current->_left, toAdd);
            }
        }
    }
}

template<typename T>
std::pair<typename my_set<T>::const_iterator, bool> my_set<T>::insert(const_reference val)
{
    std::pair<my_set<T>::const_iterator, bool> my_pair;
    my_pair.first = find(val);
    my_pair.second = (my_pair.first._ptr == nullptr);
    if ((!empty()) && (!my_pair.second))
    {
        return my_pair;
    }
    std::shared_ptr<Node> toAdd = std::make_shared<Node>(Node(val));
    if (empty())
    {
        _last = toAdd, _first = toAdd;
        _root = toAdd;
    }
    else
    {
        my_set<T>::insertHelper(_root, toAdd);
        if (val < _first->getData())
        {
            _first = std::make_shared<Node>(*toAdd);
        }
        else if (val > _last->getData())
        {
            _last = std::make_shared<Node>(*toAdd);
        }
    }
    _size++;
    my_pair.first = const_iterator(toAdd);
    return my_pair;
}

template<typename T>
std::pair<typename my_set<T>::const_iterator, bool> my_set<T>::insert(rref val)
{
    const_reference temp = val;
    auto p = insert(temp);
    val = 0;
    return p;
}

template<typename T>
typename my_set<T>::const_iterator my_set<T>::insert(const_iterator position,
                                                     const_reference val)
{
    if (empty())
    {
        std::shared_ptr<Node> toAdd = std::make_shared<Node>(Node(val));
        _root = toAdd, _size++, _first = toAdd, _last = toAdd;
        return const_iterator(toAdd);
    }
    else if (find(val) != cend())
    {
        return cend();
    }
    std::shared_ptr<Node> toAdd = std::make_shared<Node>(Node(val));
    if (position._ptr == nullptr)
    {
        if (val > _last)
        {
            std::shared_ptr<Node> s_ptr = _last;
            std::weak_ptr<Node> w_ptr(s_ptr);
            toAdd->_parent = w_ptr;
            _last.get()->_right = toAdd;
            _last = toAdd;
        }
        return insert(val).first;
    }
    if (toAdd < _first)
    {
        std::shared_ptr<Node> s_ptr = _first;
        std::weak_ptr<Node> w_ptr(s_ptr);
        toAdd->_parent = w_ptr;
        _first.get()->_left = toAdd;
        _first = toAdd;
        return const_iterator(toAdd);
    }
    insertHelper(position._ptr, toAdd);
    return const_iterator(toAdd);
}

template<typename T>
typename my_set<T>::const_iterator my_set<T>::insert(const_iterator position, rref val)
{
    if (empty())
    {
        std::shared_ptr<Node> toAdd = std::make_shared<Node>(Node(val));
        _root = toAdd, _size++, _first = toAdd, _last = toAdd;
        val = 0;
        return const_iterator(toAdd);
    }
    else if (find(val) != cend())
    {
        val = 0;
        return cend();
    }
    std::shared_ptr<Node> toAdd = std::make_shared<Node>(Node(val));
    if (position._ptr == nullptr)
    {
        if (val > _last->getData())
        {
            std::shared_ptr<Node> s_ptr = _last;
            std::weak_ptr<Node> w_ptr(s_ptr);
            toAdd->_parent = w_ptr;
            _last->_right = toAdd;
            _last = toAdd;
            val = 0;
            return const_iterator(toAdd);
        }
        val = 0;
        return insert(val).first;
    }
    if (*toAdd < *_first)
    {
        std::shared_ptr<Node> s_ptr = _first;
        std::weak_ptr<Node> w_ptr(s_ptr);
        toAdd->_parent = w_ptr;
        _first->_left = toAdd;
        _first = toAdd;
        val = 0;
        return const_iterator(toAdd);
    }
    insertHelper(position._ptr, toAdd);
    val = 0;
    return const_iterator(toAdd);
}


//----------------erase implementations---------------------
template<typename T>
void my_set<T>::eraseLeaf(std::shared_ptr<Node> val)
{
    if (val.get()->getParent() == nullptr)
    {
        val->_data = 0, val->_right.reset(), val->_left.reset(), val->_parent.reset();
        return;
    }
    if (val.get()->getParent()->_right != nullptr)
    {
        if (val.get()->getParent()->_right.get() == val.get())
        {
            val.get()->getParent()->_right = nullptr;
        }
    }
    if (val.get()->getParent()->_left != nullptr)
    {
        if (val.get()->getParent()->_left.get() == val.get())
        {
            val.get()->getParent()->_left = nullptr;
        }
    }
    val.get()->_parent.reset();
}

template<typename T>
void my_set<T>::eraseLink(std::shared_ptr<Node> val)
{
    //if val is the root, define the one child it has as nullptr and the child's parent as nullptr
    if (val->getParent() == nullptr)
    {
        (val->_right != nullptr) ? val->_right->_parent.reset(), val->_right.reset() :
        val->_left->_parent.reset(), val->_left.reset();
        return;
    }
    if (val->_right != nullptr)
    {
        (val->getParent()->_right == val) ? val->getParent()->_right = val->_right :
                val->getParent()->_left = val->_right;
        val->_right->_parent = val->_parent;
        val->_right.reset();
    }
    else if (val->_left != nullptr)
    {
        (val->getParent()->_left == val) ? val->getParent()->_left = val->_left :
                val->getParent()->_right = val->_left;
        val->_left->_parent = val->_parent;
        val->_left.reset();
    }
    val->_parent.reset();
}

template<typename T>
void my_set<T>::eraseSubroot(std::shared_ptr<Node> val)
{
    const_iterator iter(val);
    iter++;
    std::shared_ptr<Node> temp = std::make_shared<Node>(*iter);
    erase(*iter._ptr->_data);
    val = temp;
}

template<typename T>
void my_set<T>::ptrTest(my_set<T>::const_iterator iter)
{
    if (*iter._ptr->_data == *_root.get()->_data)
    {
        if (_root.get()->_right != nullptr)
        {
            _root = std::make_shared<Node>(*_root->_right);
        }
        else if (_root.get()->_left != nullptr)
        {
            _root = std::make_shared<Node>(*_root->_left);
        }
        else
        {
            _root.reset();
        }
    }
    if (*iter._ptr->_data == *_first.get()->_data)
    {
        if (*iter._ptr->_data == *_last.get()->_data)
        {
            _first.reset();
            _last.reset();
        }
        else
        {
            iter++;
            _first = std::make_shared<Node>(*iter._ptr);
        }
    }
    else if (*iter._ptr->_data == *_last.get()->_data)
    {
        iter--;
        _last = std::make_shared<Node>(*iter._ptr);
    }
}

template<typename T>
typename my_set<T>::const_iterator my_set<T>::erase(my_set<T>::const_iterator position)
{
    const_iterator successor = cend();
    if (position._ptr != nullptr)
    {
        successor = ++position;
        erase(*position._ptr->_data);
    }
    return successor;
}

template<typename T>
size_t my_set<T>::erase(const_reference val)
{
    size_t counter = 0;
    const_iterator finding;
    finding = find(val);
    if (finding != cend())
    {
        ptrTest(finding);
        if ((finding._ptr->_right == nullptr) && (finding._ptr->_left == nullptr))
        {
            eraseLeaf(finding._ptr);
        }
        else if ((finding._ptr->_right != nullptr) && (finding._ptr->_left != nullptr))
        {
            eraseSubroot(finding._ptr);
        }
        else
        {
            eraseLink(finding._ptr);
        }
        _size--, counter++;
    }
    return counter;
}

template<typename T>
typename my_set<T>::const_iterator my_set<T>::erase(my_set<T>::const_iterator first,
                                                    my_set<T>::const_iterator last)
{
    const_iterator successor = cend();
    if ((first._ptr != nullptr) && (first._ptr <= last._ptr))
    {
        for (const_iterator it = first; it != last; ++it)
        {
            successor = ++it;
            erase(it);
        }
    }
    return successor;
}


#endif //EX3_MY_SET_HPP
