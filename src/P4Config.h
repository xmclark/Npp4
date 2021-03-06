#pragma once

#include <string>

namespace p4 {

// A configuration class for a P4 client
// This class maintains reference to the config file 
// The class unserializes json and stores the config in memory for use by a p4 client
// The class can easily serialize when application has been closed

class P4Config {
public:

  P4Config() = delete;
  P4Config(const std::wstring& configPath);
  ~P4Config();

  const std::string& getPort();
  const std::string& getWorkspace();
  const std::string& getUser();
  const std::string& getPassword();

  const std::wstring& getConfigFilePath();

  void resetToDefault();
  bool load();
  void save();

private:
  std::wstring m_configFilePath;

  std::string m_user;
  std::string m_workspace;
  std::string m_port;
  std::string m_password;
};

}