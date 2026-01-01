#ifndef NETOLIBPQ_DBCONTROLLER_HPP
#define NETOLIBPQ_DBCONTROLLER_HPP

#include <string>
#include <vector>
#include <variant>

#include "../dependencies/libpqxx-7.10.4/include/pqxx/pqxx"
#include <optional>

import Libio;

namespace App {
    namespace DB_entities {
        struct Client {
        private:
            libio::String name;
            libio::String surname;
            libio::String email;
            std::vector<libio::String> phone;

        public:
            ~Client() = default;

            Client() = delete;

            Client(Client &) = default;

            Client(libio::String_con_ref, libio::String_con_ref, libio::String_con_ref);

            Client(libio::String_con_ref, libio::String_con_ref, libio::String_con_ref, std::vector<libio::String> &);

            [[nodiscard]] libio::String get_name() const;

            [[nodiscard]] libio::String get_surname() const;

            [[nodiscard]] libio::String get_email() const;

            [[nodiscard]] std::vector<libio::String> get_phone() const;

            [[nodiscard]] libio::String to_string() const;
        };
    }

    class DB_controller {
    private:
        void create_table(libio::String_con_ref, const std::vector<libio::String>&) const;

        [[nodiscard]] pqxx::result transaction(libio::String_con_ref) const;

    public:
        DB_controller() = default;

        ~DB_controller() = default;

        void init_db();

        void add_new_client(const DB_entities::Client &, libio::String_con_ref) const;

        void update_client_phone(libio::String_con_ref, libio::String_con_ref) const; ///for existing client

        void update_client_info(libio::String_con_ref, libio::String_con_ref, libio::String_con_ref,
                                std::optional<std::vector<libio::String>> &) const; ///phones can be optional

        void delete_client_phone(libio::String_con_ref, libio::String_con_ref) const; ///for existing client

        void delete_client_info(libio::String_con_ref, libio::String_con_ref) const;

        void find_client(libio::String_con_ref, libio::String_con_ref,
                         const std::variant<libio::String, std::vector<libio::String>> &) const;
    };
}

#endif
