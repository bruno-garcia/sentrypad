#if defined(SENTRY_CRASHPAD)
#include "crashpad_wrapper.hpp"
#elif defined(SENTRY_BREAKPAD)
#include "breakpad_wrapper.hpp"
#endif
#include "sentry.h"
#include <string>

#include <msgpack.hpp>
#include <iostream>
#include <fstream>
#include <sstream>

#if defined(SENTRY_CRASHPAD)
using namespace sentry::crashpad;
#elif defined(SENTRY_BREAKPAD)
using namespace sentry::breakpad;
#endif

using namespace std;

typedef struct sentry_event_s
{
    const char *release;
    const char *environment;
} sentry_event_t;

void write()
{
    // msgpack::type::tuple<int, bool, std::string> src(1, true, "example");
    sentry_event_t evt;
    evt.release = "21345678";
    evt.environment = "Production";

    std::ofstream myfile;
    myfile.open("example.txt");

    // serialize the object into the buffer.
    // any classes that implements write(const char*,size_t) can be a buffer.
    std::stringstream buffer;
    msgpack::pack(myfile, evt);

    myfile.close();
    // send the buffer ...
    buffer.seekg(0);
}

int sentry_init(const sentry_options_t *options)
{
    auto err = init(options);
    if (err != 0)
    {
        return err;
    }

    if (options->environment != nullptr)
    {
        set_annotation("sentry[environment]", options->environment);
    }

    if (options->release != nullptr)
    {
        set_annotation("sentry[release]", options->release);
    }

    if (options->dist != nullptr)
    {
        set_annotation("sentry[dist]", options->dist);
    }

    write();

    return SENTRY_ERROR_NULL_ARGUMENT;
}

void sentry_options_init(sentry_options_t *options)
{
}

// int sentry_add_breadcrumb(sentry_breadcrumb_t *breadcrumb);
// int sentry_push_scope();
// int sentry_pop_scope();
int sentry_set_user(sentry_user_t *user);
int sentry_remove_user();
int sentry_set_fingerprint(const char **fingerprint, size_t len);
int sentry_remove_fingerprint();
int sentry_set_transaction(const char *transaction);
int sentry_remove_transaction();
int sentry_set_level(enum sentry_level_t level)
{
}

int sentry_set_tag(const char *key, const char *value)
{
    std::string string_key(key);
    std::string final_key = "sentry[tags][" + string_key + "]";
    return set_annotation(final_key.c_str(), value);
}

int sentry_remove_tag(const char *key)
{
    std::string string_key(key);
    std::string final_key = "sentry[tags][" + string_key + "]";
    return remove_annotation(final_key.c_str());
}

int sentry_set_extra(const char *key, const char *value)
{
    std::string string_key(key);
    std::string final_key = "sentry[extra][" + string_key + "]";
    return set_annotation(final_key.c_str(), value);
}

int sentry_remove_extra(const char *key)
{
    std::string string_key(key);
    std::string final_key = "sentry[extra][" + string_key + "]";
    return remove_annotation(final_key.c_str());
}

int sentry_set_release(const char *release)
{
    return set_annotation("sentry[release]", release);
}

int sentry_remove_release()
{
    return remove_annotation("sentry[release]");
}
