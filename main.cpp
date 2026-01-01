#include "core/entities/DbController.hpp"

using namespace App;
using namespace App::DB_entities;

int main() {
    DB_controller controller;
    Client client("Kirill", "Avvakumov", "email");

    controller.init_tables();
    controller.add_new_client(client);
    controller.update_client_phone(client.get_name(), client.get_surname());
    controller.find_client(client.get_name(), client.get_surname(), "cpp@email.com");
    controller.find_client(client.get_name(), client.get_surname(), "7953365465");

    controller.delete_client_phone(client.get_name(), client.get_surname());
    controller.delete_client_info(client.get_name(), client.get_surname());
}
