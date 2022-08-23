///
/// Developed by mrybs
///
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>
#include <dirent.h>
#include <vector>

struct stat sb;
struct stat st = {0};

#define print(text) std::cout<<text

void newCommand(int argc, char* argv[]);
void renameCommand(int argc, char* argv[]);
void importCommand(int argc, char* argv[]);
void installCommand(int argc, char* argv[]);
void upgradeCommand(int argc, char* argv[]);
void helpCommand();
std::string getUpgradeLink();
bool dirExist(const char* path);
bool fileExist(const char* path);
void mkdir(const char* path);
void remdir(const char* path);

int main(int argc, char* argv[], char* envp[]){
  char** env;
  std::string currentDirectory = "";
  for (env = envp; *env != 0; env++){
    char* thisEnv = *env;
    if(thisEnv[0]=='P' &&
        thisEnv[1]=='W' &&
        thisEnv[2]=='D' &&
        thisEnv[3]=='='){
      for(int i = 4; i < strlen(thisEnv); i++){
        currentDirectory += thisEnv[i];
      }
    }
  }
  currentDirectory += '\0';
  switch(argc){
  case 1:
    helpCommand();
    break;
  case 2:
  case 3:
    if (strcmp(argv[1], "new") == 0) {
      newCommand(argc, argv);
    }
    else if (strcmp(argv[1], "rename") == 0)
      renameCommand(argc, argv);
    else if (strcmp(argv[1], "import") == 0)
      importCommand(argc, argv);
    else if (strcmp(argv[1], "install") == 0)
      installCommand(argc, argv);
    else if (strcmp(argv[1], "upgrade") == 0)
      upgradeCommand(argc, argv);
    else if (strcmp(argv[1], "help") == 0)
      helpCommand();
    else
      helpCommand();

    break;
  }
  return 0;
}

void newCommand(int argc, char* argv[]){
  if((dirExist("/usr/share/mcurses")
          && dirExist("/usr/share/mcurses/repo")
          && dirExist("/usr/share/mcurses/projects")
          && dirExist("/usr/share/mcurses/modules")
          && dirExist("/usr/share/mcurses/widgets"))) {
    print("MCurses is not installed!\nInstall it using\n\tmcurses install\n");

    return;
  }

}
void renameCommand(int argc, char* argv[]){

}
void importCommand(int argc, char* argv[]){

}
void installCommand(int argc, char* argv[]){
  bool installing = false;
  if(argc == 2){
    print("Are you sure to install MCurses engine? Needed git and internet connection [y/n]\n>>> ");
    std::string answer;
    std::cin >> answer;
    if(answer != "Y" && answer != "y" && answer != "yes" && answer != "Yes" && answer != "YES" && answer != "YEs"
        && answer != "yES" && answer != "yeS" && answer != "yEs" && answer != "YeS" && answer != "YEs") return;
    installing = true;
  }
  if((argc == 3 && strcmp(argv[2], "--noconfirm") == 0) || installing){
    remdir("/usr/share/mcurses");
    mkdir("/usr/share/mcurses");
    mkdir("/usr/share/mcurses/projects");
    mkdir("/usr/share/mcurses/modules");
    mkdir("/usr/share/mcurses/widgets");
    mkdir("/usr/share/mcurses/repo");
    mkdir("/usr/share/mcurses/tmp");
    if(!fileExist("/usr/bin/git")){
      print("Git is not installed!\n"<<
            "Install it using your package manager\n");
      return;
    }
    system(("cd /usr/share/mcurses/repo && git clone " + getUpgradeLink() + " >> /dev/null 2>>/dev/null").c_str());
    system("mv /usr/share/mcurses/repo/* /usr/share/mcurses/tmp/ >> /dev/null 2>>/dev/null");
    system("cd /usr/share/mcurses/repo && mv */* ../repo/ >> /dev/null 2>>/dev/null");
    remdir("/usr/share/mcurses/tmp");
    system("cp -r /usr/share/mcurses/repo/projects /usr/share/mcurses/");
    system("cp -r /usr/share/mcurses/repo/widgets /usr/share/mcurses/");
    system("cp -r /usr/share/mcurses/repo/modules /usr/share/mcurses/");
  }
}
void upgradeCommand(int argc, char* argv[]){
  bool upgrading = false;
  if(argc == 2) {
    print("Are you sure to upgrade MCurses engine? Needed git and internet connection [y/n]\n>>> ");
    std::string answer;
    std::cin >> answer;
    if (answer != "Y" && answer != "y" && answer != "yes" && answer != "Yes" &&
        answer != "YES" && answer != "YEs" && answer != "yES" &&
        answer != "yeS" && answer != "yEs" && answer != "YeS" &&
        answer != "YEs")
      return;
    upgrading = true;
  }
  if((argc == 3 && strcmp(argv[2], "--noconfirm") == 0) || upgrading) {
    mkdir("/usr/share/mcurses/tmp");
    mkdir("/usr/share/mcurses/repo");
    if (!fileExist("/usr/bin/git")) {
      print("Git is not installed!\n"
            << "Install it using your package manager\n");
      return;
    }
    int result = system(("cd /usr/share/mcurses/repo && git clone " +
                         getUpgradeLink() + " >> /dev/null 2>>/dev/null")
                            .c_str());
    if (result != 0) {
      print("Failed!\n");
      return;
    }
    system("mv /usr/share/mcurses/repo/* /usr/share/mcurses/tmp/ >> /dev/null 2>>/dev/null");
    system("cd /usr/share/mcurses/repo && mv */* ../repo/ >> /dev/null 2>>/dev/null");
    remdir("/usr/share/mcurses/tmp");
    remdir("/usr/share/mcurses/projects");
    remdir("/usr/share/mcurses/widgets");
    remdir("/usr/share/mcurses/modules");
    mkdir("/usr/share/mcurses/projects");
    mkdir("/usr/share/mcurses/widgets");
    mkdir("/usr/share/mcurses/modules");
    result =
        system("cp -r /usr/share/mcurses/repo/projects /usr/share/mcurses/");
    if (result != 0) {
      print("Failed!\n");
      return;
    }
    result =
        system("cp -r /usr/share/mcurses/repo/widgets /usr/share/mcurses/");
    if (result != 0) {
      print("Failed!\n");
      return;
    }
    result =
        system("cp -r /usr/share/mcurses/repo/modules /usr/share/mcurses/");
    if (result != 0) {
      print("Failed!\n");
      return;
    }
  }
}
void helpCommand(){
  print("Usage:\n"<<
        "mcurses <arguments>\n"<<
        "\t<arguments>:\n"<<
        "\t\tnew <type> <name> <arguments>- creates new project\n"<<
        "\t\t<arguments>:\n"<<
        "\t\t\t--list - displays a list of all possible project types\n"<<
        "\t\trename <newname> - renames a project\n"<<
        "\t\timport <module/widget> <arguments>- imports a module or a widget\n"<<
        "\t\t<arguments>:\n"<<
        "\t\t\t--list - displays a list of all possible modules and widgets\n"<<
        "\t\tinstall <arguments> - installs a MCurses engine\n"<<
        "\t\t<arguments>:\n"<<
        "\t\t\t--noconfirm - install MCurses without confirmation\n"
        "\t\tupgrade <arguments>- upgrade this program and a MCurses engine(only root)\n"<<
        "\t\t<arguments>:\n"<<
        "\t\t\t--chrepo <link> - changes the repository link with upgrades of MCurses\n"<<
        "\t\t\t--noconfirm - upgrade without confirmation\n"<<
        "\t\thelp - displays this text\n\n");
}

std::string getUpgradeLink(){
  return "https://github.com/mrybs/mcurses.git";
}

bool dirExist(const char* path){
  int result = system((std::string(path)+"/ >> /dev/null 2>/dev/null").c_str());
  if (result == 0) return true;
  return false;
}
bool fileExist(const char* path){
  std::ifstream fs(path);
  return !fs.fail();
}
void mkdir(const char* path){
  if(!dirExist(path)) system(("mkdir " + std::string(path) + " >> /dev/null 2>>/dev/null").c_str());
}
void remdir(const char* path){
  if(dirExist(path)) system(("rm -r " + std::string(path) + " >> /dev/null 2>>/dev/null").c_str());
}