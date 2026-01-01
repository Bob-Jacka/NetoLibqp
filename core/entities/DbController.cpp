#include "DbController.hpp"
#include "SQLexception.hpp"

App::DB_entities::Client::Client(libio::String_con_ref name, libio::String_con_ref surname,
                                 libio::String_con_ref email) {
    this->name = name;
    this->surname = surname;
    this->email = email;
    this->phone = std::vector<libio::String>();
}

App::DB_entities::Client::Client(libio::String_con_ref name, libio::String_con_ref surname, libio::String_con_ref email,
                                 std::vector<std::string> &phones) {
    this->name = name;
    this->surname = surname;
    this->email = email;
    this->phone = phones;
}

std::string App::DB_entities::Client::get_name() const {
    return name;
}

std::string App::DB_entities::Client::get_surname() const {
    return surname;
}

std::string App::DB_entities::Client::get_email() const {
    return email;
}

std::vector<std::string> App::DB_entities::Client::get_phone() const {
    return phone;
}

libio::String App::DB_entities::Client::to_string() const {
    return std::string(name + ", " + surname + ", " + email + ", " + phone);
}

///////////////////////DB_controller

void
App::DB_controller::create_table(libio::String_con_ref table_name, const std::vector<libio::String> &) const {
    using namespace libio::database;
    std::string column_string;
    auto res = transaction(
            Sql_methods::CREATE + " TABLE IF NOT EXISTS " + table_name +
            " (" + " )"
    );
}

void App::DB_controller::init_db() {
    create_table("NamesSurnames");
    create_table("Emails");
    create_table("Phones");
}

void App::DB_controller::add_new_client(const DB_entities::Client &new_client, libio::String_con_ref table_name) const {
    using namespace libio::database;
    auto res = transaction(
            Sql_methods::INSERT +
            " INTO " + table_name +
            " (" +
            new_client.to_string()
            + " )");
}

void App::DB_controller::update_client_phone(libio::String_con_ref, libio::String_con_ref) const {
    using namespace libio::database;
    auto res = transaction();
}

void App::DB_controller::update_client_info(libio::String_con_ref, libio::String_con_ref, libio::String_con_ref,
                                            std::optional<std::vector<libio::String>> &) const {
    using namespace libio::database;
    auto res = transaction(Sql_methods::UPDATE);
}

void App::DB_controller::delete_client_phone(libio::String_con_ref, libio::String_con_ref) const {
    using namespace libio::database;
    auto res = transaction(Sql_methods::DELETE);
}

void App::DB_controller::delete_client_info(libio::String_con_ref, libio::String_con_ref) const {
    using namespace libio::database;
    auto res = transaction(Sql_methods::DELETE);
}

void
App::DB_controller::find_client(libio::String_con_ref, libio::String_con_ref,
                                const std::variant<libio::String, std::vector<libio::String>> &) const {
    using namespace libio::database;
    auto res = transaction(Sql_methods::SELECT);
}

pqxx::result App::DB_controller::transaction(libio::String_con_ref query) const {
    try {
        pqxx::connection cx;
        pqxx::work tx(cx);
        auto r = tx.exec(query);
        tx.commit();
        return r;
    } catch (...) {
        throw SQLexception(__LINE__, "Error in transaction to database", __FILE_NAME__);
    }
}
