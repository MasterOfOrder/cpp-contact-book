#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

struct Contact {
    std::string name;
    std::string phone;
    std::string email;
};

std::vector<Contact> contacts;

void addContact(const std::string& name, const std::string& phone, const std::string& email) {
    Contact newContact{name, phone, email};
    contacts.push_back(newContact);
    std::cout << "Contact added successfully!" << std::endl;
}
void displayContacts() {
    for (const auto& contact : contacts) {
        std::cout << "Name: " << contact.name << ", Phone: " << contact.phone << ", Email: " << contact.email << std::endl;
    }
}
static std::string toLower(const std::string &s) {
    std::string result = s;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

void searchContact(const std::string& name) {
    std::string query = toLower(name);
    for (const auto& contact : contacts) {
        if (toLower(contact.name) == query) {
            std::cout << "Name: " << contact.name << ", Phone: " << contact.phone << ", Email: " << contact.email << std::endl;
            return;
        }
    }
    std::cout << "Contact not found!" << std::endl;
}
void deleteContact(const std::string& name) {
    std::string query = toLower(name);
    auto it = std::remove_if(contacts.begin(), contacts.end(), [&](const Contact& contact) {
        return toLower(contact.name) == query;
    });
    if (it != contacts.end()) {
        contacts.erase(it, contacts.end());
        std::cout << "Contact deleted successfully!" << std::endl;
    } else {
        std::cout << "Contact not found!" << std::endl;
    }
}

int main() {
    std::ifstream File("contacts.txt");
    std::string line;
    while (std::getline(File, line)) {
        std::stringstream ss(line);
        std::string name, phone, email;
        std::getline(ss, name, ',');
        std::getline(ss, phone, ',');
        std::getline(ss, email, ',');
        contacts.push_back({name, phone, email});
    }
    File.close();
    bool running = true;
    while (running) {
        std::cout << "1.Add Contact\n2.Display Contacts\n3.Search Contact\n4.Delete Contact\n5.Exit\nChoose an option: ";
        int choice;
        std::cin >> choice;
        switch(choice) {
            case 1: {
                std::string name, email, phone;
                std::cout << "Enter name: ";
                std::cin >> name;
                std::cout << "Enter phone number: ";
                std::cin >> phone;
                std::cout << "Enter email: ";
                std::cin >> email;
                addContact(name, phone, email);
                std::ofstream File("contacts.txt");
                for (const auto& contact : contacts) {
                    File << contact.name << "," << contact.phone << "," << contact.email << std::endl;
                }
                File.close();
                break;
            }
            case 2: {
                displayContacts();                
                break;
            }
            case 3: {
                std::string name;
                std::cout << "Enter name to search: ";
                std::cin >> name;
                searchContact(name);
                break;
            }
            case 4: {
                std::string name;
                std::cout << "Enter name to delete: ";
                std::cin >> name;
                deleteContact(name);
                break;
            }
            case 5: {
                running = false;
                std::cout << "Exiting..." << std::endl;
                break;
            }
        }
    }
    return 0;
}