#include "core/entities/DbController.hpp"

using namespace App;
using namespace App::DB_entities;

int main() {
    DB_controller controller;
    Client client("Kirill", "Avvakumov", "email");

    controller.init_db();
    controller.add_new_client(client);
}
