#include <iostream>
#include <string>

using namespace std;

//input validation//
bool isNumeric(string str) {
    for (int i = 0; i < str.length(); i++)
        if (isdigit(str[i]) == false)
            return false;
    return true;
}

class Passenger {
public: string name;
      int age;
      int contact;
};

class Bus {
public: int busNumber;
      string destination;
      float price;
      string departureTime;
      int totalSeats;
      int bookedSeats;
      string review;
};

class Node {
public: Bus busData;
      int bookedSeats;
      Node* next;
};

class BusReservationSystem {
private: Node* head;

public: BusReservationSystem() {
    head = NULL;
}

      bool isEmpty() {
          return head == NULL;
      }

      void addBus() {

          Node* newNode = new Node();
          newNode->busData.bookedSeats = 0;
          cout << "Enter Bus Number: ";
          cin >> newNode->busData.busNumber;
          cin.ignore();

          cout << "Enter Destination: ";
          getline(cin, newNode->busData.destination);

          cout << "Enter Price: ";
          cin >> newNode->busData.price;

          cout << "Enter Departure Time: ";
          cin >> newNode->busData.departureTime;

          cout << "Enter Total Seats: ";
          cin >> newNode->busData.totalSeats;

          newNode->next = NULL;
          if (isEmpty()) {
              head = newNode;
          }
          else {
              Node* temp = head;
              while (temp->next != NULL) {
                  temp = temp->next;
              }
              temp->next = newNode;
          }
          cout << "Bus added successfully!" << endl;
      }

      void deleteBus(int busNumber) {
          if (isEmpty()) {
              cout << "No buses available!" << endl;
              return;
          }
          bool found = false;
          Node* prev = NULL;
          Node* curr = head;
          while (curr != NULL) {
              if (curr->busData.busNumber == busNumber) {
                  if (prev == NULL) {
                      head = curr->next;
                  }
                  else {
                      prev->next = curr->next;
                  }
                  delete curr;
                  cout << "Bus deleted successfully!" << endl;
                  found = true;
              }

              prev = curr;
              curr = curr->next;
          }
          if (found == false)
              cout << "Bus not found!" << endl;
      }

      void searchBus(int busNumber, string destination) {
          if (isEmpty()) {
              cout << "No buses available!" << endl;
              return;
          }

          Node* curr = head;
          while (curr != NULL) {
              if (curr->busData.busNumber == busNumber && curr->busData.destination == destination) {
                  cout << "Bus Number: " << curr->busData.busNumber << endl;
                  cout << "Destination: " << curr->busData.destination << endl;
                  cout << "Price: " << curr->busData.price << endl;
                  cout << "Departure Time: " << curr->busData.departureTime << endl;
                  cout << "Total Seats: " << curr->busData.totalSeats << endl;
                  return;
              }
              curr = curr->next;
          }

          cout << "Bus not found!" << endl;
      }

      void updateBus(int busNumber, float newPrice, string newDepartureTime) {
          if (isEmpty()) {
              cout << "No buses available!" << endl;
              return;
          }
          bool found = false;
          Node* curr = head;
          while (curr != NULL) {
              if (curr->busData.busNumber == busNumber) {
                  curr->busData.price = newPrice;
                  curr->busData.departureTime = newDepartureTime;
                  cout << "Bus updated successfully!" << endl;
                  found = true;
              }
              curr = curr->next;
          }
          if (found == false)
          {
              cout << "Bus not found!" << endl;
          }

      }

      void displayBuses() {
          if (isEmpty()) {
              cout << "No buses available!" << endl;
              return;
          }

          Node* curr = head;
          while (curr != NULL) {
              cout << "Bus Number: " << curr->busData.busNumber << endl;
              cout << "Destination: " << curr->busData.destination << endl;
              cout << "Price: " << curr->busData.price << endl;
              cout << "Departure Time: " << curr->busData.departureTime << endl;
              cout << "Total Seats: " << curr->busData.totalSeats << endl;
              cout << "Booked Seats: " << curr->busData.bookedSeats << endl;
              cout << "-----------------------" << endl;
              curr = curr->next;
          }
      }

      void checkSeatAvailability(string destination) {
          if (isEmpty()) {
              cout << "No buses available!" << endl;
              return;
          }

          Node* curr = head;
          while (curr != NULL) {
              if (curr->busData.destination == destination) {
                  int availableSeats = curr->busData.totalSeats - curr->busData.bookedSeats;
                  cout << "Available seats for destination " << destination << ": " << availableSeats << endl;
                  return;
              }
              curr = curr->next;
          }
          cout << "No buses available for the given destination!" << endl;
      }
      void bookTicket(string destination, int seatNumber) {
          if (isEmpty()) {
              cout << "No buses available!" << endl;
              return;
          }

          Node* curr = head;
          while (curr != NULL) {
              if (curr->busData.destination == destination) {
                  int availableSeats = curr->busData.totalSeats - curr->busData.bookedSeats;
                  if (seatNumber > 0 && seatNumber <= availableSeats) {
                      curr->busData.bookedSeats += seatNumber;
                      curr->busData.totalSeats -= seatNumber;
                      cout << "Tickets booked successfully" << endl;
                      paymentMethod();
                      return;
                  }
                  else {
                      cout << "Seats are not available." << endl;
                      return;
                  }
              }
              curr = curr->next;
          }
          cout << "No buses available for the given destination!" << endl;
      }

      void capturePassengerDetails() {
          Passenger passenger;
          cout << "Enter Passenger Name: ";
          cin.ignore();
          getline(cin, passenger.name);

          cout << "Enter Passenger Age: ";
          cin >> passenger.age;

          cout << "Enter Passenger Contact Information: ";
          cin.ignore();
          cin >> passenger.contact;
      }

      void cancelTicket(string destination, int seatNumber) {
          if (isEmpty()) {
              cout << "No buses available!" << endl;
              return;
          }
          bool found = false;
          Node* curr = head;
          while (curr != NULL) {
              if (curr->busData.destination == destination) {
                  found = true;
                  if (seatNumber > 0 && seatNumber <= curr->busData.bookedSeats) {
                      curr->busData.bookedSeats -= seatNumber;
                      curr->busData.totalSeats += seatNumber;
                      cout << "Tickets canceled successfully" << endl;
                  }
                  else {
                      cout << "Invalid number of seats to cancel." << endl;
                  }
              }
              curr = curr->next;
          }
          if (found == true)
          {
              cout << "No tickets found for the given destination!" << endl;
          }
      }

      void addReview(int busNumber, string review) {
          if (isEmpty()) {
              cout << "No buses available!" << endl;
              return;
          }
          bool found = false;
          Node* curr = head;
          while (curr != NULL) {
              if (curr->busData.busNumber == busNumber) {
                  curr->busData.review = review;
                  cout << "Review added successfully!" << endl;
                  found = true;
              }
              curr = curr->next;
          }
          if (found == false)
          {
              cout << "Bus not found!" << endl;
          }

      }

      void viewReviews() {
          if (isEmpty()) {
              cout << "No buses available!" << endl;
              return;
          }
          Node* curr = head;
          while (curr != NULL) {
              cout << "Bus Number: " << curr->busData.busNumber << endl;
              cout << "Destination: " << curr->busData.destination << endl;
              cout << "Review: " << curr->busData.review << endl;
              cout << "-----------------------------------" << endl;
              curr = curr->next;
          }
      }

      void paymentMethod() {
          int choice;
          cout << "Select Payment Method:" << endl;
          cout << "1. Card" << endl;
          cout << "2. Cash" << endl;
          cout << "Enter your choice: ";
          cin >> choice;

          switch (choice) {
          case 1:
              cout << "Payment completed using Card." << endl;
              break;
          case 2:
              cout << "Payment completed using Cash." << endl;
              break;
          default:
              cout << "Invalid choice!" << endl;
          }
      }
};

int validateIntegerInput() {
    int input;
    while (!(cin >> input)) {
        cout << "Invalid input. Please enter an integer value: ";
        cin.clear();
        cin.ignore();
    }
    return input;
}

float validateFloatInput() {
    float input;
    while (!(cin >> input)) {
        cout << "Invalid input. Please enter a float value: ";
        cin.clear();
        cin.ignore();
    }
    return input;
}

int validateMenuChoice() {
    int input;
    while (!(cin >> input) || input < 1 || input > 8) {
        cout << "Invalid input. Please enter a valid menu choice: ";
        cin.clear();
        cin.ignore();
    }
    return input;
}

int main() {
    BusReservationSystem brs;

    int choice, busNumber, seatNumber, j;
    string destination;
    float price;
    string departureTime;
    string review, y;

    do {
        cout << "********************" << endl;
        cout << "BUS RESERVATION SYSTEM" << endl;
        cout << "********************" << endl;
        cout << "1. Admin Portal" << endl;
        cout << "2. User Portal" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
      

        while (true) {
    cout << "Enter your choice: ";
    cin >> y;
    if (isNumeric(y)) {
        j = stoi(y);
        break;  
    } else {
        cout << "Invalid input. Please enter a numeric value." << endl;
    }
}
    switch (j) {
            case 1: {

                string name, password;

                cout << endl;
            t:
                cout << "Enter Admin Name: ";
                cin >> name;
                getline(cin, name);
                cout << "Enter Admin password: ";
                cin >> password;
                if (name != "Hashir" && password != "007") {
    cout << "Invalid name or password. Write Correct Name and Password." << endl;
    goto t;
    return 0;  	
}

                int adminChoice;
                cout << endl;
                cout << "********************" << endl;
                cout << "Admin PORTAL" << endl;
                cout << "********************" << endl;
                cout << endl;
                cout << "1. Add Bus" << endl;
                cout << "2. Delete Bus" << endl;
                cout << "3. Search Bus" << endl;
                cout << "4. Update Bus" << endl;
                cout << "5. Display Buses" << endl;

                cout << "6. View Reviews" << endl;
                cout << "7. Back to Main Menu" << endl;
                cout << "Enter your choice: ";
                adminChoice = validateMenuChoice();

                switch (adminChoice) {
                case 1:
                    brs.addBus();
                    break;
                case 2:
                    cout << "Enter Bus Number to delete: ";
                    busNumber = validateIntegerInput();
                    brs.deleteBus(busNumber);
                    break;
                case 3:
                    cout << "Enter Bus Number to search: ";
                    busNumber = validateIntegerInput();
                    cout << "Enter Destination to search: ";
                    cin.ignore();
                    getline(cin, destination);
                    brs.searchBus(busNumber, destination);
                    break;
                case 4:
                    cout << "Enter Bus Number to update: ";
                    busNumber = validateIntegerInput();
                    cout << "Enter New Price: ";
                    price = validateFloatInput();
                    cout << "Enter New Departure Time: ";
                    cin.ignore();
                    getline(cin, departureTime);
                    brs.updateBus(busNumber, price, departureTime);
                    break;
                case 5:
                    brs.displayBuses();
                    break;

                case 6:
                    brs.viewReviews();
                    break;
                case 7:
                    cout << "Returning to Main Menu..." << endl;
                    break;
                default:
                    cout << "Invalid choice!" << endl;
                }

                cout << endl;
                break;
            }
            case 2: {
                int userChoice;
                cout << endl;
                cout << "********************" << endl;
                cout << "USER PORTAL" << endl;
                cout << "********************" << endl;
                cout << endl;
                cout << "1. Book Ticket" << endl;
                cout << "2. Cancel Ticket" << endl;
                cout << "3. Add Review" << endl;
                cout << "4. Back to Main Menu" << endl;
                cout << "Enter your choice: ";
                userChoice = validateMenuChoice();

                switch (userChoice) {
                case 1:
                    cout << "Enter Destination: ";
                    cin.ignore();
                    getline(cin, destination);
                    brs.checkSeatAvailability(destination);
                    cout << "How many Seats you want to book? ";
                    seatNumber = validateIntegerInput();
                    brs.capturePassengerDetails();
                    brs.bookTicket(destination, seatNumber);
                    break;
                case 2:
                    cout << "Enter Destination: ";
                    cin.ignore();
                    getline(cin, destination);
                    cout << "How many tickets you want to cancel?: ";
                    seatNumber = validateIntegerInput();
                    brs.cancelTicket(destination, seatNumber);
                    break;
                case 3:
                    cout << "Enter Bus Number to add review: ";
                    cin >> busNumber;
                    cin.ignore();
                    cout << "Enter Review: ";
                    getline(cin, review);
                    brs.addReview(busNumber, review);
                    break;
                case 4:
                    cout << "Returning to Main Menu..." << endl;
                    break;
                default:
                    cout << "Invalid choice!" << endl;
                }

                cout << endl;
                break;
            }
            case 3:
                cout << "Exiting the program..." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
            }

} while (j != 3);

    return 0;
}
