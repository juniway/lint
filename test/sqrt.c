class Solution {
public:
    double fprime(double x){
        return 2*x;
    }

    int sqrt(int x) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        double x0=1.0;
        const double tolerance = 10^-10;
        const double epsilon = 10^-1600;
        const int Maxiteration = 20;
        double newtonX = 0.0;
        for(int i=1; i<=Maxiteration; ++i){
            double denominator = fprime(x0);
            if(abs(denominator) < epsilon){
                printf("WARNING: denominator is too small!\n");
                break;
            }
            newtonX = x0 - (x0*x0 - x)/denominator;
            
            if(abs(newtonX - x0)<tolerance){
                printf("%d's root is %f\n", x, newtonX);
                break;
            }
            else
                x0=newtonX;
        }
        return (int)newtonX;
    }
};