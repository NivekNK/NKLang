#include "nkpch.h"

#include "system/file_system.h"
#include <filesystem>

#define __STDC_LIB_EXT1__
#define __STDC_WANT_LIB_EXT1__ 1
#include <stdio.h>

namespace nk {
    File::File(const FileCreateInfo& info)
        : path{info.path}, file_mode{info.mode} {
        // constexpr const char* encodings[] = {
        //     ", css=UTF-8",
        //     ", css=UNICODE",
        //     ", css=UTF-16LE",
        //     "",
        // };
        constexpr const char* encodings[] = {
            "",
            "",
            "",
            "",
        };

        const char* encoding = encodings[static_cast<u8>(info.encoding)];
        std::string mode = "";
        switch (file_mode) {
            case FileMode::Read: {
                if (!exists(path))
                    return;
                mode = std::format("r{}", encoding);
                break;
            }
            case FileMode::Write: {
                if (!exists(path)) {
                    mode = std::format("w{}", encoding);
                } else {
                    mode = std::format("r+{}", encoding);
                }
                break;
            }
            case FileMode::ReadAndWrite: {
                if (!exists(path)) {
                    mode = std::format("w+{}", encoding);
                } else {
                    mode = std::format("r+{}", encoding);
                }
                break;
            }
        }
        std::filesystem::create_directories(path.parent_path());
        fopen_s(&file, path.string().c_str(), mode.c_str());
    }
    File::~File() { close(); }

    bool File::exists(const Path& path) {
        return std::filesystem::exists(path);
    }

    Ref<File> File::open(
        std::string_view filepath,
        const FileMode mode,
        const FileEncoding encoding
    ) {
        return CreateRef<File>(FileCreateInfo{
            .path = Path{filepath},
            .mode = mode,
            .encoding = encoding,
        });
    }

    Scope<File> File::open_scope(
        std::string_view filepath,
        const FileMode mode,
        const FileEncoding encoding
    ) {
        auto file = CreateScope<File>(FileCreateInfo{
            .path = Path{filepath},
            .mode = mode,
            .encoding = encoding,
        });
        return std::move(file);
    }

    void File::close() { fclose(file); }

    bool File::is_open() const { return file != nullptr; }

    u32 File::file_length() const {
        u32 length;
        u32 current_position = ftell(file);

        fseek(file, 0, SEEK_END);
        length = ftell(file);
        fseek(file, current_position, SEEK_SET);

        return length;
    }

    bool File::read_line(std::string& line, const u16 line_length) {
        if (file_mode != FileMode::Read && file_mode != FileMode::ReadAndWrite)
            return false;

        if (!is_open())
            return false;

        if (line_length == 0)
            return false;

        char buffer[line_length];
        if (fgets(buffer, sizeof(buffer), file) != NULL) {
            size_t length = strlen(buffer);
            if (length > 0) {
                if (buffer[length - 2] == '\r' && buffer[length - 1] == '\n') {
                    buffer[length - 2] = '\0';
                    length -= 2;
                } else if (buffer[length - 1] == '\n') {
                    buffer[length - 1] = '\0';
                    length--;
                }
                line = buffer;
                return true;
            }

            line = "";
            return true;
        }

        return false;
    }

    std::vector<std::string> File::read_all_lines(const u16 line_length) {
        std::vector<std::string> lines;
        std::string line;
        while (read_line(line, line_length)) {
            lines.push_back(line);
        }
        return lines;
    }

    std::vector<char> File::read_all_bytes() {
        if (file_mode != FileMode::Read && file_mode != FileMode::ReadAndWrite)
            return std::vector<char>();

        if (!is_open())
            return std::vector<char>();

        std::vector<char> bytes(file_length());
        size_t c;
        for (u32 i = 0; (c = fgetc(file)) != EOF; i++) {
            bytes[i] = static_cast<char>(c);
        }
        return bytes;
    }

    void File::for_each_line(Callback callback, const u16 line_length) {
        std::string line;
        while (read_line(line)) {
            callback(line);
        }
    }

    bool File::write_line(std::string line, bool end_line, bool append) {
        if (file_mode != FileMode::Write &&
            file_mode != FileMode::ReadAndWrite) {
            return false;
        }

        if (!is_open())
            return false;

        if (append)
            fseek(file, 0, SEEK_END);

        if (end_line)
            line += '\n';

        fwrite(line.c_str(), sizeof(char), line.length(), file);

        return true;
    }

    bool File::write(std::string_view text) {
        if (file_mode != FileMode::Write && file_mode != FileMode::ReadAndWrite)
            return false;

        if (!is_open())
            return false;

        fwrite(text.data(), sizeof(char), text.length(), file);
        return true;
    }
} // namespace nk
