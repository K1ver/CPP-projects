#ifndef S21_CONTAINERS_EXTRA_VECTOR
#define S21_CONTAINERS_EXTRA_VECTOR

#include <initializer_list>
#include <limits>
#include <stdexcept>

namespace s21 {

template <class T> class vector {
public:
  // для работы с элементами массива
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using value_type = T;
  using size_type = std::size_t;

  // конструкторы, деструктор и оператор присваивани
  vector();                                               //
  vector(size_type n);                                    //
  vector(std::initializer_list<value_type> const &items); //
  vector(const vector &v);                                //
  vector(vector &&v) noexcept;                            //
  ~vector();                                              //
  vector &operator=(const vector &v);                     //
  //   vector& operator=(vector&& v) noexcept;

  // методы для доступа к элементам
  reference at(size_type pos);                     //
  const_reference at(size_type pos) const;         //
  reference operator[](size_type pos);             //
  const_reference operator[](size_type pos) const; //
  const_reference front() const;                   //
  const_reference back() const;                    //
  iterator data();                                 //

  // методы для итераторов
  iterator begin();             //
  iterator end();               //
  const_iterator begin() const; //
  const_iterator end() const;   //

  // методы для информации о состоянии контейнера
  bool empty() const noexcept; //
  size_type size() const noexcept;
  size_type max_size() const noexcept; //
  void reserve(size_type size);
  size_type capacity() const noexcept;
  void shrink_to_fit(); //

  // публичные методы для изменения контейнера
  void clear();                                         //
  iterator insert(iterator pos, const_reference value); //
  void erase(iterator pos);                             //
  void push_back(const_reference value);                //
  void pop_back();                                      //
  void swap(vector &other);                             //

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args); //

  template <typename... Args> void insert_many_back(Args &&...args); //
private:
  // Опр типов
  value_type *elements_ = nullptr;
  size_type size_ = 0;
  size_type capacity_ = 0;
};
} // namespace s21

#include "s21_vector.tpp"

#endif
