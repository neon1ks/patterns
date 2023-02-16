#include "Logger.h"

std::mutex Logger::s_mutex;

void __fastcall Logger::OpenLogFile(const std::string &FN)
{
    CloseLogFile(); // Уже содержит lock_guard
    std::lock_guard<std::mutex> lock(s_mutex);
    m_logOut.open(FN, std::ios_base::out);
}

void Logger::CloseLogFile()
{
    std::lock_guard<std::mutex> lock(s_mutex);
    if (m_logOut.is_open()) {
        m_logOut.close();
    }
}

void __fastcall Logger::WriteToLog(const std::string &str, const std::string &prefix /* = {} */)
{
    std::lock_guard<std::mutex> lock(s_mutex);
    if (m_logOut.is_open()) {
        m_logOut << prefix << GetCurDateTime() << " - " << str << std::endl;
    }
}

void __fastcall Logger::WriteToLog(const std::string &str, int n,
                                   const std::string &prefix /* = {} */)
{
    std::lock_guard<std::mutex> lock(s_mutex);
    if (m_logOut.is_open()) {
        m_logOut << prefix << GetCurDateTime() << " - " << str << n << std::endl;
    }
}

void __fastcall Logger::WriteToLog(const std::string &str, double d,
                                   const std::string &prefix /* = {} */)
{
    std::lock_guard<std::mutex> lock(s_mutex);
    if (m_logOut.is_open()) {
        m_logOut << prefix << GetCurDateTime() << " - " << str << d << std::endl;
    }
}

std::string Logger::GetCurDateTime()
{
    auto cur = std::chrono::system_clock::now();
    time_t time = std::chrono::system_clock::to_time_t(cur);
    char buf[64] = { 0 };
    ctime_s(buf, 64, &time);
    buf[strlen(buf) - 1] = '\0';
    return { buf };
}
