#pragma once

namespace nk {
    enum class FileMode {
        Read = 0,
        Write,
        ReadAndWrite,
    };

    enum class FileEncoding {
        UTF_8 = 0,
        UNICODE = 1,
        UTF_16 = 2,
        ANSI = 3,
    };

    class File {
    private:
        struct FileCreateInfo {
            std::filesystem::path path;
            FileMode mode;
            FileEncoding encoding;
        };

    public:
        File(const FileCreateInfo& info);
        ~File();

        using Path = std::filesystem::path;
        using Callback = std::function<void(std::string_view)>;

        /**
         * @brief Checks if a file with the given path exists.
         * @param path The path of the file to be checked of type Path.
         * @returns True if exists; otherwise false.
         */
        static bool exists(const Path& path);
        /**
         * @brief Checks if a file with the given filepath exists.
         * @param filepath The path of the file to be checked.
         * @returns True if exists; otherwise false.
         */
        inline static bool exists(std::string_view filepath) {
            return exists(Path{filepath});
        }

        /**
         * @brief Attempt to open file located at path.
         * @param filepath The path of the file to be opened.
         * @param mode Mode flags for the file when opened (read/write). See
         * FileMode enum in file.h.
         * @param binary Indicates if the file should be opened in binary mode.
         * @returns A Ref pointer to a File which holds the handle information
         * or nullptr if the file doesn't exists.
         */
        static Ref<File> open(
            std::string_view filepath,
            const FileMode mode,
            const FileEncoding encoding = FileEncoding::UTF_8
        );

        static Scope<File> open_scope(
            std::string_view filepath,
            const FileMode mode,
            const FileEncoding encoding = FileEncoding::UTF_8
        );

        void close();
        bool is_open() const;
        u32 file_length() const;
        bool read_line(std::string& line, const u16 line_length = 256);
        std::vector<std::string> read_all_lines(const u16 line_length = 256);
        std::vector<char> read_all_bytes();
        void for_each_line(Callback callback, const u16 line_length = 256);
        bool
        write_line(std::string line, bool end_line = true, bool append = true);
        bool write(std::string_view text);

    private:
        Path path;
        FILE* file;
        FileMode file_mode;
    };
} // namespace nk
