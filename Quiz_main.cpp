#include <iostream>
#include <vector>
#include <string>

void main(void) {

	setlocale(LC_ALL, "rus");

	int choice_menu, choice_signin, choice_registration;
	std::vector <std::string> login;
	std::string answer;
	bool flag = true;

	int index;

	std::cout << "Добро пожаловать на викторину 'У Богдана'!" << std::endl;

	while (flag) {

		std::cout << "Выберите действие: \n" << std::endl;
		std::cout << "1 - Вход\n" << "2 - Регистрация\n" << std::endl;
		std::cin >> choice_menu;

		switch (choice_menu)
		{
		case 1:

			std::cout << "Функция ввода данных" << std::endl;
			std::cout << "Функция проверки по шаблону" << std::endl;
			std::cout << "Функция хеширования введённого пароля" << std::endl;
			std::cout << "Функция сравнения из базы и введённого" << std::endl;
			
			std::cout << "Если(совпадает) { " << std::endl; 


			std::cout << " Вывод на экран: Успешно авторизировано!" << std::endl; 

			std::cout << "Начать викторину? " << std::endl;
			std::cin >> answer;


			std::cout << "Если(ответ == да) { " << std::endl;
			
			std::cout << "Функция игры" << std::endl;

			std::cout << " } " << std::endl;


			std::cout << "Если же(ответ == нет) { " << std::endl;

			std::cout << "Возвращение в основное меню" << std::endl;

			std::cout << " } " << std::endl;


		    std::cout << " } " << std::endl;

			break;

		case 2:

			std::cout << "Ресайз вектора на +1" << std::endl;

			std::cout << "Функция ввода данных" << std::endl;
			std::cout << "Функция проверки данных" << std::endl;
			std::cout << "Функция хеширования введённого пароля" << std::endl;
			std::cout << "Функция записи введённого логина и пароля в базу" << std::endl;

			break;

		default:
			flag = false;
			break;
		}

	}

}
