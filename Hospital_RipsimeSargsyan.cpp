#include <iostream>
#include <istream>
#include <ostream>
#include <cmath>
#include <string>
#include <regex>
#include <vector>

using namespace std;


enum Profession {
    GENERAL_PRACTITIONER,
    SURGEON,
    PEDIATRICIAN,
    PSYCHIATRIST,
    DENTIST,
    ORTHOPEDIST,
    ONCOLOGIST,
    NEUROLOGIST,
    CARDIOLOGIST,
    ANESTHESIOLOGIST,
    OPHTHALMOLOGIST,
    DERMATOLOGIST,
    RADIOLOGIST
};

// PRINT FUNCTIONS
static void PrintDateTime(tm& dateTime) {
    cout << "Дата Регистрации:\n";
    cout << "Месяц- " << dateTime.tm_mon;
    cout << "\nДень- " << dateTime.tm_mday;
    cout << "\nЧасы- " << dateTime.tm_hour;
    cout << "\nМинуты- " << dateTime.tm_min;
}
static void PrintAllProfessions() {

    cout << "\nВыберите профессию:\n";
    cout << "0 - Терапевт\n";
    cout << "1 - Хирург\n";
    cout << "2 - Педиатр\n";
    cout << "3 - Психиатр\n";
    cout << "4 - Стоматолог\n";
    cout << "5 - Ортопед\n";
    cout << "6 - Онколог\n";
    cout << "7 - Невролог\n";
    cout << "8 - Кардиолог\n";
    cout << "9 - Анестезиолог\n";
    cout << "10 - Офтальмолог\n";
    cout << "11 - Дерматолог\n";
    cout << "12 - Радиолог\n";
}

// ENTER FUNCTIONS
static tm EnterDateTime() {
    std::cout << "\nВведите дату и время регистрации в формате ММ-ДД ЧЧ:ММ):\n";

    tm dateTime = {};
    std::string input;
    string s, s1;
    int d[6];
    cin >> s >> s1;
    s += ' ' + s1;
    std::regex rgx("\\d+");
    auto words_begin = std::sregex_iterator(s.begin(), s.end(), rgx);
    auto words_end = std::sregex_iterator();

    if (std::distance(words_begin, words_end) < 4) {
        cout << "Введите корректные данные в формате мм-дд чч:мм\n";
    }

    int l = 0;

    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i; //берет из совпадений обьект тип сматч
        std::string match_str = match.str(); //их смач берет его значение
        d[l++] = stoi(match_str);            //делает инт

        std::cout << d[l - 1] << '\n';
    }
    if (d[0] <= 0 || d[0] > 12) { // month check
        cout << "Некорректные данные\n";
        EnterDateTime();
    }
    else if (d[1] <= 0 || d[1] > 31) { // day check
        cout << "Некорректные данные\n";
        EnterDateTime();
    }
    else if (d[2] < 0 || d[2] > 24) { //часы
        cout << "Некорректные данные\n";
        EnterDateTime();
    }
    else if (d[3] < 0 || d[3] > 60) { // minutes
        cout << "Некорректные данные\n";
        EnterDateTime();
    }
    else {
        dateTime.tm_mon = d[0];
        dateTime.tm_mday = d[1];
        dateTime.tm_hour = d[2];
        dateTime.tm_min = d[3];
    }
    return dateTime;
}
static Profession EnterProfession() {
    int input;
    Profession profession = Profession::GENERAL_PRACTITIONER;

    while (true) {
        PrintAllProfessions();
        std::cin >> input;

        if (input >= 0 && input <= static_cast<int>(Profession::RADIOLOGIST)) {
            profession = static_cast<Profession>(input);
            break;
        }
        else {
            std::cout << "Ошибка ввода. Пожалуйста, введите числов диапазоне 0 и "
                << static_cast<int>(Profession::RADIOLOGIST) << std::endl;

            // Очистим буфер ввода, чтобы избежать зацикливания при некорректном вводе
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    return profession;
}
static string EnterName() {
    string name = "";
    cout << "\nВведите имя\n";
    cin >> name;
    return name;
}
static int EnterNumber() {
    int number = -1;
    while (number == -1) {
        cout << "\nВведите корректные данные\n";
    }
    return number;
}



ostream& operator<<(ostream& os, const Profession& profession) {
    switch (profession) {
    case GENERAL_PRACTITIONER:
        os << "Терапевт";
        break;
    case SURGEON:
        os << "Хирург";
        break;
    case PEDIATRICIAN:
        os << "Педиатр";
        break;
    case PSYCHIATRIST:
        os << "Психиатр";
        break;
    case DENTIST:
        os << "Стоматолог";
        break;
    case ORTHOPEDIST:
        os << "Ортопед";
        break;
    case ONCOLOGIST:
        os << "Онколог";
        break;
    case NEUROLOGIST:
        os << "Невролог";
        break;
    case CARDIOLOGIST:
        os << "Кардиолог";
        break;
    case ANESTHESIOLOGIST:
        os << "Анестезиолог";
        break;
    case OPHTHALMOLOGIST:
        os << "Офтальмолог";
        break;
    case DERMATOLOGIST:
        os << "Дерматолог";
        break;
    case RADIOLOGIST:
        os << "Радиолог";
        break;
    default:
        os << "Unknown Profession";
        break;
    }
    return os;
}
class Person {
protected:
    static int count;
    static int deleted;
    string name = "";
    int id = 0;

    Person() {}
    Person(string _name) : name(_name) {
        count++;
        id = count;
    }

    ~Person() { deleted++; }
};
int Person::count = 0;
int Person::deleted = 0;
class Doctor : public Person {
public:
    Profession profession;
    Doctor() {}
    Doctor(string _name, Profession _profession)
        : Person(_name), profession(_profession) {}

    int Count() { return this->count - deleted; }

    void PrintInfo() const {
        cout << "Имя: " << name << "\n";
        cout << "ИД: " << id << "\n";
        cout << "Профессия: " << profession << endl;
    }
    int GetId() const { return id; }

    bool operator==(const Doctor& other) const {
        return this->id == other.id; 
    }
};
class Patient : public Person {
public:
    Doctor doctor;
    tm regisTime;
    Patient() {}
    Patient(string _name, Doctor& _doctor, tm& _time) : Person(_name), doctor(_doctor), regisTime(_time) {}

    void AddRegisTime(tm& time) {
        regisTime = time;
    }
    void PrintInfo() {
        cout << "Имя: " << name << "\n";
        cout << "ИД: " << id << "\n";
        cout << "Данные доктора: " << endl;
        cout << "Данные регистрации: " << endl;
        PrintDateTime(regisTime);

    }
    static int Count() { return count; }
    int GetDoctorId() const { return doctor.GetId(); }

    bool operator==(const Patient& other) const {
        return this->id == other.id; 
    }
};

class Hospital {
public:
    static vector <Doctor> Doctors;
    static vector <Patient> Patients;
    
    static void AddDoctorToList(const Doctor& doc) { Doctors.push_back(doc); }
    static void DeleteDoctor(const Doctor& doc) {
        auto it = find(Doctors.begin(), Doctors.end(), doc);
        if (it != Doctors.end()) {
            Doctors.erase(it);
        }
    }
    static void PrintAllDoctors() {
        std::cout << "Все доступные докторы: " << std::endl;
        for (Doctor& elem : Doctors) {
            elem.PrintInfo();
        }
    }
    static void AddPatientToList(const Patient& pat) { Patients.push_back(pat); }
    static void DeletePatient(const Patient& pat) { 
        auto it = find(Patients.begin(), Patients.end(), pat);
        if (it != Patients.end()) {
            Patients.erase(it);
        }
    }
    static void PrintAllPatients() {
        std::cout << "Все действующие пациенты : " << std::endl;
        for (Patient& elem : Patients) {
            elem.PrintInfo();
        }
    }

};
vector<Doctor> Hospital::Doctors;
vector<Patient> Hospital::Patients;
bool DateIsEqual(tm& date1, tm& date2) {
    time_t d1 = mktime(&date1);
    time_t d2 = mktime(&date2);

    if (d1 == d2) {
        return true;
    }
    return false;
}
static bool TimeBookedChecker(tm date, Doctor& doc) //проверка свободности даты
{
    if (Hospital::Patients.empty())
        return true;
    else {
        for (int i = 0; i < Hospital::Patients.size(); i++) {
            if (Hospital::Patients[i].GetDoctorId() == doc.GetId() &&
                !DateIsEqual(Hospital::Patients[i].regisTime, date)) {
                return true;
            }
        }
    }
    return false;
}




int main() {

    setlocale(LC_ALL, "Russian");

    Hospital newHosp;
    // Создание доктора
    Profession doctorProfession = EnterProfession();
    //string doctorName = EnterName();
    /*cout << "\nВведите имя\n";
    cin >> doctorName;*/
    string doctorName = EnterName();
    Doctor doctor(doctorName, doctorProfession);
    doctor.PrintInfo();


    //// Создание пациента
    string patientName = EnterName();
    tm dateTime = EnterDateTime();
    Patient patient(patientName, doctor, dateTime);
    patient.AddRegisTime(dateTime);
    patient.PrintInfo();

    //// Добавление доктора и пациента в списки госпиталя
    newHosp.AddDoctorToList(doctor);
    newHosp.AddPatientToList(patient);

    //// Вывод информации о докторах и пациентах
    Hospital::PrintAllDoctors();
    Hospital::PrintAllPatients();
    return 0;
}
