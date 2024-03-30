#include "Student.h"
#include <fstream>
#include <iostream>
using namespace std;

Student::~Student() {

}
Student::Student(string department, string password, int id, timeTable memory):User(password,id) {
    m_department = department;

    for (int i = 0; i < memory.getSize();i++) {
       event temp = memory.getEvent(i);
       vector<int> ID = temp.getEventParticipants();
       for (int j = 0; j < ID.size(); j++)
       {
           if (id == ID[j]) {
               m_timetable.addEventToTimetable(temp);
           }
       }
    }
}

void Student::selecttimetable(timeTable memory) {
    cout << "code" << "\t" << "course name" << "\t" << "start and end time of the course" << "\t" << "day" << "\t" << endl;
    for (int i = 0; i < memory.getSize(); i++) {
        event temp = memory.getEvent(i);
        cout << temp.getEventCode() << "\t" << temp.getEventName() << "\t" << temp.getEventStart() << "-" << temp.getEventEnd() << "\t" << temp.getEventDay() << endl;
    }
    cout << "Please choose the course you want to have in this semester" << endl;
    int code;
    cin >> code;
    event temp = memory.getEventByCode(code);
    for (int j = 0; j < m_timetable.getSize(); j++) {
        event temp2 = m_timetable.getEvent(j);
        if (temp2.getEventCode() == code) {
            cout << "You already choose this class" << endl;
        }
        if (temp2.getEventCode() != code) {
            temp.addParticipants(m_id);
            m_timetable.addEventToTimetable(temp);
            if (m_timetable.timeConfilctCheck() == true)
            {
                cout << "you can not choose this course there's time confilct" << endl;
                m_timetable.deletEvent(code);
           }
            else
            {
              cout << "Congratulations on making it to this class" << endl;
            }
          
        }
    }
    memory.updateFrom(m_timetable);
}
void Student::deletevent(timeTable memory) {
    cout << "Do you want to delet any course" << endl;
    int code;
    cin >> code;
    for (int i = 0; i < m_timetable.getSize(); i++) {
        event temp = m_timetable.getEvent(i);
        temp.deleteParticipants(m_id);
        m_timetable.updateFrom(temp);
    }
    memory.updateFrom(m_timetable);
    m_timetable.deletEvent(code);
}

ostream& operator<<(ostream& out, Student& student) {
    timeTable studenttimetable = student.gettimetable();
    out << "code" << "\t" << "course name" << "\t" << "start and end time of the course" << "\t" << "day" << "\t" << endl;
    for (int i = 0; i < studenttimetable.getSize(); i++) {
        event temp = studenttimetable.getEvent(i);
        out << temp.getEventCode() << "\t" << temp.getEventName() << "\t" << temp.getEventStart() << "-" << temp.getEventEnd() << "\t" << temp.getEventDay() << endl;
    }
    return out;
}

