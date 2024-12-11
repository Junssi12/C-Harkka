// Jussi Koivurinta
//C++ Harjoitustyö (2-3 pistettä)

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
    int yöt; // Yöpymisten määrä
    int hinta; // Kokonaislasku
    int varausnumero; // Varausnumero
};

// Funktio, joka tarkistaa käyttäjän syötteen olevan positiivinen luku
int Tarkastus() {
    int value;
    while (true) {
        cin >> value;
        if (cin.fail() || value <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Poistaa virheellisen syötteen
            cout << "Virheellinen syöte, anna positiivinen kokonaisluku: ";
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
            vapaatHuoneet.push_back(i + 1); // Lisää huoneen numero listalle
        }
    }

    if (vapaatHuoneet.empty()) {
        return -1;  // Ei vapaata huonetta
    }

    int randomIndex = rand() % vapaatHuoneet.size();
    return vapaatHuoneet[randomIndex];
}

// Funktio, joka arpoo varausnumeron väliltä 10000-99999
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
    return nullptr; // Ei löytynyt varausta
}

// Funktio, joka hakee varauksen varaajan nimellä
Varaukset* etsiNimi(vector<Varaukset>& varaukset, const string& asiakas) {
    for (auto& varaus : varaukset) {
        if (varaus.asiakas == asiakas) {
            return &varaus; // Palautetaan varauksen osoite
        }
    }
    return nullptr; // Ei löytynyt varausta
}

int main() {
    setlocale(LC_ALL, "FI_fi");

    srand(time(0)); // Satunnaislukugeneraattorin alustus

    // Arvotaan huoneiden määrä ja hinta
    int huoneittenMäärä = rand() % 41 + 30;
    int yönHinta = rand() % 21 + 80;

    // Ohjelman käyttäjälle tulostetaan tervehdys ja kerrotaan teidot
    cout << "Tervetuloa hotellin huonevarausohjelmaan!" << endl;
    cout << "\nHotellissamme on " << huoneittenMäärä << " huonetta." << endl;
    cout << "Huoneen hinta on " << yönHinta << " euroa per yö." << endl;

    // Huoneiden varaus: aluksi kaikki huoneet vapaita
    vector<bool> huoneet(huoneittenMäärä, false); // false tarkoittaa, että huone on vapaa
    vector<Varaukset> varaukset; // Varausten säilytys

    while (true) { //Luodaan ohjelman "menu"
        cout << "\n--Valitse toiminto--" << endl;
        cout << "1. Tee uusi varaus" << endl;
        cout << "2. Hae varaus varausnumerolla" << endl;
        cout << "3. Hae varaus varaajan nimellä" << endl;
        cout << "4. Poistu" << endl;
        cout << "\nValintasi: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1: { // Tee uusi varaus
            cin.ignore(); // Poistetaan edellinen syöte
            string asiakas;
            cout << "\nSyötä varaajan nimi: ";
            getline(cin, asiakas); // Varaajan nimi

            cout << "\nKuinka monta yötä haluat varata?" << endl;
            int yöt = Tarkastus(); // Käyttäjän antama yöiden määrä

            int huoneNumero = vapaaHuone(huoneet);
            if (huoneNumero == -1) { // Jos kaikki huneet täynnä, ilmoitetaan varaajalle
                cout << "\nValitettavasti ei ole vapaata huonetta." << endl;
            }
            else {
                int varausNumero = Varausnumero(); // Arvotaan varausnumero
                huoneet[huoneNumero - 1] = true; // Merkitään huone varatuksi

                int kokonaisHinta = yöt * yönHinta;
                Varaukset uusiVaraus = { asiakas, huoneNumero, yöt, kokonaisHinta, varausNumero };
                varaukset.push_back(uusiVaraus); // Tallennetaan varaus

                cout << "\nVarauksesi on onnistunut!" << endl;
                cout << "Varausnumero: " << varausNumero << endl;
                cout << "Varattu huoneen numero: " << huoneNumero << endl;
                cout << "Kokonaishinta: " << kokonaisHinta << " euroa." << endl;
            }
            break;
        }
        case 2: {  // Hae varaus varausnumerolla
            cout << "\nSyötä varausnumero: "; // Pyydetään varausnumero
            int varausnumero;
            cin >> varausnumero;

            bool found = false;
            for (const auto& varaus : varaukset) {
                if (varaus.varausnumero == varausnumero) { // Tulsotetaan pyydetyn asiakkaan tiedot
                    cout << "\nVaraus löytyi!" << endl;
                    cout << "Varaaja: " << varaus.asiakas << endl;
                    cout << "Huoneen numero: " << varaus.huone << endl;
                    cout << "Yöpymisten määrä: " << varaus.yöt << endl;
                    cout << "Kokonaishinta: " << varaus.hinta << " euroa." << endl;
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "\nVarausta ei löytynyt!" << endl; // Jos syötetään jokin muu kuin olemassa oleva varausnumero, varausta ei löydy
            }
            break;
        }
        case 3: { // Hae varaus varaajan nimellä
            cin.ignore(); // Poistetaan edellinen syöte
            string asiakas;
            cout << "\nSyötä varaajan nimi: "; // Pyydetään asiakkaan nimi
            getline(cin, asiakas);

            Varaukset* varaus = etsiNimi(varaukset, asiakas);
            if (varaus) { // Tulsotetaan pyydetyn asiakkaan tiedot
                cout << "\nVaraus löytyi!" << endl;
                cout << "Varaaja: " << varaus->asiakas << endl;
                cout << "Huoneen numero: " << varaus->huone << endl;
                cout << "Yöpymisten määrä: " << varaus->yöt << endl;
                cout << "Kokonaishinta: " << varaus->hinta << " euroa." << endl;
            }
            else {
                cout << "\nVarausta ei löytynyt!" << endl; // Jos nimeä ei löydy ohjelmasta tai sen kirjoittaa väärin varausta ei löydy
            }
            break;
        }
        case 4: { // Suljetaan ohjelma
            system("cls"); // Tyhjennetään näyttö
            cout << "\nKiitos ja tervetuloa uudelleen!" << endl; // Kiitetään asiakasta
            std::this_thread::sleep_for(std::chrono::seconds(3)); // Suljetaan ohjelma ajastetust
            exit(0);
        }
        default:
            cout << "\nVirheellinen valinta!" << endl; // Jos mikään case ei toteudu, ilmoitetaan virheestä ja aloitetaan alust
            break;
        }
    }

    return 0;
}
