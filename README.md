# Supermarket Point of Sale in C++

This project is a simple point of sale system for hipotetical supermarket developed in C++. The goal of this project is to understand the different kinds of linked lists.

## Table of Contents
1. [Project Overview](#project-overview)
2. [Features](#features)
3. [Requirements](#requirements)
4. [How to Compile and Run](#how-to-compile-and-run)
5. [Usage](#usage)

## Project Overview

This point of sale project makes use of different linked lists to handle users, inventory, sales, customer visits, and admin activity. The application uses `Simple Linked Lists`, `Double Linked Lists` and `Double Circular Linked Lists`.

## Features

- **User Authentication**: Allows users to log into the application and create new accounts.
- **User Groups**: Differentiates between types of users such as administrator, seller, worker, client and guest.
- **Price Lookup**: Displays the price of a given product.
- **Discount Lookup**: Displays if the user has some discount.
- **Product List**: Lists all the products available in a location.
- **Shopping Cart**: Stores the products the user has selected to be bought. The user can add or remove items from the cart.
- **Checkout**: Calcultes the final amount to be charged based on the products in the shopping cart and the user discount, and creates an invoice for the purchase.
- **Invetory Management**: Administrators can create, update or delete products from a location.
- **Report Generation**: Administrators can generate reports on newests products, products updated and deleted, best and worst selling products, best and worst client, best and worst location; and best and worst adminstrator.
- **Command Line Interface**: The user can interact with a application using command line menus.

## Requirements

- **C++ Compiler**: A C++ compiler supporting the C++11 standard or higher (e.g., MSVC or MinGW).

## How to Compile and Run

An already compiled version of the program is present in the repository. If you need to compile a new version of the project you can follow the next steps:

### Step 1: Clone the repository

``` bash
git clone https://github.com/abzave/SistemaSupermercados.git
cd SistemaSupermercados
```

### Step 2: Compile the project

If you are using **Visual Studio**, you can open a new `.sln` file in Visual Studio and build the project.
Alternatively, for **MinGW**, you can compile the source file using:

``` bash
g++ Main.cc src/*.cc include/*.h -Wall
```

### Step 3: Run the program

Once compiled, run the application executable.

## Usage

1. Log into the application by providing your national ID and your user type.
    - If the user does not have an account but is register as a client, the option to create an account will be displayed.
2. If the user is a client the menu options will be as follows:
    1. Select `1` to look up a price.
         - Enter the code of the product to look up.
    3. Select `2` to display your user's discount.
    4. Select `3` to list the product catalog of a location.
        - Enter the code of the location to list the catalog.
    6. Select `4` to access the shopping cart.
    7. Select `5` to go to checkout.
    8. Select `0` to exit the application.
3. If the user is an administrator the menu options will be as follows:
    1. Select `1` to add a new product.
        1. Enter the code for the new product.
        2. Enter the code of the location the product will be added to.
        3. Enter the name of the product.
        4. Enter the amount available of the product.
        5. Enter the price of the product.
    3. Select `2` to delete a product.
        - Enter the code of the product to delete. 
    4. Select `3` to update a product.
        1. Select `1` to update the location code where the product is available.
            - Enter the new location code.
        3. Select `2` to update the product name.
            - Enter the new product name.
        5. Select `3` to update the product amount.
            - Enter the new product amount.
        7. Select `4` to update the product price.
            - Enter the new product price.
        9. Select `0` to go back to the previous menu.
    6. Select `4` to look up a price.
        - Enter the code of the product to look up.
    7. Select `5` to display your user's discount.
    8. Select `6` to list the product catalog of a location.
        - Enter the code of the location to list the catalog.
    9. Select `7` to register a new client.
        1. Select `1` to process new account requests.
           - All pending requests will be displayed one by one.
           - Enter `Y` to approve a request or `N` to deny the request.
        3. Select `2` to manually add a new client.
            - Enter the client's city.
            - Enter the client's name.
            - Enter the client's phone number.
            - Enter the client's user type.
            - Enter the client's national ID.
        5. Select `0` to go back to the previous menu.
    11. Select `8` to generate a report.
        1. Select `1` to display the last 2 products added to the invetory.
        2. Select `2` to display the last product updated.
        3. Select `3` to display the last product deleted.
        4. Select `4` to display the best selling product.
        5. Select `5` to display the worst selling product of each location.
        6. Select `6` to display the client with the most purchases.
        7. Select `7` to display the client with the least purchases.
        8. Select `8` to display the amount of purchases of each client.
        9. Select `9` to display the most visited location.
        10. Select `10` to display the least visited location.
        11. Select `11` to display the administrator with the most activity.
        12. Select `12` to display the administrator with the least activity.
        13. Select `0` to go back to the previous menu.
    13. Select `0` to exit the application.
4. If the user is a seller the menu options will be as follows:
    1. Select `1` to look up a price.
        - Enter the code of the product to look up.
    2. Select `2` to look up the discount of a client.
        - Enter the national ID of the client.
    3. Select `3` to list the product catalog of a location.
        - Enter the code of the location to list the catalog.
    5. Select `0` to exit the application.
5. If the user is a guest the menu options will be as follows:
    1. Select `1` to look up a price.
        - Enter the code of the product to look up.
    2. Select `2` to list the product catalog of a location.
        - Enter the code of the location to list the catalog.
    3. Select `0` to exit the application.
