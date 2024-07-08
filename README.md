# Nifty50 Momentum Strategy

This repository contains C++ code for generating test data and executing a momentum trading strategy on Nifty50 stocks.

## Files

- `generate_test_data.cpp`: Generates synthetic price data for Nifty50 stocks.
- `execute_strategy.cpp`: Executes a simple momentum strategy using moving average crossover.

## Usage

### Generate Test Data

```sh
g++ generate_test_data.cpp -o generate_test_data
./generate_test_data
