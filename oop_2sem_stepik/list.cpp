#include <assert.h>
#include <algorithm>
#include <stdexcept>
#include <cstddef>
#include <utility>

namespace stepik
{
  template <class Type>
  struct node
  {
    Type value;
    node* next;
    node* prev;

    node(const Type& value, node<Type>* next, node<Type>* prev)
      : value(value), next(next), prev(prev)
    {
    }
  };

  template <class Type>
  class list; //forward declaration

  template <class Type>
  class list_iterator
  {
  public:
    typedef ptrdiff_t difference_type;
    typedef Type value_type;
    typedef Type* pointer;
    typedef Type& reference;
    typedef size_t size_type;
    typedef std::forward_iterator_tag iterator_category;

    list_iterator()
      : m_node(NULL)
    {
    }

    list_iterator(const list_iterator& other)
      : m_node(other.m_node)
    {
    }

    list_iterator& operator = (const list_iterator& other)
    {
        m_node = other.m_node;
        return *this;
    }

    bool operator == (const list_iterator& other) const
    {
        return m_node == other.m_node;
    }

    bool operator != (const list_iterator& other) const
    {
        return m_node != other.m_node;
    }

    reference operator * ()
    {
        return m_node->value;
    }

    pointer operator -> ()
    {
        return &(m_node->value);
    }

    list_iterator& operator ++ ()
    {
        m_node = m_node->next;
        return *this;
    }

    list_iterator operator ++ (int)
    {
        auto temp_iter = *this;
        ++(*this);
        return temp_iter;
    }

  private:
    friend class list<Type>;

    list_iterator(node<Type>* p)
      : m_node(p)
    {
    }

    node<Type>* m_node;
  };

  template <class Type>
  class list
  {
  public:
    typedef Type value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef list_iterator<Type> iterator;

    list()
      : m_head(nullptr), m_tail(nullptr)
    {
    }

    ~list()
    {
        clear();
    }

    list(const list& other):
      list()
    {
        auto t_node = other.m_head;
        while(t_node){
            push_back(t_node->value);
            t_node = t_node->next;
        }
    }

    list(list&& other):
      list()
    {
        if(this != &other){
            std::swap(m_head, other.m_head);
            std::swap(m_tail, other.m_tail);
        }
    }

    list& operator= (const list& other)
    {
        if(this != &other){
            list tmp(other);
            std::swap(m_head, tmp.m_head);
            std::swap(m_tail, tmp.m_tail);
        }
        return *this;
    }

    list::iterator begin()
    {
      return iterator(m_head);
    }

    list::iterator end()
    {
      return iterator();
    }

    void push_back(const value_type& value)
    {
        auto new_node =  new node<Type>(value, nullptr, nullptr);
        if(empty()){
            m_head = new_node;
            m_tail = new_node;
        }
        else{
            new_node->prev = m_tail;
            m_tail->next = new_node;
            m_tail = new_node;
        }
    }

    void push_front(const value_type& value)
    {
        auto new_node = new node<Type>(value, nullptr, nullptr);
        if(empty()){
            m_head = new_node;
            m_tail = new_node;
        }
        else{
            new_node->next = m_head;
            m_head->prev = new_node;
            m_head = new_node;
        }
    }

    reference front()
    {
      return m_head->value;
    }

    const_reference front() const
    {
      return m_head->value;
    }

    reference back()
    {
      return m_tail->value;
    }

    const_reference back() const
    {
      return m_tail->value;
    }

    void pop_front()
    {
        if(empty()) return;
        
        if(size() == 1){
            delete m_head;
            m_head = nullptr;
            m_tail = nullptr;
        }
        else{   
            auto t_head = m_head;
            m_head = m_head->next;
            m_head->prev = nullptr;
            delete t_head;
        }
    }

    void pop_back()
    {
        if(empty()) return;
        
        if(size() == 1){
            delete m_head;
            m_head = nullptr;
            m_tail = nullptr;
        }
        else{   
            auto t_tail = m_tail;
            m_tail = m_tail->prev;
            m_tail->next = nullptr;
            delete t_tail;
        }
    }

    void clear()
    {
        while(m_head){
            auto t_head = m_head;
            m_head = m_head->next;
            delete t_head;
        }
        m_tail = nullptr;
    }

    bool empty() const
    {
      if(m_head)
          return 0;
      return 1;
    }

    size_t size() const
    {
        auto t_node = m_head;
        size_t size = 0;
        while(t_node){
            size++;
            t_node = t_node->next;
        }
        return size;
    }

    iterator insert(iterator pos, const Type& value)
    {
        if(pos.m_node == nullptr){
            push_back(value);
            return iterator(m_tail);
        }
        
        if(pos.m_node == m_head){
            push_front(value);
            return iterator(m_head);
        }
        
        auto new_node = new node<Type>(value, pos.m_node, pos.m_node->prev);
        pos.m_node->prev->next = new_node;
        pos.m_node->prev = new_node;
        return iterator(new_node);
    }

    iterator erase(iterator pos)
    {
        if(pos.m_node == nullptr) return iterator(nullptr);
        if(pos.m_node == m_head){
            pop_front();
            return iterator(m_head);
        }
        if(pos.m_node == m_tail){
            pop_back();
            return iterator(m_tail);
        }
        
        auto out = pos.m_node->next;
        pos.m_node->next->prev = pos.m_node->prev;
        pos.m_node->prev->next = pos.m_node->next;
        delete pos.m_node;
        return iterator(out);
    }

  private:
    //your private functions

    node<Type>* m_head;
    node<Type>* m_tail;
  };

}// namespace stepik