#ifndef TSINGLETON_H
#define TSINGLETON_H

template <class T>
class TSingleton {
 public:
    static T& getInstance() {
        static T instance;
        return instance;
    }
  private:
    TSingleton(TSingleton const&);    // copy ctor hidden
    TSingleton& operator=(TSingleton const&);  // assign op hidden
  protected:
    ~TSingleton(){};
    TSingleton(){};
};

#endif //TSINGLETON_H
