#include <iostream>

int fermi(std::string guess_number, std::string usr_number, int number_of_digit){
    int count = 0;
    for(int i = 0; i < number_of_digit; i++) {
        if (guess_number[i] == usr_number[i]) {
            count++;
        }
    }
    return count;
}

int pico(std::string guess_number, std::string usr_number, int number_of_digits){
    int count = 0;

    for(int i = 0; i < number_of_digits; i++){
        for(int k = 0; k < number_of_digits; k++){

            if(usr_number[k] == guess_number[i]){
                count++;
                usr_number[k] = '-';
                guess_number[i] = '+';
                k = number_of_digits;
        }
    }
    }
    return count;
}

int main() {
    std::string guess_number = "14501";
    std::string user_number =  "14015";
    int number_of_digit = 5;
    int fermi_number;
    int pico_number;
    std::cout << "Хорошо, пора начинать. Я загадал число. Удачи!" << std::endl;

    std::cout << "Попытка №" << "\n"; //добавить номер попытки
    //std::cin >> user_number;
    fermi_number = fermi(guess_number, user_number, number_of_digit);
    pico_number = pico(guess_number, user_number,number_of_digit);
    std::cout << "Совпадений FERME = " << fermi_number << "\n";
    std::cout << "Совпадений ПИКО = " << pico_number - fermi_number << "\n";
    //pico( guess_number, user_number,arr_size);
    return 0;
}
