-- CREATE DATABASE FINAL_PROJECT

USE FINAL_PROJECT;
 
CREATE TABLE Country (
	Id CHAR(3) PRIMARY KEY, 
    Name VARCHAR(256) NOT NULL
);

CREATE TABLE Ceo (
	Id INTEGER PRIMARY KEY, 
    NetWealth DECIMAL(14, 2) NOT NULL
);

CREATE TABLE Company (
	Id INTEGER PRIMARY KEY, 
    Name VARCHAR(256) NOT NULL, 
    CEO INTEGER NOT NULL, 
    nStocks INTEGER, 
    stockValue DECIMAL(6, 2),
	FOREIGN KEY (CEO) REFERENCES Ceo(Id)
);

CREATE TABLE CompanyCountry (
	Company INTEGER NOT NULL,
    Country CHAR(3) NOT NULL, 
    PRIMARY KEY(Company, Country), 
	FOREIGN KEY (Company) REFERENCES Company(Id),
	FOREIGN KEY (Country) REFERENCES Country(Id)
);

CREATE TABLE Department (
	Id INTEGER PRIMARY KEY, 
    Name VARCHAR(512), 
    Company INTEGER NOT NULL, 
	FOREIGN KEY (Company) REFERENCES Company(Id)
);

CREATE TABLE Employee (
    Id INT PRIMARY KEY,
    Name VARCHAR(256) NOT NULL,
    PersonalId CHAR(24) UNIQUE NOT NULL,
    Email VARCHAR(128) NOT NULL UNIQUE,
    Gender CHAR(1) CHECK (Gender IN ('M', 'F')),
    FullRemote BOOLEAN NOT NULL
);

CREATE TABLE EmployeeDepartment (
	Employee INTEGER, 
    Date DATE, 
    Department INTEGER,
    PRIMARY KEY (Employee, Date), 
	FOREIGN KEY (Employee) REFERENCES Employee(Id),
    FOREIGN KEY (Department) REFERENCES Department(Id)
);

CREATE TABLE Role (
	Id SMALLINT PRIMARY KEY, 
    Name VARCHAR(256) NOT NULL
);

CREATE TABLE EmployeeRole (
	Employee INTEGER NOT NULL,
    Date DATE NOT NULL, 
    AssignedRole SMALLINT NOT NULL, 
    Salary DECIMAL(8, 2) NOT NULL, 
    RoleStartingYear YEAR NOT NULL, 
    PRIMARY KEY (Employee, Date),
	FOREIGN KEY (Employee) REFERENCES Employee(Id),
	FOREIGN KEY (AssignedRole) REFERENCES Role(Id)
);

CREATE TABLE Office (
	Code CHAR(10) PRIMARY KEY, 
    Company INTEGER NOT NULL, 
    City VARCHAR(128) NOT NULL UNIQUE, 
    Street VARCHAR(256) NOT NULL UNIQUE,
    Number INTEGER NOT NULL UNIQUE, 
    Country CHAR(3) NOT NULL,
	FOREIGN KEY (Company) REFERENCES Company(Id),
    FOREIGN KEY (Country) REFERENCES Country(Id)
);

CREATE TABLE EmloyeeBadging (
	Employee INTEGER NOT NULL, 
    Office CHAR(10) NOT NULL, 
    BadgeIn DATETIME NOT NULL, 
    BadgeOut DATETIME, 
    PRIMARY KEY (Employee, Office, BadgeIn),
	FOREIGN KEY (Employee) REFERENCES Employee(Id),
	FOREIGN KEY (Office) REFERENCES Office(Code)
);

CREATE TABLE Report (
	Id SMALLINT PRIMARY KEY, 
    Name VARCHAR(128) NOT NULL, 
    Description VARCHAR(512) NOT NULL
);

CREATE TABLE UserReport (
	ReportId SMALLINT NOT NULL, 
    UserId INTEGER NOT NULL, 
    Date DATETIME NOT NULL, 
    PRIMARY KEY (ReportId, UserId, Date), 
	FOREIGN KEY (ReportId) REFERENCES Report(Id)
);

CREATE TABLE User (
	Id INTEGER PRIMARY KEY,
    Name VARCHAR(256) NOT NULL, 
    Email VARCHAR (128) UNIQUE, 
    Password CHAR(128) NOT NULL
);


