#include <iostream>
#include <cmath>
#include <locale>
#include <string>

void showStatus(const std::string& message) {
    std::cout << "\n[БАЛЛАСТ] " << message << "\n";
}

int main() {
    std::setlocale(LC_ALL, "Russian");

    std::cout << "--- УПРАВЛЕНИЕ БАЛЛАСТОМ СУБМАРИНЫ ---\n\n";

    const double LITERS_PER_METER = 60.0;
    const double MAX_DEPTH = 300.0;
    const double TANK_CAPACITY = 15000.0;

    double currentVolume = 0.0;
    double targetDepth = 0.0;

    std::cout << "Введите текущий объем воды в цистернах (л): ";
    std::cin >> currentVolume;

    std::cout << "Введите необходимую глубину погружения (м): ";
    std::cin >> targetDepth;

    if (std::cin.fail()) {
        std::cout << "\n❌ [ОШИБКА] Некорректный ввод. Введите числа.\n";
        return 1;
    }
    if (currentVolume < 0) {
        std::cout << "\n❌ [ОШИБКА] Объем воды не может быть отрицательным.\n";
        return 1;
    }
    if (currentVolume > TANK_CAPACITY) {
        std::cout << "\n❌ [ОШИБКА] Объем превышает вместимость цистерн ("
                  << TANK_CAPACITY << " л).\n";
        return 1;
    }
    if (targetDepth <= 0) {
        std::cout << "\n❌ [ОШИБКА] Глубина должна быть больше нуля.\n";
        return 1;
    }
    if (targetDepth > MAX_DEPTH) {
        showStatus("❌ ОПАСНО: превышен предел прочности корпуса (300 м). Погружение отменено.");
        return 2;
    }

    double targetVolume = targetDepth * LITERS_PER_METER;
    double delta = targetVolume - currentVolume;

    std::cout << "\nЦелевой объем воды для глубины " << targetDepth
              << " м: " << targetVolume << " л.\n";

    if (targetVolume > TANK_CAPACITY) {
        showStatus("❌ НЕВОЗМОЖНО: для заданной глубины не хватит цистерн.");
        std::cout << "Требуется " << targetVolume << " л, доступно "
                  << TANK_CAPACITY << " л.\n";
        return 3;
    }

    if (std::fabs(delta) < 1e-6) {
        showStatus("✅ СУБМАРИНА УЖЕ НА ЦЕЛЕВОЙ ГЛУБИНЕ. Изменения не требуются.");
    } else if (delta > 0) {
        showStatus("⬇️ ДОКАЧАТЬ ВОДУ: " + std::to_string((int)delta) + " л (погружение).");
        std::cout << "Итоговый объем в цистернах: " << targetVolume << " л.\n";
    } else {
        showStatus("⬆️ СБРОСИТЬ ВОДУ: " + std::to_string((int)(-delta)) + " л (всплытие).");
        std::cout << "Итоговый объем в цистернах: " << targetVolume << " л.\n";
    }

    return 0;
}