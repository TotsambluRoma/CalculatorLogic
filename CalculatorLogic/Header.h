#pragma once
#include "pch.h"
#pragma once

#include <string>
#include <stdexcept>
using namespace std;
class CalculatorLogic {
private:
    double first_num = 0;
    char user_action = ' ';
    bool is_equal = false;
    string current_display = "0";

public:
    // Обработка ввода цифр
    void inputDigit(const string& digit) {
        if (current_display == "0" || is_equal) {
            current_display = digit;
            is_equal = false;
        }
        else {
            current_display += digit;
        }
    }

    // Обработка ввода точки
    void inputPoint() {
        if (current_display.find('.') == string::npos) {
            current_display += ".";
        }
    }

    // Установка операции
    void setOperation(char op) {
        first_num = stod(current_display);
        user_action = op;
        current_display = "0";
    }

    // Вычисление результата
    void calculate() {
        if (user_action == ' ') return;

        double second = stod(current_display);
        double result = 0;

        switch (user_action) {
        case '+': result = first_num + second; break;
        case '-': result = first_num - second; break;
        case '*': result = first_num * second; break;
        case '/':
            if (second == 0) {
                throw runtime_error("Division by zero");
            }
            result = first_num / second;
            break;
        case '%': result = first_num * second / 100; break;
        }

        current_display = to_string(result);
        // Удаление лишних нулей после точки
        size_t dot_pos = current_display.find('.');
        if (dot_pos != string::npos) {
            size_t last_non_zero = current_display.find_last_not_of('0');
            if (last_non_zero == dot_pos) {
                current_display.erase(dot_pos);
            }
            else {
                current_display.erase(last_non_zero + 1);
            }
        }

        is_equal = true;
        user_action = ' ';
    }

    // Сброс калькулятора
    void reset() {
        first_num = 0;
        user_action = ' ';
        is_equal = false;
        current_display = "0";
    }

    // Смена знака
    void changeSign() {
        double num = stod(current_display);
        num *= -1;
        current_display = to_string(num);
        // Удаление лишних нулей после точки
        size_t dot_pos = current_display.find('.');
        if (dot_pos != string::npos) {
            size_t last_non_zero = current_display.find_last_not_of('0');
            if (last_non_zero == dot_pos) {
                current_display.erase(dot_pos);
            }
            else {
                current_display.erase(last_non_zero + 1);
            }
        }
    }

    // Получение текущего отображаемого значения
    string getDisplay() const {
        return current_display;
    }
};