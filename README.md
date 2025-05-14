# Karachi Stock Market Simulator

## Project Overview

This C++ command-line application simulates a simplified stock market environment, specifically modeled after the Karachi Stock Market. Users can view live (simulated) stock prices, manage a virtual portfolio, buy and sell stocks, and manage their virtual funds. The simulation includes dynamic price updates, tracking of daily high/low prices, and identification of top-performing and underperforming stocks.

## Features

*   **Live Market Screen:**
    *   Displays a list of companies with their symbols, names, previous prices, current prices, daily high, and daily low.
    *   Prices update dynamically (on user prompt - pressing Enter).
    *   Uses color-coding (green for price increase, red for decrease) and arrow indicators.
    *   Shows the "Top % advancer symbol" and "Top % decliner symbol".
    *   Displays total gain/loss from the user's portfolio transactions during the session.
*   **Portfolio Management:**
    *   View your current stock holdings, including symbol, company name, shares owned, current price, previous price, gain/loss per stock, daily high, and daily low.
    *   Calculates and displays total gain/loss for the portfolio.
    *   Shows previous and new account balance after considering portfolio gains/losses.
*   **Stock Trading:**
    *   **Add (Buy) Stock:** Purchase shares of a company using its symbol, provided sufficient funds are available.
    *   **Remove (Sell) Stock:** Sell owned shares of a company using its symbol.
*   **Fund Management:**
    *   **Add Money:** Deposit virtual funds into your trading account.
    *   **Withdraw Money:** Withdraw virtual funds from your trading account.
*   **Data Persistence:**
    *   Company data (symbol, name, initial price) is read from `companies.txt`.
    *   User portfolio and funds are managed in memory and reset when the application closes.
*   **User Interface:**
    *   Interactive command-line interface.
    *   Formatted output for readability using `iomanip`.
    *   Uses basic ANSI escape codes for text coloring and special characters for price change indication (▲/▼).

## Requirements

*   A C++ compiler that supports C++11 or later (for `stof`, etc.). E.g., g++, MinGW.
*   Windows Operating System (due to `windows.h`, `conio.h`, `system("CLS")`).
*   The `companies.txt` file must be in the same directory as the executable.

## Files

*   `22i-1559_B_Project.cpp`: The main C++ source code file.
*   `companies.txt`: A text file containing the initial stock data. Each line should be in the format: `SYMBOL,Company Name,InitialPrice`

## How to Compile

You can compile the project using a C++ compiler like g++ (MinGW on Windows).

```bash
g++ 22i-1559_B_Project.cpp -o StockMarketSim -static-libgcc -static-libstdc++
Use code with caution.
Markdown
(The -static-libgcc -static-libstdc++ flags are optional but help create a more portable executable on Windows by linking these libraries statically.)
How to Run
Ensure companies.txt is in the same directory as the compiled executable.
Run the executable from the command line:
./StockMarketSim.exe
Use code with caution.
Bash
or simply double-click StockMarketSim.exe on Windows.
Usage / Controls
The application starts by displaying the Live Market Screen. You can interact using single key presses:
Main Live Market Screen:
Enter Key: Refresh the market data (updates stock prices).
P or p: Go to your Portfolio screen.
A or a: Add (buy) a stock.
R or r: Remove (sell) a stock.
M or m: Add money to your account.
W or w: Withdraw money from your account.
E or e: Exit the application.
Portfolio Screen:
Enter Key: Refresh the portfolio data (updates stock prices within the portfolio view).
L or l: Return to the Live Market Screen.
A or a: Add (buy) a stock.
R or r: Remove (sell) a stock.
M or m: Add money to your account.
W or w: Withdraw money from your account.
When prompted (e.g., for adding/removing stock, adding/withdrawing money), you will need to enter further input like stock symbols, number of shares, or amounts.
Code Structure (Key Functions)
main(): Main program loop, handles user input for navigation.
filereading(): Reads company data from companies.txt.
duplicate(): Helper function to copy arrays.
updateprice(): Simulates stock price changes randomly (within a +/- 15% range of the original price, though the logic for this constraint might have nuances). Updates daily high and low.
livemarketscreen(): Displays the main market overview.
topsalecompany(): Identifies the top advancing and declining stocks based on percentage change from their original prices.
addmoney(): Allows the user to add funds to their account.
with_draw_money(): Allows the user to withdraw funds.
showportfolio(): Displays the user's current holdings and overall performance.
addstock(): Handles the logic for buying stocks.
removestock(): Handles the logic for selling stocks.
Known Issues / Limitations
Windows Specific: Uses Windows-specific headers (windows.h, conio.h) and commands (system("CLS")), so it will not compile/run directly on other operating systems like Linux or macOS without modification.
No Data Persistence: Portfolio status and account balance are lost when the application is closed.
Fixed Company List: The number of companies (37) is hardcoded in array sizes. Adding more companies to companies.txt without changing array sizes in the code will lead to issues.
Price Update Model: The price update mechanism is a simple random percentage change. The logic for capping changes within +/- 15% seems to be based on the initial stock price rather than the previous day's price for the random generation, and the subsequent check if (percent < 115 && percent > 85) might not perfectly achieve a strict 15% cap from the previous price in all scenarios.
Top/Bottom Performer Logic: The topsalecompany function calculates percentage change based on the original stock price, not the previous day's price, for determining top/bottom performers.
The "Portfolio owner: Bill Gates (Live)" is hardcoded in showportfolio().
"Total Shares Shared Today" in livemarketscreen actually displays the total_gainloss from the user's portfolio if it was recently viewed/updated.
Author: sultan umar cheema (22i-1559)
Course: PF PROJECT
Section: CYS - B
