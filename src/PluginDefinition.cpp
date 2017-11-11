// This file is part of the Npp4 plugin for Notepad++.

// MIT License

// Copyright (c) [2017] [mackenzie clark]

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "PluginDefinition.h"
#include "menuCmdID.h"
#include "P4Config.h"
#include "RunCommand.h"
#include <memory>
#include <iostream>
#include <fstream>
#include <array>
#include <algorithm>
#include "Windows.h"

//
// The plugin data that Notepad++ needs
//
FuncItem funcItem[nbFunc];

//
// The data of Notepad++ that you can use in your plugin commands
//
NppData nppData;


// global instance of the P4Config
// any object can easily consume this data
std::unique_ptr<p4::P4Config> g_pConfig;

//
// Initialize your plugin data here
// It will be called while plugin loading   
void pluginInit(HANDLE hModule)
{
}

//
// Here you can do the clean up, save the parameters (if any) for the next session
//
void pluginCleanUp()
{
    g_pConfig->save();
}

//
// Initialization of your plugin commands
// You should fill your plugins commands here
void commandMenuInit()
{

  //--------------------------------------------//
  //-- STEP 3. CUSTOMIZE YOUR PLUGIN COMMANDS --//
  //--------------------------------------------//
  // with function :
  // setCommand(int index,                      // zero based number to indicate the order of command
  //            TCHAR *commandName,             // the command name that you want to see in plugin menu
  //            PFUNCPLUGINCMD functionPointer, // the symbol of function (function pointer) associated with this command. The body should be defined below. See Step 4.
  //            ShortcutKey *shortcut,          // optional. Define a shortcut to trigger this command
  //            bool check0nInit                // optional. Make this menu item be checked visually
  //            );
  setCommand(0, L"Checkout Current File", checkoutOpenedFile, NULL, false);
  setCommand(1, L"Revert Current File", revertOpenedFile, NULL, false);
  setCommand(2, L"Add Current File", addOpenedFile, NULL, false);

  // divider
  setCommand(4, L"Open P4 Config File", openConfig, NULL, false);
  setCommand(5, L"Reload P4 Config", reloadConfig, NULL, false);
  setCommand(6, L"Reset P4 Config File to Default", resetConfig, NULL, false);


  auto configPath = getConfigPath();
  g_pConfig = std::make_unique<p4::P4Config>(configPath);
  g_pConfig->load();
}

//
// Here you can do the clean up (especially for the shortcut)
//
void commandMenuCleanUp()
{
	// Don't forget to deallocate your shortcut here
}


//
// This function help you to initialize your plugin commands
//
bool setCommand(size_t index, wchar_t *cmdName, PFUNCPLUGINCMD pFunc, ShortcutKey *sk, bool check0nInit) 
{
    if (index >= nbFunc)
        return false;

    if (!pFunc)
        return false;

    lstrcpy(funcItem[index]._itemName, cmdName);
    funcItem[index]._pFunc = pFunc;
    funcItem[index]._init2Check = check0nInit;
    funcItem[index]._pShKey = sk;

    return true;
}

//----------------------------------------------//
//-- STEP 4. DEFINE YOUR ASSOCIATED FUNCTIONS --//
//----------------------------------------------//

// 
// get the config path
std::wstring getConfigPath()
{
    wchar_t configDir[MAX_PATH];
    ::SendMessage(nppData._nppHandle, NPPM_GETPLUGINSCONFIGDIR, MAX_PATH, (LPARAM)configDir);
    std::wstring configPath = configDir;
    configPath.shrink_to_fit();
    configPath += L"\\";
    std::transform(configPath.begin(), configPath.end(), configPath.begin(), ::tolower);
    return configPath;
}

bool openDocument(std::wstring& path)
{
  std::wifstream inputStream(path);
  if(inputStream.good()) {
    ::SendMessage(nppData._nppHandle, NPPM_DOOPEN, 0, reinterpret_cast<LPARAM>(path.c_str()));
    return true;
  }
  else {
    // error, file does not exist
    return false;
  }
}

void openNewDocument()
{
    // Open a new document
    ::SendMessage(nppData._nppHandle, NPPM_MENUCOMMAND, 0, IDM_FILE_NEW);
}

void writeToCurrentDocument()
{
    // Get the current scintilla
    int which = -1;
    ::SendMessage(nppData._nppHandle, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&which);

    if (which == -1)
        return;
    
    HWND curScintilla = (which == 0)
      ? nppData._scintillaMainHandle
      : nppData._scintillaSecondHandle;

    // Scintilla control has no Unicode mode, so we use (char *) here
    ::SendMessage(curScintilla, SCI_SETTEXT, 0, (LPARAM)"Hello, Notepad++!");
}

// resets the config file to default
void resetConfig()
{
  g_pConfig->resetToDefault();
}

// open the plugins config file
void openConfig()
{
  auto npp4ConfigPath = g_pConfig->getConfigFilePath();
  bool fileExists = openDocument(npp4ConfigPath);
  (void)fileExists;
}

// reload the configuration using P4Config
void reloadConfig()
{
  bool loaded = g_pConfig->load();
  if (!loaded) {
    // open the config file
    auto configPath = g_pConfig->getConfigFilePath();
    openDocument(configPath);
    // show a message box
    ::MessageBox(NULL, L"Failed to parse JSON. Please fix P4 config file or reset it.", L"JSON Error", MB_OK);
  }
}

// A file has just been saved
void onFileSaved()
{
  auto currentFilePath = getCurrentFilePath();
  auto configPath = g_pConfig->getConfigFilePath();
  if (currentFilePath == configPath) {
    // config file has just been saved
    reloadConfig();
  }
}

// get the current file path
std::wstring getCurrentFilePath()
{
  std::array<wchar_t, MAX_PATH> currentFilePath;
  ::SendMessage(nppData._nppHandle, NPPM_GETFULLCURRENTPATH, MAX_PATH, reinterpret_cast<LPARAM>(currentFilePath.data()));
  std::wstring sCurrentFilePath(currentFilePath.data());
  sCurrentFilePath.shrink_to_fit();
  // lower case for consistent paths - this is windows
  std::transform(sCurrentFilePath.begin(), sCurrentFilePath.end(), sCurrentFilePath.begin(), ::tolower);
  return sCurrentFilePath;
}

// add the currently opened file to the default changelist 
void checkoutOpenedFile()
{
  auto wsCurrentFilePath = getCurrentFilePath();
  char* szTo = new char[wsCurrentFilePath.length() + 1];
  szTo[wsCurrentFilePath.size()] = '\0';
  WideCharToMultiByte(CP_ACP, 0, wsCurrentFilePath.c_str(), -1, szTo, static_cast<int>(wsCurrentFilePath.size()), NULL, NULL);
  std::string sCurrentFilePath(szTo);

  p4::runCommand(g_pConfig, [&sCurrentFilePath]() {
    return std::make_pair("edit", std::vector<std::string>{"-c", "default", sCurrentFilePath});
  });
}

// revert the currently opened file to your depot
void revertOpenedFile()
{
  auto wsCurrentFilePath = getCurrentFilePath();
  char* szTo = new char[wsCurrentFilePath.length() + 1];
  szTo[wsCurrentFilePath.size()] = '\0';
  WideCharToMultiByte(CP_ACP, 0, wsCurrentFilePath.c_str(), -1, szTo, static_cast<int>(wsCurrentFilePath.size()), NULL, NULL);
  std::string sCurrentFilePath(szTo);

  p4::runCommand(g_pConfig, [&sCurrentFilePath]() {
    return std::make_pair("revert", std::vector<std::string>{"-a", "-c", "default", sCurrentFilePath});
  });
}

void addOpenedFile()
{
  auto wsCurrentFilePath = getCurrentFilePath();
  char* szTo = new char[wsCurrentFilePath.length() + 1];
  szTo[wsCurrentFilePath.size()] = '\0';
  WideCharToMultiByte(CP_ACP, 0, wsCurrentFilePath.c_str(), -1, szTo, static_cast<int>(wsCurrentFilePath.size()), NULL, NULL);
  std::string sCurrentFilePath(szTo);

  p4::runCommand(g_pConfig, [&sCurrentFilePath]() {
    return std::make_pair("add", std::vector<std::string>{"-d", "-c", "default", sCurrentFilePath});
  });
}
