#include "main.h"

int RANDOM(int n){
    long long a = rand();
    long long b = rand();

    return (int)((a * 32768 + b) % n);
    /*  
        랜덤으로 출력된 난수 a에 32768을 곱하고 b를 더함
        생성하고자 하는 난수의 범위로 mod
    */ 
}
