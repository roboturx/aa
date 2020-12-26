#ifndef Tek_Ton_H
#define Tek_Ton_H

#include <QtGlobal>
#include <QScopedPointer>
#include "VTKontTekkere.h"

template <class T>
class Tekton
{
private:
  typedef T* (*CreateInstance)();
public:
  static T* instance(CreateInstance create);
private:
  static void init();

  Tekton();
  ~Tekton();
  Q_DISABLE_COPY(Tekton)
  static QBasicAtomicPointer<T* (void)> create;
  static QBasicAtomicInt flag;
  static QBasicAtomicPointer<void> tptr;
  bool inited;
};

template <class T>
T* Tekton<T>::instance(CreateInstance create)
{
  Tekton::create.storeRelaxed(create);
  qTekKere(init, flag);
  return (T*)tptr.loadRelaxed();
}

template <class T>
void Tekton<T>::init()
{
  static Tekton Tekton;
  if (Tekton.inited) {
    CreateInstance createFunction = (CreateInstance)Tekton::create.loadRelaxed();
    tptr.storeRelaxed(createFunction());
  }
}

template <class T>
Tekton<T>::Tekton() {
  inited = true;
};

template <class T>
Tekton<T>::~Tekton() {
  T* createdTptr = (T*)tptr.fetchAndStoreOrdered(nullptr);
  if (createdTptr) {
    delete createdTptr;
  }
  create.storeRelaxed(nullptr);
}

template<class T> QBasicAtomicPointer<T* (void)> Tekton<T>::create = Q_BASIC_ATOMIC_INITIALIZER(nullptr);
template<class T> QBasicAtomicInt Tekton<T>::flag = Q_BASIC_ATOMIC_INITIALIZER(TekKere::CO_Request);
template<class T> QBasicAtomicPointer<void> Tekton<T>::tptr = Q_BASIC_ATOMIC_INITIALIZER(nullptr);

#endif // Tek_Ton_H
