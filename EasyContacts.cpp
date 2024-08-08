#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>  // For std::sort

struct Contact {
    std::string name;
    std::string phone;
    std::string email;
};

// Function declarations
void addContact(std::vector<Contact>& contacts);
void searchContact(const std::vector<Contact>& contacts);
void deleteContact(std::vector<Contact>& contacts);
void saveContacts(const std::vector<Contact>& contacts);
void loadContacts(std::vector<Contact>& contacts, const std::string& filePath);
void displayContacts(const std::vector<Contact>& contacts);
int countContacts(const std::vector<Contact>& contacts);

int main() {
    std::vector<Contact> contacts;
    std::string filePath = "indian_contacts.txt";  // Path to the file with 100 Indian contacts
    loadContacts(contacts, filePath);

    int choice;
    while (true) {
        std::cout << "\nContact Management System\n";
        std::cout << "1. Add Contact\n";
        std::cout << "2. Search Contact\n";
        std::cout << "3. Delete Contact\n";
        std::cout << "4. Display All Contacts\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();  // Clear input buffer

        switch (choice) {
            case 1:
                addContact(contacts);
                break;
            case 2:
                searchContact(contacts);
                break;
            case 3:
                deleteContact(contacts);
                break;
            case 4:
                displayContacts(contacts);
                break;
            case 5:
                saveContacts(contacts);
                std::cout << "Exiting...\n";
                return 0;
            default:
                std::cout << "Invalid choice, please try again.\n";
        }
    }
}

void addContact(std::vector<Contact>& contacts) {
    Contact newContact;
    std::cout << "Enter Name: ";
    std::getline(std::cin, newContact.name);
    std::cout << "Enter Phone Number: ";
    std::getline(std::cin, newContact.phone);
    std::cout << "Enter Email: ";
    std::getline(std::cin, newContact.email);

    contacts.push_back(newContact);
    std::cout << "Contact added successfully.\n";
}

void searchContact(const std::vector<Contact>& contacts) {
    std::string searchName;
    std::cout << "Enter the name to search: ";
    std::getline(std::cin, searchName);

    for (const auto& contact : contacts) {
        if (contact.name == searchName) {
            std::cout << "Name: " << contact.name << "\n";
            std::cout << "Phone: " << contact.phone << "\n";
            std::cout << "Email: " << contact.email << "\n";
            return;
        }
    }
    std::cout << "Contact not found.\n";
}

void deleteContact(std::vector<Contact>& contacts) {
    std::string searchName;
    std::cout << "Enter the name to delete: ";
    std::getline(std::cin, searchName);

    auto it = std::remove_if(contacts.begin(), contacts.end(), [&](const Contact& contact) {
        return contact.name == searchName;
    });

    if (it != contacts.end()) {
        contacts.erase(it, contacts.end());
        std::cout << "Contact deleted successfully.\n";
    } else {
        std::cout << "Contact not found.\n";
    }
}

void saveContacts(const std::vector<Contact>& contacts) {
    std::ofstream outfile("contacts.txt");
    if (!outfile) {
        std::cerr << "Error opening file for writing.\n";
        return;
    }

    // Sort contacts alphabetically by name
    std::vector<Contact> sortedContacts = contacts;
    std::sort(sortedContacts.begin(), sortedContacts.end(), [](const Contact& a, const Contact& b) {
        return a.name < b.name;
    });

    for (const auto& contact : sortedContacts) {
        outfile << contact.name << "\n" << contact.phone << "\n" << contact.email << "\n";
    }
    std::cout << "Contacts saved to file.\n";
}

void loadContacts(std::vector<Contact>& contacts, const std::string& filePath) {
    std::ifstream infile(filePath);
    if (!infile) {
        std::cout << "Unable to open contacts file.\n";
        return;
    }

    Contact contact;
    while (std::getline(infile, contact.name)) {
        std::getline(infile, contact.phone);
        std::getline(infile, contact.email);
        contacts.push_back(contact);
    }
    infile.close();
    std::cout << "Contacts loaded from file.\n";
}

void displayContacts(const std::vector<Contact>& contacts) {
    if (contacts.empty()) {
        std::cout << "No contacts to display.\n";
    } else {
        // Sort contacts alphabetically by name
        std::vector<Contact> sortedContacts = contacts;
        std::sort(sortedContacts.begin(), sortedContacts.end(), [](const Contact& a, const Contact& b) {
            return a.name < b.name;
        });

        std::cout << "Total number of contacts: " << countContacts(contacts) << "\n";

        for (const auto& contact : sortedContacts) {
            std::cout << "Name: " << contact.name << "\n";
            std::cout << "Phone: " << contact.phone << "\n";
            std::cout << "Email: " << contact.email << "\n";
            std::cout << "-------------------------\n";
        }
    }
}

int countContacts(const std::vector<Contact>& contacts) {
    return contacts.size();
}
