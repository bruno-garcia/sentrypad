#if defined(SENTRY_BREAKPAD)
#include <stdio.h>
#include <map>
#include <string>
#include <vector>
#include <atomic>

#include "sentry.h"
#if defined(WINDOWS)
#include "client/windows/handler/exception_handler.h"
#elif defined(MAC)
#include "client/mac/handler/exception_handler.h"
#include "client/mac/crash_generation/crash_generation_client.h"
#include "client/mac/Framework/Breakpad.h"
#endif

// using namespace breakpad;

namespace sentry
{
namespace breakpad
{

int init(const sentry_options_t *options)
{
#if defined(WINDOWS)
    // https://chromium.googlesource.com/breakpad/breakpad/+/master/docs/windows_client_integration.md
    auto handler = new ExceptionHandler(const wstring &dump_path,
                                        FilterCallback filter,
                                        MinidumpCallback callback,
                                        void *callback_context,
                                        int handler_types,
                                        MINIDUMP_TYPE dump_type,
                                        const wchar_t *pipe_name,
                                        const CustomClientInfo *custom_info);
#elif defined(MAC)
    // https://chromium.googlesource.com/breakpad/breakpad/+/master/docs/mac_breakpad_starter_guide.md
    auto handler = new ExceptionHandler(const string &dump_path,
                                        FilterCallback filter,
                                        MinidumpCallback callback,
                                        void *callback_context,
                                        int handler_types,
                                        MINIDUMP_TYPE dump_type,
                                        const wchar_t *pipe_name,
                                        const CustomClientInfo *custom_info);
#endif
    return SENTRY_ERROR_SUCCESS;
}

int set_annotation(const char *key, const char *value)
{
    if (key == nullptr || value == nullptr)
    {
        return SENTRY_ERROR_NULL_ARGUMENT;
    }
    return SENTRY_ERROR_SUCCESS;
} // namespace crashpad

int remove_annotation(const char *key)
{
    if (key == nullptr)
    {
        return SENTRY_ERROR_NULL_ARGUMENT;
    }
    return SENTRY_ERROR_SUCCESS;
}

} // namespace breakpad
} // namespace sentry
#endif
