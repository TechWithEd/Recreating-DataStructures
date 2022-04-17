#pragma once

#include <iostream>
#include <fstream>

const char* PAUSE_0[] = {"pause>0", "pause>null"};
const char* PAUSE = "pause";
const char* CLS = "CLS";
const char* ABORT = "abort";
const char* CALCULATOR = "calculator";

namespace System {
	void Calculate()
	{
		float num1, num2, result;
		char op;
		bool invalidOperator = false;
		bool appIsOpen = true;

		std::cout << "Please enter the operation to perform. Format: a+b | a-b | a*b | a/b" << std::endl << std::endl;

		std::cin >> num1 >> op >> num2;

		switch (op)
		{
		case '+':
			result = num1 + num2;
			break;
		case '-':
			result = num1 - num2;
			break;
		case '*':
			result = num1 * num2;
			break;
		case '/':
			result = num1 / num2;
			break;
		default:
			invalidOperator = true;
			break;
		}

		switch (invalidOperator)
		{
		case true:
			std::cout << "\nInvalid Operator";
			invalidOperator = false;
			break;
		default:
			std::cout << '\n' << num1 << ' ' << op << ' ' << num2 << " = " << result << std::endl;
			break;
		}

		std::cin.get();
	}

	class Log
	{
	public:
		template<typename T>
		Log print(T text)
		{
			std::cout << text;
			return *this;
		}

		template<typename T>
		std::ostream& operator<<(T text)
		{
			return std::cout << text;
		}
	};

	void warn(const char* warningText)
	{
		std::cout << warningText;
		throw std::error_code();
	}

	void changeSUDO(std::string user, std::string password)
	{
		std::ofstream File;
		File.open("C:/Users/user/source/repos/RecreatingDataStructures/RecreatingDataStructures/Source Code/header files/Neccesary Things/MainUser.txt");
		File << "UserName: " << user << std::endl << "Password: " << password;
		File.close();
	}

	void command(std::string toDo)
	{
		if (toDo == PAUSE_0[0] || toDo == PAUSE_0[1])
		{
			std::cin.get();
			return;
		}
		else if (toDo == PAUSE)
		{
			std::cout << "Press enter to continue...";
			std::cin.get();
			return;
		}
		else if (toDo == CLS)
		{
			system("CLS");
			return;
		}
		else if (toDo == ABORT)
		{
			abort();
			return;
		}
		else if (toDo == CALCULATOR)
		{
			Calculate();
			return;
		}
		else if (toDo == "change- main user")
		{
			std::string userName, password;
			std::cout << "New Username: ";
			std::getline(std::cin, userName);
			std::cout << "New Password: ";
			std::getline(std::cin, password);

			changeSUDO(userName, password);
			return;
		}
		else if (toDo != "")
		{
			std::cout << "'" << toDo << "' is not recognized as an internal or external command," << std::endl;
			std::cout << "operable program or batch file." << std::endl << std::endl;
		}
		else
			std::cout << std::endl;
		
	}

	void commandPrompt()
	{
		std::cout << "AGL-OS [Version 1.0]" << std::endl;
		std::cout << "(c) AGL Corporation. All rights reserved." << std::endl << std::endl;

		while (true)
		{
			std::string command;
			std::cout << "C:\\Users\\user>";
			std::getline(std::cin, command);
			System::command(command);

			if (command == "CLS")
			{
				std::cout << "AGL-OS [Version 1.0]" << std::endl;
				std::cout << "(c) AGL Corporation. All rights reserved." << std::endl << std::endl;
			}
		}
	}

	Log log;
};
