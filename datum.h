#ifndef DATUM_H
#define DATUM_H

#include <iostream>

class Datum {
public:
    static const int MIN_ROK = 1970;
    static const int MAX_ROK = 2050;

    enum DnyVTydnu { PONDELI, UTERY, STREDA, CTVRTEK, PATEK, SOBOTA, NEDELE };

    Datum();
    Datum(int d, int m, int r);
    Datum(const Datum& other);

    int ziskejDen() const;
    int ziskejMesic() const;
    int ziskejRok() const;
    void nastavDatum(int d, int m, int r);

    long pocetDniOd1970() const;
    DnyVTydnu poradoveCisloDneVTydnu() const;

    friend std::ostream& operator<<(std::ostream& os, const Datum& datum);

private:
    bool jePlatneDatum() const;
    int pocetDniVMesici() const;
    bool jePrestupnyRok() const;

    int den;
    int mesic;
    int rok;
};

#endif // DATUM_H
