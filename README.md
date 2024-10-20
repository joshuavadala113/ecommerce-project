# E-commerce Project

## Description
This is a simple e-commerce project built using C++ for the backend and HTML/CSS/JavaScript for the frontend.

## Setup Instructions

1. **Prerequisites:**
   - Install C++ compiler (g++, Visual Studio, etc.)
   - Install the C++ REST SDK.
   - Install a database (SQLite or MySQL).

2. **Build the Backend:**
   - Navigate to the `backend` directory.
   - Compile the code:
     ```bash
     g++ -o ecommerce main.cpp Product.cpp User.cpp Database.cpp -lcpprest -lboost_system -lssl -lcrypto
     ```

3. **Run the Backend:**
   - Start the server:
     ```bash
     ./ecommerce
     ```

4. **Serve the Frontend:**
   - Open `index.html` in a web browser.

## Usage
- Visit the frontend page to interact with the e-commerce site.
