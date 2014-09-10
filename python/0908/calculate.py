#!/usr/bin/env python

def calculate(func):
    word = func.split(' ')
    if word[0].isdigit():
        a = int(word[0])
    else:
        a = float(word[0])
    if word[0].isdigit():
        b = int(word[2])
    else:
        b = float(word[2])
    if word[1] == '+':
        return a + b
    elif word[1] == '-':
        return a - b
    elif word[1] == '*':
        return a * b
    elif word[1] == '/':
        return a / b
    elif word[1] == '%':
        return a % b
    elif word[1] == '**':
        return a ** b

if __name__ == '__main__':
    print calculate('123 + 345')
    print calculate('123.123 + 123.123')
    print calculate('3.4 * 5')
    print calculate('4 ** 4')
    print calculate('4.2 / 2')
    print calculate('5 % 2')
