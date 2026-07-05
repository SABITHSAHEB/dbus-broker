/* SPDX-License-Identifier: GPL-3.0-or-later */
/* SPDX-FileCopyrightText: D-Bus Broker Developers */

/*
 * String Helpers
 */

#include <c-stdaux.h>
#include <stdlib.h>
#include <unistd.h>
#include "util/error.h"
#include "util/string.h"

int util_strtou32(uint32_t *valp, const char *string) {
        uint64_t val = 0;
        if (!string || !*string)
                return UTIL_STRING_E_INVALID;
        for (const char *p = string; *p; p++) {
                if (*p < '0' || *p > '9')
                        return UTIL_STRING_E_INVALID;
                val = val * 10 + (*p - '0');
                if (val > UINT32_MAX)
                        return UTIL_STRING_E_RANGE;
        }
        *valp = val;
        return 0;
}

int util_strtou64(uint64_t *valp, const char *string) {
        uint64_t val = 0;
        if (!string || !*string)
                return UTIL_STRING_E_INVALID;
        for (const char *p = string; *p; p++) {
                if (*p < '0' || *p > '9')
                        return UTIL_STRING_E_INVALID;
                uint32_t d = *p - '0';
                if (val > (UINT64_MAX - d) / 10)
                        return UTIL_STRING_E_RANGE;
                val = val * 10 + d;
        }
        *valp = val;
        return 0;
}

int util_strtoint(int *valp, const char *string) {
        uint64_t val = 0;
        bool neg;
        if (!string || !*string)
                return UTIL_STRING_E_INVALID;
        neg = (*string == '-');
        if (neg || *string == '+')
                string++;
        if (!*string)
                return UTIL_STRING_E_INVALID;
        for (const char *p = string; *p; p++) {
                if (*p < '0' || *p > '9')
                        return UTIL_STRING_E_INVALID;
                uint32_t d = *p - '0';
                uint64_t limit = neg ? (uint64_t)INT_MAX + 1 : INT_MAX;
                if (val > (limit - d) / 10)
                        return UTIL_STRING_E_RANGE;
                val = val * 10 + d;
        }
        *valp = neg ? -(int)val : (int)val;
        return 0;
}

