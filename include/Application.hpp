#pragma once

#include <string>
#include <vector>
#include <boost/program_options.hpp>
#include "FileScanner.hpp"
#include "FileMatcher.hpp"
#include "FileGrouper.hpp"
#include "DuplicateFinder.hpp"
#include "IHashAlgorithm.hpp"

namespace po = boost::program_options;

class Application
{
public:
    Application(int argc, char **argv);
    int run();

private:
    void parseCommandLine(int argc, char **argv);
    void showHelp() const;
    void processFiles();
    HashAlgorithmPtr createHashAlgorithm(const std::string &algoName);

    po::options_description desc_;
    po::variables_map vm_;
};
