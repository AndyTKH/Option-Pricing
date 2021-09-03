//
//  main.cpp
//  C-Finance
//
//  Created by Andy Tan on 9/2/21.
//  Copyright © 2021 Andy Tan. All rights reserved.
//

#include <iostream>
#include <cmath>

// An approximation to the cumulative distribution function
// for the standard normal distribution
double norm_cdf(const double& x)
{
    return 0.5 * erfc(-x * sqrt(0.5));
}

// Calculate d_j（j as 1 or 2) term in the closed form solution for the European call put option price
double d_j(const int& j, const double& S, const double& K, const double& r, const double& v, const double& T) {
    return (log(S/K) + (r + (pow(-1,j-1))*0.5*v*v)*T)/(v*(sqrt(T)));
}

// Calculate the European vanilla call price
double call_price(const double& S, const double& K, const double& r, const double& v, const double& T) {
    return S * norm_cdf(d_j(1, S, K, r, v, T))-K*exp(-r*T) * norm_cdf(d_j(2, S, K, r, v, T));
}

// Calculate the European vanilla put price
double put_price(const double& S, const double& K, const double& r, const double& v, const double& T) {
    return -S*norm_cdf(-d_j(1, S, K, r, v, T))+K*exp(-r*T) * norm_cdf(-d_j(2, S, K, r, v, T));
}


int main(int argc, char **argv) {
    
    // First we create the parameter list
    double S = 100.0;  // Underlying
    double K = 100.0;  // Strike price
    double r = 0.05;   // Risk-free rate (5%)
    double v = 0.3;    // Volatility of the underlying (30%)
    double T = 1.0;    // One year until expiry
    
    // Then we calculate the call/put values
    double call = call_price(S, K, r, v, T);
    double put = put_price(S, K, r, v, T);
    
    // Finally we output the parameters and prices
    std::cout << "Underlying:      " << S << std::endl;
    std::cout << "Strike:          " << K << std::endl;
    std::cout << "Risk-Free Rate:  " << r << std::endl;
    std::cout << "Volatility:      " << v << std::endl;
    std::cout << "Maturity:        " << T << std::endl;
    
    std::cout << "Call Price:      " << call << std::endl;
    std::cout << "Put Price:       " << put << std::endl;
    
    return 0;
}
