#include "core/entities/DbController.hpp"

using namespace App;
using namespace App::DB_entities;

int main() {
    DB_controller controller = DB_controller(); //controls postgresql bd

    controller.drop_tables();
    controller.init_tables();

    Client client1("Kirill", "Ivanov", "email");
    controller.add_client(client1, "");
    controller.update_client("email", "Egor", "Ivanov", "egorushka@yandex.ru");
    controller.add_phone("Egor", "89554753549");
    controller.select_all();

    Client client2("Slava", "Vasiliev", "slavic@email.ru");
    controller.add_client(client2, "78125463022");
    controller.select_all();

    Client client3("Aleksandr", "Petrov", "best_actor@email.ru");
    controller.add_client(client3, "78237462021");
    controller.select_all();

    std::vector<Client> found_clients = controller.find_clients("Aleksandr");
    for (const auto &[name, surname, email, phones]: found_clients) {
        libio::output::println("Found client: ");
        libio::output::println("Name: " + name);
        libio::output::println("Surname: " + surname);
        libio::output::println("Email: " + email);
        libio::output::println(); //just new line
    }

    controller.remove_client("slavic@email.ru");
    controller.select_all();

    controller.remove_phone("egorushka@yandex.ru", "89554753549");
    controller.select_all(); //and at the end of the script, the best actor of the world!
}
