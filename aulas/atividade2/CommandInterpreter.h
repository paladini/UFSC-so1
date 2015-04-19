// COMPLETAR COM O NOME DA DUPLA
// ACADÊMICO 1: Fernando Paladini
// ACADÊMICO 2: Emmanuel Podesta Junior

#include <cstdlib>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

// COMPLETAR COM OS INCLUDES PARA AS CHAMADAS DE SISTEMA
#include <syscall.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/utsname.h> 
#include <unistd.h>  
#include <fcntl.h> 

using namespace std;

class CommandInterpreter {

public:
    void run() {	
        while (true) {
            //Get a command with parameters
            //and parse it into a vector
            string input;
            vector<string> commands;
            getline(cin, input);
            istringstream iss(input);
            copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(commands));
            string command(commands[0]);
            //Verify the command
            int result;
            if (command.compare("exit") == 0) {
                return;
            } else if (command.compare("creat") == 0) {
                if (commands.size() != 2) {
                    cout << "Incorrect number of arguments!" << endl;
                    continue;
                }
                string aux(commands[1]);
                const char * file_name = aux.c_str();

                // COMPLETAR COM A CHAMADA DE SISTEMA
                result = creat(file_name, O_CREAT);
                cout << result << endl;

            } else if (command.compare("cd") == 0) {
                if (commands.size() != 2) {
                    cout << "Incorrect number of arguments!" << endl;
                    continue;
                }
                string aux(commands[1]);
                const char * path = aux.c_str();

                // COMPLETAR COM A CHAMADA DE SISTEMA
                result = chdir(path);
                cout << result << endl;

            } else if (command.compare("open") == 0) {
                if (commands.size() != 2) {
                    cout << "Incorrect number of arguments!" << endl;
                    continue;
                }
                string aux(commands[1]);
				// COMPLETAR COM A ADAPTAÇÃO DO PARÂMETRO
                const char * path = aux.c_str();
                
                // COMPLETAR COM A CHAMADA DE SISTEMA
                result = open(path, O_RDONLY, S_IRUSR);
                cout << result << endl;

            } else if (command.compare("link") == 0) {
                if (commands.size() != 3) {
                    cout << "Incorrect number of arguments!" << endl;
                    continue;
                }
				// COMPLETAR COM A ADAPTAÇÃO DOS PARÂMETROS
                string aux(commands[1]);
                string auxTwo(commands[2]);

                const char* fileOne = aux.c_str();
                const char* fileTwo = auxTwo.c_str(); 

                // COMPLETAR COM A CHAMADA DE SISTEMA
                result = link(fileOne, fileTwo);
                cout << result << endl;

            } else if (command.compare("write") == 0) {
                if (commands.size() != 2) {
                    cout << "Incorrect number of arguments!" << endl;
                    continue;
                }
				// COMPLETAR COM A ADAPTAÇÃO DO PARÂMETRO
                string aux(commands[1]);
                const char * content = aux.c_str();

                // COMPLETAR COM A CHAMADA DE SISTEMA
                int fd = open("rola.txt", O_RDWR, S_IRWXU);
                write(fd, content, aux.size());
                cout << result << endl;

            } else if (command.compare("mkdir") == 0) {
                if (commands.size() != 2) {
                    cout << "Incorrect number of arguments!" << endl;
                    continue;
                }
				// COMPLETAR COM A ADAPTAÇÃO DO PARÂMETRO
                string aux(commands[1]);
                const char * path = aux.c_str();

                // COMPLETAR COM A CHAMADA DE SISTEMA
                result = mkdir(path, S_IWUSR);
                cout << result << endl;

            } else if (command.compare("unlink") == 0) {
                if (commands.size() != 2) {
                    cout << "Incorrect number of arguments!" << endl;
                    continue;
                }
				// COMPLETAR COM A ADAPTAÇÃO DO PARÂMETRO
                string aux(commands[1]);
                const char * path = aux.c_str();

                // COMPLETAR COM A CHAMADA DE SISTEMA
                unlink(path);
                cout << result << endl;

            } else if (command.compare("uname") == 0) {
                struct utsname u;

                // COMPLETAR COM A CHAMADA DE SISTEMA
                uname(&u);
                cout << u.sysname << " " << u.release << "" << u.version << endl;

            } else if (command.compare("getuid") == 0) {
                // COMPLETAR COM A CHAMADA DE SISTEMA
                result = getuid();
                cout << result << endl;

            } else {
                cout << "Command not found!" << endl;
            }
        }
    }
};

int main() {
    CommandInterpreter ci;
    ci.run();
}
