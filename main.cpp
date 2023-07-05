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

int main() {
    int guess_number = 123;
    int user_number = 423;
    std::cout << "Хорошо, пора начинать. Я загадал число. Удачи!" << std::endl;

    std::cout << "Попытка №" << "\n"; //добавить номер попытки
    //std::cin >> user_number;
    std::cout << "Совпадений = " << fermi(guess_number, user_number) << "\n";
    return 0;
}
