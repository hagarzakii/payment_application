# Payment Application

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)

## Introduction

Welcome to the Payment Application, a solution for processing card transactions. This application is designed to facilitate secure and efficient financial transactions, ensuring that cardholders can manage payments with ease.

**Key Features**:

- Comprehensive card transaction processing
- Cardholder authentication
- Real-time account validation
- Transaction amount management
- Account balance updates
- Transaction logging

## Features

### Comprehensive Card Transaction Processing

The Payment Application streamlines the card transaction process, offering a sequence of steps to ensure a smooth experience. Here's how it works:

1. **Get Card Holder Name**: Collect the cardholder's name for identification.

2. **Get Card Expiration Date**: Gather the card's expiration date for validation.

3. **Get Card PAN**: Securely capture the card's Primary Account Number (PAN).

4. **Get All Card Data**: Retrieve essential card information, including cardholder name, expiration date, and PAN.

5. **Get Transaction Date**: Record the transaction date for reference.

6. **Is Card Expired?**: Verify if the card has expired. If it's expired, decline the transaction due to an expiration date error.

7. **Get Transaction Amount**: Prompt for the transaction amount. If it exceeds the maximum allowed, the transaction is declined.

8. **Is Valid Account?**: Authenticate the cardholder's account. If it's not valid, the transaction is declined due to an invalid account.

9. **Is Amount Available?**: Check if the card has sufficient funds. If the balance is insufficient, the transaction is declined due to insufficient funds.

10. **Update Account Balance**: If all checks pass successfully, update the cardholder's account balance accordingly.

11. **Save Transaction**: Log the transaction for record-keeping and future reference.

## Installation

To install the Payment Application, follow these steps:

1. Clone this repository to your local machine:

   ```bash
   git clone https://github.com/yourusername/payment-application.git
   
## Usage
1. **Card Transaction Process**: Follow the step-by-step card transaction process described in the Features section.
2. **Logging**: All successful and declined transactions are logged for future reference and auditing.

