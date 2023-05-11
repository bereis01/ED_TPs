#include "stringOperations.hpp"

void gatherArguments(int argc, char **argv, std::string &inputFile, std::string &outputFile, int &median, int &minPartSize)
{
    // Guarantees that some parameter has been provided.
    if (argc <= 1)
    {
        throw std::logic_error(std::string("Error: No parameters provided!"));
    }

    // Limits the number of command line arguments.
    if (argc > 15)
    {
        throw std::logic_error(std::string("Error: Too many command line arguments!"));
    }

    // Transforms char** to std::string for better manipulation.
    std::string arguments[argc - 1];
    for (int i = 1; i < argc; i++)
    {
        arguments[i - 1] = argv[i];
    }

    // Checks for the desired parameters, initializing them accordingly.
    int inputFlag = 0;
    int outputFlag = 0;
    for (int i = 0; i < argc - 1; i++)
    {
        if (arguments[i] == "-i" || arguments[i] == "-I")
        {
            if (i < argc - 2)
            {
                inputFile = arguments[i + 1];
                inputFlag = 1;
                i++;
            }
        }
        else if (arguments[i] == "-o" || arguments[i] == "-O")
        {
            if (i < argc - 2)
            {
                outputFile = arguments[i + 1];
                outputFlag = 1;
                i++;
            }
        }
        else if (arguments[i] == "-m" || arguments[i] == "-M")
        {
            if (i < argc - 2)
            {
                try
                {
                    median = stoi(arguments[i + 1]);
                }
                catch (const std::exception &e)
                {
                    throw std::logic_error(std::string("Error: Invalid domain for median parameter!"));
                }
                i++;
            }
        }
        else if (arguments[i] == "-s" || arguments[i] == "-S")
        {
            if (i < argc - 2)
            {
                try
                {
                    minPartSize = stoi(arguments[i + 1]);
                }
                catch (const std::exception &e)
                {
                    throw std::logic_error(std::string("Error: Invalid domain for partition parameter!"));
                }
                i++;
            }
        }
    }

    // Guarantees that an input file and an output file have been provided.
    if (!(inputFlag))
    {
        throw std::logic_error(std::string("Error: No input file provided!"));
    }
    if (!(outputFlag))
    {
        throw std::logic_error(std::string("Error: No output file provided!"));
    }
}

void gatherTextAndOrder(std::ifstream &inputFile, std::stringstream &text, std::stringstream &order, int &maxNumOfWords)
{
    std::string holdStr;
    std::string command;

    maxNumOfWords = 0;

    // Simply extracts the content of the input file into the corresponding string stream.
    inputFile >> command;

    // Verifies if the input file was correctly read.
    if (inputFile.bad())
    {
        throw std::runtime_error(std::string("Error: Input file not appropriately read!"));
    }

    while (inputFile >> holdStr)
    {
        // Verifies if the input file was correctly read.
        if (inputFile.bad())
        {
            throw std::runtime_error(std::string("Error: Input file not appropriately read!"));
        }

        if (command == "#ORDEM")
        {
            if (holdStr == "#TEXTO")
            {
                command = holdStr;
            }
            else
            {
                order << holdStr << " ";

                // Verifies if the stream was correctly read/written.
                if (order.bad())
                {
                    throw std::runtime_error(std::string("Error: Stream not appropriately read/written!"));
                }
            }
        }
        else if (command == "#TEXTO")
        {
            if (holdStr == "#ORDEM")
            {
                command = holdStr;
            }
            else
            {
                text << holdStr << " ";

                // Verifies if the stream was correctly read/written.
                if (text.bad())
                {
                    throw std::runtime_error(std::string("Error: Stream not appropriately read/written!"));
                }

                maxNumOfWords++;
            }
        }
    }
}

void formatText(std::stringstream &text)
{
    std::string holdStr;
    std::stringstream textCorrected;
    int hyphenFlag = 0;

    while (text >> holdStr)
    {
        // Verifies if the stream was correctly read/written.
        if (text.bad())
        {
            throw std::runtime_error(std::string("Error: Stream not appropriately read/written!"));
        }

        for (int i = 0; i < (int)holdStr.size(); i++)
        {
            // Accent and 'ç' treatment.
            std::string accentLetter;
            if (i < (int)holdStr.size() - 1)
            {
                std::stringstream accentStream;
                accentStream << holdStr[i] << holdStr[i + 1];
                accentStream >> accentLetter;

                // Verifies if the stream was correctly read/written.
                if (accentStream.bad())
                {
                    throw std::runtime_error(std::string("Error: Stream not appropriately read/written!"));
                }
            }
            else
            {
                accentLetter = "";
            }

            // Changes higher case to lower case letters.
            if (holdStr[i] >= 65 && holdStr[i] <= 90)
            {
                holdStr[i] += 32;
                textCorrected << holdStr[i];
            }
            // Treats any punctuation marks.
            else if (holdStr[i] == ',' || holdStr[i] == '.' || holdStr[i] == '!' || holdStr[i] == '?' || holdStr[i] == ':' || holdStr[i] == ';' || holdStr[i] == '_')
            {
                holdStr[i] = ' ';
            }
            // Treats 'ç'.
            else if (accentLetter == "Ç" || accentLetter == "ç")
            {
                textCorrected << "ç";
                i++;
            }
            // Treats 'a' with accent.
            else if (accentLetter == "á" || accentLetter == "à" || accentLetter == "ã" || accentLetter == "â" || accentLetter == "ä" ||
                     accentLetter == "Á" || accentLetter == "À" || accentLetter == "Ã" || accentLetter == "Â" || accentLetter == "Ä")
            {
                textCorrected << 'a';
                i++;
            }
            // Treats 'e' with accent.
            else if (accentLetter == "é" || accentLetter == "è" || accentLetter == "ê" || accentLetter == "ë" ||
                     accentLetter == "É" || accentLetter == "È" || accentLetter == "Ê" || accentLetter == "Ë")
            {
                textCorrected << 'e';
                i++;
            }
            // Treats 'i' with accent.
            else if (accentLetter == "í" || accentLetter == "ì" || accentLetter == "î" || accentLetter == "ï" ||
                     accentLetter == "Í" || accentLetter == "Ì" || accentLetter == "Î" || accentLetter == "Ï")
            {
                textCorrected << 'i';
                i++;
            }
            // Treats 'o' with accent.
            else if (accentLetter == "ó" || accentLetter == "ò" || accentLetter == "õ" || accentLetter == "ô" || accentLetter == "ö" ||
                     accentLetter == "Ó" || accentLetter == "Ò" || accentLetter == "Õ" || accentLetter == "Ô" || accentLetter == "Ö")
            {
                textCorrected << 'o';
                i++;
            }
            // Treats 'u' with accent.
            else if (accentLetter == "ú" || accentLetter == "ù" || accentLetter == "û" || accentLetter == "ü" ||
                     accentLetter == "Ú" || accentLetter == "Ù" || accentLetter == "Û" || accentLetter == "Ü")
            {
                textCorrected << 'u';
                i++;
            }
            // Treats 'y' with accent.
            else if (accentLetter == "ý" || accentLetter == "ÿ" || accentLetter == "Ý")
            {
                textCorrected << 'y';
                i++;
            }
            // Treats 'n' with accent.
            else if (accentLetter == "ñ" || accentLetter == "Ñ")
            {
                textCorrected << 'n';
                i++;
            }
            // Default case. Nothing to correct.
            else
            {
                textCorrected << holdStr[i];
            }

            // Verifies if the stream was correctly read/written.
            if (textCorrected.bad())
            {
                throw std::runtime_error(std::string("Error: Stream not appropriately read/written!"));
            }
        }

        // Treats hyphens at the end of the word.
        if (holdStr[holdStr.size() - 1] == '-' && holdStr.size() > 1)
        {
            if (hyphenFlag)
            {
                textCorrected << " ";
                hyphenFlag = 0;
            }
            else
            {
                hyphenFlag = 1;
            }
        }
        else
        {
            hyphenFlag = 0;
            textCorrected << " ";
        }

        // Verifies if the stream was correctly read/written.
        if (textCorrected.bad())
        {
            throw std::runtime_error(std::string("Error: Stream not appropriately read/written!"));
        }
    }

    std::swap(text, textCorrected);
}