#include <iostream>
#include <ctime>

std::string fermi(std::string guess_number, std::string usr_number, int number_of_digit){
    int count = 0;
    std::string output = "бык";
    for(int i = 0; i < number_of_digit; i++) {
        if (guess_number[i] == usr_number[i]) {
            count++;
        }
    }
    if(count > 1 && count < 5) return std::to_string(count) + " быка";
    else if(count > 4 || count == 0) return std::to_string(count) + " быков";
    return std::to_string(count) + " " + output;

}//быки

std::string pico(std::string guess_number, std::string usr_number, int number_of_digits, std::string bull){
    int count = 0;
    std::string output = "корова";
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
    count = count - std::stoi(bull);//сколько коров
    if(count > 1 && count < 5) return std::to_string(count) + " коровы";
    else if(count > 4 || count == 0) return std::to_string(count) + " коров";
    return std::to_string(count) + " " + output;

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
        std::cout << "1. Начать игру\n2. Правила игры\n3. Об авторе\n4. Выход\n>";
        getline(std::cin, start);
        if (start == "3") {
            std::cout << "Автор: Яковлев Игорь\nВерсия 1.0\nСовместно с Dialas\n\n";
        }
        if(start == "2"){
            std::cout << "Компьютер загадывает несколько цифр, количество цифр задает игрок. После каждой "
                         "попытки компьтер выводит подсказку в виде звуковых сигналов. (звук1)(корова)- если введенная "
                         "цифра есть, но находиться на другом месте, (звук2)(быки) - если введенная  цифра есть и "
                         "ее место угадано, (звук3) - нет таких цифр. Для вывода истории своих попыток нужно "
                         "ввести ? и количество попыток без пробела, которое хотите вывести. Вам даеться 20 попыток. "
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
            //int repit = 0;
            std::string string_number_of_digit = "";
            std::string fermi_number;
            std::string pico_number;
            std::string *save_number = new std::string[20];
            std::string *aim = new std::string [20];
            std::string *near = new std::string [20];
            while (true) {
                std::cout << "Какое количество цифр желаете отгадывать? Не более 9. >" ;
                getline(std::cin, string_number_of_digit);

                if (input_usr(string_number_of_digit)) {
                    number_of_digit = std::stoi(string_number_of_digit);
                } else {
                    std::cout << "Попробуйте еще раз.\n";
                    continue;
                }

                if (number_of_digit > 0 && number_of_digit < 10) {
                    while (true) {
                        guess_number = random_guess(number_of_digit);
                        if(guess_number.size() == number_of_digit) break;
                    }
                    break;
                } else {
                    std::cout << "Попробуйте еще раз.\n";
                }
            }

            std::cout << "Хорошо, пора начинать. Я загадал число. Удачи!" << std::endl;

            for (int i = 1; i < 21; i++) {//21
                std::cout << "\nПопытка №" << i << "   " << ">";
                getline(std::cin, user_number);
                if (user_number == "00000") break;// выход из игры
                else if(user_number == "cheat") std::cout << guess_number << "\n";//выводит загаданное число
                else if(user_number[0] == char('?')){//вывод предыдущих попыток
                    int repit = 0;
                        if (static_cast<int>(user_number[1]) > 48 && static_cast<int>(user_number[1] < 58)) {
                            repit = user_number[1] - '0';
                            if (static_cast<int>(user_number[2]) > 47 && static_cast<int>(user_number[2] < 58)) {
                                repit = (repit * 10) + (user_number[2] - '0');
                            }
                            repit = (repit >= i)? i - 1: repit;
                            for(int s = i - repit; s < i; s++){
                                std::cout << aim[s - 1] + ",   " + save_number[s - 1] + ",   " + near[s - 1] + "\n";
                            }
                        }
                    i = i - 1;
                    continue;
                    }



                if (!input_usr(user_number, number_of_digit)) {
                    std::cout << "Неправильный ввод, введите " << error_input(number_of_digit) <<  "\n";
                    i = i - 1;
                    continue;
                } else {
                    save_number[i - 1] = user_number;//print
                    fermi_number = fermi(guess_number, user_number, number_of_digit);
                    pico_number = pico(guess_number, user_number, number_of_digit, fermi_number);
                    aim[i - 1] = fermi_number;
                    near[i - 1] = pico_number;
                    std::cout << fermi_number + ",   " + user_number + ",   " + pico_number + "\n";
                }
                if ((fermi_number[0] - '0') == number_of_digit) {
                    std::cout << "Победа! Число угадано верно.\n\n";
                    break;
                }

                if (i == 20) std::cout << "Попытки закончены. Загаданное число " << guess_number << "\n";
            }
            std::cout << "Играем дальше? 1 - Да, Остальное - Нет >";
            getline(std::cin, exit);

            delete[] save_number;
            delete[] aim;
            delete[] near;

        }
    }
    std::cout << "До свидания!";
    return 0;
}
