# C++ for Finance - Options Pricing Project 💹

# 🚧🔨 This project is currently under development 🚧🔨

## Introduction
The project aims to implement options pricing models in C++, focusing on European vanilla options as well as more complex options, such as path-dependent options. The main aspects of the project include defining abstract classes for options, implementing different pricing models, and utilizing simulation methods. 🚀

---

## Part I: Black-Scholes Model 📈

**1. Model Specification**
A European vanilla option is defined by:
- **Type**: Call or Put (modeled with an enum)
- **Strike Price**: K
- **Expiration Date**: T

It depends on the following market data:
- **Underlying Price**: S
- **Interest Rate**: r
- **Volatility**: σ

**2. Implementation**

- **Abstract Class `Option`**:
  - Private member: `double _expiry`
  - Getter method: `getExpiry()`
  - Pure virtual method: `double payOff(double)` representing the option's payoff function.

- **Abstract Class `EuropeanVanillaOption`** derived from `Option`:
  - Private attribute: `double _strike`
  - Constructor that initializes `_expiry` and `_strike` with arguments, ensuring they are non-negative.
  - Enum `optionType` with values `call` and `put`.
  - Pure virtual method `GetOptionType()`.

- **Derived Classes `CallOption` and `PutOption`**:
  - Use the constructor of `EuropeanVanillaOption`.
  - Implement the payoff function for Call and Put options.

- **Class `BlackScholesPricer`**:
  - Constructor `BlackScholesPricer(EuropeanVanillaOption* option, double asset_price, double interest_rate, double volatility)`.
  - Declare `BlackScholesPricer` as a friend class of `EuropeanVanillaOption` to access the strike price.
  - Method `operator()` to calculate the option price using the Black-Scholes formula (hint: `std::erfc`).
  - Method `delta()` to return the option's Delta.

---

## Part II: Cox-Ross-Rubinstein (CRR) Model 🌳

**1. CRR Model**
The price of an asset evolves in discrete time steps. At each step, it can either go up or down by defined factors, starting from an initial price \( S_0 \).

- **Price at step \( n \) and node \( i \)**:
\[ S(n, i) = S_0 (1 + U)^i (1 + D)^{n-i} \]

**2. Implementation**

- **Class `BinaryTree`**:
  - Template class `BinaryTree<T>` with members `_depth` and `_tree` (vector of vectors).
  - Methods to set depth, define and retrieve nodes, and display the tree structure.

- **Class `CRRPricer`**:
  - Constructor `CRRPricer(Option* option, int depth, double asset_price, double up, double down, double interest_rate)`.
  - Arbitrage check.
  - Create the tree structure to store option prices.
  - Methods to calculate prices using the CRR method and an operator to obtain the option price, with an optional argument to use a closed-form formula.

---

## Part III: Path-Dependent Options and Monte Carlo 🎲

**1. Theory of Options**
Path-dependent options have a payoff that depends on the prices of the underlying assets at dates prior to maturity.

**2. Implementation**

- **Extension of the `Option` Class**:
  - Added a method `payOffPath(std::vector<double>)` to handle path-dependent options.

- **Class `AsianOption` derived from `Option`**:
  - Constructor taking a `std::vector<double>` to represent prices at different dates.
  - Method to calculate the payoff based on the arithmetic average of the underlying prices.

---

## Part IV - Pricing American Options in the Binomial Model 🇺🇸

### Overview

This section extends our binomial model to include the pricing of American options, which can be exercised at any time up to expiration. We will use a backward induction method to determine the price at each node of the binomial tree and to establish an early exercise policy.

### Pricing Procedure

1. **At Expiration**:
   - At expiration date \( N \):
     \[
     H(N, i) = h(S(N, i))
     \]
   
2. **Backward Induction**:
   - For \( n < N \):
     \[
     H(n, i) = \max \left\{ qH(n + 1, i + 1) + (1 - q) H(n + 1, i)(1 + R), \, h(S(n, i)) \right\}
     \]

3. **Early Exercise Policy**:
   - Determine if the option should be exercised at each node and store this information in a `BinaryTree<bool>` structure.

## Conclusion 🎉
This project allows for a deep understanding of options pricing models, from options theory to practical implementation in C++. Users will be able to model simple and complex options, integrating advanced techniques such as Monte Carlo simulation and binomial trees. Together, we're taking a step toward smarter finance! 💡
