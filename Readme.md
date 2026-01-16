# 🔐 Secrets Manager (DPA)

A simple and secure command-line Secrets Manager written in C that allows you to store, retrieve, and manage your passwords safely.  
All passwords are encrypted using **AES encryption** before being stored in the database, ensuring your sensitive data remains protected even if the database is compromised.

---

## ✨ Features
- AES-based encryption for all stored passwords  
- Tag-based password management  
- SQLite database for lightweight and fast storage  
- Simple CLI interface  
- Works completely offline  

---

## 🛠️ Technologies Used
- **C** – Core implementation  
- **AES Encryption** – For secure password storage  
- **SQLite** – Database to store encrypted passwords and tags  
- **OpenSSL / Crypto library** – For cryptographic operations  

---

## 📦 Commands

Your executable is named `dpa`. The following commands are available:

### 1. Add a new secret
```bash
dpa add -t <tag> -p <password>
```

### 2. Retrieve stored secres
```bash
dpa get -t <tag>
```

### 3. Retrieve all stored tags
```bash
dpa getall
```

### 4. Delete a secret based on tag
```bash
dpa delete -t <tag>
```


## Note
You will be prompted for the master key after add, get and delete commands. 

