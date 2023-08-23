#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "windows.h"
//Поключаем звук
//сначала vorbis только дефайны
#define STB_VORBIS_HEADER_ONLY
#include "stb_vorbis.c"    

//теперь весь миниаудио, подтягивает дефайны ворбиса
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

//vorbis реализацию
#undef STB_VORBIS_HEADER_ONLY
#include "stb_vorbis.c"   

//наш звуковой движок
static ma_engine snd_engine;

//инициализация звука
bool initSound()
{
    ma_result result = ma_engine_init(NULL, &snd_engine);
    if (result != MA_SUCCESS) {
        std::cout << "Failed init sound engine\n";
        return false;  // Failed to initialize the engine.
    }
    return true;
}

//играем мелодию
void playSound(std::string sound_file_name)
{
    ma_result result = ma_engine_play_sound(&snd_engine, sound_file_name.c_str(), NULL);
    if (result != MA_SUCCESS) {
        std::cout << "Failed play sound "<< sound_file_name<<"\n";
    }
}



std::string fermi(std::string guess_number, std::string usr_number, int number_of_digit) {
    int count = 0;
    std::string output = "бык";
    for (int i = 0; i < number_of_digit; i++) {
        if (guess_number[i] == usr_number[i]) {
            count++;
            playSound("bull.wav");
            Sleep(1000);/////////////////////
        }
    }
    if (count > 1 && count < 5) return std::to_string(count) + " быка";
    else if (count > 4 || count == 0) return std::to_string(count) + " быков";
    return std::to_string(count) + " " + output;

}//быки

std::string pico(std::string guess_number, std::string usr_number, int number_of_digits, std::string bull) {
    int count = 0;
    std::string output = "корова";
    for (int i = 0; i < number_of_digits; i++) {
        for (int k = 0; k < number_of_digits; k++) {

            if (usr_number[k] == guess_number[i]) {
                count++;
                usr_number[k] = '-';
                guess_number[i] = '+';
                k = number_of_digits;
            }
        }
    }
    count = count - std::stoi(bull);//сколько коров
    for (int i = 0; i < count; i++) {
        playSound("cow.wav");
        Sleep(1000);
    }
    if (count > 1 && count < 5) return std::to_string(count) + " коровы";
    else if (count > 4 || count == 0) return std::to_string(count) + " коров";
    return std::to_string(count) + " " + output;

}//коровы

bool input_usr(std::string input, int number_of_digit = 1) {
    bool flag = true;

    if (input.size() == number_of_digit) {
        for (int i = 0; i < input.size(); i++) {
            if (!isdigit(input[i])) {
                flag = false;
            }
        }
    }
    else flag = false;
    return flag;

} //проверка на правильность ввода

std::string random_guess(int number_of_digit, int qwest = 0) {
    srand(time(nullptr));
    std::string total_output = "";
    for (int i = 0; i < number_of_digit; i++) {
        total_output = total_output + std::to_string(rand() % 10);
    }
    if (qwest == 1 && total_output[0] == '0') total_output[0] = '1';
    return total_output;
}
std::string error_input(int number_of_digit) {
    if (number_of_digit == 1) return  std::to_string(number_of_digit) + " цифру\n";
    else if (number_of_digit > 1 && number_of_digit < 5) return std::to_string(number_of_digit) + " цифры\n";
    else return std::to_string(number_of_digit) + " цифр\n";
}//сообщает пользователю сколько надо ввести цифр

void text_out_quest(int various) {
    switch (various) {
    case 0:
        std::cout << "Семья Ренди переехала в новый, красивый, большой жилой комплекс. "
            "Ренди учился со второй смены и сегодня как обычно собирался в школу."
            " Зашел в ванную, включил воду, чтобы набрать ванну. Пошел на кухню, включил чайник. "
            "Открыл холодильник и обнаружил, что нет колбасы для завтрака. Взял деньги и пошел "
            "в магазин. На обратном пути понял, что оставил ключи дома. Помоги Ренди найти номер "
            "квартиры друзей семьи, чтобы открыть дверь подъезда (3 цифры)."; //(3 цифры);
        break;
    case 1:
        std::cout << "Ты молодец, справился. Ренди зашел в лифт, но  конечно, без бирки на ключах "
            "он не помнил номера своей квартиры и тем более этажа. Нужно найти этаж (2 цифры) и номер "
            "квартиры (3 цифры)."; // 2 and 3 цифры
        break;
    case 2:
        std::cout << "Отлично, не пройдет и полгода, как Ренди вернется домой (надеюсь, с колбасой)."
            " Ты, наверно, уже догадался, что дальше. Нужно придумать, как открыть дверь. "
            "Болгаркой Ренди  пользоваться не умеет  и соседа-спасателя у него нет. К счастью, "
            "есть альтернативный способ отпереть дверь, о нём Ренди по-секрету рассказал папа. "
            "Нужно ввести пятизначный код на потайной панели. Вот только код папа сказать позабыл, "
            "придётся угадывать (5 цифр). К делу без промедления, ведь у нас в квартире включен чайник, хотя "
            "он самоотключаемый, но вода в ванной точно не выключиться.";//5 цифры
        break;
    case 3:
        std::cout << "Хорошо, хорошо, теперь ты заслуженный медвежатник. Продолжаем, теперь ванная."
            "Довольный собой Ренди заходит в ванную, тянет за  ручку крана  и наступает на железного "
            "солдатика, которого оставил его маленький братик. Дергаеться от боли и вырывает ручку"
            " крана. Вода продолжает бежать в ванну, ну а ванна почти полная. Ренди бежит к телефону "
            "и набирает номер, первый раз - ничего, второй раз - ничего. Ванна наполнилась почти до"
            " краёв. Помоги Ренди дозвониться до службы спасения (6 цифр), нет, сначала до местного сантехника."
            " Вперед, времени мало."; //(6 цифр)";
        break;
    case 4:
        std::cout << "Все, спасибо тебе, помощь пришла вовремя, жильцы нижнего этажа спасены от затопа, а Ренди от "
            "наказания родителей. Мальчик был так благодарен сантехнику Стиву Александровичу, что решил "
            "отблагодарить его и дать ему немного денег из своей копилки, угадай, на сколько рублей был "
            "благодарен Ренди (2 цифры).";//(2 цифры)" ;
        break;
    case 5:
        std::cout << "С завтраком покончено, наш герой идет в школу, нет, даже не идет, а едет на электросамокате."
            " Дорога прошла на удивление без приключений,  Ренди припарковал свой блестящий самокат, обмотал"
            " велосипедным замком и отправился было в здание школы, но тут заметил, что  нечаянно замотал и "
            "колесо соседнего велосипеда, этот велосипед принадлежал старшекласснику не самого хорошего "
            "поведения. Из школы показалась толпа старшеклассников, активно обсуждающих последние приключения"
            " учителя физкультуры. Ренди начал открывать замок, но не тут-то было, как мы знаем, наш Ренди"
            " срывал ручки водопроводных кранов, теперь он от спешки сделал из ключа спираль. Осталась одна"
            " надежда- это код. Надо помочь, всего 4 цифры и 10000 комбинаций.";//(4 цифры)
        break;
    case 6:
        std::cout << "После плодотворной учебы мальчик едет домой. Спешить некуда, и поэтому он выбирает длинную "
            "дорогу.  Начался дождь, и Ренди спрятался под мостом переждать, вдруг он услышал писки,"
            " исходившие из-под земли. Он в недоумении осмотрелся и обнаружил в канале для стока воды за"
            " решеткой маленького котенка по имени Бренди(шутка, имени пока не было). Дождь идет, вода"
            " прибывает, котенку все более не комфортно и даже становиться опасно. Нужно спасать животное,"
            " Ренди хватаеться за решетку, пытаеться выдрать ее, как кран, но ничего не происходит. Надо"
            " думать головой, успокаиваеться, садиться и начинает крутить колесики кодового замка (4 цифры).";// (4 цифры)";
        break;
    case 7:
        std::cout << "Ура, кот на свободе, звали его Бренди или Денди, мы так и не узнаем, так как он был не "
            "очень вежлив и после освобождения убежал, даже не оглянувшись на своего спасителя. Кот,"
            " однако. Дождь успокоился, и Ренди поехал в сторону дома. День близился к завершению. Ренди "
            "проезжает мимо бабушек торгующих домашними разносолами, газетами и лотерейными билетами. "
            "Неожиданно налетевший порыв ветра раскидывает газеты и прочее лежавшее на прилавке. Мальчик "
            "с дрифтом останавливаеться и помогает одной из пожилых женщин. В ответ она ему дарит один "
            "лотерейный  билет, моментальный выйгрышь. Ренди восторженно берет его и пытаеться угадать "
            "6 цифр. Попытайте удачу вместе.";//(6 цифр)";
        break;
    case 8:
        std::cout << "Цифры угаданы, выйгрышь оказался небольшой. Мальчик покупает мороженное и довольный катит на самокате дальше."
            "... Прошло 15 лет. Наш Ренди вырос и стал обычным человеком с обычными потребностями и "
            "желаниями, однако этот насыщенный на события день он помнит и до сих пор. Но хоть юноша"
            " и повзрослел, у него иногда случаються подобные казусы.\n"
            "День начался хорошо, и погода была солнечная в отличие от прошлых дней. Ренди отправляеться"
            " на работу на своем стареньком форде, по пути решает помыть машину, ставит ее на конвейер,"
            " закрывает дверь и обнаруживает, что машина на ручном тормозе. Конвеер начинает двигаться, "
            "Ренди дергает дверь, но она закрыта, ключи в сумке, сумка в комнате ожидания. Остаеться "
            "один выход- это набрать код на двери (7 цифр), благо, производитель догадался сделать такую функцию. "
            "Твой выход, уважаемый игрок.";//(7 цифр)";
        break;
    case 9:
        std::cout << "Машина помыта, на работе показался, теперь время сходить расслабиться."
            "Вечером Ренди катит в клуб, не сказать, что большой, но просто уютный и с довольно "
            "милыми посетительницами. "
            "Вечер проходит весело и душевно, масса новых знакомств, новых впечатлений и  одна "
            "очень интересная и милая собеседница. Ренди предлагает выйти на улицу- все равно скоро "
            "закрытие- подышать свежим воздухом. Он просто горит желанием показать свой дрон. Они "
            "выходят, Ренди садиться на капот своего форда и начинает запускать дрон в небо, аппарат "
            " взлетает, показывает вид сверху на них на горизонт, подруга в восторге."
            "Тут неожиданно подбегает парень,  хватает сумку девушки и пытаеться скрыться. Ренди, "
            "не теряясь, держит его в поле зрения дрона. Подруга(уже подруга) звонит в полицию."
            "Преступник стремительно удаляеться, радиус действия пульта и дрона 1000 метров, после "
            "все может быть потеряно,  Ренди делает фото и собираеться отозвать дрон на базу, но "
            "программа предлагает ввести код от аккаунта. Времени мало, расстояние уже 890 метров, "
            "все на грани срыва. "
            "Нужна холодная голова, приступай (8 цифр).";//(8 цифр)";
        break;
    case 10:
        std::cout << "Все хорошо, дрон возвращен, сумка потеряна, с подругой периодически видимся. Но что-то"
            " тоскливо на душе. Может, сгонять за границу? Нет, не хочеться, да и денег нет. Может, "
            "на рыбалку? Нет, никогда там не был, зачем поеду? Может, напиться? Тоже нееее. И тут он "
            "вспомнил про гараж, где хранились какие-то вещи. Много раз он хотел заглянуть туда, но"
            " все время откладывал. Не долго думая, садиться в машину- и он уже возле. Тут опять та "
            "же история, железные двери, отсутствие ключей и желание попасть внутрь. Ты, наверно, "
            "задашься вопросом, почему всегда есть кодовый замок у него на пути? Да потому,-что с "
            "самого детства его преследует это, сначала он сам хотел сделать вариант доступа без "
            "ключей, так как терял или забывал их постоянно, а после замки с кодом начали его самого "
            "преследовать. Но не суть, замок есть, приступим (9 цифр).";//(9 цифр)";
        break;
    case 11:
        std::cout << "Отлично, ты справился и с этим заданием, молодец!!! Ренди открыл гараж, там было много "
            "старых вещей, все было пыльное, а в углу аккуратно стоял его блестящий самокат. Он "
            "достал его, протер, попытался включить, но безуспешно. Сел с ним рядом и предался "
            "воспоминаниям о своем детстве. Так незаметно прошло пару часов, после которых Ренди"
            " стал бодрым и более взрослым. Он аккуратно поставил самокат на место, закрыл гараж и"
            " покатил в свою жизнь с новыми мыслями и новым настроением. Иногда хорошо побыть с "
            "самим собой и своими воспоминаниями наедине. Спасибо, милый друг, что был с нами на "
            "протяжении игры. До свидания!";
        Sleep(10000);
        break;
    case 12:
        std::cout << "на самом деле, все должно было получиться, попробуй еще раз.\n";
        break;
    }
}

class Guessing {//принимает количество цифр и загаданное цисло //скопировать это в отдельный файл и запустить
public:
    std::string* save_number = new std::string[20];
    std::string* aim = new std::string[20];
    std::string* near_ = new std::string[20]; //совпадает с дефайнами студии far/near, поэтому переименовал
    std::string user_number = "";
    int quest_or_not = 0;
    std::string fermi_number;
    std::string pico_number;
    int exit = 0;

    void guess(int number_of_digit, std::string guess_number, int qwest = 0) {

        for (int i = 1; i < 21; i++) {//21
            std::cout << "\nПопытка №" << i << "   " << ">";
            getline(std::cin, user_number);
            if (user_number == "00000") {
                this->exit = 1;
                break;
            }// выход из игры
            else if (user_number == "cheat") std::cout << guess_number << "\n";//выводит загаданное число
            else if (user_number[0] == char('?')) {//вывод предыдущих попыток
                int repit = 0;
                if (static_cast<int>(user_number[1]) > 48 && static_cast<int>(user_number[1] < 58)) {
                    repit = user_number[1] - '0';
                    if (static_cast<int>(user_number[2]) > 47 && static_cast<int>(user_number[2] < 58)) {
                        repit = (repit * 10) + (user_number[2] - '0');
                    }
                    repit = (repit >= i) ? i - 1 : repit;
                    for (int s = i - repit; s < i; s++) {
                        std::cout << aim[s - 1] + ",   " + save_number[s - 1] + ",   " + near_[s - 1] + "\n";
                    }
                }
                i = i - 1;
                continue;
            }


            if (!input_usr(user_number, number_of_digit)) {
                playSound("wrong_input.mp3");//music
                std::cout << "Неправильный ввод, введите " << error_input(number_of_digit) << "\n";
                i = i - 1;
                continue;
            }
            else {
                save_number[i - 1] = user_number;//print
                fermi_number = fermi(guess_number, user_number, number_of_digit);
                pico_number = pico(guess_number, user_number, number_of_digit, fermi_number);
                aim[i - 1] = fermi_number;
                near_[i - 1] = pico_number;
                std::cout << fermi_number + ",   " + user_number + ",   " + pico_number + "\n";
              
            }
            if ((fermi_number[0] - '0') == number_of_digit) {
                (quest_or_not == 0 ? std::cout << "Победа! Число угадано верно.\n\n" : std::cout << "\n");
                if(qwest == 1) playSound("win_single.wav");
                i = 21;

            }

            if (i == 20) {
                playSound("20_attempt.wav");//music
                (quest_or_not == 0 ? std::cout << "Попытки закончены. Загаданное число "
                    << guess_number << "\n" : std::cout << "на самом деле, все должно было получиться, "
                    "попробуй еще раз.\n");
                Sleep(5000);
                this->exit = 1;
            }

        }
    }
};

int main() {

    initSound();//инициализируем звуковой движок
    
    std::string exit = "1";
    std::string start = "2";
    std::system("chcp 65001"); //исходники поидее в UTF-8, надо выводить в консоль также
    std::system("cls");
    Guessing guessing;


    std::cout << "Приветствуем Вас в игре Быки и коровы!\n";
    while (start != "5") {
        exit = "1";
        if (start != "3" && start != "4") playSound("cheerful.wav");//music
        std::cout << "\nВыберите пункт меню:\n";
        std::cout << "1. Начать игру\n2. Начать сюжетную игру\n3. Правила игры\n4. Об авторе\n5. Выход\n>";
        getline(std::cin, start);
        if (start == "4") {
            std::cout << "Автор: Яковлев Игорь\nВерсия 1.0\nСовместно с Dialas\n\n";
        }
        if (start == "3") {
            std::cout << "Компьютер загадывает несколько цифр, количество цифр задает игрок. После каждой "
                "попытки компьтер выводит подсказку о угаданных числах, в виде звуковых сигналов. "
                "(звук1)(корова)- если введенная "
                "цифра есть, но находиться на другом месте, (звук2)(быки) - если введенная  цифра есть и "
                "ее место угадано, (звук3) - нет таких цифр. Для вывода истории своих попыток нужно "
                "ввести ? и количество попыток без пробела, которое хотите вывести. Вам даеться 20 попыток. "
                "Существует несколько стратегий для успешного прохождения этой игры. Опытный игрок"
                " проходит игру в среднем за 9 попыток. Находи их и выигрывай! Если надоест набери 00000.\n"
                "Удачи Homo Sapiens!\n\n";
        }
        // }

        if (start == "2") {
            guessing.quest_or_not = 1;
            int passing[11] = { 3, 2, 5, 6, 2, 4, 4, 6, 7, 8, 9 };

            playSound("happy.mp3");//music
           
            std::cout << "Привет в этой игре тебе нужно будет помогать нашему герою Ренди, решать "
                "задачи, которые встречаються у него на пути. Удачи Вам!\n\n";
            for (int i = 0; i < 12; i++) {
                if (guessing.exit == 1) break;
                playSound("happy.mp3");//music
                text_out_quest(i);
                if (i < 11) {
                    if (i == 1) std::cout << "\nНачнем с этажа (2 цифры)\n";
                    guessing.guess(passing[i], random_guess(passing[i], 1));
                    if (guessing.exit == 1) break;
                    if (i == 1) {
                        playSound("happy.mp3");//music 
                        std::cout << "\nА теперь квартира (3 цифры)\n";
                        guessing.guess(3, random_guess(3, 1));
                    }
                }
            }
            guessing.exit = 0;
            guessing.quest_or_not = 0;
        }


        if (start == "1") {
            while (exit == "1") {
                std::string guess_number = "";
                int number_of_digit;
                std::string string_number_of_digit = "";

                while (true) {
                    playSound("start_single.wav");//music/////надо найти музыку
                    std::cout << "Какое количество цифр желаете отгадывать? Не более 9. >";
                    getline(std::cin, string_number_of_digit);

                    if (input_usr(string_number_of_digit)) {
                        number_of_digit = std::stoi(string_number_of_digit);
                    }
                    else {
                        playSound("wrong_input.mp3");//music
                        std::cout << "Попробуйте еще раз.\n";
                        continue;
                    }

                    if (number_of_digit > 0 && number_of_digit < 10) {
                        while (true) {
                            guess_number = random_guess(number_of_digit);
                            if (guess_number.size() == number_of_digit) break;
                        }
                        break;
                    }
                    else {
                        playSound("wrong_input.mp3");//music
                        std::cout << "Попробуйте еще раз.\n";
                    }
                }

                std::cout << "Хорошо, пора начинать. Я загадал число. Удачи!" << std::endl;

                guessing.guess(number_of_digit, guess_number, 1);
                if (guessing.exit == 0) {
                    std::cout << "Играем дальше? - 1, Выход в главное меню - остальное >";
                    getline(std::cin, exit);
                }
                else {
                    exit = "2";
                    guessing.exit = 0;
                 

                }

            }
        }
        
    }
   
    delete[] guessing.save_number;
    delete[] guessing.aim;
    delete[] guessing.near_;
    std::cout << "До свидания!";
    playSound("exit_game.wav");
    return 0;
}
