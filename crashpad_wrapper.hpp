#include "sentry.h"

namespace sentry
{
namespace crashpad
{
int init(const sentry_options_t *options);
int set_annotation(const char *key, const char *value);
int remove_annotation(const char *key);
} // namespace crashpad
} // namespace sentry
