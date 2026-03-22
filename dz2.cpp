#include <iostream>
#include <string>
using namespace std;

class BuildingTask {
protected:
    string name;
    string manager;
    int plannedDays;
    int completionPercent;

public:
    BuildingTask(string taskName, string taskManager, int days, int percent) {
        name = taskName;
        manager = taskManager;

        if (days > 0) {
            plannedDays = days;
        } else {
            plannedDays = 1;
            cout << "Срок не может быть меньше 1 дня. Установлен 1 день." << endl;
        }

        if (percent >= 0 && percent <= 100) {
            completionPercent = percent;
        } else {
            completionPercent = 0;
            cout << "Процент выполнения должен быть от 0 до 100. Установлен 0." << endl;
        }
    }

    virtual ~BuildingTask() {
        cout << "Задача \"" << name << "\" удалена" << endl;
    }

    string getName() { return name; }
    string getManager() { return manager; }
    int getPlannedDays() { return plannedDays; }
    int getCompletionPercent() { return completionPercent; }

    void setManager(string newManager) {
        if (newManager != "") {
            manager = newManager;
        } else {
            cout << "Ошибка: имя не может быть пустым" << endl;
        }
    }

    void setPlannedDays(int days) {
        if (days > 0) {
            plannedDays = days;
        } else {
            cout << "Ошибка: срок должен быть больше 0" << endl;
        }
    }

    void updateProgress(int newPercent) {
        if (newPercent >= 0 && newPercent <= 100) {
            completionPercent = newPercent;
            cout << "Прогресс обновлен: " << completionPercent << "%" << endl;
            if (completionPercent == 100) {
                cout << "Задача завершена!" << endl;
            }
        } else {
            cout << "Ошибка: процент должен быть от 0 до 100" << endl;
        }
    }

    virtual void printInfo() {
        cout << "==========================================" << endl;
        cout << "Название:        " << name << endl;
        cout << "Ответственный:   " << manager << endl;
        cout << "Срок:            " << plannedDays << " дней" << endl;
        cout << "Выполнено:       " << completionPercent << "%" << endl;
    }

    virtual double estimateCost() = 0;
    virtual string getRiskLevel() = 0;
};

class ExcavationTask : public BuildingTask {
private:
    double soilVolume;
    double depth;

public:
    ExcavationTask(string taskName, string taskManager, int days, int percent,
                   double volume, double excavDepth)
        : BuildingTask(taskName, taskManager, days, percent) {
        
        if (volume > 0) {
            soilVolume = volume;
        } else {
            soilVolume = 1;
            cout << "Объем грунта установлен 1 м³" << endl;
        }
        
        if (excavDepth > 0) {
            depth = excavDepth;
        } else {
            depth = 1;
            cout << "Глубина установлена 1 м" << endl;
        }
    }
    
    double getSoilVolume() { return soilVolume; }
    double getDepth() { return depth; }
    
    double calculateExcavationCost() {
        double baseCost = soilVolume * 2000;
        double depthBonus = 0;
        
        if (depth > 2) {
            depthBonus = baseCost * (depth - 2) * 0.05;
        }
        
        return baseCost + depthBonus;
    }
    
    double estimateCost() override {
        double cost = calculateExcavationCost();
        double remainingFactor = (100.0 - completionPercent) / 100.0;
        return cost * remainingFactor;
    }
    
    string getRiskLevel() override {
        if (depth > 5 || soilVolume > 1000) {
            return "ВЫСОКИЙ";
        } else if (depth > 3 || soilVolume > 500) {
            return "СРЕДНИЙ";
        } else {
            return "НИЗКИЙ";
        }
    }
    
    void printInfo() override {
        BuildingTask::printInfo();
        cout << "Объем грунта:    " << soilVolume << " м³" << endl;
        cout << "Глубина:         " << depth << " м" << endl;
        cout << "Стоимость:       " << calculateExcavationCost() << " руб." << endl;
        cout << "Осталось оплатить: " << estimateCost() << " руб." << endl;
        cout << "Риск:            " << getRiskLevel() << endl;
        cout << "==========================================" << endl;
    }
};

class FinishingTask : public BuildingTask {
private:
    double surfaceArea;
    string finishType;

public:
    FinishingTask(string taskName, string taskManager, int days, int percent,
                  double area, string type)
        : BuildingTask(taskName, taskManager, days, percent) {
        
        if (area > 0) {
            surfaceArea = area;
        } else {
            surfaceArea = 1;
            cout << "Площадь установлена 1 м²" << endl;
        }
        
        if (type == "покраска" || type == "обои" || type == "штукатурка" || type == "плитка") {
            finishType = type;
        } else {
            finishType = "стандартная";
            cout << "Тип отделки установлен 'стандартная'" << endl;
        }
    }
    
    double getSurfaceArea() { return surfaceArea; }
    string getFinishType() { return finishType; }
    
    double calculateMaterialConsumption() {
        double consumptionPerSqm = 0;
        
        if (finishType == "покраска") {
            consumptionPerSqm = 0.2;
        } else if (finishType == "обои") {
            consumptionPerSqm = 1.1;
        } else if (finishType == "штукатурка") {
            consumptionPerSqm = 8.5;
        } else if (finishType == "плитка") {
            consumptionPerSqm = 1.05;
        } else {
            consumptionPerSqm = 1.0;
        }
        
        return surfaceArea * consumptionPerSqm;
    }
    
    double estimateCost() override {
        double costPerSqm = 0;
        
        if (finishType == "покраска") {
            costPerSqm = 300;
        } else if (finishType == "обои") {
            costPerSqm = 250;
        } else if (finishType == "штукатурка") {
            costPerSqm = 400;
        } else if (finishType == "плитка") {
            costPerSqm = 800;
        } else {
            costPerSqm = 200;
        }
        
        double totalCost = surfaceArea * costPerSqm;
        double remainingFactor = (100.0 - completionPercent) / 100.0;
        return totalCost * remainingFactor;
    }
    
    string getRiskLevel() override {
        if (finishType == "плитка" && surfaceArea > 200) {
            return "ВЫСОКИЙ";
        } else if (finishType == "штукатурка" && surfaceArea > 300) {
            return "СРЕДНИЙ";
        } else if (finishType == "покраска" && surfaceArea > 500) {
            return "СРЕДНИЙ";
        } else {
            return "НИЗКИЙ";
        }
    }
    
    void printInfo() override {
        BuildingTask::printInfo();
        cout << "Площадь:         " << surfaceArea << " м²" << endl;
        cout << "Тип отделки:     " << finishType << endl;
        
        cout << "Расход материалов: " << calculateMaterialConsumption();
        if (finishType == "покраска") {
            cout << " л" << endl;
        } else if (finishType == "обои") {
            cout << " рул." << endl;
        } else if (finishType == "штукатурка") {
            cout << " кг" << endl;
        } else {
            cout << " усл. ед." << endl;
        }
        
        cout << "Осталось оплатить: " << estimateCost() << " руб." << endl;
        cout << "Риск:            " << getRiskLevel() << endl;
        cout << "==========================================" << endl;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    
    cout << "\n========== СТРОИТЕЛЬНЫЕ РАБОТЫ ==========\n" << endl;
    
    BuildingTask* tasks[4];
    
    tasks[0] = new ExcavationTask("Котлован", "Иванов", 14, 30, 850, 3.5);
    tasks[1] = new FinishingTask("Отделка стен", "Петрова", 21, 45, 320, "штукатурка");
    tasks[2] = new ExcavationTask("Траншея", "Сидоров", 7, 80, 250, 2.0);
    tasks[3] = new FinishingTask("Плитка", "Васильева", 10, 20, 85, "плитка");
    
    cout << "\n--- ИНФОРМАЦИЯ О ЗАДАЧАХ ---\n" << endl;
    
    for (int i = 0; i < 4; i++) {
        cout << "\nЗадача " << (i + 1) << ":" << endl;
        tasks[i]->printInfo();
    }
    
    cout << "\n--- РАСЧЕТ СТОИМОСТИ ---" << endl;
    for (int i = 0; i < 4; i++) {
        cout << tasks[i]->getName() << ": " << tasks[i]->estimateCost() << " руб." << endl;
    }
    
    cout << "\n--- ОЦЕНКА РИСКА ---" << endl;
    for (int i = 0; i < 4; i++) {
        cout << tasks[i]->getName() << ": " << tasks[i]->getRiskLevel() << endl;
    }
    
    cout << "\n--- ОБНОВЛЕНИЕ ПРОГРЕССА ---" << endl;
    tasks[0]->updateProgress(50);
    tasks[1]->updateProgress(60);
    tasks[2]->updateProgress(100);
    tasks[3]->updateProgress(35);
    
    cout << "\n--- ИТОГОВАЯ ИНФОРМАЦИЯ ---\n" << endl;
    
    for (int i = 0; i < 4; i++) {
        cout << "\nЗадача " << (i + 1) << ":" << endl;
        tasks[i]->printInfo();
    }
    
    cout << "\n--- ОСВОБОЖДЕНИЕ ПАМЯТИ ---" << endl;
    for (int i = 0; i < 4; i++) {
        delete tasks[i];
    }
    
    return 0;
}
