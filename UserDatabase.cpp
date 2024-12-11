#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include <iomanip>

using namespace std;

// User Class
class User {
public:
    string fullName;
    string phoneNumber;
    string address;
    string username;
    string password;
};

// MenuItem Class
class MenuItem {
public:
    string name;
    int price;
};

// Order Class
class Order {
public:
    User customer;
    MenuItem food;
    MenuItem drink;
    int totalPrice;
    string paymentMethod;
    bool isCompleted = false;
};

// User Database Management
class UserDatabase {
private:
    vector<User> users;
    User adminUser = {"Admin", "", "", "admin", "admin123"};

public:
    bool registerUser(const User& newUser) {
        // Check if username already exists
        for (const auto& user : users) {
            if (user.username == newUser.username) {
                return false;
            }
        }
        users.push_back(newUser);
        return true;
    }

    bool authenticateUser(const string& username, const string& password, bool isAdmin = false) {
        if (isAdmin) {
            return username == adminUser.username && password == adminUser.password;
        }

        for (const auto& user : users) {
            if (user.username == username && user.password == password) {
                return true;
            }
        }
        return false;
    }

    User getUserByUsername(const string& username) {
        for (const auto& user : users) {
            if (user.username == username) {
                return user;
            }
        }
        return User();
    }
};

// Menu Database Management
class MenuDatabase {
private:
    vector<MenuItem> foods = {
        {"Nasi orak arik telur", 10000},
        {"Nasi ayam balado", 12000},
        {"Magelangan", 11000},
        {"Indomie rebus telur", 10000},
        {"Indomie goreng telur", 10000},
        {"Gorengan", 1000}
    };

    vector<MenuItem> drinks = {
        {"Air mineral", 5000},
        {"Es teh", 2000},
        {"Kopi susu", 5000}
    };

public:
    void displayFoods() {
        cout << "Daftar Makanan:\n";
        for (size_t i = 0; i < foods.size(); ++i) {
            cout << i + 1 << ". " << foods[i].name << " - Rp" << foods[i].price << endl;
        }
    }

    void displayDrinks() {
        cout << "Daftar Minuman:\n";
        for (size_t i = 0; i < drinks.size(); ++i) {
            cout << i + 1 << ". " << drinks[i].name << " - Rp" << drinks[i].price << endl;
        }
    }

    MenuItem getFoodByIndex(int index) {
        return (index >= 1 && index <= foods.size()) ? foods[index - 1] : MenuItem();
    }

    MenuItem getDrinkByIndex(int index) {
        return (index >= 1 && index <= drinks.size()) ? drinks[index - 1] : MenuItem();
    }

    void addFood(const MenuItem& food) {
        foods.push_back(food);
    }

    void addDrink(const MenuItem& drink) {
        drinks.push_back(drink);
    }

    void removeFoodByIndex(int index) {
        if (index >= 1 && index <= foods.size()) {
            foods.erase(foods.begin() + index - 1);
        }
    }

    void removeDrinkByIndex(int index) {
        if (index >= 1 && index <= drinks.size()) {
            drinks.erase(drinks.begin() + index - 1);
        }
    }

    int getFoodCount() const {
        return foods.size();
    }

    int getDrinkCount() const {
        return drinks.size();
    }
};

// Main Application Class
class WarmindoApp {
private:
    UserDatabase userDB;
    MenuDatabase menuDB;
    vector<Order> orders;
    User currentUser;

    // Utility Methods
    void clearScreen() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

    template<typename T>
    T getValidInput(const string& prompt, T min, T max) {
        T input;
        while (true) {
            cout << prompt;
            if (cin >> input && input >= min && input <= max) {
                return input;
            }
            cout << "Input tidak valid. Silakan coba lagi.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    // Menu Methods
   void mainMenu() {
    while (true) {
        clearScreen();
        cout << "ww           ww    aaa    rrrrrr mmm    mmm ii nnn   nn ddddd   oooo\n";
        cout << "ww    www    ww   aa aa   rr     mm m  m mm ii nn n  nn dd  dd oo  oo\n";
        cout << " ww  ww ww  ww   aa   aa  rr     mm  mm  mm ii nn  n nn dd  dd oo  oo\n";
        cout << "  www     www   aa     aa rr     mm      mm ii nn   nnn ddddd   oooo\n\n";
        cout << " ^^^^^^^^^^^^^^^^^^^^^^^^^^^ SiyapAnter ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n";
        
        cout << "1. Registrasi Akun\n";
        cout << "2. Login\n";
        cout << "3. Keluar\n\n";

        int choice = getValidInput<int>("Pilih menu: ", 1, 3);

        switch (choice) {
            case 1: registrationMenu(); break;
            case 2: loginMenu(); break;
            case 3: 
                cout << "Terima kasih telah menggunakan Warmindo SiyapAnter!\n";
                exit(0);
        }
    }
}

    void registrationMenu() {
        User newUser;
        
        clearScreen();
        cout << "Registrasi Akun\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        cout << "Nama Lengkap: ";
        getline(cin, newUser.fullName);
        
        cout << "No Telepon: ";
        getline(cin, newUser.phoneNumber);
        
        cout << "Alamat: ";
        getline(cin, newUser.address);
        
        cout << "Username: ";
        getline(cin, newUser.username);
        
        cout << "Password: ";
        getline(cin, newUser.password);

        if (userDB.registerUser(newUser)) {
            cout << "Registrasi Berhasil!\n";
            cin.get();
        } else {
            cout << "Username sudah ada. Registrasi gagal.\n";
            cin.get();
        }
    }

    void loginMenu() {
        clearScreen();
        cout << "Login\n";
        cout << "1. Login Admin\n";
        cout << "2. Login Pelanggan\n";

        int choice = getValidInput<int>("Pilih menu: ", 1, 2);

        string username, password;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        cout << "Username: ";
        getline(cin, username);
        
        cout << "Password: ";
        getline(cin, password);

        if (choice == 1 && userDB.authenticateUser(username, password, true)) {
            adminMenu();
        } else if (choice == 2 && userDB.authenticateUser(username, password)) {
            currentUser = userDB.getUserByUsername(username);
            customerMenu();
        } else {
            cout << "Login gagal. Coba lagi.\n";
            cin.get();
        }
    }

       void adminMenu() {
        while (true) {
            clearScreen();
            cout << "Menu Admin\n";
            cout << "1. Tambah Menu Makanan\n";
            cout << "2. Tambah Menu Minuman\n";
            cout << "3. Hapus Menu Makanan\n";
            cout << "4. Hapus Menu Minuman\n";
            cout << "5. Lihat Daftar Pesanan\n";
            cout << "6. Kembali ke Menu Utama\n";

            int choice = getValidInput<int>("Pilih menu: ", 1, 6);

            switch (choice) {
                case 1: tambahMenuMakanan(); break;
                case 2: tambahMenuMinuman(); break;
                case 3: hapusMenuMakanan(); break;
                case 4: hapusMenuMinuman(); break;
                case 5: lihatDaftarPesanan(); break;
                case 6: return;
            }
        }
    }

    void tambahMenuMakanan() {
        MenuItem newFood;
        clearScreen();
        cout << "Tambah Menu Makanan\n";
        
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        cout << "Nama Makanan: ";
        getline(cin, newFood.name);
        
        cout << "Harga Makanan: ";
        cin >> newFood.price;
        
        menuDB.addFood(newFood);
        cout << "Makanan berhasil ditambahkan!\n";
        cin.get();
        cin.get();
    }

    void tambahMenuMinuman() {
        MenuItem newDrink;
        clearScreen();
        cout << "Tambah Menu Minuman\n";
        
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        cout << "Nama Minuman: ";
        getline(cin, newDrink.name);
        
        cout << "Harga Minuman: ";
        cin >> newDrink.price;
        
        menuDB.addDrink(newDrink);
        cout << "Minuman berhasil ditambahkan!\n";
        cin.get();
        cin.get();
    }

    void hapusMenuMakanan() {
        clearScreen();
        menuDB.displayFoods();
        
        int foodCount = menuDB.getFoodCount();
        if (foodCount == 0) {
            cout << "Tidak ada makanan untuk dihapus.\n";
            cin.get();
            return;
        }

        int choice = getValidInput<int>("Pilih nomor makanan yang akan dihapus: ", 1, foodCount);
        menuDB.removeFoodByIndex(choice);
        
        cout << "Makanan berhasil dihapus!\n";
        cin.get();
    }

    void hapusMenuMinuman() {
        clearScreen();
        menuDB.displayDrinks();
        
        int drinkCount = menuDB.getDrinkCount();
        if (drinkCount == 0) {
            cout << "Tidak ada minuman untuk dihapus.\n";
            cin.get();
            return;
        }

        int choice = getValidInput<int>("Pilih nomor minuman yang akan dihapus: ", 1, drinkCount);
        menuDB.removeDrinkByIndex(choice);
        
        cout << "Minuman berhasil dihapus!\n";
        cin.get();
    }

void lihatDaftarPesanan() {
    clearScreen();
    cout << "DAFTAR PESANAN PELANGGAN\n";
    cout << "===============================\n";
    
    if (orders.empty()) {
        cout << "Belum ada pesanan.\n";
    } else {
        for (size_t i = 0; i < orders.size(); ++i) {
            cout << "Pesanan ke-" << i + 1 << ":\n";
            
            // Tampilkan informasi pelanggan
            cout << "Nama Pelanggan    : " << orders[i].customer.fullName << endl;
            cout << "Nomor Handphone   : " << orders[i].customer.phoneNumber << endl;
            cout << "Alamat Pengiriman : " << orders[i].customer.address << endl;
            
            cout << "\nDetail Pesanan:\n";
            cout << "Makanan: " << orders[i].food.name << " (Rp" << orders[i].food.price << ")\n";
            cout << "Minuman: " << orders[i].drink.name << " (Rp" << orders[i].drink.price << ")\n";
            
            cout << "Total Harga: Rp" << orders[i].totalPrice << endl;
            cout << "Metode Pembayaran: " 
                 << (orders[i].paymentMethod == "1" ? "Transfer Bank" : "COD") << endl;
            
            cout << "-------------------\n";
        }
    }
    
    cout << "\nTekan Enter untuk kembali...";
    cin.get();
    cin.get();
}
    void customerMenu() {
        while (true) {
            clearScreen();
            cout << "Selamat datang, " << currentUser.fullName << "!\n";
            
            menuDB.displayFoods();
            int foodChoice = getValidInput<int>("Pilih makanan (1-" + 
                to_string(menuDB.getFoodCount()) + "): ", 1, menuDB.getFoodCount());
            MenuItem selectedFood = menuDB.getFoodByIndex(foodChoice);

            menuDB.displayDrinks();
            int drinkChoice = getValidInput<int>("Pilih minuman (1-" + 
                to_string(menuDB.getDrinkCount()) + "): ", 1, menuDB.getDrinkCount());
            MenuItem selectedDrink = menuDB.getDrinkByIndex(drinkChoice);

            prosesCheckout(selectedFood, selectedDrink);
            return;
        }
    }

void prosesCheckout(const MenuItem& makanan, const MenuItem& minuman) {
    clearScreen();
    cout << "Checkout Pesanan\n";
    cout << "Makanan: " << makanan.name << " - Rp" << makanan.price << endl;
    cout << "Minuman: " << minuman.name << " - Rp" << minuman.price << endl;
    
    int totalHarga = makanan.price + minuman.price;
    cout << "Total Harga: Rp" << totalHarga << endl;

    cout << "Metode Pembayaran:\n";
    cout << "1. Transfer Bank\n";
    cout << "2. COD (Cash on Delivery)\n";

    int metodePembayaran = getValidInput<int>("Pilih metode pembayaran: ", 1, 2);

    Order pesananBaru;
    pesananBaru.customer = currentUser;
    pesananBaru.food = makanan;
    pesananBaru.drink = minuman;
    pesananBaru.totalPrice = totalHarga;
    pesananBaru.paymentMethod = to_string(metodePembayaran);

    if (metodePembayaran == 1) {
        clearScreen();
        cout << "INFORMASI PEMBAYARAN\n";
        
        // Tambahkan kalimat konfirmasi sesuai permintaan
        cout << "Kami akan mengirimkan pesanan " 
             << makanan.name << " dan " << minuman.name 
             << " ke alamat " << currentUser.address 
             << " atas nama " << currentUser.fullName << "terimakasih:).\n\n";

        cout << "Silahkan transfer ke no rekening berikut:\n\n";
        cout << "Nama Pemilik  : BELT SAZAR MEGA RIZK\n";
        cout << "Bank          : Mandiri\n";
        cout << "Nomor Rekening: 1370024068856\n\n";
        cout << "Jumlah Transfer: Rp" << totalHarga << "\n\n";
        cout << "Chef terbaik kami akan langsung memproses pesanan anda\n";
        cout << "         setelah selesai pembayaran\n\n";
        
        cout << "Konfirmasi pembayaran?\n";
        cout << "1. Sudah Transfer\n";
        cout << "2. Batalkan Pesanan\n";

        int konfirmasi = getValidInput<int>("Pilih opsi: ", 1, 2);

        if (konfirmasi == 1) {
            orders.push_back(pesananBaru);
            cout << "\nPesanan berhasil dibuat! Chef akan segera memproses.\n";
            cout << "Terima kasih telah memesan di Warmindo SiyapAnter!\n";
            cin.get();
            cin.get();
        } else {
            cout << "Pesanan dibatalkan.\n";
            cin.get();
        }
    } else {
        // Untuk metode COD
        clearScreen();
        cout << "KONFIRMASI PESANAN COD\n";
        
    
        cout << "Kami akan mengirimkan pesanan " 
             << makanan.name << " dan " << minuman.name 
             << " ke alamat " << currentUser.address 
             << " atas nama " << currentUser.fullName << "terimakasih:).\n\n";

        char konfirmasi;
        cout << "Konfirmasi pesanan COD? (y/n): ";
        cin >> konfirmasi;

        if (konfirmasi == 'y' || konfirmasi == 'Y') {
            orders.push_back(pesananBaru);
            cout << "Pesanan berhasil dibuat!\n";
            cout << "Pesanan akan dibayar saat pengantaran.\n";
            cin.get();
            cin.get();
        }
    }
}

public:
    void jalankan() {
        mainMenu();
    }
};

int main() {
    WarmindoApp app;
    app.jalankan();
    return 0;
}