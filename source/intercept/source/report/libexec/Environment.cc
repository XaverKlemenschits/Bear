/*  Copyright (C) 2012-2021 by László Nagy
    This file is part of Bear.

    Bear is a tool to generate compilation database for clang tooling.

    Bear is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Bear is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "report/libexec/Environment.h"
#include "report/libexec/Array.h"

namespace el::env {

    const char* get_env_value(const char **envp, const char *const key) noexcept
    {
        const size_t key_size = el::array::length(key);

        for (const char** it = envp; *it != nullptr; ++it) {
            const char* const current = *it;
            // Is the key a prefix of the pointed string?
            if (!el::array::equal_n(key, current, key_size))
                continue;
            // Is the next character is the equal sign?
            if (current[key_size] != '=')
                continue;
            // It must be the one! Calculate the address of the value.
            return current + key_size + 1;
        }
        return nullptr;
    }
}
