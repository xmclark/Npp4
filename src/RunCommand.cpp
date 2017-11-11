#include "RunCommand.h"
#include <vector>
#include <algorithm>
#include "P4Config.h"
#include "p4/clientapi.h"

namespace p4 {


// Runs the designated command that is run returned by the lambda
// The command is composed of a p4 command and a list of additional arguments
// The string returned is an error string. It will be empty if no error occurs. 

std::string runCommand(std::unique_ptr<P4Config>& config, std::function<Command()> command)
{
  using namespace std::string_literals;
  ClientApi clientApi;
  ClientUser clientUser;
  Error e;

  if (e.Test()) {
    return "An error has occured before the connection was create."s;
  }

  clientApi.SetUser(config->getUser().c_str());
  clientApi.SetPassword(config->getPassword().c_str());
  clientApi.SetClient(config->getWorkspace().c_str());
  clientApi.SetPort(config->getPort().c_str());

  clientApi.Init(&e);
  if (e.Test()) {
    return "An error occured during client api initialization."s;
  }

  auto commandResult = command();
  auto primaryCommand = std::get<0>(commandResult);
  auto arguments = std::get<1>(commandResult);

  if (primaryCommand.empty()) {
    return "Empty command."s;
  }

  if (!arguments.empty()) {
    std::vector<char*> cArguments;
    // copy the strings into the char* vectors
    std::transform(arguments.begin(), arguments.end(), std::back_inserter(cArguments), [](const std::string& arg) -> char* {
      char* pArg = new char[arg.size() + 1];
      strcpy_s(pArg, arg.size() + 1, arg.c_str());
      return pArg;
    });
    clientApi.SetArgv(cArguments.size(), &cArguments[0]);
  }

  // Run the command
  clientApi.Run(primaryCommand.c_str(), &clientUser);

  clientApi.Final(&e);

  if (e.Test()) {
    return "An error occured closing the connection."s;
  }

  return ""s;
}

}
