#ifndef CPP2_S21_CONTAINERS_QUEUE_HPP
#define CPP2_S21_CONTAINERS_QUEUE_HPP

#include "../List/s21_list.hpp"

namespace s21 {

template <typename T> class queue {
public:
  using value_type = T; // параметр шаблона T
  using reference = T &; // T &определяет тип ссылки на элемент
  using const_reference =
      const T &; // const T &определяет тип константной ссылки
  using size_type = size_t; // size_tопределяет тип размера контейнера
                            // (стандартный тип — size_t)
  using Container = list<T>;

  ////конструкторы
  queue(); // empty stack
  queue(std::initializer_list<value_type> const
            &items);           // construktor c zadanimi dannimi
  queue(const queue &s);       // copy
  queue(queue &&s);            // constr peremeshenia
  ~queue();                    // destructor
  queue &operator=(queue &&s); // perehruzka dla peremeshenia

  //// доступ
  const_reference front(); // доступ к first
  const_reference back();  // доступ к last

  bool empty();     // проверка на suck
  size_type size(); // возврат колво элементов

  void push(const_reference value); // вставляет элемент в конец
  void pop();              // удаляет первый элемент
  void swap(queue &other); // меняет местами содержимое

  template <typename... Args>
  void insert_many_back(
      Args &&...args); // Добавляет новые элементы в конец контейнера.

private:
  Container container_;
};

} // namespace s21

#include "s21_queue.tpp"
#endif // CPP2_S21_CONTAINERS_QUEUE_HPP
