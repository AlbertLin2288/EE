#include <iostream>
#include <iomanip>
#include <vector>
#include <assert.h>
using namespace std;


struct Mat{
    int N;
    vector<vector<char>> val;

    Mat(int n){
        N = n;
        val.assign(n, vector<char>(n,0));
    }

    Mat operator+(const Mat &rhs){
        Mat res(N);
        for (int i=0;i<N;i++){
            for (int j=0;j<N;j++){
                res.val[i][j] = val[i][j] ^ rhs.val[i][j];
            }
        }
        return res;
    };

    Mat operator*(const Mat &rhs){
        Mat res(N);
        for (int i=0;i<N;i++){
            for (int j=0;j<N;j++){
                res.val[i][j] = 0;
                for (int k=0;k<N;k++){
                    res.val[i][j] ^= val[i][k] && rhs.val[k][j]; 
                }
            }
        }
        return res;
    };

    int get_rank(){
        int ans = 0, i1;
        vector<vector<char>> m = val;
        for (int j=0;j<N;j++){
            i1 = N;
            for (int i=0;i<N;i++){
                if (!m[i][j]){
                    continue;
                }
                if (i1==N){
                    i1=i;
                    ans++;
                    continue;
                }
                for (int k=j;k<N;k++){
                    m[i][k] ^= m[i1][k];
                }
            }
            if (i1<N){
                for (int k=j;k<N;k++){
                    m[i1][k] = 0;
                }
            }
        }
        return ans;
    };

    int get_nullity(){
        return int(N) - get_rank();
    };
};

ostream& operator<<(ostream &os, const Mat &out) {
    for (auto&r:out.val){
        for (auto&v:r){
            os << !!v << " ";
        }
        os << "\n";
    }
    return os;
}


Mat make_E(int n){
    Mat res(n);
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            res.val[i][j] = i==j;
        }
    }
    return res;
}

Mat make_A(int n){
    Mat res(n);
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            res.val[i][j] = i==j || i==j+1 || i+1==j;
        }
    }
    return res;
}

signed main(int argc, char** argv){
    int max_n;
    if (argc == 2){
        max_n = stoi(argv[1]);
    } else {
        cout << "Please input number of rows/columns to calculate: ";
        cin >> max_n;
    }
    cout << "   "; 
    for (int m=0;m<max_n;m++){
        cout << setw(3) << m;
    }
    cout << "\n   ";
    for (int m=0;m<max_n;m++){
        cout << "___";
    }
    cout << "\n";
    for (int n=0;n<max_n;n++){
        Mat A = make_A(n), B = make_E(n), B_next = make_A(n);
        cout << setw(2) << n << "|";
        for (int m=0;m<max_n;m++){
            cout << setw(3) << B.get_nullity();
            B = B + A * B_next;
            swap(B, B_next);
        }
        cout << "\n";
    }
}