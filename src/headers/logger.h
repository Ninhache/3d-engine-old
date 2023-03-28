#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <chrono>


class Logger
{
public:
    /**
	* @brief Creates a new Logger,
	* The logger is an util class to handle logging events, all the logs events are writed in a file called "log.txt" if the boolean "m_fileLog" equals true, also it can be printed in the console by putting the "m_consoleLog" to true
	* 
	* The class is used in the project but, not enough.
	*/
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

    /**
	* @brief Destroy the logger by closing the log file
	*/
    ~Logger() {
        m_logfile.close();
    }

    /**
    * @brief Log the message into the logfile
    * 
    * @param message - The message to write into the file
    */    
    void log(std::string message) {
        auto now = std::chrono::system_clock::now();
        auto now_c = std::chrono::system_clock::to_time_t(now);
        std::tm *tm = std::localtime(&now_c);

        char buffer[9];
        std::strftime(buffer, sizeof(buffer), "%H:%M:%S", tm);
        
        if (m_fileLog) {
            m_logfile << buffer << " : " << message << std::endl;
        }

        if (m_consoleLog) {
            std::cout << buffer << " : " << message << std::endl;
        }
    }

    /**
    * @brief Change the "m_consoleLog" value
    * 
    * If it's true, the console will print all the logs
    * If it's false, the console won't print
    * 
    * @param value - The new value
    */
    void setConsoleLog(bool value) { this->m_consoleLog = value; }

    /**
    * @brief Change the "setFileLog" value
    * 
    * If it's true, the file will be filled with all the logs
    * If it's false, the file won't be filled
    * 
    * @param value - The new value
    */
    void setFileLog(bool value) { this->m_fileLog = value; }

    private:
        bool m_consoleLog = true;
        bool m_fileLog = true;
        std::ofstream m_logfile;
};

static Logger logger;

#endif