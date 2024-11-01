/* 
Pouya Rahimpour
CE isfahan university
Project: School Management System
*/

// The School can delete data in files every year and use this ststem again
// Things to know when reading source code:
// 1. there are three main rolls in this program including boss, teacher, and student
// 2. to make the program cleaner more adaptable some useful structures and their funcionalities are defined in form of stuctures like: Class, Exam, and Score 
// 3. name of about all identifiers is related to their functionality to make it more comprehensible
// 4. the approach in this program was to write most of the functionalities from scratch, so some stuctures are defined to satisfy this like: Time
// 5. each student, teacher, and class has a unique number but exams and scores inherit thier number from the class in which they're defined, so: class num == exam num == score num
// 6. as this program stores date in files it's hard to avoid wrong data caused by human mistake when entering information, though this programs tries not to let people from entering wrong data in a lot of cases
// 7. bosses default username is "chandler bing" and difault password is "sickPassword"

// headerfiles
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <ctime>
using namespace std;

// global variables
const string universityPass = "university of c++"; // this is used when a new student is going to create an account for higher security
int studentCount = 0, teacherCount = 0, classCount = 0, examCount = 0, scoreCount = 0;

// stuctures
struct Boss {
    const string fname = "chandler";
    const string lname = "bing";
    const string password = "sickPassword";
    string fullName() {
        string str = fname + " " + lname;
        return str;
    }
} bs;

struct Student {
    string fname;
    string lname;
    string password;
    int num;
    void move_to_file() {
        fstream members;
        members.open("studentsList.txt", ios::app);
        if (members.is_open()) {
            members << num << '&' << password << '&' << fname << '&' << lname << '&' << endl;
        } else {
            cout << "An error accurred while openning files!" << endl;
        }
        members.close();
    }
    void print_info() {
        cout << "full name: " << fname << " " << lname << endl
            << "student's number: " << num << endl;
        for (int i=0; i<100; i++) cout << '=';
        cout << endl;
    }
    string fullName() {
        string fullName = fname + " " + lname;
        return  fullName;
    }
} stu;

struct Teacher {
    string fname;
    string lname;
    string password;
    int num;
    void move_to_file() {
        fstream members;
        members.open("teachersList.txt", ios::app);
        if (members.is_open()) {
            members << num << '&' << password << '&' << fname << '&' << lname << '&' << endl;
        } else {
            cout << "An error accurred while openning files!" << endl;
        }
        members.close();
    }
    void print_info() {
        cout << "full name: " << fname << " " << lname << endl
            << "teacher's number: " << num << endl;
        for (int i=0; i<100; i++) cout << '=';
        cout << endl;
    }
    string fullName() {
        string fullName = fname + " " + lname;
        return  fullName;
    }
} tchr;

struct Class {
    string name;
    string teacher;
    string password;
    int num;
    void move_to_file() {
        fstream classes;
        classes.open("classesList.txt", ios::app);
        if (classes.is_open()) {
            classes << num << '&' << password << '&' << name << '&' << teacher << '&' << endl;
        } else {
            cout << "An error accurred while openning files!" << endl;
        }
        classes.close();
    }
    void print_info() {
        cout << "class name: " << name << endl
            << "class's teacher: " << teacher << endl
            << "class number: " << num << endl;
        for (int i=0; i<100; i++) cout << '=';
        cout << endl;
    }
} cls;

struct Time {
    int month;
    int day;
    int hour;
    int minute;
    int second;
    void print_info() {
        cout << day << "/" << month << "\t"<< hour << ":" << minute << ":" << second << endl;
    }
} curr_time;

// these three functions are requiered for Exam structure
Time time_end_make(Time time_start, int durationMinutes);
int time_compare(Time time1, Time time2);
string current_time(Time& tim);
struct Exam {
    int num;
    Time time;
    int duration;
    string questions[100];
    int answers[100];
    int questionsCount;

    void get_time() {
        int month, day, hour, min, second;
        
        cout << "enter the month (in number): ";
        cin >> month;
        while (month<0 || month>12) {
            cout << "wrong input.try again: ";
            cin >> month;
        } 
        time.month = month;

        cout << "enter the day: ";
        cin >> day;
        while (day<0 || day>32) {
            cout << "wrong input.try again: "; 
            cin >> day;
        }
        time.day = day;

        cout << "enter the hour(24 hour with no am or pm): ";
        cin >> hour;
        while (hour<0 || hour>23) {
            cout << "wrong input.try again: "; 
            cin >> hour;
        }
        time.hour = hour;

        cout << "enter the minute: ";
        cin >> min;
        while (min<0 || min>59) {
            cout << "wrong input.try again: "; 
            cin >> min;
        }
        time.minute = min;

        cout << "enter the second: ";
        cin >> second;
        while (second<0 || second>59) {
            cout << "wrong input.try again: ";
            cin >> second;
        }
        time.second = second;

        cout << "how much is the time for the exam (how many minutes): ";
        cin >> duration;
    }
    void enter_questions() {
        int num;
        cout << "enter the number of questions: ";
        cin >> num;
        questionsCount = num;
        for (int i = 0; i < num; i++) {
            cout << "enter questoin " << i+1 << " please: ";
            cin.ignore();
            getline(cin, questions[i]);
            cout << "enter the answer of this question (1, 2, 3 or 4): ";
            cin >> answers[i];
        }
    }
    void move_to_file() {
        fstream exam;
        exam.open("examsList.txt", ios::app);
        if (exam.is_open()) {
            exam << "***" << endl
                << num << endl
                << time.day << "/" << time.month << "-" << time.hour << ":" << time.minute << ":" << time.second << "-" << duration << "-" << questionsCount  << "." << endl;
            int i = 0;
            while (questions[i] != "") {
                exam << questions[i] << "*" << answers[i] << endl;
                i++;
            }
            exam << "END" << endl;
            exam.close();
        } else cout << "An error accurred while openning files!" << endl;
    }
    void print_info() {
        cout << "exam date: " << time.day << "/" << time.month << endl
            << "exam starts at: " << time.hour << ":" << time.minute << ":" << time.second << endl
            << "exam time: " << duration << " minutes." << endl
            << "number of questions: " << questionsCount << endl;
        //exam's status based on current time
        cout << "exam status: ";
        Time time_end = time_end_make(time, duration);
        current_time(curr_time);
        if ((time_compare(time, curr_time) <= 0) && (time_compare(time_end, curr_time) > 0)) cout << "exam is being held" << endl;
        else if (time_compare(time_end, curr_time) <= 0) cout << "exam is finished" << endl;
        else if (time_compare(time, curr_time) > 0) cout << "exam hasn't started yet." << endl;
        for (int i=0; i<100; i++) cout << '=';
        cout << endl;
    }
} ex;

// these two functions are required for Score structure
Student student_search(int number);
Class class_search(int number);
struct Score {
    int examNum;
    int studentNum;
    int score;
    Time time;
    void move_to_file() {
        fstream scores;
        scores.open("scoresList.txt", ios::app);
        if (scores.is_open()) {
            scores << examNum << '&' << studentNum << '&' << score << '&' 
                << time.day << "/" << time.month << '&' << endl;
        } else {
            cout << "An error accurred while openning files!" << endl;
        }
        scores.close();
    }
    void print_info() {
        cout << "code of exam (code of class): " << examNum << endl
            << "date of exam: " << time.day << "/" << time.month << endl
            << "name of class: " << class_search(examNum).name << endl
            << "student name: " << student_search(studentNum).fullName() << endl
            << "student number: " << student_search(studentNum).num << endl
            << "student's score: " << score << endl;
        for (int i=0; i<100; i++) cout << '=';
        cout << endl;
    }
} scr;

// arrays that store informations from files when program starts
Student studentsArr[10000];
Teacher teachersArr[10000];
Class classesArr[1000];
Exam examsArr[10000];
Score scoresArr[100000];

// practical functions
Time time_end_make(Time time_start, int durationMinutes) {
    Time time_end;
    time_end.second = time_start.second;
    time_end.minute = time_start.minute + durationMinutes;
    time_end.hour = time_start.hour;
    time_end.day = time_start.day;
    time_end.month = time_start.month;
    while (time_end.minute > 59) {
        time_end.minute -= 60;
        time_end.hour++;
    }
    while (time_end.hour > 23) {
        time_end.hour -= 24;
        time_end.day++;
    }
    return time_end;
}
int time_compare(Time time1, Time time2) {
    if (time1.month > time2.month) return 1;
    else if (time1.month < time2.month) return -1;
    else if (time1.day > time2.day) return 1;
    else if (time1.day < time2.day) return -1;
    else if (time1.hour > time2.hour) return 1;
    else if (time1.hour < time2.hour) return -1;
    else if (time1.minute > time2.minute) return 1;
    else if (time1.minute < time2.minute) return -1;
    else if (time1.second > time2.second) return 1;
    else if (time1.second < time2.second) return -1;
    else return 0;
}
string current_time(Time& tim) {
    string timestr;
    time_t curr_time;
    time(&curr_time);
    timestr = ctime(&curr_time);
    tm* ptr = localtime(&curr_time);
    tim.hour = ptr->tm_hour;
    tim.second = ptr->tm_sec;
    tim.minute = ptr->tm_min;
    tim.day = ptr->tm_mday;
    tim.month = ptr->tm_mon+1;
    return timestr;
}
int to_int(string str) {
    int number = 0;
    // check if number is negative or not
    if (str[0] != '-') {
        for (int i=0; i<str.length(); i++) {
            number = 10*number + (str[i]-'0');
        }
    } else {
        for (int i=1; i<str.length(); i++) {
            number = 10*number + (str[i]-'0');
        }
        number *= -1;
    }
    return number;
}
int students_array_make() {
    int count = 0;
    fstream members;
    members.open("studentsList.txt", ios::in);
    if (members.is_open()) {
        string fname, lname, password, num, temp;
        while (getline(members, temp)) {
            int i = 0;
            
            // num
            num = "";
            while (temp[i] != '&') {
                num.push_back(temp[i]);
                i++;
            }
            i++;
            stu.num = to_int(num);
            
            // password
            password = "";
            while (temp[i] != '&') {
                password.push_back(temp[i]);
                i++;
            }
            i++;
            stu.password = password;
            
            // first name
            fname = "";
            while (temp[i] != '&') {
                fname.push_back(temp[i]);
                i++;
            }
            i++;
            stu.fname = fname;
            
            // last name
            lname = "";
            while (temp[i] != '&') {
                lname.push_back(temp[i]);
                i++;
            }
            i++;
            stu.lname = lname;
            
            studentsArr[count] = stu;
            count++;
        }
        members.close();

        // sort based on student number using insertion sort
        for (int j = 1; j < count; j++) {
            Student temp = studentsArr[j];
            int i = j-1;
            while (i>=0 && studentsArr[i].num > temp.num) {
                studentsArr[i+1] = studentsArr[i];
                i--;
            }
            studentsArr[i+1] = temp;
        }
    } else cout << "An error accurred while openning files!" << endl;
    return count;
}
int teachers_array_make() {
    int count = 0;
    fstream members;
    members.open("teachersList.txt", ios::in);
    if (members.is_open()) {
        string fname, lname, password, num, temp;
        while (getline(members, temp)) {
            int i = 0;
            
            // num
            num = "";
            while (temp[i] != '&') {
                num.push_back(temp[i]);
                i++;
            }
            i++;
            tchr.num = to_int(num);
            
            // password
            password = "";
            while (temp[i] != '&') {
                password.push_back(temp[i]);
                i++;
            }
            i++;
            tchr.password = password;
            
            // first name
            fname = "";
            while (temp[i] != '&') {
                fname.push_back(temp[i]);
                i++;
            }
            i++;
            tchr.fname = fname;
            
            // last name
            lname = "";
            while (temp[i] != '&') {
                lname.push_back(temp[i]);
                i++;
            }
            i++;
            tchr.lname = lname;
            
            teachersArr[count] = tchr;
            count++;
        }
        members.close();
        
        // sort based on student number using insertion sort
        for (int j = 1; j < count; j++) {
            Teacher temp = teachersArr[j];
            int i = j-1;
            while (i>=0 && teachersArr[i].num > temp.num) {
                teachersArr[i+1] = teachersArr[i];
                i--;
            }
            teachersArr[i+1] = temp;
        }
    } else cout << "An error accurred while openning files!" << endl;
    return count;
}
int classes_array_make() {
    int count = 0;
    fstream classes;
    classes.open("classesList.txt", ios::in);
    if (classes.is_open()) {
        string name, password, num, teacher, temp;
        while (getline(classes, temp)) {
            int i = 0;
            
            // num
            num = "";
            while (temp[i] != '&') {
                num.push_back(temp[i]);
                i++;
            }
            i++;
            cls.num = to_int(num);
            
            // password
            password = "";
            while (temp[i] != '&') {
                password.push_back(temp[i]);
                i++;
            }
            i++;
            cls.password = password;
            
            // name
            name = "";
            while (temp[i] != '&') {
                name.push_back(temp[i]);
                i++;
            }
            i++;
            cls.name = name;
            
            // teacher
            teacher = "";
            while (temp[i] != '&') {
                teacher.push_back(temp[i]);
                i++;
            }
            i++;
            cls.teacher = teacher;
            
            classesArr[count] = cls;
            count++;
        }
        classes.close();
        
        // sort based on student number using insertion sort
        for (int j = 1; j < count; j++) {
            Class temp = classesArr[j];
            int i = j-1;
            while (i>=0 && classesArr[i].num > temp.num) {
                classesArr[i+1] = classesArr[i];
                i--;
            }
            classesArr[i+1] = temp;
        }
    } else cout << "An error accurred while openning files!" << endl;
    return count;
}
int exams_array_make() {
    int count = 0;
    fstream exams;
    exams.open("examsList.txt", ios::in);
    if (exams.is_open()) {
        string temp;
        while (true) {
            getline(exams, temp);
            if (temp == "***") {
                // getting exam number which is the same as class number
                string num;
                getline(exams, num);
                ex.num = to_int(num);
                
                // getting time
                getline(exams, temp);
                string month, day, hour, min, second, duration, questionsCount;
                
                // day
                int i = 0;
                day = "";
                while (temp[i] != '/') {
                    day.push_back(temp[i]);
                    i++;
                }
                i++;
                ex.time.day = to_int(day);
                
                // month
                month = "";
                while (temp[i] != '-') {
                    month.push_back(temp[i]);
                    i++;
                }
                i++;
                ex.time.month = to_int(month);
                
                // hour
                hour = "";
                while (temp[i] != ':') {
                    hour.push_back(temp[i]);
                    i++;
                }
                i++;
                ex.time.hour = to_int(hour);
                
                // minute
                min = "";
                while (temp[i] != ':') {
                    min.push_back(temp[i]);
                    i++;
                }
                i++;
                ex.time.minute = to_int(min);
                
                // second
                second = "";
                while (temp[i] != '-') {
                    second.push_back(temp[i]);
                    i++;
                }
                i++;
                ex.time.second = to_int(second);
                
                // duration
                while (temp[i] != '-') {
                    duration.push_back(temp[i]);
                    i++;
                }
                i++;
                ex.duration = to_int(duration);
                
                // number of questions
                while (temp[i] != '.') {
                    questionsCount.push_back(temp[i]);
                    i++;
                }
                i++;
                ex.questionsCount = to_int(questionsCount);
                
                // questions
                getline(exams, temp);
                int qcount = 1;
                while (temp != "END") {
                    int j = 0;
                    string question = "", answer = "";
                    while (temp[j] != '*') {
                        question.push_back(temp[j]);
                        j++;
                    }
                    j++;
                    answer.push_back(temp[j]);
                    ex.questions[qcount-1] = question;
                    ex.answers[qcount-1] = to_int(answer);
                    qcount++;
                    getline(exams, temp);
                }
                examsArr[count] = ex;
                count++;
            }
            else if (temp == "") break;
        }
        exams.close();
        // sort based on student number using insertion sort
        for (int j = 1; j < count; j++) {
            Exam temp = examsArr[j];
            int i = j-1;
            while (i>=0 && examsArr[i].num > temp.num) {
                examsArr[i+1] = examsArr[i];
                i--;
            }
            examsArr[i+1] = temp;
        }
    } else cout << "An error accurred while openning files!" << endl;
    return count;
}
int score_array_make() {
    int count = 0;
    fstream scores;
    scores.open("scoresList.txt", ios::in);
    if (scores.is_open()) {
        string examNum, studentNum, score, day, month, temp;
        while (getline(scores, temp)) {
            int i = 0;
            // examNum
            examNum = "";
            while (temp[i] != '&') {
                examNum.push_back(temp[i]);
                i++;
            }
            i++;
            scr.examNum = to_int(examNum);
            
             // studentNum
            studentNum = "";
            while (temp[i] != '&') {
                studentNum.push_back(temp[i]);
                i++;
            }
            i++;
            scr.studentNum = to_int(studentNum);
            
            // score
            score = "";
            while (temp[i] != '&') {
                score.push_back(temp[i]);
                i++;
            }
            i++;
            scr.score = to_int(score);

            // date
            day = "";
            while (temp[i] != '/') {
                day.push_back(temp[i]);
                i++;
            }
            i++;
            scr.time.day = to_int(day);

            month = "";
            while (temp[i] != '&') {
                month.push_back(temp[i]);
                i++;
            }
            i++;
            scr.time.month = to_int(month);
            
            
            scoresArr[count] = scr;
            count++;
        }
        scores.close();
        
        // sort based on number using insertion sort
        for (int j = 1; j < count; j++) {
            Score temp = scoresArr[j];
            int i = j-1;
            while (i>=0 && scoresArr[i].examNum > temp.examNum) {
                scoresArr[i+1] = scoresArr[i];
                i--;
            }
            scoresArr[i+1] = temp;
        }
    } else cout << "An error accurred while openning files!" << endl;
    return count;
}
Student student_search(int number) {
    // binary search
    int p1=0, p2=studentCount-1;
    stu.num = 0;
    while (p1 <= p2) {
        int mid = (p1+p2)/2;
        if (studentsArr[mid].num > number) p2 = mid-1;
        if (studentsArr[mid].num < number) p1 = mid+1;
        if (studentsArr[mid].num == number) {
            stu = studentsArr[mid];
            break;
        }
    }
    return stu;
}
Teacher teacher_search(int number) {
    // binary search
    int p1=0, p2=teacherCount-1;
    tchr.num = 0;
    while (p1 <= p2) {
        int mid = (p1+p2)/2;
        if (teachersArr[mid].num > number) p2 = mid-1;
        if (teachersArr[mid].num < number) p1 = mid+1;
        if (teachersArr[mid].num == number) {
            tchr = teachersArr[mid];
            break;
        }
    }
    return tchr;
}
Class class_search(int number) {
   // binary search
    int p1=0, p2=classCount-1;
    cls.num = 0;
    while (p1 <= p2) {
        int mid = (p1+p2)/2;
        if (classesArr[mid].num > number) p2 = mid-1;
        if (classesArr[mid].num < number) p1 = mid+1;
        if (classesArr[mid].num == number) {
            cls = classesArr[mid];
            break;
        }
    }
    return cls;
} 

void page_wellcome();
void page_create_account();
void page_sign_in();
void page_personal_boss(Boss);
void page_create_new_class(Teacher);
void page_personal_student(Student stu);

void page_create_exam(Class cls) {
    // page cover
    for (int i = 0; i<43; i++) cout << '=';
    cout << "EXAM CREATION";
    for (int i = 0; i<43; i++) cout << '=';
    cout << endl << current_time(curr_time) << endl;
    // teacher should set a date and time for exam
    ex.get_time();
    // teacher enters questions of this exam
    ex.enter_questions();
    // setting the exam number equal to class number
    ex.num = cls.num;
    // completing the process of making an exam by storing it into file
    ex.move_to_file();
    examCount = exams_array_make();
    cout << "exam successfully created. press Enter to continue"<< endl;
    cin.ignore();
    cin.get();
    system("cls");
}

void page_participate_exam(Student stu, Exam exm) {
    // page cover
    for (int i = 0; i<45; i++) cout << '=';
    cout << "EXAM PAGE";
    for (int i = 0; i<45; i++) cout << '=';
    cout << endl << current_time(curr_time) << endl;
    // 
    bool participated = false;
    for (int i = 0; i < scoreCount; i++) {
        if (scoresArr[i].studentNum == stu.num && scoresArr[i].time.month == exm.time.month && scoresArr[i].time.day == exm.time.day && ex.num == scoresArr[i].examNum) {
            participated = true;
        }
    }
    if (!participated) {
        Time time_end = time_end_make(exm.time, exm.duration);
        exm.print_info();
        current_time(curr_time);
        if ((time_compare(exm.time, curr_time) <= 0) && (time_compare(time_end, curr_time) > 0)) {
            cout << "Good luck!" << endl;
            Sleep(1*1000);
            system("cls");
            
            // questioins
            int questionsAnswered = 0, temp;
            int ansArr[100];
            while(true) {
                if (questionsAnswered >= exm.questionsCount) break;
                current_time(curr_time);
                if (time_compare(curr_time, time_end) > 0) break;
                cout << "Question " << questionsAnswered+1 << ": " << endl
                    << exm.questions[questionsAnswered] << endl
                    << "your answer: ";
                cin >> temp;
                current_time(curr_time);
                if (time_compare(curr_time, time_end) > 0) {
                    cin.ignore();
                    break;
                } else {
                    ansArr[questionsAnswered++] = temp;
                    cout << endl;
                } 
            }
            int rightAnswers = 0;
            for (int j = 0; j < questionsAnswered; j++) {
                if (ansArr[j] == exm.answers[j]) rightAnswers++;
            }
            int whiteAnswers = exm.questionsCount-questionsAnswered;
            int wrongAnswers = exm.questionsCount-whiteAnswers-rightAnswers;
            int score = (3*rightAnswers-wrongAnswers)*100/(3*exm.questionsCount);// wrong answers have negative 1/3 negetive point
            scr.examNum = exm.num;
            scr.studentNum = stu.num;
            scr.score = score;
            scr.time.day = exm.time.day;
            scr.time.month = exm.time.month;
            scr.move_to_file();
            scoreCount = score_array_make();

            cout << endl << "exam time is over." << endl << endl
                << "right answers: " << rightAnswers << endl
                << "wrong answers: "  << wrongAnswers << endl
                << "white answers: " << whiteAnswers << endl
                << "Your score is " << score << " from 100 ." << endl << endl
                << "Press Enter to continue." << endl;
                cin.ignore();
                cin.get();
                system("cls");
                page_personal_student(stu);
        }
        else if (time_compare(time_end, curr_time) <= 0) {
            cout << "exam time is over." << endl
                << "press Enter to continue." << endl;
            cin.ignore();
            cin.get();
            system("cls");
            page_personal_student(stu);
        }
        else if (time_compare(exm.time, curr_time) > 0) {
            cout << "exam hasn't started yet." << endl
                << "press Enter to continue." << endl;
            cin.ignore();
            cin.get();
            system("cls");
            page_personal_student(stu);
        }
    } else {
        cout << "Sorry! you have patricipated in this exam before and can't participate again." << endl
            << "press Enter to continue." << endl;
        cin.ignore();
        cin.get();
        system("cls");
        page_personal_student(stu);
    }
}

void page_personal_student(Student stu) {
    // page cover
    for (int i = 0; i<43; i++) cout << '=';
    cout << "PERSONAL PAGE";
    for (int i = 0; i<43; i++) cout << '=';
    cout << endl << current_time(curr_time);
    cout << endl << "Wellcome to you page " << stu.fname << " " << stu.lname << " !" << endl;
    //options
    cout << "Here's a complete list of tasks you can perform." << endl << endl
        << "1. search for a class and participate in an exam." << endl
        << "2. list of your scores in a class." << endl
        << "3. list of all your scores." << endl
        << "or enter any other number to log out." << endl << endl
        << "Please enter the number: ";
    int choice, i, num, month, day;
    char chr;
    bool found = false;
    cin >> choice;
    switch (choice) {
    case 1:
        system("cls");
        cout << "Please enter class number: ";
        cin >> num;
        for (i = 0; i < classCount; i++) {
            if (classesArr[i].num == num) {
                classesArr[i].print_info();
            }
        }
        for (i = 0; i < examCount; i++) {
            if (examsArr[i].num == num) {
                cout << "---------------------> " << "EXAM" << " <---------------------" << endl;
                examsArr[i].print_info();
                found = true;
            }
        }
        if (found) {

            cout << "Do you want to participate in an exam? (y or n): ";
            cin >> chr;
            if (chr == 'Y' || chr == 'y') {
                cout << "if your're sure about entering an exam please enter the date of exam: "<< endl
                    << "(you can only participate once so if you want to get back set the date to 0/0)" << endl
                    << "day: ";
                    cin >> day;
                    cout << "month: ";
                    cin >> month;
                    for (i = 0; i < examCount; i++) {
                        if ((examsArr[i].time.month == month) && (examsArr[i].time.day == day) && (examsArr[i].num == num)) {
                            cout << "*moving you to exam page*" << endl;
                            Sleep(2*1000);
                            system("cls");
                            page_participate_exam(stu, examsArr[i]);
                        }
                    }
                    cout << "wrong date!" << endl
                        << "press Enter to continue." << endl;
                    cin.ignore();
                    cin.get();
                    system("cls");
                    page_personal_student(stu);
            } else {
                cout << "press Enter to continue." << endl;
                cin.ignore();
                cin.get();
                system("cls");
                page_personal_student(stu);
            }
        } else {
            cout << "no exams for this class found!" << endl
                <<"press Enter to continue.";
            cin.ignore();
            cin.get();
            system("cls");
            page_personal_student(stu);
        }
        break;
    
    case 2:
        system("cls");
        cout << "Please enter the class number: ";
        cin >> num;
        for (i = 0; i < scoreCount; i++) {
            if (scoresArr[i].examNum == num && scoresArr[i].studentNum == stu.num) {
                scoresArr[i].print_info();
            }
        }
        cout << "Press Enter to continue."<< endl;
        cin.ignore();
        cin.get();
        system("cls");
        page_personal_student(stu);
        break;
    
    case 3:
        system("cls");
        for (i = 0; i < scoreCount; i++) {
            if (scoresArr[i].studentNum == stu.num) {
                scoresArr[i].print_info();
            }
        }
        cout << "Press Enter to continue."<< endl;
        cin.ignore();
        cin.get();
        system("cls");
        page_personal_student(stu);
        break;

    default:
        system("cls");
        page_sign_in();
    }
}

void page_personal_teacher(Teacher tchr) {
    // page cover
    for (int i = 0; i<43; i++) cout << '=';
    cout << "PERSONAL PAGE";
    for (int i = 0; i<43; i++) cout << '=';
    cout << endl << current_time(curr_time);
    cout << "Wellcome to you page " << tchr.fname << " " << tchr.lname << " !" << endl;
    
    // options
    cout << "Here's a complete list of tasks you can perform." << endl << endl
        << "1. create a new class." << endl
        << "2. list of your classes, define exams, and view hold exams." << endl
        << "3. view students' scores in your classes." << endl
        << "or enter any other number to log out." << endl << endl
        << "Please enter the number: ";
    int choise, choise1, num, i;
    cin >> choise;
    switch (choise) {
    case 1:
        system("cls");
        page_create_new_class(tchr);
        break;
    case 2:
        system("cls");
        for (i = 0; i < classCount; i++) {
            if (classesArr[i].teacher == tchr.fullName()) {
                classesArr[i].print_info();
                cout << endl;
            }
        }
        cout << "1. define exam for a class." << endl
            << "2. view exams defined for a class." << endl
            << "or enter any other number to get back." << endl;
        cin >> choise1;
        switch (choise1) {
        case 1:
            cout << endl <<"Please enter class number: ";
            cin >> num;
            cls = class_search(num);
            while (class_search(num).teacher != tchr.fullName() || class_search(num).num == 0) {
                cout << "The number you've entered is not correct. Please try again: " << endl
                    << "or enter 0 to get back to your page." << endl;
                cin >> num;
                if (num == 0) {
                    system("cls");
                    page_personal_teacher(tchr);
                }
            }
            system("cls");
            page_create_exam(cls);
            page_personal_teacher(tchr);
            break;
        
        case 2:
            cout << endl << "Please enter class number: ";
            cin.ignore();
            cin >> num;
            for (i = 0; i < examCount; i++) {
                if (examsArr[i].num == num) {
                    examsArr[i].print_info();
                }
            }
            cout << endl << "Press Enter to continue." << endl;
            cin.ignore();
            cin.get();
            system("cls");
            page_personal_teacher(tchr);
            break;
        
        default:
            system("cls");
            page_personal_teacher(tchr);
        }
        break;
    
    case 3:
        cout << endl << "Please enter class number: " << endl;
        cin >> num;
        for (i = 0; i < scoreCount; i++) {
            if (scoresArr[i].examNum == num) {
                scoresArr[i].print_info();
            }
        }
        cout << endl << "Press Enter to continue." << endl;
        cin.ignore();
        cin.get();
        system("cls");
        page_personal_teacher(tchr);
        break;
    
    default:
        system("cls");
        page_sign_in();
    }

}

void page_create_new_class(Teacher tchr) {
    // page cover
    for (int i = 0; i<40; i++) cout << '=';
    cout << "CREATING NEW CLASS";
    for (int i = 0; i<41; i++) cout << '=';
    cout << endl;
    
    // teacher should set a name for class
    cout << "Please enter the class name: ";
    cin.ignore();
    string name;
    getline(cin, name);
    
    // teacher should set a password for class
    string password;
    cout << "Please choose a password (space and & are not allowed): ";
    getline(cin, password);
    bool validPassword = true;
    for (int i = 0; i<password.length(); i++) {
        if (isspace(password[i]) || password[i] == '&') validPassword = false;
    }
    while (!validPassword) {
        cout << "The password you've chosen is not valid (contains space or &).Try again: ";
        getline(cin, password);
        validPassword = true;
        for (int i = 0; i<password.length(); i++) {
            if (isspace(password[i]) || password[i] == '&') validPassword = false;
        }
    }
    // teacher should set a 7 digit number for the class
    cout << "Please set a 7 digit number for this class: ";
    int num;
    cin >> num;
    while ((num > 9999999 )|| (num < 1000000) || (class_search(num).num != 0)) {
        cout << "The number you've entered is not correct or already exists. Please try again: ";
        cin >> num;
    }

    // process of creating a new class
    cls.name = name;
    cls.num = num;
    cls.password = password;
    cls.teacher = tchr.fullName();
    cls.move_to_file();
    classCount = classes_array_make();
    
    // end of process
    cout << "Creating your new class is successfully done!" << endl
        << "Announce class's number to your stuents, so they can join." << endl
        << "Press Enter to continue." << endl;
    cin.ignore();
    cin.get();
    system("cls");
    page_personal_teacher(tchr);
}

void page_create_new_teacher() {
    // boss enters first and last name
    string fname;
    cout << "Enter teacher's FIRST name: ";
    cin.ignore();
    getline(cin, fname);
    cout << "Enter teacher's LAST name: " ;
    string lname;
    getline(cin, lname);

    // boos must choose a password for that teacher
    string password;
    cout << "Please choose a password (space and & are not allowed): ";
    getline(cin, password);
    bool validPassword = true;
    for (int i = 0; i<password.length(); i++) {
        if (isspace(password[i]) || password[i] == '&') validPassword = false;
    }
    while (!validPassword) {
        cout << "The password you've chosen is not valid (contains space or &).Try again: ";
        getline(cin, password);
        validPassword = true;
        for (int i = 0; i<password.length(); i++) {
            if (isspace(password[i]) || password[i] == '&') validPassword = false;
        }
    }
    int teacherNum;
    cout << "Please enter the teacher number (7 digits): " ;
    cin >> teacherNum;
    // if teacher number is not in range or number already exists the boss should try again
    while ((teacherNum > 9999999) || (teacherNum < 1000000) || (teacher_search(teacherNum).num != 0)) {
        cout << "The number you've entered is not correct or already exists. Please try again " << endl
            << "(enter 0 if you want to get back to wellcome page): ";
        int choise;
        cin >> choise;
        if (choise == 0) {
            system("cls");
            page_wellcome();
        } else teacherNum = choise; 
    }
    // process of making a new teacher
    tchr.fname = fname;
    tchr.lname = lname;
    tchr.password = password;
    tchr.num = teacherNum;
    tchr.move_to_file();
    teacherCount = teachers_array_make();
    // end of process
    cout << "Creating teacher's account finished successfully" << endl
         << "The username and the teacher number is: \""<< tchr.num <<"\".And the password is \"" << tchr.password << "\" .Keep is safe." << endl
         << "Press Enter to get back to boss's page.";
    cin.ignore();
    cin.get();
    system("cls");
    page_personal_boss(bs);
}

void page_personal_boss(Boss bs) {
    // page cover
    for (int i = 0; i<43; i++) cout << '=';
    cout << "PERSONAL PAGE";
    for (int i = 0; i<43; i++) cout << '=';
    cout << endl<< current_time(curr_time);
    cout << "Wellcome to you page " << bs.fname << " " << bs.lname << " !" << endl;
    // options
    cout << "Here's a complete list of tasks you can perform." << endl << endl
        << "1. student options.(student numbers, names and scores)" << endl
        << "2. teacher options.(teachers' classes, names and numbers)" << endl
        << "3. class options.(exams and scores in classes)" << endl
        << "or enter any other number to log out." << endl << endl
        << "Please enter the number: ";
    int choise, choise1, i, num;
    cin >> choise;
    switch (choise) {
    case 1:
        cout << endl << "1. view all students sorted by student number.(without scores)" << endl
            << "2. search for a specific student using student number. (with scores)" << endl
            << "or enter any other number to go back." << endl;     
        cin >> choise1;
        switch (choise1) {
        case 1:
            for (i = 0; i < studentCount; i++) {
                studentsArr[i].print_info();
            }
            cout << "press Enter to continue." << endl;
            cin.ignore();
            cin.get();
            system("cls");
            page_personal_boss(bs);
            break;
        
        case 2:
            cout << "enter the student number: ";
            cin >> num;
            stu = student_search(num);
            if (stu.num != 0) {
                stu.print_info();
                for (i = 0; i < scoreCount; i++) {
                    if (scoresArr[i].studentNum == num) {
                        scoresArr[i].print_info();
                    }
                }
            } else cout << "student not found!." << endl;
            cout << "press Enter to continue." << endl;
            cin.ignore();
            cin.get();
            system("cls");
            page_personal_boss(bs);
            break;
        
        default:
            system("cls");
            page_personal_boss(bs);

        }
        break;
    
    case 2:
        cout << endl << "1. view all teachers sorted by teacher number. (no view of classes)" << endl
            << "2. search for a specific teacher using teacher number. (with view of classes)" << endl
            << "3. sign in a new teacher." << endl
            << "or enter any other number to go back." << endl;     
        cin >> choise1;
        switch (choise1) {
        case 1:
            for (i = 0; i < teacherCount; i++) {
                teachersArr[i].print_info();
            }
            cout << "press Enter to continue." << endl;
            cin.ignore();
            cin.get();
            system("cls");
            page_personal_boss(bs);
            break;
        
        case 2:
            cout << "enter the teacher number: ";
            cin >> num;
            tchr = teacher_search(num);
            if (tchr.num != 0) {
                tchr.print_info();
                for (i = 0; i < classCount; i++) {
                    if (classesArr[i].teacher == tchr.fullName()) {
                        classesArr[i].print_info();
                    }
                }
            } else cout << "teacher not found!" << endl;
            cout << "press Enter to continue." << endl;
            cin.ignore();
            cin.get();
            system("cls");
            page_personal_boss(bs);
            break;
        
        case 3:
            system("cls");
            page_create_new_teacher();
            break;
        
        default:
            system("cls");
            page_personal_boss(bs);
        }
        break;
    
    case 3:
        cout << endl << "1. view all classes sorted by class number.(no detail, only name and teacher)" << endl
            << "2. search for a specific class using class number.(complete information)" << endl
            << "3. view all exams in a classe." << endl
            << "4. view all scores in a class." << endl
            << "or enter any other number to go back." << endl;     
        cin >> choise1;
        switch (choise1) {
        case 1:
            for (i = 0; i < classCount; i++) {
                classesArr[i].print_info();
            }
            break;
        
        case 2:
            cout << "enter the class number: " << endl;
            cin >> num;
            cls = class_search(num);
            if (cls.num != 0) {
                cls.print_info();
                // all exams of this class
                cout << "\t";
                for (i = 0; i < 39; i++) cout << '*';
                cout << "EXAMS";
                for (i = 0; i < 39; i++) cout << '*';
                cout << "\t" << endl;

                for (i = 0; i < examCount; i++) {
                    if (examsArr[i].num == cls.num) {
                        examsArr[i].print_info();
                    }
                }
                // all scores in this class
                cout << "\t";
                for (i = 0; i < 39; i++) cout << '*';
                cout << "SCORES";
                for (i = 0; i < 38; i++) cout << '*';
                cout << "\t" << endl;

                for (i = 0; i < scoreCount; i++) {
                    if (scoresArr[i].examNum == cls.num) {
                        scoresArr[i].print_info();
                    }
                }
            } else cout << "class not found!" << endl;
            break;
        
        case 3:
            cout << "enter the class number: " << endl;
            cin >> num;
            cls = class_search(num);
            if (cls.num != 0) {
                // design
                cout << "\t";
                for (i = 0; i < 39; i++) cout << '*';
                cout << "EXAMS";
                for (i = 0; i < 39; i++) cout << '*';
                cout << "\t" << endl;

                for (i = 0; i < examCount; i++) {
                    if (examsArr[i].num == cls.num) {
                        examsArr[i].print_info();
                    }
                }
            } else cout << "class not found!" << endl;
            break;
        
        case 4:
            cout << "enter the class number: " << endl;
            cin >> num;
            cls = class_search(num);
            if (cls.num != 0) {
                // design
                cout << "\t";
                for (i = 0; i < 39; i++) cout << '*';
                cout << "SCORES";
                for (i = 0; i < 38; i++) cout << '*';
                cout << "\t" << endl;

                for (i = 0; i < scoreCount; i++) {
                    if (scoresArr[i].examNum = cls.num) {
                        scoresArr[i].print_info();
                    }
                }
            } else cout << "class not found!" << endl;
            break;
        
        default:
            system("cls");
            page_personal_boss(bs);
        }
        cout << "press Enter to continue." << endl;
        cin.ignore();
        cin.get();
        system("cls");
        page_personal_boss(bs);
        break;
    
    default:
        system("cls");
        page_sign_in();
    } 
}

void page_sign_in() {
    // page cover
    for (int i = 0; i<44; i++) cout << '=';
    cout << "SIGN IN PAGE";
    for (int i = 0; i<44; i++) cout << '=';
    cout << endl;
    // roll
    cout << "1. students entry." << endl;
    cout << "2. teachers entry." << endl;
    cout << "3. boss entry." << endl;
    cout << "or enter any other number to get back to homepage." << endl << endl;
    cout << "Please enter the number: ";
    int choice, choice1;
    cin >> choice;

    string username, password, temp;
    bool found = false;
    switch (choice) {
    case 1:
        // students
        while (!found) {
            cout << "Enter your username: " << endl;
            cin.ignore();
            getline(cin, username);
            cout << "Enter your password: " << endl;
            getline(cin, password);
            
            
            stu = student_search(to_int(username));
            if ((stu.num != 0) && (stu.password == password)) {
                found = true;
                cout << "Found!";
                Sleep(1*1000);
                system("cls");
                page_personal_student(stu);
                break;
            } else {
                cout << "Sorry. We couldn't find any user with this username and password." << endl
                        << "Please try again or go to welcome page and create an account." << endl;
                cout << "1. get back to homepage." << endl;
                cout << "2. try to sign in again." << endl;
                cout << "Please enter the number: ";
                cin >> choice1;
                switch (choice1) {
                case 1:
                    page_wellcome();
                    break;
                case 2:
                    Sleep(1*1000);
                    break;
                default:
                    Sleep(1*1000);
                }
            }  
        }
        break;
    case 2:
        // teachers
        while (!found) {
            cout << "Enter your username: " << endl;
            cin.ignore();
            getline(cin, username);
            cout << "Enter your password: " << endl;
            getline(cin, password);
            
            tchr = teacher_search(to_int(username));
            if ((tchr.num != 0) && (tchr.password == password)) {
                found = true;
                cout << "Found!";
                Sleep(1*1000);
                system("cls");
                page_personal_teacher(tchr);
                break;
            } else {
                cout << "Sorry. We couldn't find any user with this username and password." << endl
                        << "Please try again or go to welcome page and create an account." << endl;
                cout << "1. get back to homepage." << endl;
                cout << "2. try to sign in again." << endl;
                cout << "Please enter the number: ";
                cin >> choice1;
                switch (choice1) {
                case 1:
                    page_wellcome();
                    break;
                case 2:
                    Sleep(1*1000);
                    break;
                default:
                    Sleep(1*1000);
                }
            }
        }
        break;
    case 3:
        // boss
        while (!found) {
            cout << "Enter your username: ";
            cin.ignore();
            getline(cin, username);
            cout << "Enter your password: ";
            getline(cin, password);
            if (username == bs.fullName() && password == bs.password) {
                cout << "Found!";
                Sleep(1*1000);
                system("cls");
                page_personal_boss(bs);
                break;
            } else {
                cout << "Sorry. We couldn't find any user with this username and password." << endl
                    << "Please try again or go to welcome page and create an account." << endl;
                cout << "1. get back to homepage." << endl;
                cout << "2. try to sign in again." << endl;
                cout << "Please enter the number: ";
                cin >> choice1;
                switch (choice1) {
                case 1:
                    page_wellcome();
                    break;
                case 2:
                    Sleep(1*1000);
                    break;
                default:
                    Sleep(1*1000);
                }
            } 
        }
        break;
    default:
        system("cls");
        page_wellcome();
    }
}

void page_create_account() {
    // page cover
    for (int i = 0; i<39; i++) cout << '=';
    cout << "ACCOUNT CREATION PAGE";
    for (int i = 0; i<40; i++) cout << '=';
    cout << endl;
    // student enters first and last name
    string fname;
    cout << "Enter your FIRST name: ";
    cin.ignore();
    getline(cin, fname);
    cout << "Enter your LAST name: " ;
    string lname;
    getline(cin, lname);

    // student enters DUSP to make sure they are students of this university
    cout << "Enter the GUSP (general university security password): ";
    string GUSP;
    getline(cin, GUSP);
    while (GUSP != universityPass) {
        cout << "GUSP is not correct." << endl
             << "Please try again: ";
        getline(cin, GUSP);
    }

    // student must choose a password
    string password;
    cout << "Please choose a password (space and & are not allowed): ";
    getline(cin, password);
    bool validPassword = true;
    for (int i = 0; i<password.length(); i++) {
        if (isspace(password[i]) || password[i] == '&') validPassword = false;
    }
    while (!validPassword) {
        cout << "The password you've chosen is not valid (contains space or &).Try again: ";
        getline(cin, password);
        validPassword = true;
        for (int i = 0; i<password.length(); i++) {
            if (isspace(password[i]) || password[i] == '&') validPassword = false;
        }
    }
    int studentNum;
    cout << "Please enter your student number (7 digits): " ;
    cin >> studentNum;
    // if student number is not in range or number already exists the student should try again
    while ((studentNum > 9999999) || (studentNum < 1000000) || (student_search(studentNum).num != 0)) {
        cout << "The number you've entered is not correct or already exists. Please try again " << endl
            << "(enter 0 if you want to get back to wellcome page): ";
            int choise;
            cin >> choise;
            if (choise == 0) {
                system("cls");
                page_wellcome();
            } else studentNum = choise;
    }
    // process of making a new student
    stu.fname = fname;
    stu.lname = lname;
    stu.password = password;
    stu.num = studentNum;
    stu.move_to_file();
    studentCount = students_array_make();
    // end of process
    cout << "Creating your account finished successfully" << endl
         << "Your username and your student number is: \""<< stu.num <<"\".And your password is \"" << stu.password << "\" .Keep is safe." << endl
         << "Press Enter to go to sign in page.";
    cin.ignore();
    cin.get();
    system("cls");
    page_sign_in();
}

void page_wellcome() {
    fstream wellcomePage;
    wellcomePage.open("wellcome.txt", ios::in);
    string str;
    if (wellcomePage.is_open()) {
        while (getline(wellcomePage, str)) {
            cout << str << endl;
        }
        wellcomePage.close();
    } else {
        cout << "An error accurred while openning files!" << endl
            << "Please copy wellcome.txt file into the directory in which this program is and try to run the program again." << endl;
    }
    int choice; 
    cin >> choice;

    switch (choice) {
    case 1:
        system("cls");
        page_sign_in();
        break;
    case 2:
        system("cls");
        page_create_account();
        break;
    default:
        exit(0);
    }
}

int main() {
    // creating necessary files
    fstream files;
    files.open("studentsList.txt", ios::app);
    files.close();
    files.open("teachersList.txt", ios::app);
    files.close();
    files.open("classesList.txt", ios::app);
    files.close();
    files.open("examsList.txt", ios::app);
    files.close();
    files.open("scoresList.txt", ios::app);
    files.close();
    studentCount = students_array_make();
    teacherCount = teachers_array_make();
    classCount = classes_array_make();
    examCount = exams_array_make();
    scoreCount = score_array_make();
    
    page_wellcome();  
    return 0;
}