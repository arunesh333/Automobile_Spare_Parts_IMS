# AutoSpare Inventory System (C++)

Simple inventory management system made for Typical Auto Mobile Spareparts Shop in C++.  
Built it to handle product sales, customer details, loyalty points, and track profit — mainly for an auto spare parts shop use case.

---

## 🎯 Project Objective

To build a basic system that:
- Stores and displays items
- Handles item sales with stock reduction
- Adds customers and tracks how much they’ve spent
- Gives loyalty points (esp. for mechanics)
- Calculates the overall profit made

---

## 🔧 Tech Stack

- **Language**: C++ (compiled with G++)
- **File Handling**: CSV for storing and loading data
- **Interface**: Just a CLI menu (no GUI)
- **Environment**: VS Code + g++ (Windows)

---

## 🛠 Tools Used

- g++ compiler  
- VS Code  
- Excel (for editing the CSV manually sometimes)  
- Git & GitHub (for version control)

---

## 📘 What I Learnt

- Proper use of classes and arrays in C++
- Reading/writing to CSV files
- Using `getline`, `cin.ignore()`, and fixing input bugs
- How to simulate real-world logic like customers, stock, sales, etc.
- Debugging small, annoying logic issues that take forever to find 😑

---

## 😤 Challenges Faced

- CSV parsing kept breaking at first because of bad data or blank lines  
- Accidentally looped the wrong way while checking product IDs (classic logic bug)  
- Mixing `cin` with `getline()` caused annoying input handling issues  
- Handling `stoi()` and `stof()` safely — they kept throwing exceptions on malformed CSV lines  
- Keeping customer type logic separate while calculating loyalty points without mixing it up

---

## 🌱 Future Scope

- Add login for admin (just basic password-based)
- Add search bar for product name / ID
- Maybe use JSON instead of CSV later
- GUI in the future? Maybe Qt or Python + C++ backend
- Export profit reports per day/month

---

## 📜 License

MIT — free to use, copy, or modify. Just don’t claim you wrote it from scratch if you didn’t 😄

---

## 👨‍💻 Author

**Arunesh E**
Electrcial and Electronics Engineering Student, SASTRA Deemed University  
Exploring C++,Java and Data Analytics  
Intersted in Building real-world, logic-driven systems that solve practical problems   
2005arunesh@gmail.com  
+91 9789834211  
🔗 [LinkedIn](https://www.linkedin.com/in/arunesh33/)

**Made this project to learn, mess up, fix it, and learn again.**
