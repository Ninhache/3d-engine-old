#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <chrono>


class Logger {
    public:
        Logger() {
            m_logfile.open("log.txt", std::ios::out | std::ios::trunc);
            if (!m_logfile.is_open()) {
                std::cerr << "Error opening log file" << std::endl;
            }

            auto now = std::chrono::system_clock::now();
            auto now_c = std::chrono::system_clock::to_time_t(now);
            std::tm *tm = std::localtime(&now_c);

            char buffer[9];
            std::strftime(buffer, sizeof(buffer), "%H:%M:%S", tm);
            m_logfile << "[CORE] App started at : " << buffer << std::endl;
        }

        ~Logger() {
            m_logfile.close();
        }

        void log(const std::string& message) {
            auto now = std::chrono::system_clock::now();
            auto now_c = std::chrono::system_clock::to_time_t(now);
            std::tm *tm = std::localtime(&now_c);

            char buffer[9];
            std::strftime(buffer, sizeof(buffer), "%H:%M:%S", tm);
            
            if (m_fileLog) m_logfile << buffer << " : " << message << std::endl;
            if (m_consoleLog) std::cout << buffer << " : " << message << std::endl;
        }

        void setConsoleLog(const bool& value) { m_consoleLog = value; }
        void setFileLog(const bool& value) { m_fileLog = value; }



    private:
        bool m_consoleLog = true, m_fileLog = true;
        std::ofstream m_logfile;
};

static Logger logger;

#endif