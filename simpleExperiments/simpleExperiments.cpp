#include<limits.h>
//#include<iostream>
#include<vector>
#include<string>
#include "factoryPattern.h"

class Char {
protected:
    char ch;
    bool bDigit;
public:
    virtual char getChar(void) const = 0;
    virtual void setChar(const char chr) = 0;
    virtual bool isDigit(void) const = 0;
};

class CharToInt final : public Char {
private:
    bool bSign;
public:
    CharToInt(const char chr) {
        this->bSign = false;
        this->bDigit = false;
        this->ch = chr;
        setChar(chr);
    }
    char getChar(void) const override {
        return this->ch;
    }
    void showChar() const {
        std::cout << "current char=" << static_cast<int>(getChar()) << std::endl;
    }
    void setChar(const char chr) override {
        switch (chr) {
        case '+':
        case '-':
            this->ch = chr;
            this->bSign = true;
            break;
        default:
            if (0 <= chr - '0' && 9 >= chr - '0') {
                this->ch = chr - '0';
                this->bDigit = true;
            }
            else this->ch = chr;
        }
    }
    bool isDigit(void) const override {
        return this->bDigit;
    }

    bool isSign(void) const {
        return this->bSign;
    }
};

class ArrangeCharsToInt {
private:
    bool bFoundSign;
    bool bFoundDigits;
    bool bNegative;
    std::vector<CharToInt> charsToInts;
public:
    ArrangeCharsToInt(const std::string str) {
        bFoundDigits = false;
        bFoundSign = false;
        bNegative = false;
        setArrangement(str);
    }
    void setArrangement(std::string str) {
        for (auto ch : str) {
            if (ch != ' ') {
                CharToInt curChar(ch);
                bool bDigit = curChar.isDigit();
                bool bSign = curChar.isSign();
                if (!bDigit && !bSign) return;
                if (bFoundSign && bSign) return;
                if (bFoundSign && !bDigit) return;
                if (bFoundDigits && bSign) return;
                if (bFoundDigits && !bDigit) return;
                if (bDigit) this->charsToInts.push_back(curChar);
                if (!this->bFoundSign && bSign) {
                    this->bFoundSign = true;
                    this->bNegative = (curChar.getChar() == '-' ? true : false);
                }
                if (bDigit && !this->bFoundDigits) this->bFoundDigits = true;
            }
            else if (this->bFoundDigits || this->bFoundSign) return;
        }
    }
    std::vector<CharToInt> getArrangements(void) const {
        return this->charsToInts;
    }
    bool isNegative(void) const {
        return this->bNegative;
    }
};

class Solution {
public:
    int myAtoi(std::string s) {
        ArrangeCharsToInt arrangeChars(s);
        std::vector<CharToInt> arrangements = arrangeChars.getArrangements();
        if (arrangements.empty()) return 0;
        int nDigits = arrangements.size();
        long long result = 0;
        bool isNegative = arrangeChars.isNegative();
        int sign = (isNegative ? -1 : 1);
        for (auto ci : arrangements) {
            long long item = ci.getChar();
            item *= sign;
            --nDigits;
            for (int i = 0; i < nDigits; i++) {
                item *= 10;
                if (item <= INT_MIN) return INT_MIN;
                if (item >= INT_MAX) return INT_MAX;
            }
            result += item;
            if (result <= INT_MIN) return INT_MIN;
            if (result >= INT_MAX) return INT_MAX;
        }
        return (int)result;
    }
};

class Shape {
protected:
    double area;
public:
    virtual void draw() = 0; // Pure virtual function
    virtual void calcArea() = 0;
    virtual double getArea() = 0;
};

class Circle : public Shape {
public:
    Circle() {
        this->area = 0.5;
    }
    void draw() override {
        std::cout << "Drawing Circle\n";
    }
    void calcArea() override {
    }
    double getArea() override {
        return this->area;
    }
};

class Rectangle : public Shape {
public:
    Rectangle() {
        this->area = 4;
    }
    void draw() override {
        std::cout << "Drawing Rectangle\n";
    }
    void calcArea() override {
    }
    double getArea() override {
        return this->area;
    }
};

std::mutex mtx1;
std::mutex mtx2;


int main() {

    // Error in the below line : Cannot create 
    // object of abstract class
    // Shape s;      
    sensorFacotry* sf = new ccdFacotry();
    auto ccd = sf->createSensor();
    ccd->build();
    struct threadArgs tArgs;
    tArgs.factPtr = sf;
    tArgs.mutex1 = &mtx1;
    tArgs.mutex2 = &mtx2;
    std::thread t1(buildSensors, &tArgs);
    std::thread t2(buildSensors, &tArgs);
    std::thread t3(showSensors, &tArgs);
    std::thread t4(showSensors, &tArgs);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
}