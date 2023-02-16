#pragma once

#include <fstream>
#include <string>
#include <mutex>

class Logger
{
public:
    static Logger &getInstance()
    {
        static Logger instance;
        return instance;
    }

    void __fastcall OpenLogFile(const std::string &FN);
    void CloseLogFile();

    void __fastcall WriteToLog(const std::string &str, const std::string &prefix = {});
    void __fastcall WriteToLog(const std::string &str, int n, const std::string &prefix = {});
    void __fastcall WriteToLog(const std::string &str, double d, const std::string &prefix = {});

private:
    Logger() { }
    Logger(const Logger &root) = delete;
    Logger &operator=(const Logger &) = delete;

    Logger(Logger &&root) = delete;
    Logger &operator=(Logger &&) = delete;

    std::ofstream m_logOut;
    static std::mutex s_mutex;

    static std::string GetCurDateTime();
};
