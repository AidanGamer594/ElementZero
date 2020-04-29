#pragma once

#include "pch.h"

struct Settings {
  struct Commands {
    bool transferserver = true;
    bool customname     = true;
    struct Teleport {
      bool enabled = true;
      int timeout  = 30;

      template <typename IO> static inline bool io(IO f, Teleport &self, YAML::Node &node) {
        return f(self.enabled, node["enabled"]) && f(self.timeout, node["timeout"]);
      }
    } teleport;
    bool home = true;
    bool warp = true;

    template <typename IO> static inline bool io(IO f, Commands &commands, YAML::Node &node) {
      return f(commands.transferserver, node["transferserver"]) && f(commands.customname, node["custom-name"]) &&
             f(commands.teleport, node["tpa"]) && f(commands.home, node["home"]) && f(commands.warp, node["warp"]);
      return true;
    }
  } commands;
  std::string database      = "essentials.db";
  std::string worldDatabase = "essentials.db";

  template <typename IO> static inline bool io(IO f, Settings &settings, YAML::Node &node) {
    return f(settings.commands, node["commands"]) && f(settings.database, node["database"]) &&
           f(settings.worldDatabase, node["world-database"]);
  }
};

extern Settings settings;

void registerTransferServer(CommandRegistry *registry);
void registerCustomName(CommandRegistry *registry);
void registerTeleport(CommandRegistry *registry);
void registerHome(CommandRegistry *registry);
void registerWarp(CommandRegistry *registry);

void initDatabase();
void initWorldDatabase(std::filesystem::path const &);

extern std::unique_ptr<SQLite::Database> database;
extern std::unique_ptr<SQLite::Database> world_database;