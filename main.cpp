#include <iostream>
#include <ctime>
#include <iomanip>

int fermi(std::string guess_number, std::string usr_number, int number_of_digit){
    int count = 0;
    for(int i = 0; i < number_of_digit; i++) {
        if (guess_number[i] == usr_number[i]) {
            count++;
        }
    }
    return count;
}//быки

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
}//коровы

bool input_usr(std::string input, int number_of_digit = 1){
    bool flag = true;
    char* check_input = const_cast<char*>(input.c_str());
    if(input.size() == number_of_digit) {
        for (int i = 0; i < strlen(check_input); i++) {
            if(!isdigit(check_input[i])) {
                flag = false;
            }
        }
    }else flag = false;
    return flag;

} //проверка на правильность ввода

std::string random_guess(int number_of_digit){
    srand(time(nullptr));
    number_of_digit = pow(10,number_of_digit);
    return std::to_string (rand() % number_of_digit);

}// генерирует число // ОШИБКА иногда генерирует на один знак меньше

std::string error_input(int number_of_digit){
    if(number_of_digit == 1) return  std::to_string(number_of_digit) + " цифру\n";
    else if(number_of_digit > 1 && number_of_digit < 5) return std::to_string(number_of_digit) + " цифры\n";
    else return std::to_string(number_of_digit) + " цифр\n";
}//сообщает пользователю сколько надо ввести цифр


int main() {
    std::string exit = "1";
    std::string start = "2";


    std::cout << "Приветствуем Вас в игре Быки и коровы!\n";
    while (start == "2" || start == "3") {
        std::cout << "Выберите пункт меню:\n";
        std::cout << "1. Начать игру\n2. Правила игры\n3. Об авторе\n4. Выход\n";
        getline(std::cin, start);
        if (start == "3") {
            std::cout << "Автор: Яковлев Игорь\nВерсия 1.0\nСовместно с Dialas\n\n";
        }
        if(start == "2"){
            std::cout << "Компьютер загадывает несколько цифр, количество цифр задает игрок. После каждой "
                         "попытки компьтер выводит подсказку в виде звуковых сигналов. (звук1)(корова)- если введенная "
                         "цифра есть, но находиться на другом месте, (звук2)(быки) - если введенная  цифра есть и "
                         "ее место угадано, (звук3) - нет таких цифр. Для вывода истории своих попыток нужно "
                         "ввести 'история' и количество попыток, которое хотите вывести. Вам даеться 20 попыток. "
                         "Существует несколько стратегий для успешного прохождения этой игры. Опытный игрок"
                         " проходит игру в среднем за 9 попыток. Находи их и выигрывай! Если надоест набери 00000.\n"
                         "Удачи Homo Sapiens!\n\n";
        }
    }


    if(start == "1") {
        while (exit == "1") {
            std::string guess_number = "";
            std::string user_number = "";
            int number_of_digit;
            std::string string_number_of_digit = "";
            int fermi_number;
            int pico_number;
            std::string *save_number = new std::string[20];
            int *aim = new int[20];
            int *near = new int[20];
            while (true) {
                std::cout << "Какое количество цифр желаете отгадывать? Не более 9. ";
                getline(std::cin, string_number_of_digit);

                if (input_usr(string_number_of_digit)) {
                    number_of_digit = std::stoi(string_number_of_digit);
                } else {
                    std::cout << "Попробуйте еще раз.\n";
                    continue;
                }

                if (number_of_digit > 0 && number_of_digit < 10) {
                    //std::cout << "number_of_digit = " << number_of_digit << "\n";
                    while (true) {
                        guess_number = random_guess(number_of_digit);
                        if(guess_number.size() == number_of_digit) break;
                    }
                    //std::cout << "guess number = " << guess_number << "\n";
                    break;
                } else {
                    std::cout << "Попробуйте еще раз.\n";
                }
            }

            std::cout << "Хорошо, пора начинать. Я загадал число. Удачи!" << std::endl;

            for (int i = 1; i < 21; i++) {//21
                std::cout << "\nПопытка №" << i << (i < 10? "   ": "  ");
                getline(std::cin, user_number);
                if (user_number == "00000") break;// выход из игры
                if(user_number == "cheat") std::cout << guess_number << "\n";//выводит загаданное число
                if (!input_usr(user_number, number_of_digit)) {
                    std::cout << "Неправильный ввод, введите " << error_input(number_of_digit) <<  "\n";
                    i = i - 1;
                    continue;
                } else {
                    save_number[i - 1] = user_number;//print
                    fermi_number = fermi(guess_number, user_number, number_of_digit);
                    aim[i - 1] = fermi_number;
                    pico_number = pico(guess_number, user_number, number_of_digit);
                    near[i - 1] = pico_number - fermi_number;

                    for (int l = 0; l < i; l++) {
                        std::cout << "В цель = " << aim[l] << "   " << save_number[l] << "   " << "Рядом = "<< near[l] << "\n";
                    }
                }
                if (fermi_number == number_of_digit) {
                    std::cout << "Победа! Число угадано верно.\n";
                    break;
                }

                if (i == 20) std::cout << "Попытки закончены. Загаданное число " << guess_number << "\n";
            }
            std::cout << "Играем дальше? 1 - Да, Остальное - Нет ";
            getline(std::cin, exit);

            delete[] save_number;
            delete[] aim;
            delete[] near;

        }
    }
    std::cout << "До свидания!";
    return 0;
}
