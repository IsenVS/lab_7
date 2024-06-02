#include <iostream> 
#include <vector> 
#include <algorithm> 
#include <unordered_map> 

using namespace std; 

unordered_map<string, pair<int, vector<int>>> memo; // Объявление неупорядоченного словаря для хранения результатов

pair<int, vector<int>> maximizeScore(int remainingArrows, int target, const vector<int>& aliceArrows) {
    if (target < 0 || remainingArrows <= 0) { // Если нет цели или стрелы закончились
        return {0, vector<int>(12, 0)}; // Возвращаем пару с нулевым баллом и пустым вектором стрел
    }

    string key = to_string(remainingArrows) + "-" + to_string(target); // Формирование ключа для хранения результата в словаре
    if (memo.find(key) != memo.end()) { // Если результат уже есть в словаре
        return memo[key]; // Возвращаем результат из словаря
    }

    auto skip = maximizeScore(remainingArrows, target - 1, aliceArrows); // Попытка не стрелять в эту цель
    int maxScore = skip.first; // Максимальное количество баллов
    vector<int> bestArrows = skip.second; // Лучший вариант стрел

    int requiredArrows = aliceArrows[target] + 1; // Необходимое количество стрел для попадания
    if (remainingArrows >= requiredArrows) { // Если у Боба достаточно стрел
        auto shoot = maximizeScore(remainingArrows - requiredArrows, target - 1, aliceArrows); // Попытка выстрелить в эту цель
        shoot.first += target; // Боб зарабатывает 'target' баллов
        shoot.second[target] = requiredArrows; // Сохранение количества использованных стрел
        if (shoot.first > maxScore) { // Если текущий результат лучше
            maxScore = shoot.first; // Обновление максимального количества баллов
            bestArrows = shoot.second; // Обновление лучших стрел
        }
    }

    memo[key] = {maxScore, bestArrows}; // Сохранение результата в словаре
    return memo[key]; // Возвращаем результат
}

vector<int> maximizeBobScores(int numArrows, vector<int> aliceArrows) {
    memo.clear(); // Очистка словаря
    return maximizeScore(numArrows, 11, aliceArrows).second; // Максимизация баллов Боба и возврат лучших стрел
}

int main() {
    int numArrows; // Количество стрел для Боба
    vector<int> aliceArrows(12); // Количество стрел, необходимых Алисе для каждой цели

    cout << "Введите количество стрел для Боба: "; 
    cin >> numArrows;
    cout << "Введите количество стрел, необходимых Алисе для каждой цели (от 0 до 11) :" << endl; 
    for (int i = 0; i < 12; i++) {
        cout << "Оценка " << i << ": "; 
        cin >> aliceArrows[i];
    }

    vector<int> bobArrows = maximizeBobScores(numArrows, aliceArrows); // Максимизация баллов Боба
    cout << "Оптимальные стрелы для Боба для максимизации его баллов:" << endl; // 
    for (int arrows : bobArrows) {
        cout << arrows << " "; 
    }
    cout << endl;

    return 0;
}
