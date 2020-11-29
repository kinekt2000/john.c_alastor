namespace stepik
{
  template <typename T>
  class shared_ptr
  {
      template<class A> friend class shared_ptr;
      
  public:
    explicit shared_ptr(T *ptr = 0):
      ptr(ptr), p_cnt((ptr ==  nullptr)?nullptr:new long(1))
    {}

    ~shared_ptr()
    {
      if(use_count() > 1){
          (*p_cnt) --;
      }
      else{
          delete ptr;
          ptr = nullptr;
          
          delete p_cnt;
          p_cnt = nullptr;
      }
    }

    shared_ptr(const shared_ptr & other):
      ptr(other.ptr), p_cnt(other.p_cnt)
    {
      if(use_count())
          (*p_cnt)++;
    }
      
    template<typename A>
    shared_ptr(const shared_ptr<A> other):
      ptr(other.ptr), p_cnt(other.p_cnt)
    {
      if(use_count())
          (*p_cnt)++;
    }

    shared_ptr& operator=(const shared_ptr & other)
    {
      if(ptr != other.ptr){
          this->~shared_ptr();
          ptr = other.ptr;
          p_cnt = other.p_cnt;
          if(use_count()){
              (*p_cnt) ++;
          }
      }
      return *this;
    }
     
    template<typename A>
    shared_ptr& operator=(const shared_ptr<A> & other)
    {
      if(ptr != other.ptr){
          this->~shared_ptr();
          ptr = other.ptr;
          p_cnt = other.p_cnt;
          if(use_count()){
              (*p_cnt) ++;
          }
      }
      return *this;
    }
      
    bool operator==(const shared_ptr &other) const
    {
      return ptr == other.ptr;
    }
    
    template<typename A>
    bool operator==(const shared_ptr<A> &other) const
    {
      return ptr == other.ptr;
    }

    explicit operator bool() const
    {
      return ptr != nullptr;
    }

    T* get() const
    {
      return ptr;
    }

    long use_count() const
    {
      return (p_cnt == nullptr)?0:*p_cnt;
    }

    T& operator*() const
    {
      return *ptr;
    }

    T* operator->() const
    {
      return ptr;
    }

    void swap(shared_ptr& x) noexcept
    {
      std::swap(ptr, x.ptr);
      std::swap(p_cnt, x.p_cnt);
    }

    void reset(T *ptr = 0)
    {
      shared_ptr<T>(ptr).swap(*this);
    }

  private:
    T *ptr;
    long *p_cnt;
  };      
} // namespace stepik
