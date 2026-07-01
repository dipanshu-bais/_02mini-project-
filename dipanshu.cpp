#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
using namespace std;
//  ANSI COLOR CODES
#define RST "\033[0m"
#define BOLD "\033[1m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YEL "\033[33m"
#define BLUE "\033[34m"
#define CYN "\033[36m"
#define WHT "\033[37m"
#define BBLUE "\033[44m"
#define BGRN "\033[42m"
#define BRED "\033[41m"
// UI HELPER FUNCTIONS
void clrscr()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
void drawLine(int len = 56)
{
    cout << CYN;
    for (int i = 0; i < len; i++)
        cout << "=";
    cout << RST << endl;
}
void drawThinLine(int len = 56)
{
    cout << BLUE;
    for (int i = 0; i < len; i++)
        cout << "-";
    cout << RST << endl;
}
void printTitle()
{
    clrscr();
    cout << CYN << BOLD << YEL << " SMART ATTENDANCE MANAGEMENT SYSTEM " << RST << CYN << "" << RST << endl;
    cout << endl;
}
void printSection(string title)
{
    clrscr();
    cout << CYN << BOLD << YEL << " SMART ATTENDANCE MANAGEMENT SYSTEM " << RST << CYN << RST << endl;
    // center the title
    int spaces = (52 - (int)title.size()) / 2;
    cout << CYN << BOLD << CYN;
    for (int i = 0; i < spaces; i++)
        cout << " ";
    cout << title;
    for (int i = 0; i < 52 - spaces - (int)title.size(); i++)
        cout << " ";
    cout << RST << CYN << RST << endl;
    cout << endl;
}
void msgSuccess(string msg)
{
    cout << endl
         << GREEN << BOLD << "  [OK] " << RST << GREEN << msg << RST << endl;
}
void msgError(string msg)
{
    cout << endl
         << RED << BOLD << "  [!!] " << RST << RED << msg << RST << endl;
}
void msgInfo(string msg)
{
    cout << CYN << "  [>>] " << RST << msg << endl;
}
void waitEnter()
{
    cout << endl
         << YEL << "  Press ENTER to go back to menu..." << RST;
    cin.ignore();
    cin.get();
}
//  ATTENDANCE CLASS
class Attendance
{
private:
    string studentName[100];
    int attendance[100];
    int totalStudents;
    int totalDays;

public:
    Attendance()
    {
        totalStudents = 0;
        totalDays = 0;
    }
    // 1. ADD STUDENTS
    void addStudents()
    {
        printSection("[ ADD STUDENTS ]");
        cout << YEL << "  Enter number of students: " << RST;
        cin >> totalStudents;
        cin.ignore();
        cout << endl;
        drawThinLine();
        for (int i = 0; i < totalStudents; i++)
        {
            cout << CYN << "  [" << i + 1 << "]" << RST << " Enter name: ";
            getline(cin, studentName[i]);
            attendance[i] = 0;
        }
        drawThinLine();
        msgSuccess(to_string(totalStudents) + " students added successfully!");
        waitEnter();
    }
    //  2. MARK ATTENDANCE
    void markAttendance()
    {
        printSection("[ MARK ATTENDANCE ]");
        if (totalStudents == 0)
        {
            msgError("No students found! Please add students first.");
            waitEnter();
            return;
        }
        totalDays++;
        cout << BOLD << YEL << "  Attendance for Day " << totalDays << RST << endl;
        cout << endl;
        drawThinLine();
        for (int i = 0; i < totalStudents; i++)
        {
            char status;
            cout << CYN << "  [" << setw(2) << i + 1 << "] " << RST
                 << left << setw(22) << studentName[i]
                 << YEL << "(P/A): " << RST;
            cin >> status;
            if (status == 'P' || status == 'p')
            {
                attendance[i]++;
                cout << GREEN << " Present" << RST << endl;
            }
            else
            {
                cout << RED << " Absent" << RST << endl;
            }
        }
        drawThinLine();
        msgSuccess("Day " + to_string(totalDays) + " attendance saved!");
        waitEnter();
    }
    //  3. ATTENDANCE REPORT
    void attendanceReport()
    {
        printSection("[ ATTENDANCE REPORT ]");
        if (totalStudents == 0)
        {
            msgError("No student data available!");
            waitEnter();
            return;
        }
        // Table header
        cout << BBLUE << WHT << BOLD
             << setw(5) << right << " No."
             << setw(22) << left << "  Name"
             << setw(10) << right << "Present"
             << setw(10) << right << "Absent"
             << setw(9) << right << "Days "
             << RST << endl;
        drawThinLine(56);
        for (int i = 0; i < totalStudents; i++)
        {
            int absent = totalDays - attendance[i];
            cout << CYN << setw(5) << right << i + 1
                 << RST << setw(22) << left << "  " + studentName[i]
                 << GREEN << setw(10) << right << attendance[i]
                 << RED << setw(10) << right << absent
                 << WHT << setw(9) << right << totalDays
                 << RST << endl;
        }
        drawThinLine(56);
        cout << endl;
        msgInfo("Total days recorded: " + to_string(totalDays));
        msgInfo("Total students     : " + to_string(totalStudents));
        waitEnter();
    }
    //  4. ATTENDANCE PERCENTAG
    void attendancePercentage()
    {
        printSection("[ ATTENDANCE PERCENTAGE ]");
        if (totalStudents == 0 || totalDays == 0)
        {
            msgError("No attendance data available!");
            waitEnter();
            return;
        }
        // Table header
        cout << BBLUE << WHT << BOLD
             << setw(5) << " No."
             << setw(22) << "  Name"
             << setw(12) << "Percentage"
             << setw(14) << "  Status  "
             << RST << endl;
        drawThinLine(53);
        int eligible = 0;
        for (int i = 0; i < totalStudents; i++)
        {
            double pct = (attendance[i] * 100.0) / totalDays;
            cout << CYN << setw(5) << right << i + 1
                 << RST << setw(22) << left << "  " + studentName[i];
            if (pct >= 75)
            {
                cout << GREEN << BOLD
                     << setw(11) << right << fixed << setprecision(1) << pct << "%"
                     << setw(14) << right << "  ELIGIBLE "
                     << RST;
                eligible++;
            }
            else if (pct >= 50)
            {
                cout << YEL << BOLD
                     << setw(11) << right << fixed << setprecision(1) << pct << "%"
                     << setw(14) << right << "  WARNING  "
                     << RST;
            }
            else
            {
                cout << RED << BOLD
                     << setw(11) << right << fixed << setprecision(1) << pct << "%"
                     << setw(14) << right << "  SHORT    "
                     << RST;
            }
            cout << endl;
        }
        drawThinLine(53);
        cout << endl;
        cout << GREEN << BOLD << "  Eligible  : " << RST << GREEN << eligible << RST << endl;
        cout << RED << BOLD << "  Short Att : " << RST << RED << (totalStudents - eligible) << RST << endl;
        waitEnter();
    }
};
// MAIN MENU + MAIN FUNCTION
void showMenu()
{
    cout << CYN << BOLD << YEL << " MAIN  MENU " << RST << CYN << RST << endl;
    cout << CYN << GREEN << "1." << RST << "  Add Students" << CYN << RST << endl;
    cout << CYN << GREEN << "2." << RST << "  Mark Attendance" << CYN << RST << endl;
    cout << CYN << GREEN << "3." << RST << "  Attendance Report" << CYN << RST << endl;
    cout << CYN << GREEN << "4." << RST << "  Attendance Percentage " << CYN << RST << endl;
    cout << CYN << RED << "5." << RST << "  Exit " << CYN << RST << endl;
    cout << endl;
    cout << YEL << "  Enter your choice (1-5): " << RST;
}
int main()
{
    Attendance obj;
    int choice;
    do
    {
        printTitle();
        showMenu();
        cin >> choice;
        switch (choice)
        {
        case 1:
            obj.addStudents();
            break;
        case 2:
            obj.markAttendance();
            break;
        case 3:
            obj.attendanceReport();
            break;
        case 4:
            obj.attendancePercentage();
            break;
        case 5:
            clrscr();
            cout << endl;
            cout << CYN << GREEN << BOLD << "Thank you :)" << RST << CYN << RST << endl;
            cout << endl;
            break;
        default:
            msgError("Invalid choice! Please enter between 1 and 5.");
            cout << endl
                 << YEL << "  Press ENTER to try again" << RST;
            cin.ignore();
            cin.get();
        }
    } while (choice != 5);
    return 0;
}