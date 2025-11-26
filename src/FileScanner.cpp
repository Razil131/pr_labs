#include "FileScanner.hpp"

FileScanner::FileScanner(int maxDepth, int minSize, const std::vector<std::string> &excludeDirs)
    : maxDepth_(maxDepth), minSize_(minSize), excludeDirs_(excludeDirs)
{
}

void FileScanner::scan(const std::vector<std::string> &directories,
                       const FileMatcher &matcher,
                       std::vector<fs::path> &files)
{
    for (const auto &dir : directories)
    {
        fs::path dirPath(dir);
        scanDirectory(dirPath, files, 0, matcher);
    }
}

void FileScanner::scanDirectory(const fs::path &dirPath,
                                std::vector<fs::path> &files,
                                int currentDepth,
                                const FileMatcher &matcher)
{
    if (currentDepth > maxDepth_)
    {
        return;
    }

    if (!fs::exists(dirPath) || !fs::is_directory(dirPath))
    {
        return;
    }

    for (const auto &entry : fs::directory_iterator(dirPath))
    {
        if (isExcluded(entry.path()))
        {
            continue;
        }

        if (fs::is_directory(entry))
        {
            scanDirectory(entry.path(), files, currentDepth + 1, matcher);
        }
        else if (fs::is_regular_file(entry))
        {
            if (minSize_ > 0 && fs::file_size(entry) <= static_cast<uintmax_t>(minSize_))
            {
                continue;
            }

            if (matcher.matches(entry.path().filename().string()))
            {
                files.push_back(entry.path());
            }
        }
    }
}

bool FileScanner::isExcluded(const fs::path &path) const
{
    fs::path canonicalPath = fs::weakly_canonical(path);

    for (const auto &excludeDir : excludeDirs_)
    {
        fs::path excludePath = fs::weakly_canonical(excludeDir);

        auto pathStr = canonicalPath.string();
        auto excludeStr = excludePath.string();

        if (pathStr.size() >= excludeStr.size())
        {
            if (pathStr.compare(0, excludeStr.size(), excludeStr) == 0)
            {
                if (pathStr.size() == excludeStr.size() ||
                    pathStr[excludeStr.size()] == fs::path::preferred_separator)
                {
                    return true;
                }
            }
        }
    }
    return false;
}
