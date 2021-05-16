#include <bits/stdc++.h>

using namespace std;

/*
 *  number of bitstrings of length n
 *  where there are not 3 0's next to 
 *  eachother -- example (n = 4):
 *  '0001' is NOT valid
 *  '1001' is VALID
 */

long numBitStrings(int n, int in_a_row){
    vector<vector<long>> dp(n+1, vector<long>(in_a_row));
    /* dp[0] = num valid bitstrings ending with 1
     * dp[1] = num valid bitstrings ending with 0
     * dp[2] = num valid bitstrings ending with 00
     */
    // base (where to build up from)
    // for n = 1 (bitstrings are '1' and '0')
    dp[1][0] = 1;
    dp[1][1] = 1;
    // rest of options are empty for now (we cant have '00' if n is only 1)
    for(int x = 2; x < dp[1].size(); ++x)
        dp[1][x] = 0;

    for(int x = 2; x <= n; ++x){
        /* rules:
         * can always add '1' to end of a valid string and still have a valid string
         * only way to get '00' is to add '0' to a '0'
         * cant add to '00' or we break invariant
         */
        long fsum{};
        for(int y{}; y < in_a_row; ++y){
            fsum += dp[x-1][y];
            if(y > 0)
                dp[x][y] = dp[x-1][y-1];
        }
        dp[x][0] = fsum;
    }
    long rsum{};
    for(int x{}; x < in_a_row; ++x)
        rsum += dp[n][x];
    return rsum;
}

/*
 * what to memoize (valid bitstrings)
 * bitstrings ending with '1'
 * bitstrings ending with '0'
 * bitstrings ending with '00'
 */

int main(){
    constexpr int n = 3, max_zeroes_in_a_row = 2;
    long num = pow(2, n);
    cout << "All bitstrings of length: " << n << ": \n";
    for(int x{}; x < num; ++x){
        cout << bitset<n>(x) << "\t";
        if(x % 5 == 0 && x) cout << "\n";
    }cout << "\n";
    long result = numBitStrings(n, max_zeroes_in_a_row);
    printf("Number of bitstrings of length %d where bitstrings with %d consecutive '0's are NOT included: %lu\n",
                    n, max_zeroes_in_a_row, result);
    return 0;
}
