// find_single.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#include <memory>
/*
In array of integers, nums, all elements have their equal pair.
Find a single element that has no pair and return it.
*/
int findSingle(std::vector<int>& nums) {
    int size = nums.size();
    int curNum = -1;
    int res = 0;
    for (int i = 0; i < size; i++) {
        res ^= nums[i];
        printf("res=%d\n", res);
        if(res!=0 && res!=nums[i]) {
            curNum = res;
        }
        else curNum = 0;
    }
    return curNum;
}

class Dog {
public:
    Dog(std::string name) : m_name(name) {
        std::cout << "Dog " << m_name << " created\n";
    }
    void bark() {
        std::cout << m_name << " woooof\n";
    }
    ~Dog() {
        std::cout << m_name << " removed\n";
    }

private:
    std::string m_name;
};

int main()
{
    std::cout << "Hello World!\n";
    std::vector<int> nums( { 7, 2, 3, 1, 3, 4, 4, 2, 5, 7, 1,11,5 } );
    //std::vector<int> nums({ 4,1,25,1,4,3,25,3 });
    //std::vector<int> nums({ 1,1,33,2,5,2,33 });
    //int single = findSingle(nums);
    //printf("Single num=%d\n", single);
    
    std::shared_ptr<Dog> dog_sp(new Dog("Fido"));
    int use_count = dog_sp.use_count();
    printf("use_count1=%d\n", use_count);
    std::shared_ptr<Dog> dog_sp2(dog_sp);
    use_count = dog_sp2.use_count();
    printf("use_count2=%d\n", use_count);

    Dog* dog_ptr = dog_sp.get();
    dog_ptr->bark();
    //std::shared_ptr<Dog> dog_sp3(dog_ptr);
    dog_ptr->bark();
    //use_count = dog_sp3.use_count();
    //printf("use_count3=%d\n", use_count);

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
