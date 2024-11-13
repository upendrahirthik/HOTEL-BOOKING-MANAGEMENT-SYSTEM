#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Room {
public:
    int roomNumber;
    string roomType;
    double price;
    bool isAvailable;

    Room(int number, string type, double price) : roomNumber(number), roomType(type), price(price), isAvailable(true) {}
};

class Hotel {
public:
    string name;
    vector<Room> rooms;

    Hotel(string name) : name(name) {}

    void addRoom(int number, string type, double price) {
        rooms.emplace_back(number, type, price);
    }

    void displayRooms() {
        cout << "Rooms available in " << name << ":\n";
        for (const auto& room : rooms) {
            if (room.isAvailable) {
                cout << "Room Number: " << room.roomNumber << ", Type: " << room.roomType 
                     << ", Price: $" << room.price << endl;
            }
        }
    }

    Room* findAvailableRoom(int roomNumber) {
        for (auto& room : rooms) {
            if (room.roomNumber == roomNumber && room.isAvailable) {
                return &room;
            }
        }
        return nullptr;
    }
};

class Booking {
public:
    string customerName;
    Hotel* hotel;
    Room* room;

    Booking(string name, Hotel* h, Room* r) : customerName(name), hotel(h), room(r) {
        room->isAvailable = false; // Mark room as booked
    }

    void displayBooking() {
        cout << "Booking Confirmation:\n";
        cout << "Customer Name: " << customerName << "\n";
        cout << "Hotel: " << hotel->name << "\n";
        cout << "Room Number: " << room->roomNumber << ", Type: " << room->roomType 
             << ", Price: $" << room->price << endl;
    }
};

int main() {
    Hotel hotel("Grand Hotel");
    hotel.addRoom(101, "Single", 100.0);
    hotel.addRoom(102, "Double", 150.0);
    hotel.addRoom(103, "Suite", 250.0);

    vector<Booking> bookings;
    int choice;

    do {
        cout << "\n--- Hotel Booking Management System ---\n";
        cout << "1. View Available Rooms\n";
        cout << "2. Book a Room\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

       
 switch (choice) {
            case 1:
                hotel.displayRooms();
                break;
            case 2: {
                string customerName;
                int roomNumber;
                cout << "Enter your name: ";
                cin >> ws; // to consume any leading whitespace
                getline(cin, customerName);
                cout << "Enter room number to book: ";
                cin >> roomNumber;

                Room* room = hotel.findAvailableRoom(roomNumber);
                if (room) {
                    Booking booking(customerName, &hotel, room);
                    bookings.push_back(booking);
                    booking.displayBooking();
                } else {
                    cout << "Room not available or does not exist.\n";
                }
                break;
            }
            case 3:
                cout << "Exiting the system.\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 3);

    return 0;
}
