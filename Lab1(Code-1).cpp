#include <iostream>
#include <vector>
#include <unordered_map>
#include <ctime>
#include <cstdlib>
using namespace std;

int main() {
    int n;
    cout<<"Enter number of packages:";
    cin>>n;
        vector<int> packages(n);
       srand(time(0));
        for (int i = 0; i < n; i++) {
             packages[i] = rand() % 9 + 1;   // random values from 1 to 9
        }
        clock_t start, end;

        // 1. Access package n/2  --> O(1)
        start = clock();
        int middle = packages[n / 2];
        end = clock();
        double t1 = double(end - start) / CLOCKS_PER_SEC;

        // 2. Check every package --> O(n)
        start = clock();
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            sum += packages[i];
        }
        end = clock();
        double t2 = double(end - start) / CLOCKS_PER_SEC;

        // 3. Check all values with freq > 1 --> O(n)
        start = clock();
        unordered_map<int, int> freq;
        for (int x : packages) {
            freq[x]++;
        }
        for (auto &p : freq) {
            if (p.second > 1) {
                // just checking
            }
        }
        end = clock();
        double t3 = double(end - start) / CLOCKS_PER_SEC;
        cout << "Access package n/2 (O(1))      : "
             << t1 << " sec" << endl;

        cout << "Check every package (O(n))     : "
             << t2 << " sec" << endl;

        cout << "Check values with freq > 1     : "
             << t3 << " sec" << endl;
    
    return 0;
}