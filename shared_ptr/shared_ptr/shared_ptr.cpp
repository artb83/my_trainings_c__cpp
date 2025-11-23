// shared_ptr.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <memory>
#include <exception>

template <class T>
class Sptr {
public:
    Sptr(T* ptr) : m_ptr(ptr) {
        m_count = new int();
        ++(*m_count);
    }
    
    Sptr(Sptr<T>& otherSptr) {
        otherSptr.setCount(otherSptr.getCount()+1);
        this->m_count = otherSptr.counter();
        this->m_ptr = otherSptr.getPtr();
    }
    
    Sptr& operator=(const Sptr& otherSptr) {
        if (&otherSptr != this) {
            if (this->getPtr() != otherSptr.getPtr()) {
                --*(this->m_count);
                if (*(this->m_count) <= 0) {
                    delete this->m_count;
                    delete this->m_ptr;
                    this->m_ptr = nullptr;
                    this->m_count = nullptr;
                }
                this->m_ptr = otherSptr.getPtr();
                if (this->m_ptr != nullptr) {
                    this->m_count = otherSptr.counter();
                    ++*(this->m_count);
                }
            } else {
                if (this->getPtr() != nullptr) {
                    this->m_count = otherSptr.counter();
                    ++*(this->m_count);
                }
            }
        }
        return *this;
    }
    T* operator->(){
        return this->m_ptr;
    }

    T& operator*() {
        return *(this->m_ptr);
    }

    int use_count() {
        return this->getCount();
    }

    T* get() {
        return this->m_ptr;
    }

    virtual ~Sptr() {
        --(*m_count);
        std::cout << "Removed 1 ref, count=" << *m_count << "\n";
        if (*m_count <= 0) {
            delete m_ptr;
            delete m_count;
        }
    }

    int getCount() const {
        return *m_count;
    }

    int* counter() const {
        return m_count;
    }
    T* getPtr() const {
        return m_ptr;
    }
private:
    void setCount(int val) {
        *(this->m_count) = val;
    }

    T* m_ptr = nullptr;
    int* m_count = nullptr;
};


class Animal {
public:
    Animal(std::string name) : m_name(name) {
        std::cout << "Animal created\n";
    }

    virtual void talk() const {}
    void walk() const {
        std::cout << "Animal " << m_name << " is walking\n";
    }
    std::string getName() const {
        return m_name;
    }

    virtual ~Animal() {
        //throw 200;
        std::cout << "Animal " << m_name << " removed\n";
    }
protected:
    std::string m_name;
};

class Dog final : public Animal{
public:
    Dog(std::string name) : Animal(name) {
        std::cout << "Dog " << m_name << " created\n";
    }
    void talk() const override{
        std::cout << m_name << " wooof\n";
    }
    void walk() const{
        std::cout << "Dog " << m_name << " is walking\n";
    }

    void walkBase() const {
        Animal::walk();
    }

    ~Dog() {
        std::cout <<"Dog " << m_name << " removed\n";
    }
};

class Cat final : public Animal {
public:
    Cat(std::string name) : Animal(name) {
        std::cout << "Cat " << m_name << " created\n";
    }
    void talk() const override {
        std::cout << m_name << " miaaau\n";
    }
    ~Cat() {
        std::cout << "Cat " << m_name << " removed\n";
    }
};

class Mouse final : public Animal {
public:
    Mouse(std::string name) : Animal(name) {
        std::cout << "Mouse " << m_name << " created\n";
    }
    void talk() const override {
        std::cout << m_name << " pipipi\n";
    }
    ~Mouse() {
        std::cout << "Mouse " << m_name << " removed\n";
    }
};

int main()
{
    try{
        Animal* dptr = new Dog("Fido");
        dptr->talk();
        dptr->walk();
        delete dptr;
    }
    catch (const int& e) {
        std::cout << "Exception " << e << std::endl;
    }

    /*Sptr<Dog> dog_sp(new Dog("Fido"));
    std::cout << dog_sp->getName() << " use_count=" << dog_sp.use_count() << std::endl;
    Sptr<Dog> dog_sp2(dog_sp);
    std::cout << dog_sp2->getName() << " use_count2=" << dog_sp2.use_count() << std::endl;
    dog_sp2->talk();
    Dog* dog_ptr = dog_sp.get();

    dog_ptr->talk();
    std::cout << dog_ptr->getName() << " use_count=" << dog_sp.use_count() << std::endl;

    try {
        Sptr<Dog> dog_sp3(new Dog("Bandit"));
        dog_sp3->talk();
        std::cout << dog_sp3->getName() << " use_count3=" << dog_sp3.use_count() << std::endl;
        dog_sp3 = dog_sp2;
        {
            Mouse mouse("Jerry");
            mouse.talk();
        }
        std::cout << dog_sp3->getName() << " use_count3=" << dog_sp3.use_count() << std::endl;
        Cat cat("Mitzi");
        cat.talk();
    }
    catch (std::exception& ex)
    {
        std::cout << "Exception: " << ex.what() << std::endl;
    }
    catch (const std::string& ex) {
        std::cout << "Exception: " << ex << std::endl;
    }
    catch (...) {
        std::cout << "Exception" << std::endl;
    }*/

    return 0;
}


//int main()
//{
//    std::shared_ptr<Dog> dog_sp(new Dog("Fido"));
//    std::cout << dog_sp->getName() << " use_count=" << dog_sp.use_count() << std::endl;
//    std::shared_ptr<Dog> dog_sp2(dog_sp);
//    std::cout << dog_sp2->getName() << " use_count2=" << dog_sp2.use_count() << std::endl;
//    dog_sp2->talk();
//    Dog* dog_ptr = dog_sp.get();
//
//    dog_ptr->talk();
//    std::cout << dog_ptr->getName() << " use_count=" << dog_sp.use_count() << std::endl;
//
//    try {
//        std::shared_ptr<Dog> dog_sp3(new Dog("Bandit"));
//        dog_sp3->talk();
//        std::cout << dog_sp3->getName() << " use_count3=" << dog_sp3.use_count() << std::endl;
//    } catch (std::exception& ex)
//    {
//        std::cout << "Exception: " << ex.what() << std::endl;
//    } catch (const std::string& ex) {
//        std::cout << "Exception: " << ex << std::endl;
//    } catch (...) {
//        std::cout << "Exception" << std::endl;
//    }
//
//    return 0;
//}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
