#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
#include <cstdlib>
#include <chrono> // Include for time measurement
using namespace std;
using namespace chrono;

// Function to generate random spot price P[x, y]
long long spotPrice(int x, int y) {
    // Replace this with your desired logic for random spot prices
    return rand() % 100 + 1; // Generates a random price between 1 and 100
}

// Recursive function to compute maximum profit
long long computeM(int n, int m, vector<vector<long long>>& M) {
    if (M[n][m] != -1) {
        return M[n][m]; // Avoid recomputing
    } else if (n == 0 || m == 0) {
        M[n][m] = 0; // Base case
    } else {
        long long maxProfit = 0;

        // Check all horizontal cuts
        for (int i = 1; i <= floor(n / 2); ++i) {
            long long profit = computeM(i, m, M) + computeM(n - i, m, M);
            if (profit > maxProfit) {
                maxProfit = profit;
            }
        }

        // Check all vertical cuts
        for (int j = 1; j <= floor(m / 2); ++j) {
            long long profit = computeM(n, j, M) + computeM(n, m - j, M);
            if (profit > maxProfit) {
                maxProfit = profit;
            }
        }

        // Should we sell the entire slab?
        if (spotPrice(n, m) > maxProfit) {
            maxProfit = spotPrice(n, m);
        }

        M[n][m] = maxProfit;
    }

    return M[n][m];
}

int main() {
    int n, m; // Dimensions of the marble slab
    cout << "Enter the dimensions of the marble slab (n m): ";
    cin >> n >> m;

    // Initialize memoization table with NIL values
    vector<vector<long long>> memoTable(n + 1, vector<long long>(m + 1, -1));

    // Start measuring time
    auto start = high_resolution_clock::now();

    long long maxProfit = computeM(n, m, memoTable);

    // Stop measuring time
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "Maximum profit: " << maxProfit << endl;
    cout << "Time elapsed: " << duration.count() << " milliseconds" << endl;

    return 0;
}
