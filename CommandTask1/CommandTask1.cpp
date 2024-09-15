#include <iostream>
#include <fstream>
#include <string>

class LogCommand {
public:
    virtual ~LogCommand() = default;
    virtual void print(const std::string& message) = 0;
};

class ConsoleLogCommand : public LogCommand {
public:
    void print(const std::string& message) override {
        std::cout << message << std::endl;
    }
};

class FileLogCommand : public LogCommand {
public:
    FileLogCommand(const std::string& filePath) : filePath(filePath) {}

    void print(const std::string& message) override {
        std::ofstream file(filePath, std::ios::app); 
        if (file.is_open()) {
            file << message << std::endl;
            file.close();
        }
        else {
            std::cerr << "Не удалось открыть файл: " << filePath << std::endl;
        }
    }

private:
    std::string filePath;
};

void print(LogCommand& logCommand, const std::string& message) {
    logCommand.print(message);
}

int main() {
    setlocale(LC_ALL, "RU");
    ConsoleLogCommand consoleLog;
    FileLogCommand fileLog("log.txt");

    print(consoleLog, "Сообщение для консоли");

    print(fileLog, "Сообщение для файла");

    return 0;
}
