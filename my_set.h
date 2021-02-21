//
// Created by daniel.brown1 on 9/16/18.
//

#ifndef EX3_MY_SET_H
#define EX3_MY_SET_H


#include <cstdlib>
#include <utility>
#include <memory>

/**
 * my_set template class. represents a set of unique keys of type T represented as a BST.
 * @tparam T- the template type.
 */
template<typename T>
class my_set
{
private:
    /**
     * a nested class representing a node in a my_set instance with T type data.
     */
    class Node
    {
    private:
        /**a weak pointer to the Node's parent**/
        std::weak_ptr<Node> _parent;
        /**a shared pointer to the Node's right child**/
        std::shared_ptr<Node> _right = nullptr;
        /**a shared pointer to the Node's left  child**/
        std::shared_ptr<Node> _left = nullptr;
        /**a shared pointer to the Node's data of type T**/
        std::shared_ptr<T> _data;

    public:
        friend class my_set;

        //----------------constructors and destructor---------------------

        /**
         * default constructor;
         */
        Node() : _data(std::make_shared<T>(T()))
        {};

        /**
         * copy constructor
         * @param _new- node to copy
         */
        Node(const Node &_other) : _right(_other._right), _left(_other._left),
                                   _parent(_other._parent),
                                   _data(std::make_shared<T>(*_other._data.get()))
        {};

        /**
         * move constructor
         * @param move- node to move.
         */
        Node(Node &&move) noexcept
        {
            _parent = move._parent;
            _left = move._left;
            _right = move._right;
            _data = move._data;
            move._data.reset(), move._parent.reset(), move._right.reset(), move._left.reset();
        }

        /**
         * T const reference arg constructor.
         * @param t- a const reference to a T typed element.
         */
        explicit Node(const T &t) : _data(std::make_shared<T>(T(t)))
        {};

        /**
         * a move constructor.
         * @param t- T type rvalue reference element
         */
        explicit Node(T &&t) noexcept
        {
            _right.reset();
            _left.reset();
            _parent = std::weak_ptr<Node>();
            _data = std::make_shared<T>(T(t));
            t = 0;
        }

        /**
         * default destructor.
         */
        ~Node() = default;

        //----------------access functions--------------------

        /**
         * parent getter function.
         * @return- a shared ptr to the node's parent.
         */
        std::shared_ptr<Node> getParent()
        {
            std::shared_ptr<Node> sp;
            sp = this->_parent.lock();
            return sp;
        }

        /**
         * getter function for the node's data
         * @return- a reference to the node's data of type T.
         */
        T &getData()
        {
            return *_data;
        }

        /**
         * getter function for a const node's data
         * @return- a reference to the node's data of type T.
         */
        T &getData() const
        {
            return *_data;
        }

        //---------------operators overloading----------------

        /**
 * move assignment operator overload.
 * @param other- Node to move.
 * @return- reference to this.
 */
        Node &operator=(Node &&other) noexcept
        {
            std::swap(*this->_data, *other._data);
            std::swap(this->_right, other._right);
            std::swap(this->_left, other._left);
            std::swap(this->_parent, other._parent);
            return *this;
        }

        /**
         * assignment operator overload.
         * @param _other- Node to copy
         * @return- reference to this.
         */
        Node &operator=(const Node &_other)
        {
            _right = _other._right, _left = _other._left, _parent = _other._parent;
            _data = std::make_shared<T>(T(_other._data));
        }

        /**
         * bigger-than operator overload.
         * @param rhs- Node to be compared with
         * @return- true iff (this._data > rhs._data) == true, false otherwise.
         */
        bool operator>(const Node &rhs)
        { return (this->getData() > rhs.getData()); }

        /**
         * bigger-or-equal-than operator overload.
         * @param rhs- Node to be compared with
         * @return- true iff (this.getData() >= rhs.getData()) == true, false otherwise.
         */
        bool operator>=(const Node &rhs)
        { return (this->getData() >= rhs.getData() ); }

        /**
         * smaller-than operator overload.
         * @param rhs- Node to be compared with
         * @return- true iff (this.getData() < rhs.getData()) == true, false otherwise.
         */
        bool operator<(const Node &rhs)
        { return (this->getData() < rhs.getData() ); }

        /**
         * smaller-or-equal-than operator overload.
         * @param rhs- Node to be compared with
         * @return- true iff (this.getData() <= rhs.getData()) == true, false otherwise.
         */
        bool operator<=(const Node &rhs)
        { return (this->getData() <= rhs.getData() ); }

        /**
         * equality operator overload.
         * @param rhs- Node to be compared with
         * @return- true iff (this.getData() == rhs.getData()) = true, false otherwise.
         */
        bool operator==(const Node &rhs)
        { return (this->getData() == rhs.getData() ); }

        /**
         * non-equality operator overload.
         * @param rhs- Node to be compared with
         * @return- true iff (this.getData() != rhs.getData()) = true, false otherwise.
         */
        bool operator!=(const Node &rhs)
        { return (this->getData() != rhs.getData() ); }
    };

    /**a shared pointer to the BST's root**/
    std::shared_ptr<my_set::Node> _root = nullptr;
    /**a shared pointer to the BST's smallest key**/
    std::shared_ptr<my_set::Node> _first = nullptr;
    /**a shared pointer to the BST's bigest key**/
    std::shared_ptr<my_set::Node> _last = nullptr;
    /**the BST's size**/
    std::size_t _size = 0;

public:

    /**
     * a nested class of a const iterator.
     */
    class const_iterator
    {
    public:
        /**a shared pointer to the iterator's current pointed node**/
        std::shared_ptr<Node> _ptr;
        /**a boolean flag, true iff crend() or crbegin() were called**/
        bool _isReversed;
        /**defining my_set as a friend function**/
        friend class my_set;

    //----------------constructors and destructor---------------------

        /**
         * default construct
         */
        const_iterator() : _ptr(nullptr), _isReversed(false)
        {};

        /**
         * _isReversed arg construct
         */
        explicit const_iterator(bool isReversed) : _ptr(nullptr), _isReversed(isReversed)
        {};


        /**
         * node argument constructor.
         * @param node- node to point to.
         */
        explicit const_iterator(std::shared_ptr<Node> node, bool isReversed = false) : _ptr(node),
        _isReversed(isReversed)
        {};

        /**
         * copy constructor.
         * @param other- iterator to copy.
         */
        const_iterator(const const_iterator &other) : _ptr(other._ptr),
                                                      _isReversed(other._isReversed)
        {};

        /**
         * move constructor
         * @param move- the iterator to move.
         */
        const_iterator(const_iterator &&move) noexcept
        {
            std::swap(_ptr, move._ptr);
            (_isReversed == move._isReversed) ? (_isReversed = move._isReversed) : (_isReversed =
                                                                                            !_isReversed, move._isReversed = !move._isReversed);
        }

        /**
         * destructor.
         */
        ~const_iterator() = default;

    //----------------access functions--------------------

        /**
         * finds the minimum node in the subtree rooted by current
         * @param current- a node, the root of the subtree to be searched.
         * @return- a shared ptr to the node
         */
        std::shared_ptr<Node> findMinimum(std::shared_ptr<Node> current)
        {
            while (current->_left != nullptr)
            {
                current = current->_left;
            }
            return current;
        }

        /**
         * finds the maximum node in the subtree rooted by current
         * @param current- a node, the root of the subtree to be searched.
         * @return- a shared ptr to the node
         */
        std::shared_ptr<Node> findMaximum(std::shared_ptr<Node> current)
        {
            while (current->_right != nullptr)
            {
                current = current->_right;
            }
            return current;
        }

        /**
         * gets the successor of the node iterator's current node
         * @return- the node's successor.
         */
        std::shared_ptr<Node> getSuccessor()
        {
            if (_ptr != nullptr)
            {
                if (_ptr->_right != nullptr)
                {
                    return findMinimum(_ptr->_right);
                }
                if (!_ptr->_parent.expired())
                {
                    std::shared_ptr<Node> parent = _ptr->_parent.lock(), current = _ptr;
                    while ((parent != nullptr) && (current == parent->_right))
                    {
                        current = parent;
                        parent = parent->_parent.lock();
                    }
                    return parent;
                }
                return _ptr->_right;
            }
            return _ptr;
        }

        /**
         * gets the predecessor of the node iterator's current node
         * @return- the node's predecessor.
         */
        std::shared_ptr<Node> getPredecessor()
        {
            if (_ptr != nullptr)
            {
                if (_ptr->_left != nullptr)
                {
                    return findMaximum(_ptr->_left);
                }
                if (!_ptr->_parent.expired())
                {
                    std::shared_ptr<Node> parent = _ptr->_parent.lock(), current = _ptr;
                    while ((parent != nullptr) && (current == parent->_left))
                    {
                        current = parent;
                        parent = parent->_parent.lock();
                    }
                    return parent;
                }
                return _ptr->_left;
            }
            return _ptr;
        }

    //---------------operators overloading----------------

        /**
 * assignment operator
 * @param rhs- right hand side iterator.
 * @return- the new iterator.
 */
        const_iterator &operator=(const const_iterator &rhs)
        {
            _ptr = rhs._ptr;
            _isReversed = rhs._isReversed;
            return *this;
        }

        /**
         * move assignment operator
         * @param move- right hand side iterator to move.
         * @return- the new iterator.
         */
        const_iterator &operator=(const_iterator &&move) noexcept
        {
            _ptr = move._ptr;
            move._ptr = nullptr;
            _isReversed = move._isReversed;
            move._isReversed = false;
            return *this;
        }

        /**
         * dereference operator
         * @return- pointer's data
         */
        const T &operator*()
        { return _ptr->getData(); }

        /**
         * dereference pointer's data.
         * @return- pointer to pointer's data
         */
        const std::shared_ptr<T> operator->()
        { return _ptr->_data; }

        /**
         * pre-increment operator
         * @return- this
         */
        const_iterator &operator++()
        {
            _ptr = (!_isReversed) ? getSuccessor() : getPredecessor();
            return *this;
        }

        /**
         * post-increment operator
         * @param num- number to increment
         * @return- new operator
         */
        const const_iterator operator++(int)
        {
            const_iterator copy(*this);
            this->operator++();
            return copy;
        }

        /**
         * pre-decrement operator
         * @return- this
         */
        const_iterator &operator--()
        {
            _ptr = (_isReversed) ? getSuccessor() : getPredecessor();
            return *this;
        }

        /**
         * post-decrement operator
         * @param num- number to decrement
         * @return- new iterator
         */
        const const_iterator operator--(int)
        {
            const_iterator copy(*this);
            this->operator--();
            return copy;
        }

        /**
         * boolean equality operator
         */
        bool operator==(const const_iterator &rhs) const
        {
            return (_ptr == rhs._ptr);
        }

        /**
         * boolean inequality operator
         */
        bool operator!=(const const_iterator &rhs)
        {
            return !(*this == rhs);
        }

    };

//--------------------typedefs---------------------------

    /**const reference T typedef **/
    typedef const T &const_reference;

    /**rvalue reference (move) T typedef **/
    typedef T &&rref;

//----------------constructors and destructor---------------------

    /**
	 * this function swaps the content of two my_set instances
	 * @param set1- my_set instance
	 * @param set2- my_set instance
	 */
    friend void swap(my_set &set1, my_set &set2) noexcept
    {
        std::swap(set1._root, set2._root);
        std::swap(set1._first, set2._first);
        std::swap(set1._last, set2._last);
        size_t temp = set1._size;
        set1._size = set2._size;
        set2._size = temp;
    }

    /**
     * this function swaps the content of this with other
     * @param other- my_set instance to be swapped with
     */
    void swap(my_set &other) noexcept
    {
        _root = other._root;
        _first = other._first;
        _last = other._last;
        _size = other._size;
    }
    // _root(nullptr), _first(nullptr), _last(nullptr), _size(0)
    /**
     * default constructor.
     */
    my_set() : _root(nullptr), _first(nullptr), _last(nullptr)
    {};

    /**
     * copy constructor.
     * @param other- instance to copy.
     */
    my_set(const my_set &other) : _root(nullptr), _first(nullptr), _last(nullptr)
    {
        for (const_iterator it = other.cbegin(); it != other.cend(); ++it)
        {
            insert(*it);
        }
    }

    /**
     * move constructor.
     * @param other- instance to move
     */
    my_set(my_set &&other) noexcept : _root(nullptr), _first(nullptr), _last(nullptr)
    {
        swap(other);
    }

    /**
     * iterator constructor.
     * @param first- the place of the first element to copy.
     * @param last- the after last place to copy.
     */
    template<class InputIterator>
    my_set(InputIterator first, InputIterator last) : _root(nullptr), _first(nullptr),
                                                      _last(nullptr)
    {
        for (InputIterator it = first; it != last; ++it)
        {
            insert(*it);
        }
    };

    /**
     * class destructor.e
     */
    ~my_set() = default;

//----------------operators---------------------

    /**
     * = move operator overload
     * @param other- my_set to copy.
     * @return- the updated this my_set instance.
     */
    my_set<T> &operator=(my_set &&other) noexcept
    {
        _root = other._root;
        _size = other._size;
        _first = other._first;
        _last = other._last;
        return *this;
    }

    /**
     * = operator overload
     * @param other- my_set to copy.
     * @return- the updated this my_set instance.
     */
    my_set<T> &operator=(const my_set &other)
    {
        clear(), _size = 0, _last = nullptr, _first = nullptr, _root = nullptr;
        for (const_iterator it = other.cbegin(); it != other.cend(); ++it)
        {
            insert(*it);
        }
        return *this;
    }


//----------------insert declarations ---------------------

    /**
     * an aid function for the insert function. takes care of finding the suitable position for
     * the new node and of pointer updating for the new node and for his new parent and children.
     * recursive function.
     * @param current- current root of a certain subtree in the set. called with current = _root.
     * @param toAdd- the node to add.
     */
    void insertHelper(std::shared_ptr<Node> current, std::shared_ptr<Node> toAdd);

    /**
     * inserts the input T element to the set.
     * @param toInsert- T to insert.
     * @return- return a pair, with its member pair::first set to an iterator pointing to either
     *      the newly inserted element or to the equivalent element already in the set.
     *      The pair::second element in the pair is set to true if a new element was inserted
     *      or false if an equivalent element already existed.
     */
    std::pair<const_iterator, bool> insert(const_reference val);

    /**
     * inserts the input T element to the set with move semantics.
     * @param toInsert- T to insert.
     * @return- return a pair, with its member pair::first set to an iterator pointing to either
     *      the newly inserted element or to the equivalent element already in the set.
     *      The pair::second element in the pair is set to true if a new element was inserted
     *      or false if an equivalent element already existed.
     */
    std::pair<const_iterator, bool> insert(rref val);

    /**
     * insert with a hint.
     * @param position- a hint to the position val might be inserted to
     * @param val- val to add to set.
     * @return- return an iterator pointing to either the newly inserted element or to the element
     *          that already had its same value in the set.
     */
    const_iterator insert(const_iterator position, const const_reference val);

    /**
     * insert with a hint and move semantics.
     * @param position- a hint to the position val might be inserted to
     * @param val- val to add to set.
     * @return- return an iterator pointing to either the newly inserted element or to the element
     *          that already had its same value in the set.
     */
    const_iterator insert(const_iterator position, rref val);

    /**
     * aid function for the insert with last and first iterator args function. does the insertion
     * in case all is valid.
     * @tparam InputIterator- a generic input iterator
     * @param first- iterator to first.
     * @param last- iterator to last.
     */
    template<class InputIterator>
    void iteratorInsertHelper(InputIterator first, InputIterator last)
    {
        for (InputIterator it = first; it != last; ++it)
        {
            insert(*it);
        }
    }

    /**
     * insert all elements from first (including) to last (excluding)
     * @tparam InputIterator- a generic input iterator
     * @param first- iterator to first.
     * @param last- iterator to last.
     */
    template<class InputIterator>
    void insert(InputIterator first, InputIterator last)
    {
        if (first != nullptr)
        {
            if (last != nullptr)
            {
                if (*first <= *(last))
                {
                    iteratorInsertHelper(first, last);
                }
            }
            else
            {
                iteratorInsertHelper(first, last);
            }
        }
    }


//----------------erase declarations ---------------------

    /**
     * aid function to check whether the node to be deleted is the root/last/first, and replace
     * it in case it is
     * @param iter- iterator to the node to be deleted
     */
    void ptrTest(my_set<T>::const_iterator iter);

    /**
     * erases a leaf node.
     * @param val - node to delete
     */
    void eraseLeaf(std::shared_ptr<Node> val);

    /**
     * erases a node with one child.
     * @param val - node to delete
     */
    void eraseLink(std::shared_ptr<Node> val);

    /**
     * erases a node with two children.
     * @param val - node to delete
     */
    void eraseSubroot(std::shared_ptr<Node> val);

    /**
     * erases the input T element from the set.
     * @param position- iterator to the node to erase.
     * @return true iff erasure is successful.
     */
    const_iterator erase(const_iterator position);

    /**
     *
     * @param val- value to be removed
     * @return- number of elements erased
     */
    size_t erase(const_reference val);

    /**
     * remove all elements from first (including) to last (excluding)
     * @param first- iterator to first.
     * @param last- iterator to last.
     */
    const_iterator erase(const_iterator first, const_iterator last);

//----------------find, empty, size and clear ---------------------

    /**
    * find value in the set.
    * @param val- the type T value to be found.
    * @return- An iterator to the element, if val is found, or set::end otherwise.
    */
    const_iterator find(const_reference val)
    {
        if (!empty())
        {
            if ((val > *crbegin()) || (val < *cbegin()))
            {
                return cend();
            }
            for (const_iterator it = cbegin(); it != cend(); ++it)
            {
                if (val < *it)
                {
                    return cend();
                }
                if (*it == val)
                {
                    return it;
                }
            }
        }
        return cend();
    }

    /**
     * checks if the set is empty
     * @return- true iff there is at least one item in the set, false otherwise.
     */
    bool empty() const noexcept
    {
        return (_root.get() == nullptr);
    }

    /**
     * getter for the size of the set.
     * @return- the size of the set.
     */
    size_t size() const noexcept
    {
        return _size;
    }

    /**
     * makes this my_set to an empty set (zero elements).
     */
    void clear() noexcept
    {
        this->erase(const_iterator(_first), const_iterator(_last));
        _root = nullptr, _size = 0, _first = nullptr, _last = nullptr;
    }

//----------------const_iterator getters ---------------------

    /**
     * returns an iterator to the first (smallest) object.
     * @return- iterator to the first (smallest) object.
     */
    const_iterator cbegin() const noexcept
    {
        return const_iterator(_first);
    }

    /**
     * returns a null pointer, the one after last element.
     * @return- nullptr.
     */
    const_iterator cend() const noexcept
    {
        return const_iterator();
    }

    /**
     * returns a reverse iterator to the reverse beginning (which is the last) object.
     * @return- iterator to _last.
     */
    const_iterator crbegin() const noexcept
    {
        return const_iterator(_last, true);
    }

    /**
     * returns a reverse iterator to the reverse end (nullptr)
     * @return- nullptr.
     */
    const_iterator crend() const noexcept
    {
        return const_iterator(true);
    }
};


#include "my_set.hpp"

#endif //EX3_MY_SET_H
