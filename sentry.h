#ifndef SENTRY_H
#define SENTRY_H

#include <stddef.h>
#ifdef __cplusplus
extern "C"
{
#endif

    enum sentry_error_t
    {
        SENTRY_SUCCESS,
        SENTRY_ERROR_NULL_ARGUMENT,
        SENTRY_ERROR_HANDLER_STARTUP_FAIL,
        SENTRY_ERROR_NO_DSN,
        SENTRY_ERROR_NO_MINIDUMP_URL
    };

    typedef struct sentry_options_s
    {
        // Unified API
        const char *dsn;
        const char *release;
        const char *environment;
        const char *dist;
        int debug;
        // Crashpad
        const char *handler_path;
        const char *database_path;
        // TODO hook/callback to crashpad configuration object.
        // Breakpad
        // TODO: whatever breakpad needs
    } sentry_options_t;

    typedef struct sentry_breadcrumb_s
    {

    } sentry_breadcrumb_t;

    typedef struct sentry_user_s
    {
        const char *username;
        const char *email;
        const char *id;
        const char *ip_address;
    } sentry_user_t;

    enum sentry_level_t
    {
        SENTRY_LEVEL_DEBUG = 0,
        SENTRY_LEVEL_INFO = 1,
        SENTRY_LEVEL_WARNING = 2,
        SENTRY_LEVEL_ERROR = 3,
    };

    // Unified API
    int sentry_init(const sentry_options_t *options);
    int sentry_add_breadcrumb(sentry_breadcrumb_t *breadcrumb);
    int sentry_push_scope();
    int sentry_pop_scope();
    int sentry_set_user(sentry_user_t *user);
    int sentry_remove_user();
    int sentry_set_tag(const char *key, const char *value);
    int sentry_remove_tag(const char *key);
    int sentry_set_extra(const char *key, const char *value);
    int sentry_remove_extra(const char *key);
    int sentry_set_release(const char *release);
    int sentry_remove_release();
    int sentry_set_fingerprint(const char **fingerprint, size_t len);
    int sentry_remove_fingerprint();
    int sentry_set_transaction(const char *transaction);
    int sentry_remove_transaction();
    int sentry_set_level(enum sentry_level_t level);

    // Sentrypad custom API
    int sentry_shutdown(void);
    int sentry_attach_file_by_path(const char *path);
    int sentry_attach_file_with_contents(const char *filename, const char *buf, size_t len);
    int sentry_capture_minidump(const char *optional_message);
    void sentry_options_init(sentry_options_t *options);

#ifdef __cplusplus
}
#endif
#endif
