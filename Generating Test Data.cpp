#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <string>

// Function to generate random price data
std::vector<double> generatePriceData(int days, double startPrice, double volatility) {
    std::vector<double> prices(days);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> d(0, volatility);
    
    prices[0] = startPrice;
    for (int i = 1; i < days; ++i) {
        prices[i] = prices[i-1] + d(gen);
    }
    return prices;
}

// Function to write data to a CSV file
void writeToFile(const std::vector<double>& data, const std::string& filename) {
    std::ofstream file(filename);
    file << "Day,Price\n";
    for (size_t i = 0; i < data.size(); ++i) {
        file << i + 1 << "," << data[i] << "\n";
    }
    file.close();
}

int main() {
    int days = 365; // Number of days of data
    double startPrice = 1000.0; // Starting price
    double volatility = 5.0; // Volatility

    std::vector<double> prices = generatePriceData(days, startPrice, volatility);
    writeToFile(prices, "nifty50_test_data.csv");

    std::cout << "Test data generated and written to nifty50_test_data.csv" << std::endl;

    return 0;
}
