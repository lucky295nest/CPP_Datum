#include "datum.h"
#include <iostream>

#if defined(_MSC_VER) && _MSC_VER >= 1400
#define _CRT_SECURE_NO_WARNINGS
#endif

Datum::Datum() {
    std::time_t systemTime = std::time(nullptr);
    std::tm localTime = {};
#if defined(_MSC_VER) && _MSC_VER >= 1400
    localtime_s(&localTime, &systemTime);
#else
    std::tm* tmp = std::localtime(&systemTime);
    if (tmp)
        localTime = *tmp;
#endif
    den = localTime.tm_mday;
    mesic = localTime.tm_mon + 1;
    rok = localTime.tm_year + 1900;
}

Datum::Datum(int d, int m, int r) : den(d), mesic(m), rok(r) {
    if (!jePlatneDatum()) {
        std::cerr << "Neplatne datum! Nastaveno na 1. 1. 1970." << std::endl;
        den = 1;
        mesic = 1;
        rok = MIN_ROK;
    }
}

Datum::Datum(const Datum& other) : den(other.den), mesic(other.mesic), rok(other.rok) {}

int Datum::ziskejDen() const {
    return den;
}

int Datum::ziskejMesic() const {
    return mesic;
}

int Datum::ziskejRok() const {
    return rok;
}

void Datum::nastavDatum(int d, int m, int r) {
    den = d;
    mesic = m;
    rok = r;
    if (!jePlatneDatum()) {
        std::cerr << "Neplatne datum! Nastaveno na 1. 1. 1970." << std::endl;
        den = 1;
        mesic = 1;
        rok = MIN_ROK;
    }
}

long Datum::pocetDniOd1970() const {
    std::tm timeinfo = {};
    timeinfo.tm_year = rok - 1900;
    timeinfo.tm_mon = mesic - 1;
    timeinfo.tm_mday = den;

    std::time_t timeSinceEpoch = std::mktime(&timeinfo);
    return static_cast<long>(timeSinceEpoch / (60 * 60 * 24));
}

Datum::DnyVTydnu Datum::poradoveCisloDneVTydnu() const {
    std::tm timeinfo = {};
    timeinfo.tm_year = rok - 1900;
    timeinfo.tm_mon = mesic - 1;
    timeinfo.tm_mday = den;

    std::mktime(&timeinfo);
    return static_cast<DnyVTydnu>(timeinfo.tm_wday);
}

bool Datum::jePlatneDatum() const {
    if (rok < MIN_ROK || rok > MAX_ROK || mesic < 1 || mesic > 12 || den < 1 || den > pocetDniVMesici()) {
        return false;
    }
    return true;
}

int Datum::pocetDniVMesici() const {
    int pocetDniVMesici[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (mesic == 2 && jePrestupnyRok()) {
        return 29;
    }
    return pocetDniVMesici[mesic];
}

bool Datum::jePrestupnyRok() const {
    return (rok % 4 == 0 && rok % 100 != 0) || (rok % 400 == 0);
}

std::ostream& operator<<(std::ostream& os, const Datum& datum) {
    os << "Datum: " << datum.ziskejDen() << "." << datum.ziskejMesic() << "." << datum.ziskejRok() << std::endl;
    os << "Pocet dni od 1. 1. 1970: " << datum.pocetDniOd1970() << std::endl;
    os << "Poradove cislo dne v tydnu: " << datum.poradoveCisloDneVTydnu() << std::endl;
    return os;
}
