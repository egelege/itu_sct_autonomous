# Restaurant Bot

Restaurant Bot is an innovative tool designed to generate dynamic, balanced menus based on user preferences. Leveraging robust object-oriented programming techniques and the json.hpp, this project ensures flexibility, extensibility, and efficient data handling.

---

## Table of Contents

- [Overview](#overview)
- [Class Relationships](#class-relationships)
  - [Inheritance](#inheritance)
  - [Association](#association)
  - [Composition](#composition)
  - [Aggregation](#aggregation)
- [Object-Oriented Concepts](#object-oriented-concepts)
- [Taste Balance Functionality](#taste-balance-functionality)
- [Conclusion](#conclusion)

---

## Overview

Restaurant Bot is built to help users create menus that suit their taste preferences. Whether you choose a randomly generated menu or specify your desired flavor profile, the bot is engineered to deliver a balanced dining experience. The project integrates object-oriented design principles to manage various food types and uses RapidJSON for seamless JSON data processing.

---

## Class Relationships

### Inheritance

- **Base Class: `MenuItem`**  
  An abstract class that defines pure virtual functions to get and set common attributes such as name, price, and taste balance.

- **Derived Classes:**  
  Classes like `Starter`, `Salad`, `MainCourse`, `Drink`, `Appetizer`, and `Dessert` inherit from `MenuItem`. They override the base class functions and introduce additional properties and behaviors specific to each food category.

### Association

- **User and Menu:**  
  The `User` class is associated with the `Menu` class by containing a `Menu` object as one of its attributes. This indicates a loose coupling where the user and menu can exist independently, yet interact with each other.

### Composition

- **Menu and MenuItems:**  
  The `Menu` class is composed of a collection of `MenuItem` pointers (stored, for instance, in a vector). This composition relationship means that the `Menu` is responsible for managing the lifecycle of its `MenuItem` objects—when the `Menu` is destroyed, its items are also cleaned up.

### Aggregation

- **Overall Taste Balance and Total Cost:**  
  The `Menu` class aggregates key attributes like overall taste balance and total cost. Unlike composition, these attributes can exist independently outside the `Menu`, even though they are essential parts of its structure.

---

## Object-Oriented Concepts

- **Inheritance:**  
  This mechanism allows new classes to derive common properties and behaviors from existing ones, streamlining the creation of a hierarchy of food items with shared attributes.

- **Association:**  
  A relationship where classes are linked but maintain their independence. The relationship between `User` and `Menu` is a prime example.

- **Composition:**  
  A strong "has-a" relationship where the contained objects' lifecycle is fully managed by the container. The `Menu`'s management of its `MenuItem` objects is an illustration of this concept.

- **Aggregation:**  
  A specialized form of association where the component parts can exist independently. In this project, the overall taste balance and total cost are aggregated within the `Menu`, yet are standalone attributes.

---

## Taste Balance Functionality

Restaurant Bot offers two main methods for menu creation:

- **Random Menu Generation:**  
  The bot can randomly select items from various food categories, providing a diverse menu experience.

- **Customized Taste Balance:**  
  Users can specify their desired taste preferences—including sweetness, saltiness, sourness, bitterness, and umami. Based on these inputs, the bot intelligently suggests food items that match the specified flavor profile, ensuring the final menu aligns perfectly with the user’s taste.

---

## Conclusion

Restaurant Bot combines the power of object-oriented programming with efficient JSON processing to offer a flexible and user-centric menu generation tool. Whether you're looking for a surprise or a meticulously tailored dining experience, Restaurant Bot adapts to your needs. Contributions and enhancements are warmly welcomed!

---

*Feel free to explore the repository, provide feedback, and contribute to the project.*
