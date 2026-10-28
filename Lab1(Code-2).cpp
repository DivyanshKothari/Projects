#include<iostream>
#include<vector>
using namespace std;
int main(){
    int n,k;
    cout<<"Enter number of products:";
    cin>>n;
    vector<int> prices(n);
    for(int i=0;i<n;i++){
        cout<<"Enter prices:";
        cin>>prices[i];
    }
    cout<<"Enter gift card value:";
    cin>>k;
    bool found = false;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (prices[i] + prices[j] == k) {
                cout << "First pair found: "
                     << prices[i] << " and "
                     << prices[j] << endl;
                found = true;
                break;
            }
        }
        if (found)
            break;
    }
    if (!found) {
        cout << "No pair found with sum " << k << endl;
    }
    return 0;
}