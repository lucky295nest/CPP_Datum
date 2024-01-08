#include "datum.h"
#include <iostream>

int main() {
    Datum d;
    std::cout << d;
    std::cout << "-----------------------------" << std::endl;

    int vyber;
    do {
        std::cout << "Vyberte moznost:" << std::endl;
        std::cout << "1. Nastavit novy datum" << std::endl;
        std::cout << "2. Ziskat datum, pocet dni od 1. 1. 1970 a den v tydnu" << std::endl;
        std::cout << "0. Konec" << std::endl;

        std::cin >> vyber;

        switch (vyber) {
        case 1: {
            int novyDen, novyMesic, novyRok;
            std::cout << "Zadejte novy den: ";
            std::cin >> novyDen;
            std::cout << "Zadejte novy mesic: ";
            std::cin >> novyMesic;
            std::cout << "Zadejte novy rok: ";
            std::cin >> novyRok;

            d.nastavDatum(novyDen, novyMesic, novyRok);
            break;
        }
        case 2: {
            std::cout << d;
            break;
        }
        case 0: {
            break;
        }
        default: {
            std::cout << "Neplatna volba. Zkuste znovu." << std::endl;
            break;
        }
        }

    } while (vyber != 0);

    return 0;
}
