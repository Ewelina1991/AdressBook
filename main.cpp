#include <iostream>
#include <windows.h> // zeby system("cls") dzialal
#include <fstream> //biblioteka odpowiedzialna za operacje plikowe

using namespace std;

struct Person {
    int id;
    string name, lastName, phoneNumber, email, address;
};

int AddPerson(Person people[], int numberOfPeople) {
    string name, lastName, phoneNumber, email, address;
    // Pobieram dane nowej osoby
    system("cls");
    cout << "Dodawanie osoby" << endl;
    cout << "Podaj imie uzytkownika: ";
    cin >> name;
    cout << "Podaj nazwisko uzytkownika: ";
    cin >> lastName;
    cout << "Podaj numer telefonu uzytkownika: ";
    cin.sync(); // oprozniam bufor
    getline(cin, phoneNumber); // wczytuje razem ze spacja
    cout << "Podaj email uzytkownika: ";
    cin >> email;
    cout << "Podaj address uzytkownika: ";
    cin.sync();
    getline(cin, address);

    // ustalam id osoby
    int PersonId = numberOfPeople+ 1;

    // dodaje osobe do tablicy
    people[numberOfPeople].id = PersonId;
    people[numberOfPeople].name = name;
    people[numberOfPeople].lastName = lastName;
    people[numberOfPeople].phoneNumber = phoneNumber;
    people[numberOfPeople].email = email;
    people[numberOfPeople].address = address;

    // dodaje osobe do pliku
    fstream file;
    file.open("AddressBook.txt", ios::out | ios::app);
    if (file.good() == true) {
        file << PersonId << endl;
        file << name << endl;
        file << lastName << endl;
        file << phoneNumber << endl;
        file << email << endl;
        file << address << endl;
        file.close();
    } else {
        cout << "Nie mozna otworzyc pliku: AddressBook.txt" << endl;
        system("pause");
    }
    cout << "Osoba zostala dodana." << endl;
    system("pause");
    return numberOfPeople+1;
}

int loadPeopleFromTheFile(Person people[]) {
    string line;
    int numberOfLine=1;
    int numberOfPeople=0;

    fstream file;
    file.open("AddressBook.txt", ios::in);
    if (file.good() == true) {
        while(getline(file,line)) {
            switch(numberOfLine) {
            case 1:
                people[numberOfPeople].id = atoi(line.c_str());
                break;
            case 2:
                people[numberOfPeople].name = line;
                break;
            case 3:
                people[numberOfPeople].lastName = line;
                break;
            case 4:
                people[numberOfPeople].phoneNumber = line;
                break;
            case 5:
                people[numberOfPeople].email = line;
                break;
            case 6:
                people[numberOfPeople].address = line;
                break;
            }

            if (numberOfLine >= 6) {
                numberOfLine=1;
                numberOfPeople++;
            } else {
                numberOfLine++;
            }
        }
        file.close();
    }
    return numberOfPeople;
}

void displayAddressBook(Person people[], int numberOfPeople) {
    for (int i = 0; i < numberOfPeople; i++) {
        cout << endl;
        cout << people[i].id << ". " << people[i].name << " " << people[i].lastName << endl;
        cout << "Telefon: " << people[i].phoneNumber << endl;
        cout << "Email: " << people[i].email << endl;
        cout << "Adres: " << people[i].address << endl;
        cout << endl;
    }
    system ("pause");
}

void findPersonByName(Person people[], int numberOfPeople) {
    string name;
    cout << "Podaj imie jakie chcesz znalezc: ";
    cin >> name;

    for (int i = 0; i < numberOfPeople; i++) {
        if (people[i].name == name) {
            cout << endl;
            cout << "ID: " << people[i].id << endl;
            cout << people[i].name << " " << people[i].lastName << endl;
            cout << "Telefon: " << people[i].phoneNumber << endl;
            cout << "Email: " << people[i].email << endl;
            cout << "Adres: " << people[i].address << endl;
            cout << endl;
        }
    }
    system ("pause");
}

void findPersonByLastName(Person people[], int numberOfPeople) {
    string lastName;
    cout << "Podaj nazwisko jakie chcesz znalezc: ";
    cin >> lastName;

    for (int i = 0; i < numberOfPeople; i++) {
        if (people[i].lastName == lastName) {
            cout << endl;
            cout << "ID: " << people[i].id << endl;
            cout << people[i].name << " " << people[i].lastName << endl;
            cout << "Telefon: " << people[i].phoneNumber << endl;
            cout << "Email: " << people[i].email << endl;
            cout << "Adres: " << people[i].address << endl;
            cout << endl;
        }
    }
    system ("pause");
}

int main() {
    Person people[1000];
    int numberOfPeople= 0;
    char choice;

    numberOfPeople= loadPeopleFromTheFile(people);

    while (true) {
        system("cls");
        cout << "1. Dodaj osobe" << endl;
        cout << "2. Wyswietl cala ksiazke adresowa" << endl;
        cout << "3. Wyszukaj osoby po imieniu" << endl;
        cout << "4. Wyszukaj osoby po nazwisku" << endl;
        cout << "5. Zakoncz program" << endl;
        cin >> choice;

        if (choice == '1') {
            numberOfPeople= AddPerson(people, numberOfPeople);
        }
        if (choice == '2') {
            displayAddressBook(people, numberOfPeople);
        }
        if (choice == '3') {
            findPersonByName(people, numberOfPeople);
        }
        if (choice == '4') {
            findPersonByLastName(people,numberOfPeople);
        } else if (choice == '5') {
            exit(0);
        }
    }
    return 0;
}

