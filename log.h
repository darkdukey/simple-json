class Log
{
public:

    enum Level { Debug, Info, Warning, Error};

    static std::ostream& GetStream() { return std::cout; }
    static bool IsLevelActive(Level l) { return true; }
};

#ifndef NO_LOG
#define LOGE(M) do { if (Log::IsLevelActive(Log::Error))   (Log::GetStream() << "ERR: " << M << "\n"); } while (false)
#define LOGW(M) do { if (Log::IsLevelActive(Log::Warning)) (Log::GetStream() << "WRN: " << M << "\n"); } while (false)
#define LOGI(M) do { if (Log::IsLevelActive(Log::Info))    (Log::GetStream() << "INF: " << M << "\n"); } while (false)
#define LOGD(M)  do { if (Log::IsLevelActive(Log::Debug))   (Log::GetStream() << M << "\n"); } while (false)
#else
#define LOGE(M)
#define LOGW(M)
#define LOGI(M)
#define LOGD(M)
#endif