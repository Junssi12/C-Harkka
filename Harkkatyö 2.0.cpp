// Jussi Koivurinta
//C++ Harjoitusty� (2-3 pistett�)

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <limits>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

// Luodaan rakenteen, jonka avulla voidaan tallentaa varaukset
struct Varaukset {
    string asiakas; // Varaajan nimi
    int huone; // Huoneen numero
    int y�t; // Y�pymisten m��r�
    int hinta; // Kokonaislasku
    int varausnumero; // Varausnumero
};

// Funktio, joka tarkistaa k�ytt�j�n sy�tteen olevan positiivinen luku
int Tarkastus() {
    int value;
    while (true) {
        cin >> value;
        if (cin.fail() || value <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Poistaa virheellisen sy�tteen
            cout << "Virheellinen sy�te, anna positiivinen kokonaisluku: ";
        }
        else {
            break;
        }
    }
    return value;
}

// Funktio, joka arpoo satunnaisen huoneen numeron, joka on vapaa
int vapaaHuone(vector<bool>& huoneet) {
    vector<int> vapaatHuoneet;
    for (int i = 0; i < huoneet.size(); ++i) {
        if (!huoneet[i]) {
            vapaatHuoneet.push_back(i + 1); // Lis�� huoneen numero listalle
        }
    }

    if (vapaatHuoneet.empty()) {
        return -1;  // Ei vapaata huonetta
    }

    int randomIndex = rand() % vapaatHuoneet.size();
    return vapaatHuoneet[randomIndex];
}

// Funktio, joka arpoo varausnumeron v�lilt� 10000-99999
int Varausnumero() {
    return rand() % 90000 + 10000;
}

// Funktio, joka hakee varauksen varausnumerolla
Varaukset* etsiHuone(vector<Varaukset>& varaukset, int huone) {
    for (auto& varaus : varaukset) {
        if (varaus.huone == huone) {
            return &varaus; // Palautetaan varauksen osoite
        }
    }
    return nullptr; // Ei l�ytynyt varausta
}

// Funktio, joka hakee varauksen varaajan nimell�
Varaukset* etsiNimi(vector<Varaukset>& varaukset, const string& asiakas) {
    for (auto& varaus : varaukset) {
        if (varaus.asiakas == asiakas) {
            return &varaus; // Palautetaan varauksen osoite
        }
    }
    return nullptr; // Ei l�ytynyt varausta
}

int main() {
    setlocale(LC_ALL, "FI_fi");

    srand(time(0)); // Satunnaislukugeneraattorin alustus

    // Arvotaan huoneiden m��r� ja hinta
    int huoneittenM��r� = rand() % 41 + 30;
    int y�nHinta = rand() % 21 + 80;

    // Ohjelman k�ytt�j�lle tulostetaan tervehdys ja kerrotaan teidot
    cout << "Tervetuloa hotellin huonevarausohjelmaan!" << endl;
    cout << "\nHotellissamme on " << huoneittenM��r� << " huonetta." << endl;
    cout << "Huoneen hinta on " << y�nHinta << " euroa per y�." << endl;

    // Huoneiden varaus: aluksi kaikki huoneet vapaita
    vector<bool> huoneet(huoneittenM��r�, false); // false tarkoittaa, ett� huone on vapaa
    vector<Varaukset> varaukset; // Varausten s�ilytys

    while (true) { //Luodaan ohjelman "menu"
        cout << "\n--Valitse toiminto--" << endl;
        cout << "1. Tee uusi varaus" << endl;
        cout << "2. Hae varaus varausnumerolla" << endl;
        cout << "3. Hae varaus varaajan nimell�" << endl;
        cout << "4. Poistu" << endl;
        cout << "\nValintasi: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1: { // Tee uusi varaus
            cin.ignore(); // Poistetaan edellinen sy�te
            string asiakas;
            cout << "\nSy�t� varaajan nimi: ";
            getline(cin, asiakas); // Varaajan nimi

            cout << "\nKuinka monta y�t� haluat varata?" << endl;
            int y�t = Tarkastus(); // K�ytt�j�n antama y�iden m��r�

            int huoneNumero = vapaaHuone(huoneet);
            if (huoneNumero == -1) { // Jos kaikki huneet t�ynn�, ilmoitetaan varaajalle
                cout << "\nValitettavasti ei ole vapaata huonetta." << endl;
            }
            else {
                int varausNumero = Varausnumero(); // Arvotaan varausnumero
                huoneet[huoneNumero - 1] = true; // Merkit��n huone varatuksi

                int kokonaisHinta = y�t * y�nHinta;
                Varaukset uusiVaraus = { asiakas, huoneNumero, y�t, kokonaisHinta, varausNumero };
                varaukset.push_back(uusiVaraus); // Tallennetaan varaus

                cout << "\nVarauksesi on onnistunut!" << endl;
                cout << "Varausnumero: " << varausNumero << endl;
                cout << "Varattu huoneen numero: " << huoneNumero << endl;
                cout << "Kokonaishinta: " << kokonaisHinta << " euroa." << endl;
            }
            break;
        }
        case 2: {  // Hae varaus varausnumerolla
            cout << "\nSy�t� varausnumero: "; // Pyydet��n varausnumero
            int varausnumero;
            cin >> varausnumero;

            bool found = false;
            for (const auto& varaus : varaukset) {
                if (varaus.varausnumero == varausnumero) { // Tulsotetaan pyydetyn asiakkaan tiedot
                    cout << "\nVaraus l�ytyi!" << endl;
                    cout << "Varaaja: " << varaus.asiakas << endl;
                    cout << "Huoneen numero: " << varaus.huone << endl;
                    cout << "Y�pymisten m��r�: " << varaus.y�t << endl;
                    cout << "Kokonaishinta: " << varaus.hinta << " euroa." << endl;
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "\nVarausta ei l�ytynyt!" << endl; // Jos sy�tet��n jokin muu kuin olemassa oleva varausnumero, varausta ei l�ydy
            }
            break;
        }
        case 3: { // Hae varaus varaajan nimell�
            cin.ignore(); // Poistetaan edellinen sy�te
            string asiakas;
            cout << "\nSy�t� varaajan nimi: "; // Pyydet��n asiakkaan nimi
            getline(cin, asiakas);

            Varaukset* varaus = etsiNimi(varaukset, asiakas);
            if (varaus) { // Tulsotetaan pyydetyn asiakkaan tiedot
                cout << "\nVaraus l�ytyi!" << endl;
                cout << "Varaaja: " << varaus->asiakas << endl;
                cout << "Huoneen numero: " << varaus->huone << endl;
                cout << "Y�pymisten m��r�: " << varaus->y�t << endl;
                cout << "Kokonaishinta: " << varaus->hinta << " euroa." << endl;
            }
            else {
                cout << "\nVarausta ei l�ytynyt!" << endl; // Jos nime� ei l�ydy ohjelmasta tai sen kirjoittaa v��rin varausta ei l�ydy
            }
            break;
        }
        case 4: { // Suljetaan ohjelma
            system("cls"); // Tyhjennet��n n�ytt�
            cout << "\nKiitos ja tervetuloa uudelleen!" << endl; // Kiitet��n asiakasta
            std::this_thread::sleep_for(std::chrono::seconds(3)); // Suljetaan ohjelma ajastetust
            exit(0);
        }
        default:
            cout << "\nVirheellinen valinta!" << endl; // Jos mik��n case ei toteudu, ilmoitetaan virheest� ja aloitetaan alust
            break;
        }
    }

    return 0;
}
