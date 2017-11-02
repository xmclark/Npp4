#pragma once

#include <string>

namespace p4 {

enum class LoadResultEnum {



};

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