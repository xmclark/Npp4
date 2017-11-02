#include "P4Config.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include "json.hpp"

p4::P4Config::P4Config(const std::wstring& configPath) : m_configFilePath(configPath + L"npp4.json")
{
}

p4::P4Config::~P4Config()
{
}

const std::string& p4::P4Config::getPort()
{
  return m_port;
}

const std::string& p4::P4Config::getWorkspace()
{
  return m_workspace;
}

const std::string& p4::P4Config::getUser()
{
  return m_user;
}

const std::string& p4::P4Config::getPassword()
{
  return m_password;
}

const std::wstring& p4::P4Config::getConfigFilePath()
{
  return m_configFilePath;
}

// returns true when the config file is loaded correctly
// returns false when there is an input stream error
bool p4::P4Config::load()
{
  using nlohmann::json;

  auto getOrSetConfig = [](json& config, std::string&& key, std::string&& defaultValue) {
    std::string result;
    if (config.find(key) != config.end()) {
      result = config.at(key).get<std::string>();
    }
    else {
      config[key] = defaultValue;
      result = defaultValue;
    }
    return result;
  };

  std::ifstream inputStream(m_configFilePath);
  if (inputStream.good() && inputStream.is_open()) {
    json jConfig;
    try {
      inputStream >> jConfig;
      inputStream.close();
    }
    catch (std::exception&) {
      // most likely invalid json
      inputStream.close();
      return false;
    }

    m_user = getOrSetConfig(jConfig, "user", "user");
    m_password = getOrSetConfig(jConfig, "password", "password");
    m_workspace = getOrSetConfig(jConfig, "workspace", "workspace");
    m_port = getOrSetConfig(jConfig, "port", "perforce:1666");

    std::ofstream outputStream(m_configFilePath);
    outputStream << std::setw(4) << jConfig;
    outputStream.close();
  }
  else {
    inputStream.close();
    json jConfig;
    jConfig["user"] = "user";
    jConfig["password"] = "password";
    jConfig["workspace"] = "workspace";
    jConfig["port"] = "perforce:1666";
    std::ofstream outputStream(m_configFilePath);
    outputStream << std::setw(4) << jConfig;
    outputStream.close();
  }
  return true;
}

// saves the config out to the configuration file
void p4::P4Config::save() 
{
  using nlohmann::json;
  json jConfig;
  jConfig["user"] = m_user;
  jConfig["password"] = m_password;
  jConfig["workspace"] = m_workspace;
  jConfig["port"] = m_port;
  std::ofstream outputStream(m_configFilePath);
  outputStream << std::setw(4) << jConfig;
  outputStream.close();
}