# AutoSpare Inventory System (C++)

A simple inventory management system built in C++ for a typical automobile spare parts shop.  
It manages product sales, customer data, loyalty points, and profit tracking through a command-line interface.

---

## Project Objective

To build a basic system that:
- Stores and displays inventory items
- Handles item sales and stock reduction
- Maintains customer details and spending
- Awards loyalty points (especially for mechanics)
- Calculates daily/overall profit

---

## Tech Stack

- **Language**: C++ (compiled using G++)
- **Data Handling**: CSV files (read/write)
- **Interface**: CLI-based menu system
- **Environment**: VS Code + g++ (Windows)

---

## Tools Used

- g++ compiler  
- Visual Studio Code  
- Microsoft Excel (for occasional CSV edits)  
- Git & GitHub (version control)

---

## What I Learned

- Object-oriented design in C++ using classes and arrays
- File I/O with `fstream` for persistent data storage
- Handling `cin`, `getline()`, `cin.ignore()` without input bugs
- Error handling with `stoi()` / `stof()` and `try-catch`
- Simulating real-world business logic in code
- Debugging input loops and logic branches patiently

---

## Challenges Faced

- CSV parsing kept failing due to blank lines or malformed data  
- Accidentally iterated the wrong way while validating product IDs  
- Mixing `cin` with `getline()` caused unexpected bugs  
- `stoi()` and `stof()` threw exceptions on bad CSV rows  
- Keeping customer type logic and loyalty point calculations consistent

---

## Future Scope

- Add password-protected admin login  
- Product search by ID or name  
- Switch to JSON or SQLite for better data handling  
- GUI (maybe Qt or Python with C++ backend)  
- Monthly/weekly profit report generation  

---

## 🚀 How to Run This Project in GitHub Codespaces

1. Open this repo in GitHub Codespaces or GitPod.
2. Compile the code:
   ```bash
   g++ Automobile_Spare_Parts_IMS.cpp -o new
3. And run as
     ./new
---

## License

Licensed under the **MIT License** — feel free to use, modify, or distribute with attribution.  
Please don’t claim the original work as your own.

---

## Author

**Arunesh E**  
Electrical and Electronics Engineering Student, SASTRA Deemed University  
Exploring C++, Java, and Data Analytics  
Interested in building real-world, logic-driven systems that solve practical problems  

📧 2005arunesh@gmail.com  
📱 +91 97898 34211  
🔗 [LinkedIn](https://www.linkedin.com/in/arunesh33/)

> *Made this project to learn, mess up, fix it, and learn again.*
