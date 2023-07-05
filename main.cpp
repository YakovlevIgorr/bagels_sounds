#include <iostream>

int fermi(int guess_number, int usr_number){
    int count = 0;
    while (guess_number > 0) {
        if ((guess_number % 10) == (usr_number % 10)) {
            count++;
        }
        guess_number = guess_number / 10;
        usr_number = usr_number / 10;
    }
    return count;
}

int pico(int guess_number, int usr_number, int* arr_size){
    int count = 0;
    int array[*arr_size];
    for(int i = 0; i < *arr_size; i++){
        array[i] = guess_number % 10;
        guess_number /= 10;
    }

    for(int i = 0; i < *arr_size; i++){
        for(int k = 0; k < *arr_size; k++){
            if(array[i] == usr_number % 10){
                count++;
            }
            usr_number /= 10;
        }
    }
    return count;
}

int main() {
    int guess_number = 123;
    int user_number = 423;
    int arr_size;
    std::cout << "Хорошо, пора начинать. Я загадал число. Удачи!" << std::endl;

    std::cout << "Попытка №" << "\n"; //добавить номер попытки
    //std::cin >> user_number;
    std::cout << "Совпадений = " << fermi(guess_number, user_number) << "\n";
    return 0;
}
