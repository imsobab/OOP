#include <iostream>
#include <string>
using namespace std;

class BuildingTask {
private:
    string name;
    string manager;
    int days;
    int progress;

public:
    BuildingTask() {
        name = "Новая задача";
        manager = "Не назначен";
        days = 1;
        progress = 0;
    }

    BuildingTask(string taskName, string taskManager, int taskDays, int taskProgress) {
        name = taskName;
        manager = taskManager;

        if (taskDays > 0) {
            days = taskDays;
        }
        else {
            days = 1;
            cout << "Срок не может быть меньше 1. Установлен 1 день." << endl;
        }

        if (taskProgress >= 0 && taskProgress <= 100) {
            progress = taskProgress;
        }
        else {
            progress = 0;
            cout << "Прогресс должен быть от 0 до 100. Установлен 0." << endl;
        }
    }

    ~BuildingTask() {
        cout << "Задача \"" << name << "\" удалена" << endl;
    }

    string getName() {
        return name;
    }

    int getProgress() {
        return progress;
    }

    void setManager(string newManager) {
        if (newManager != "") {
            manager = newManager;
        }
        else {
            cout << "Имя не может быть пустым" << endl;
        }
    }

    void setDays(int newDays) {
        if (newDays > 0) {
            days = newDays;
        }
        else {
            cout << "Количество дней должно быть больше 0" << endl;
        }
    }

    void updateProgress(int newProgress) {
        if (newProgress >= 0 && newProgress <= 100) {
            progress = newProgress;
            cout << "Прогресс обновлен: " << progress << "%" << endl;
        }
        else {
            cout << "Ошибка! Прогресс должен быть от 0 до 100" << endl;
        }
    }

    void checkCompletion() {
        if (progress >= 100) {
            cout << "Работа завершена!" << endl;
        }
        else {
            cout << "Работа еще не завершена. Сделано " << progress << "%" << endl;
        }
    }

    void showInfo() {
        cout << "\n=== ИНФОРМАЦИЯ О ЗАДАЧЕ ===" << endl;
        cout << "Название: " << name << endl;
        cout << "Ответственный: " << manager << endl;
        cout << "Срок: " << days << " дней" << endl;
        cout << "Выполнено: " << progress << "%" << endl;
        cout << "===========================\n" << endl;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "=== РАБОТА СО СТРОИТЕЛЬНЫМИ ЗАДАЧАМИ ===\n" << endl;

    cout << "Создаем задачу 1:" << endl;
    BuildingTask task1;
    task1.showInfo();

    cout << "Создаем задачу 2:" << endl;
    BuildingTask task2("Фундамент", "Иванов", 10, 20);
    task2.showInfo();

    cout << "Работа с задачей 1:" << endl;
    task1.setManager("Петров");
    task1.setDays(5);
    task1.updateProgress(30);
    task1.showInfo();

    cout << "Проверка валидации:" << endl;
    task1.setManager("");
    task1.setDays(-3);
    task1.updateProgress(150);
    cout << endl;

    cout << "Работа с задачей 2:" << endl;
    task2.updateProgress(50);
    task2.checkCompletion();
    task2.updateProgress(100);
    task2.checkCompletion();

    cout << "\nИнформация о задаче 2:" << endl;
    cout << "Название: " << task2.getName() << endl;
    cout << "Прогресс: " << task2.getProgress() << "%" << endl;

    return 0;
}
