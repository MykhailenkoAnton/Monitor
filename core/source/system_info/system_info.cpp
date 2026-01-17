#include <QtCore/QtSystemDetection>

#ifdef Q_OS_WIN
#include "core/include/system_info/windows/system_info_windows.h"
#elif defined(Q_OS_LINUX)
// linux header
#elif defined(Q_OS_MAC)
// macOS header
#endif

namespace core
{
SystemInfoBase& SystemInfoBase::instance()
{
#ifdef Q_OS_WIN
    static SystemInfoWindowsImpl singelton;
#elif defined(Q_OS_LINUX)
#elif defined(Q_OS_MAC)
#endif

    return singelton;
}

SystemInfoBase::SystemInfoBase() {}

SystemInfoBase::~SystemInfoBase() {}
}  // namespace core
