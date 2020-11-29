#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>

namespace stepik
{
  template <typename Type>
  class vector
  {
  public:
    typedef Type* iterator;
    typedef const Type* const_iterator;

    typedef Type value_type;

    typedef value_type& reference;
    typedef const value_type& const_reference;

    typedef std::ptrdiff_t difference_type;

    explicit vector(size_t count = 0):
      m_first(new Type[count]), m_last(&(m_first[count]))
    {}

    template <typename InputIterator>
    vector(InputIterator first, InputIterator last):
      m_first(new Type[last-first]), m_last(m_first + (last-first))
    {
      std::copy(first, last, m_first);
    }

    vector(std::initializer_list<Type> init):
      vector(init.begin(), init.end())
    {}

    vector(const vector& other):
      vector(other.begin(), other.end())
    {}

    vector(vector&& other):
      m_first(other.m_first), m_last(other.m_last)
    {
      other.m_first = nullptr;
      other.m_last = nullptr;
    }

    ~vector()
    {
      delete [] m_first;
    }

    //assignment operators
    vector& operator=(const vector& other)
    {
      if(this != &other){
          vector temp(other);
          std::swap(m_first, temp.m_first);
          std::swap(m_last, temp.m_last);
      }
      return *this;
    }

    vector& operator=(vector&& other)
    {
      if(this != &other){
          std::swap(m_first, other.m_first);
          std::swap(m_last, other.m_last);
      }
      return *this;
    }

    // assign method
    template <typename InputIterator>
    void assign(InputIterator first, InputIterator last)
    {
      vector temp(first, last);
      std::swap(m_first, temp.m_first);
      std::swap(m_last, temp.m_last);
    }

    // resize methods
    void resize(size_t count)
    {
      vector temp(count);
      size_t real_size = (count < size()) ? count : size();
      std::copy(m_first, m_first + real_size, temp.m_first);
      std::swap(m_first, temp.m_first);
      std::swap(m_last, temp.m_last);
    }

    //erase methods
    iterator erase(const_iterator pos)
    {
      difference_type diff = pos - m_first;
      std::rotate(m_first+diff, m_first+diff+1, m_last);
      resize(size() - 1);
      return m_first + diff;
    }

    iterator erase(const_iterator first, const_iterator last)
    {
      difference_type diff_to_first = first - m_first;
      difference_type diff_between = last - first;
      std::rotate(m_first + diff_to_first,
                  m_first + diff_to_first + diff_between,
                  m_last);
      resize(size() - diff_between);
      return m_first + diff_to_first; 
    }

    //insert methods
    iterator insert(const_iterator pos, const Type& value)
    {
      difference_type diff = pos - m_first;
      resize(size() + 1);
      std::rotate(m_first+diff, m_last-1, m_last);
      m_first[diff] = value;
      return m_first + diff;
    }

    template <typename InputIterator>
    iterator insert(const_iterator pos, InputIterator first, InputIterator last)
    {
      difference_type current = last - first;
      iterator temp = const_cast<iterator>(pos);
      while(current)
      {
          current--;
          temp = insert(temp, *(first + current));
      }
      return temp;
    }

    //push_back methods
    void push_back(const value_type& value)
    {
      insert(m_last, value);
    }

    //at methods
    reference at(size_t pos)
    {
      return checkIndexAndGet(pos);
    }

    const_reference at(size_t pos) const
    {
      return checkIndexAndGet(pos);
    }

    //[] operators
    reference operator[](size_t pos)
    {
      return m_first[pos];
    }

    const_reference operator[](size_t pos) const
    {
      return m_first[pos];
    }

    //*begin methods
    iterator begin()
    {
      return m_first;
    }

    const_iterator begin() const
    {
      return m_first;
    }

    //*end methods
    iterator end()
    {
      return m_last;
    }

    const_iterator end() const
    {
      return m_last;
    }

    //size method
    size_t size() const
    {
      return m_last - m_first;
    }

    //empty method
    bool empty() const
    {
      return m_first == m_last;
    }

  private:   
    reference checkIndexAndGet(size_t pos) const
    {
      if (pos >= size())
      {
        throw std::out_of_range("out of range");
      }

      return m_first[pos];
    }

    //your private functions

  private:
    iterator m_first;
    iterator m_last;
  };
}// namespace stepik