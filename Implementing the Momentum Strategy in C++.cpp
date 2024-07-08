#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

// Function to read CSV data
std::vector<double> readCSV(const std::string& filename) {
    std::vector<double> prices;
    std::ifstream file(filename);
    std::string line, cell;
    
    std::getline(file, line); // Skip header
    while (std::getline(file, line)) {
        std::stringstream lineStream(line);
        std::getline(lineStream, cell, ','); // Skip day
        std::getline(lineStream, cell, ','); // Get price
        prices.push_back(std::stod(cell));
    }
    return prices;
}

// Function to calculate moving average
double calculateMovingAverage(const std::vector<double>& data, int start, int period) {
    double sum = 0.0;
    for (int i = start; i < start + period; ++i) {
        sum += data[i];
    }
    return sum / period;
}

// Execute the momentum strategy
void executeStrategy(const std::vector<double>& prices, int shortWindow, int longWindow) {
    int n = prices.size();
    std::vector<double> shortMA(n);
    std::vector<double> longMA(n);
    
    // Calculate moving averages
    for (int i = longWindow - 1; i < n; ++i) {
        shortMA[i] = calculateMovingAverage(prices, i - shortWindow + 1, shortWindow);
        longMA[i] = calculateMovingAverage(prices, i - longWindow + 1, longWindow);
    }
    
    // Simulate trading
    bool position = false; // false: no position, true: holding stock
    double initialCapital = 100000.0;
    double capital = initialCapital;
    double shares = 0.0;
    
    for (int i = longWindow; i < n; ++i) {
        if (shortMA[i] > longMA[i] && !position) {
            // Buy signal
            shares = capital / prices[i];
            capital = 0.0;
            position = true;
            std::cout << "Buy at " << prices[i] << " on day " << i + 1 << std::endl;
        } else if (shortMA[i] < longMA[i] && position) {
            // Sell signal
            capital = shares * prices[i];
            shares = 0.0;
            position = false;
            std::cout << "Sell at " << prices[i] << " on day " << i + 1 << std::endl;
        }
    }
    
    // Final account value
    if (position) {
        capital = shares * prices.back();
    }
    double returnPercentage = ((capital - initialCapital) / initialCapital) * 100.0;
    std::cout << "Final capital: " << capital << std::endl;
    std::cout << "Return: " << returnPercentage << "%" << std::endl;
}

int main() {
    std::string filename = "nifty50_test_data.csv";
    std::vector<double> prices = readCSV(filename);
    
    int shortWindow = 20; // Short-term moving average window
    int longWindow = 50; // Long-term moving average window
    
    executeStrategy(prices, shortWindow, longWindow);
    
    return 0;
}
