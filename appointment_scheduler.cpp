#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

struct Appointment {
    int id;
    string name;
    string purpose;
    string date;
    string time;
};

vector<Appointment> appointments;
int nextId = 1;

// --- Load & Save ---
void loadAppointments() {
    ifstream file("appointments.txt");
    Appointment a;
    while (file >> a.id) {
        file.ignore();
        getline(file, a.name);
        getline(file, a.purpose);
        getline(file, a.date);
        getline(file, a.time);
        appointments.push_back(a);
        nextId = a.id + 1;
    }
    file.close();
}

void saveAppointments() {
    ofstream file("appointments.txt");
    for (const auto& a : appointments) {
        file << a.id << "\n" << a.name << "\n" << a.purpose << "\n"
             << a.date << "\n" << a.time << "\n";
    }
    file.close();
}

// --- Validation ---
bool isValidDate(const string& date) {
    if (date.length() != 10 || date[4] != '-' || date[7] != '-') return false;
    for (int i = 0; i < date.length(); ++i) {
        if (i == 4 || i == 7) continue;
        if (!isdigit(date[i])) return false;
    }
    return true;
}

bool isValidTime(const string& time) {
    if (time.length() != 5 || time[2] != ':') return false;
    string hh = time.substr(0, 2);
    string mm = time.substr(3, 2);
    if (!isdigit(hh[0]) || !isdigit(hh[1]) || !isdigit(mm[0]) || !isdigit(mm[1])) return false;
    int hour = stoi(hh);
    int minute = stoi(mm);
    return (hour >= 0 && hour < 24 && minute >= 0 && minute < 60);
}

bool isDuplicateSlot(const string& date, const string& time) {
    for (const auto& a : appointments) {
        if (a.date == date && a.time == time) return true;
    }
    return false;
}

// --- Appointment Functions ---
void addAppointment() {
    Appointment a;
    a.id = nextId++;
    cin.ignore();

    do {
        cout << "Client Name: ";
        getline(cin, a.name);
        if (a.name.empty()) cout << "Name cannot be empty.\n";
    } while (a.name.empty());

    do {
        cout << "Purpose: ";
        getline(cin, a.purpose);
        if (a.purpose.empty()) cout << "Purpose cannot be empty.\n";
    } while (a.purpose.empty());

    do {
        cout << "Date (YYYY-MM-DD): ";
        getline(cin, a.date);
        if (!isValidDate(a.date)) {
            cout << "Invalid date format. Try again.\n";
            continue;
        }
        break;
    } while (true);

    do {
        cout << "Time (HH:MM): ";
        getline(cin, a.time);
        if (!isValidTime(a.time)) {
            cout << "Invalid time format. Try again.\n";
            continue;
        }
        break;
    } while (true);

    if (isDuplicateSlot(a.date, a.time)) {
        cout << "An appointment already exists at that date and time.\n";
        return;
    }

    appointments.push_back(a);
    cout << "Appointment added successfully.\n";
}

void viewAppointments() {
    cout << "\n--- All Appointments ---\n";
    for (const auto& a : appointments) {
        cout << "ID: " << a.id << "\nName: " << a.name << "\nPurpose: " << a.purpose
             << "\nDate: " << a.date << "\nTime: " << a.time << "\n---\n";
    }
}

void searchAppointment() {
    cin.ignore();
    string keyword;
    cout << "Enter name to search: ";
    getline(cin, keyword);
    for (const auto& a : appointments) {
        if (a.name.find(keyword) != string::npos) {
            cout << "ID: " << a.id << "\nName: " << a.name << "\nPurpose: " << a.purpose
                 << "\nDate: " << a.date << "\nTime: " << a.time << "\n---\n";
        }
    }
}

void deleteAppointment() {
    int id;
    cout << "Enter ID to delete: ";
    cin >> id;
    for (auto it = appointments.begin(); it != appointments.end(); ++it) {
        if (it->id == id) {
            appointments.erase(it);
            cout << "Appointment deleted.\n";
            return;
        }
    }
    cout << "Appointment not found.\n";
}

// --- Login ---
bool login(string& role) {
    string username, password;

    cout << "===== Login =====\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (username == "admin" && password == "admin123") {
        role = "admin";
        return true;
    } else if (username == "user" && password == "user123") {
        role = "user";
        return true;
    } else {
        cout << "Invalid credentials.\n";
        return false;
    }
}

// --- Menus ---
void userMenu() {
    int choice;
    do {
        cout << "\n--- User Menu ---\n";
        cout << "1. Book Appointment\n2. View Appointments\n3. Search\n4. Exit\nChoose: ";
        cin >> choice;
        switch (choice) {
            case 1: addAppointment(); break;
            case 2: viewAppointments(); break;
            case 3: searchAppointment(); break;
            case 4: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 4);
}

void adminMenu() {
    int choice;
    do {
        cout << "\n--- Admin Menu ---\n";
        cout << "1. View Appointments\n2. Search\n3. Delete Appointment\n4. Exit\nChoose: ";
        cin >> choice;
        switch (choice) {
            case 1: viewAppointments(); break;
            case 2: searchAppointment(); break;
            case 3: deleteAppointment(); break;
            case 4: cout << "Logging out...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 4);
}

// --- Main ---
int main() {
    loadAppointments();
    string role;

    while (!login(role)); // Repeat until login succeeds

    if (role == "admin") {
        adminMenu();
    } else if (role == "user") {
        userMenu();
    }

    saveAppointments();
    return 0;
}

