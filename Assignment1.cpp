#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

struct TradeRecord {
    std::string sourceCurrency;
    std::string destinationCurrency;
    int lots;
    double price;
};

class TradeReader {
public:
    std::vector<std::string> readTrades(std::istream& stream) {
        std::vector<std::string> items;
        std::string item;
        while (std::getline(stream, item)) {
            items.push_back(item);
        }
        return items;
    }
};

class TradeParser {
public:
    std::vector<TradeRecord> parseTrades(const std::vector<std::string>& items) {
        std::vector<TradeRecord> trades;
        int lineCount = 1;
        for (const auto& item : items) {
            std::vector<std::string> fields;
            std::istringstream tStream(item);
            std::string field;
            while (std::getline(tStream, field, ',')) {
                fields.push_back(field);
            }
            if (fields.size() != 3) {
                std::cout << "WARN: Line " << lineCount << " malformed. Only " << fields.size() << " field(s) found." << std::endl;
                continue;
            }
            TradeRecord record;
            record.sourceCurrency = fields[0].substr(0, 3);
            record.destinationCurrency = fields[0].substr(3, 3);
            try {
                record.lots = std::stoi(fields[1]) / 100;  // Assuming LotSize is 100
                record.price = std::stod(fields[2]);
            } catch (const std::exception& e) {
                std::cout << "ERROR: Parsing error on line " << lineCount << " - " << e.what() << std::endl;
                continue;
            }
            trades.push_back(record);
            lineCount++;
        }
        return trades;
    }
};


class XMLGenerator {
public:
    std::string generateXML(const std::vector<TradeRecord>& trades) {
        std::ostringstream xStream;
        xStream << "<TradeRecords>" << std::endl;
        for (const auto& record : trades) {
            xStream << "\t<TradeRecord>" << std::endl;
            xStream << "\t\t<SourceCurrency>" << record.sourceCurrency << "</SourceCurrency>" << std::endl;
            xStream << "\t\t<DestinationCurrency>" << record.destinationCurrency << "</DestinationCurrency>" << std::endl;
            xStream << "\t\t<Lots>" << record.lots << "</Lots>" << std::endl;
            xStream << "\t\t<Price>" << record.price << "</Price>" << std::endl;
            xStream << "\t</TradeRecord>" << std::endl;
        }
        xStream << "</TradeRecords>";
        return xStream.str();
    }
};

class TradeProcessor {
public:
    void processTrades(std::istream& stream) {
        TradeReader reader;
        TradeParser parser;
        XMLGenerator generator;

        auto items = reader.readTrades(stream);
        auto trades = parser.parseTrades(items);
        auto xmlData = generator.generateXML(trades);

        std::ofstream outFile("output.xml");
        outFile << xmlData;
        std::cout << "INFO: " << trades.size() << " trades processed" << std::endl;
    }
};
