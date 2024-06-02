#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool canPlaceItemsRecursively(const vector<int>& items, vector<int>& containerFills, int index, int N, int H) {
    if (index == items.size()) {
        // Все предметы успешно размещены
        return true;
    }
    
    for (int i = 0; i < N; ++i) {
        if (containerFills[i] + items[index] <= H) {
            // Попробуем разместить текущий предмет в контейнер i
            containerFills[i] += items[index];
            
            // Рекурсивно пытаемся разместить следующий предмет
            if (canPlaceItemsRecursively(items, containerFills, index + 1, N, H)) {
                return true;
            }
            
            // Если не удалось разместить следующий предмет, убираем текущий предмет из контейнера
            containerFills[i] -= items[index];
        }
    }
    
    // Если не удалось разместить предмет в ни один из контейнеров
    return false;
}

bool canPlaceItems(const vector<int>& items, int N, int H) {
    // Подсчитаем общую высоту всех предметов
    int totalItemHeight = 0;
    for (int height : items) {
        totalItemHeight += height;
    }
    
    // Проверяем, не превышает ли общая высота предметов общую вместимость контейнеров
    if (totalItemHeight > N * H) {
        return false;
    }
    
    // Сортируем предметы по убыванию их высоты для оптимального размещения
    vector<int> sortedItems(items);
    sort(sortedItems.begin(), sortedItems.end(), greater<int>());
    
    // Создаем вектор для отслеживания заполнения каждого контейнера
    vector<int> containerFills(N, 0);
    
    // Пытаемся разместить предметы рекурсивно
    return canPlaceItemsRecursively(sortedItems, containerFills, 0, N, H);
}

int main() {
    int N, H, numItems;
    cout << "Введите количество контейнеров N: ";
    cin >> N;
    cout << "Введите высоту контейнеров H: ";
    cin >> H;
    cout << "Введите количество предметов: ";
    cin >> numItems;
    vector<int> items(numItems);
    cout << "Введите высоты предметов:\n";
    for (int i = 0; i < numItems; ++i) {
        cin >> items[i];
    }
    
    bool result = canPlaceItems(items, N, H);
    if (result) {
        cout << "Да, можно разместить все предметы в контейнерах.\n";
    } else {
        cout << "Нет, нельзя разместить все предметы в контейнерах.\n";
    }
    
    return 0;
}
