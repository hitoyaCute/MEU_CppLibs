#pragma once

#include <cstdio>
#include <filesystem>
#include <cstdio>

#ifdef _WIN32
    #include <windows.h>
    static std::filesystem::path get_exex_path() {
        char path[PATH_MAX];
        GetModuleFileNameA(NULL, path, MAX_PATH);
        return std::filesystem::path(path);
    }
#else
    #include <unistd.h>
    #include <limits.h>
    static std::filesystem::path get_exe_path() {
        char path[PATH_MAX];
        if (readlink("/proc/self/exe", path, PATH_MAX) == -1) {
            fprintf(stderr, "Unexpextederror: error while trying to read /proc/self/exe.\n");
            exit(-1);
        }
        return std::filesystem::path(path);
    }
#endif
