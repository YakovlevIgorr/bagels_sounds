#include <iostream>
#include <cstring>
//#include <vector>
#include <ctime>

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

bool input_usr(std::string input, int number_of_digit){
    if((input.size() == number_of_digit) && (all_of(input.begin(), input.end(), ::isdigit))){
        return true;
    }
    return false;
} //проверка на правильность ввода

std::string random_guess(int number_of_digit){//3
    srand(time(nullptr));
    number_of_digit = pow(10,number_of_digit);
    return std::to_string (rand() % number_of_digit);

}// генерирует число

int main() {
    std::string guess_number = "";
    std::string user_number = "";
    int number_of_digit;
    std::string string_number_of_digit = "";
    int fermi_number;
    int pico_number;
    //int count_array = 0;
    std::string* save_number = new std::string [20];
    while (true) {
        std::cout << "Какое количество цифр желаете отгадывать? Не более 9. ";
        std::cin >> string_number_of_digit;

        if (all_of(string_number_of_digit.begin(),string_number_of_digit.end(),::isdigit)){
            number_of_digit = std::stoi(string_number_of_digit);
        } else {
            std::cout << "Попробуйте еще раз.\n";
            continue;
        }

        if (number_of_digit > 0 && number_of_digit < 10) {
            guess_number = random_guess(number_of_digit);
            std::cout << "guess number = " << guess_number << "\n";//after clear
            break;
        } else{
            std::cout << "Попробуйте еще раз.\n";
        }
    }

    std::cout << "Хорошо, пора начинать. Я загадал число. Удачи!" << std::endl;

    for(int i = 1; i < 21; i++){
        int a = 0;
        if(i > 6) a = i - 6;
        for(int l = a; l < i; l++){
            std::cout << "            " << save_number[l] << "\n";
        }
        std::cout << "Попытка №" << i << "  ";
        std::cin >> user_number;
        save_number[i - 1] = user_number;//print
        if(!input_usr(user_number,number_of_digit)){
            std::cout << "Неправильный ввод, попробуйте заново. \n";
            i = i - 1;
            continue;
        }else{
            fermi_number = fermi(guess_number, user_number, number_of_digit);
            pico_number = pico(guess_number, user_number,number_of_digit);
            std::cout << "В цель = " << fermi_number << "\n";
            std::cout << "Рядом = " << pico_number - fermi_number << "\n";
        }
        if(fermi_number == number_of_digit){
            std::cout << "Победа! Число угадано верно.\n";
            break;
        }


    }
    //std::cout << "Попытка №" << "\n"; //добавить номер попытки
    //std::cin >> user_number;
    //fermi_number = fermi(guess_number, user_number, number_of_digit);
    //pico_number = pico(guess_number, user_number,number_of_digit);
   // std::cout << "Совпадений FERME = " << fermi_number << "\n";
    //std::cout << "Совпадений ПИКО = " << pico_number - fermi_number << "\n";
    //pico( guess_number, user_number,arr_size);
    //std::cout << input_usr(guess_number,number_of_digit) << "\n";
    //std::cout << std::atoi(guess_number) << "\n" << pow(10, 5);
    delete[] save_number;
    return 0;
}
