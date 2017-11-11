#pragma once
#include <memory>
#include <string>
#include <vector>
#include <functional>


namespace p4 {

  class P4Config;

  using Command = std::tuple<std::string, std::vector<std::string>>;

  std::string runCommand(std::unique_ptr<P4Config>& config, std::function<Command()> command);

}