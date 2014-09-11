#!/usr/bin/env python
def isprime(num):
        for pr in range(num / 2, 1, -1):
            if num % pr == 0:
                return False
        return True

def isprime2(num):
    return [pr for pr in range(num / 2, 1, -1) if num % pr == 0] == []

if __name__ == '__main__':
    print isprime(10)
    print isprime2(10)
    print isprime(17)
    print isprime2(17)
    print isprime2(20)
