#ifndef PLAYGROUND_H
#define PLAYGROUND_H

template <class T>
class Array2D {
  T** a;
  int length;

 public:
  Array2D(int width, int height) : width(width), height(height), length(width * height) {
    a = new T*[width];
    *a = new T[length];
    for (int i = 1; i < height; i++) {
      a[i] = a[i - 1] + width;
    }
  }

  T*& operator[](int i) { return a[i]; }
  const T*& operator[](int i) const { return a[i]; }

  virtual ~Array2D() {
    delete[] * a;
    delete[] a;
    a = nullptr;
  }
  int width, height;
};

#endif