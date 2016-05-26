/*
 * Copyright (C) 2016 Simon Fels <morphis@gravedo.de>
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 3, as published
 * by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranties of
 * MERCHANTABILITY, SATISFACTORY QUALITY, or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef ANBOX_UTILS_H_
#define ANBOX_UTILS_H_

#include <boost/format.hpp>

#include <vector>
#include <string>

namespace anbox {
namespace utils {

std::vector<std::string> collect_arguments(int argc, char **argv);

std::string read_file_if_exists_or_throw(const std::string &file_path);

bool write_to_file(const std::string &file_path, const std::string &content = "");
int write_to_fd(int fd, const char *content, ssize_t len);
int write_file_at(int dirfd, const char *path, const char *content);

bool string_starts_with(const std::string &text, const std::string &prefix);

std::string hex_dump(const uint8_t *data, uint32_t size);

template<typename... Types>
static std::string string_format(const std::string& fmt_str, Types&&... args);
} // namespace utils
} // namespace anbox

namespace impl {
// Base case, just return the passed in boost::format instance.
inline boost::format& string_format(boost::format& f)
{
    return f;
}
// Sprintf recursively walks the parameter pack at compile time.
template <typename Head, typename... Tail>
inline boost::format& string_format(boost::format& f, Head const& head, Tail&&... tail) {
    return string_format(f % head, std::forward<Tail>(tail)...);
}
} // namespace impl

template <typename... Types>
inline std::string anbox::utils::string_format(const std::string& format, Types&&... args) {
    boost::format f(format);
    return impl::string_format(f, std::forward<Types>(args)...).str();
}


#endif