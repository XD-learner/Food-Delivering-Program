# 🍔 Food Delivery Management System (Admin Side)<hr>
## 📌 Overview
> [!NOTE]
> This is a simple C++ terminal-based program designed to help manage drivers and orders in a food delivery simulation. It's a basic prototype for educational purposes to practice managing orders and driver assignments.


## 🎯 Features

### 📋 Order Management

- Add, update, delete, and search for food orders.
- Track order status (Unassigned, Pending, Delivered).
- Assign orders to available drivers.


### 🚗 Driver Management

- Add, update, and delete driver records.
- Assign orders to drivers based on availability.
- Track delivery performance.

### 🔍 Filtering & Searching

- Search orders by Customer Name, Contact, Status, Driver Name, Order ID, etc.
- Search drivers by Name, Status, Total Deliveries, etc.


# 🚀 How It Works
## 📌 1. Understanding Order and Driver Status
### 🛒 Order Status:
> #### 🟡 Unassigned – Order has been created but not yet verified.
> #### 🟠 Pending – Order has been verified and placed in the queue, awaiting assignment.
> #### 🚚 Delivering – Order has been assigned to a driver and is on its way.
> #### ✅ Delivered – Order has been successfully completed.
<br>

### 🧑‍✈ Driver Status:
> #### ✅ Available – The driver is ready to take new orders.
> #### 🚛 Delivering – The driver is currently handling a delivery.
> #### ❌ Offline – The driver is not available for assignments.
<br>

## 📖 2. System Usage
### 🆕 1.Adding Orders
- Admin creates new orders by entering customer details, order contents, and delivery addresses.
- Newly created orders are stored in a linked list with the status "Unassigned."
### 📥 2.Queue Placement
- Admin verifies order details before placing them in the queue.
- Once added, the order status changes to "Pending," meaning it's ready for assignment to a driver.
### 📌 3.Assigning Orders
- Admin selects orders from the queue and assigns them to drivers with the status "Available."
- Once an order is assigned, the order status updates to "Delivering," and the driver’s status also updates to "Delivering."
### 🔄 4.Updating Status
- Once a driver completes a delivery, the admin marks the order as "Delivered."
- The driver’s status is then updated back to "Available," indicating they can take new assignments.
### 🛠️ 5.CRUD Operations
- Admin can Create, Read, Update, and Delete orders and drivers as needed.
### 🔍 6.Search Filters
- A search feature is provided to quickly locate specific orders or drivers based on different criteria.
---
## 🏗 Technologies Used

- C++ (Standard Library)
- Data Structures:
  - Linked Lists for storing orders and drivers
  - Queue for storing orders that are ready to be delivered.
- Algorithm
  - Linear Search

---
## 🚀 Installation & Usage
1️⃣ Clone the repository

```bash
git clone https://github.com/XD-learner/Food-Delivering-Program.git
cd food-delivery-system

```
2️⃣ Compile & Run
```bash
g++ main.cpp -o food_delivery_system
food_delivery_system

```



