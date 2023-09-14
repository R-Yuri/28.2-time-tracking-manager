// 28.2 time tracking 

#include <iostream>
#include <string>
#include <ctime>
#include <map>


//будем определять текущую задачу по её имени, если имя стёрто current_task = "", то текущей задачи нет

// функция отслеживания новой задачи по команде begin
void begin_task(std::map<std::string, double>& tasks, std::string& current_task, std::time_t& start_time) {

    // завершение ранее запущеной задачи, если она есть
    if (current_task != "") {
        std::cout << "Completing previous task: " << current_task << std::endl;
        //вычисляем время задачи в часах
        double duration = std::difftime(std::time(nullptr), start_time) / 3600.0;
        tasks[current_task] += duration;    //добавляем запись в мапу
    }

    // старт отслеживания новой задачи
    std::cout << "Enter name of new task: ";
    std::getline(std::cin, current_task);
    start_time = std::time(nullptr);   //время старта = текущему времени в секундах
    std::cout << "Tracking new task: " << current_task << std::endl;
}

// функция завершения текущей задачи
void end_task(std::map<std::string, double>& tasks, std::string& current_task, std::time_t& start_time) {
    
    if (current_task == "") {
        std::cout << "No task is currently running."<<std::endl;
    }
    else {
        //завершение и вычисление времени текущей задачи, и анесение в мапу
        double duration = std::difftime(std::time(nullptr), start_time) / 3600.0;
        tasks[current_task] += duration;
        std::cout << "Task " << current_task << " ended after " << duration << " hours."<<std::endl;
        current_task = "";  //текущая задача = стёрто имя
    }
}

// функция вывода в консоль текущей и выполненных задач 
void print_status(std::map<std::string, double>& tasks, std::string& current_task, std::time_t& start_time) {
    std::cout << "============================================="<<std::endl;
    if (current_task == "") {
        std::cout << "No task is currently running."<<std::endl;
    }
    else {
        double duration = std::difftime(std::time(nullptr), start_time) / 3600.0;
        std::cout << "Currently task: " << current_task  <<": "<< duration << " hours" << std::endl;;
    }
    std::cout << "---------------------------------------------" << std::endl;
    
    for (auto const& task : tasks) {
        std::cout << "Completed task: " << task.first << ": " << task.second << " hours" << std::endl;
    }
    std::cout << "=============================================" << std::endl;
}

int main() {
    std::map<std::string, double> tasks; // объявляем мапу для хранения имён задач и времени 
    std::string current_task = ""; // пустое имя текущей задачи
    std::time_t start_time = 0; // стартовое время текущей задачи в секундах (Posix time)

    while (true) {
        std::cout << "Input command 'begin','end','status','exit' : ";
        std::string command;
        std::getline(std::cin, command);

        if (command == "begin") {
            begin_task(tasks, current_task, start_time);
        }
        else if (command == "end") {
            end_task(tasks, current_task, start_time);
        }
        else if (command == "status") {
            print_status(tasks, current_task, start_time);
        }
        else if (command == "exit") {
            break;
        }
        else {
            std::cout << "Invalid command."<<std::endl;
        }
    }

    return 0;
}