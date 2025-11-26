#include "Application.hpp"
#include "CRC32Hash.hpp"
#include "MD5Hash.hpp"
#include <iostream>

Application::Application(int argc, char **argv)
    : desc_("Parametrs: ")
{
    desc_.add_options()
        ("help,h", "Help message.")
        ("dir,d", po::value<std::vector<std::string>>()->multitoken(), "Directories to scan (can be multiple).")
        ("exclude,e", po::value<std::vector<std::string>>()->multitoken(), "Directories to exclude from scan (can be multiple).")
        ("depth,p", po::value<int>()->default_value(0), "Scan depth level (0 = only specified directory).")
        ("size,s", po::value<int>()->default_value(1), "Minimum file size in bytes (default: 1).")
        ("mask,m", po::value<std::string>()->default_value(".*"), "Filename mask pattern (case-insensitive regex).")
        ("block,b", po::value<int>()->default_value(4096), "Block size for file reading in bytes (default: 4096).")
        ("hash,a", po::value<std::string>()->default_value("crc32"), "Hash algorithm: crc32 or md5 (default: crc32).");

    parseCommandLine(argc, argv);
}

int Application::run()
{
    if (vm_.count("help"))
    {
        showHelp();
        return 0;
    }

    if (vm_.count("dir"))
    {
        processFiles();
    }

    return 0;
}

void Application::parseCommandLine(int argc, char **argv)
{
    po::store(po::parse_command_line(argc, argv, desc_), vm_);
    po::notify(vm_);
}

void Application::showHelp() const
{
    std::cout << desc_ << std::endl;
}

void Application::processFiles()
{
    std::vector<std::string> dirs = vm_["dir"].as<std::vector<std::string>>();

    int maxDepth = vm_["depth"].as<int>();
    int minSize = vm_["size"].as<int>();
    std::string mask = vm_["mask"].as<std::string>();
    int blockSize = vm_["block"].as<int>();
    std::string hashAlgo = vm_["hash"].as<std::string>();

    std::vector<std::string> excludeDirs;
    if (vm_.count("exclude"))
    {
        excludeDirs = vm_["exclude"].as<std::vector<std::string>>();
    }

    FileMatcher matcher(mask);
    FileScanner scanner(maxDepth, minSize, excludeDirs);

    std::vector<fs::path> files;
    scanner.scan(dirs, matcher, files);

    FileGrouper grouper;
    auto groupedBySize = grouper.groupBySize(files);

    HashAlgorithmPtr hashAlgorithm = createHashAlgorithm(hashAlgo);
    DuplicateFinder finder(blockSize, std::move(hashAlgorithm));

    auto duplicates = finder.findDuplicates(groupedBySize);
    finder.printDuplicates(duplicates);
}

HashAlgorithmPtr Application::createHashAlgorithm(const std::string &algoName)
{
    if (algoName == "md5")
    {
        return std::make_unique<MD5Hash>();
    }
    else if (algoName == "crc32")
    {
        return std::make_unique<CRC32Hash>();
    }
    else
    {
        std::cerr << "Unknown hash algorithm: " << algoName << ". Using CRC32." << std::endl;
        return std::make_unique<CRC32Hash>();
    }
}
