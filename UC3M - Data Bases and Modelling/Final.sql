-- CREATE DATABASE FINAL_PROJECT

USE FINAL_PROJECT;
 
CREATE TABLE Country (
	Id CHAR(3) PRIMARY KEY, 
    Name VARCHAR(256) NOT NULL
);

CREATE TABLE Ceo (
	Id INTEGER PRIMARY KEY, 
    NetWealth DECIMAL(14, 2) -- NOT NULL??
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
    Company INTEGER NOT NULL, -- should this be here??
	FOREIGN KEY (Company) REFERENCES Company(Id)
);

CREATE TABLE Employee (
    Id INT PRIMARY KEY,
    Name VARCHAR(256) NOT NULL,
    PersonalId CHAR(24) UNIQUE NOT NULL,
    Email VARCHAR(128) NOT NULL UNIQUE,
    Gender CHAR(1) CHECK (Gender IN ('M', 'F')),
    FullRemote BOOLEAN NOT NULL
    -- CONSTRAINT chk1 check (gender = 'F' or gender = 'M')
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

-- 1
SELECT Name, Email, Gender
FROM EMPLOYEE

-- 2
SELECT *
FROM COMPANY
WHERE nStocks is not null AND nStocks != 0

-- 3
SELECT C.Name, COUNT(CC.Country) AS Num_Countries
FROM COMPANYCOUNTRY CC, COMPANY C
WHERE CC.Company = C.Id
GROUP BY CC.Company
ORDER BY C.Name

-- 4
SELECT Country, Count(Company) AS Num_Companies
FROM COMPANYCOUNTRY
GROUP BY Country
HAVING Count(Company) > 0
ORDER BY Count(Company) DESC

-- 5 
SELECT d.Name AS DepartmentName, r.Name AS RoleName, COUNT(e.Id) AS EmployeeCount
FROM Employee e,EmployeeDepartment ed, Department d, Company c, 
    EmployeeRole er, Role r 
WHERE er.AssignedRole = r.Id AND e.Id = er.Employee AND 
    d.Company = c.Id AND ed.Department = d.Id AND 
	e.Id = ed.Employee AND c.Name = 'Microsoft' 
    AND ed.Date = (
		SELECT MAX(ed2.Date)
		FROM EmployeeDepartment ed2
		WHERE ed2.Employee = e.Id
	) 
    AND er.Date = (
		SELECT MAX(er2.Date)
        FROM EmployeeRole er2
        WHERE er2.Employee = e.Id
	)
GROUP BY d.Name, r.Name
ORDER BY d.Name ASC, EmployeeCount DESC;

-- 6 
SELECT E.ID AS Employee_ID, EB.BadgeIn, EB.BadgeOut, 
	O.Code AS Office_Code, O.City, O.Street, O.Number, O.Country
FROM EmloyeeBadging EB, OFFICE O, EMPLOYEE E
WHERE EB.Office = O.Code AND EB.Employee = E.ID 
	AND E.Name LIKE 'Maria%'

-- 7 
SELECT E.Name AS Employee, C.Name AS Company, D.Name AS Department
FROM Employee E, Company C, Department D, EmployeeDepartment ED, EmloyeeBadging EB
WHERE E.ID = ED.Employee AND ED.Department = D.ID AND D.Company = C.ID AND EB.Employee = E.ID
	AND DATE(EB.BadgeIn) = DATE '2024-06-01' AND ED.Date = (
		SELECT MAX(ED2.date) 
        FROM EmployeeDepartment ED2 
        WHERE ED2.Employee = E.ID
	);

-- 8
SELECT ED.Employee, ED.Date AS Department_Date, ED.Department, 
	ER.Date AS Role_Date, ER.AssignedRole, ER.RoleStartingYear
FROM EmployeeDepartment ED INNER JOIN EmployeeRole ER ON ED.Employee = ER.Employee AND ED.Employee = '1'
ORDER BY Department_Date DESC, Role_Date DESC

-- 9
SELECT R.ID, R.Name, R.Description, UR.UserId, UR.Date
FROM Report R, UserReport UR
WHERE UR.ReportID = R.ID
ORDER BY UR.Date DESC

-- 10
SELECT E.Name, E.Email, EB.employee, E.fullRemote
FROM Employee E LEFT JOIN EmloyeeBadging EB ON E.id = EB.employee AND YEAR(EB.badgeIn) = 2024
WHERE E.fullRemote = FALSE AND EB.employee IS NULL;

-- 11 
SELECT c.Name AS CompanyName, Ceo.Id AS CEOId, Ceo.NetWealth AS CEONetWealth, 
	(c.nStocks * c.stockValue) AS CompanyNetWealth
FROM Company c, Ceo  
WHERE c.CEO = ceo.Id AND c.nStocks IS NOT NULL AND c.stockValue IS NOT NULL
ORDER BY CompanyNetWealth DESC,c.Name ASC;

-- 12
SELECT e.Gender, r.Name AS Role, YEAR(CURDATE()) - er.RoleStartingYear AS ExperienceYears, 
	AVG(er.Salary) AS AverageSalary
FROM Employee e,EmployeeRole er, Role r,  EmployeeDepartment ed,  Department d, Company c  
WHERE e.Id = er.Employee AND er.AssignedRole = r.Id AND e.Id = ed.Employee AND 
	ed.Department = d.Id AND d.Company = c.Id AND c.Name = 'Netflix'
GROUP BY e.Gender, r.Name, ExperienceYears;



-- Country
INSERT INTO Country (Id, Name) VALUES
('USA', 'United States'),
('ESP', 'Spain'),
('IND', 'India'),
('CAN', 'Canada'),
('DEU', 'Germany');

-- Ceo
INSERT INTO Ceo (Id, NetWealth) VALUES
(1, 1000000000.00), (2, 500000000.00), (3, 300000000.00), 
(4, 700000000.00), (5, 150000000.00);

-- Company
INSERT INTO Company (Id, Name, CEO, nStocks, stockValue) VALUES
(1, 'Microsoft', 1, 1000000, 250.00),
(2, 'Netflix', 2, 500000, 350.75),
(3, 'EcoWorld', 3, 80000, 100.25),
(4, 'Tesla', 4, 1500000, 800.50),
(5, 'Shopify', 5, 300000, 45.75)
(6, 'EY', 1, NULL, NULL); -- ?

-- CompanyCountry
INSERT INTO CompanyCountry (Company, Country) VALUES
(1, 'USA'), (2, 'USA'), (2, 'ESP'), (3, 'IND'), (4, 'USA'), (5, 'CAN');

-- Department
INSERT INTO Department (Id, Name, Company) VALUES
(1, 'Engineering', 1), (2, 'Marketing', 2), (3, 'R&D', 3),
(4, 'Sales', 4), (5, 'Operations', 5), (6, 'Operations', 4), (7, 'Operations', 2);

-- Employee
INSERT INTO Employee (Id, Name, PersonalId, Email, Gender, FullRemote) VALUES
(1, 'Maria Lopez', '1234567890ABCDEFGHIJKL', 'maria.lopez@microsoft.com', 'F', FALSE),
(2, 'John Smith', '9876543210ABCDEFGHIJKL', 'john.smith@netflix.com', 'M', TRUE),
(3, 'Alice Brown', '5555555555ABCDEFGHIJKL', 'alice.brown@ecoworld.com', 'F', TRUE),
(4, 'Mark Davis', '1111111111ABCDEFGHIJKL', 'mark.davis@tesla.com', 'M', FALSE),
(5, 'Jane Doe', '2222222222ABCDEFGHIJKL', 'jane.doe@shopify.com', 'F', FALSE),
(6, 'Jan Do', '2222223422ABCDEFGHIJKL', 'jan.do@shopify.com', 'F', FALSE);

-- EmployeeDepartment
INSERT INTO EmployeeDepartment (Employee, Date, Department) VALUES
(1, '2024-01-01', 1), (2, '2024-01-02', 2), (3, '2024-01-03', 3),
(4, '2024-01-04', 4), (5, '2024-01-05', 5), (1, '2022-01-01', 2), 
(4, '2024-07-02', 6), (6, '2020-01-01', 1);

-- Role
INSERT INTO Role (Id, Name) VALUES
(1, 'Developer'), (2, 'Manager'), (3, 'Analyst');

-- EmployeeRole
INSERT INTO EmployeeRole (Employee, Date, AssignedRole, Salary, RoleStartingYear) VALUES
(1, '2024-01-01', 1, 80000.00, 2020),
(2, '2024-01-02', 2, 120000.00, 2018),
(3, '2024-01-03', 3, 95000.00, 2021),
(4, '2024-01-04', 2, 110000.00, 2019),
(5, '2024-01-05', 1, 85000.00, 2022), 
(4, '2024-07-02', 3, 85000.00, 2022),
(4, '2023-07-02', 3, 85000.00, 2022),
(6, '2020-01-01', 1, 8500.00, 2020),
(1, '2021-01-01', 3, 8500.00, 2021); 

Office
INSERT INTO Office (Code, Company, City, Street, Number, Country) VALUES
('OFF001', 1, 'Seattle', 'Microsoft Way', 1, 'USA'),
('OFF002', 2, 'Los Gatos', 'Netflix Street', 456, 'USA'),
('OFF003', 3, 'Mumbai', 'Eco Avenue', 123, 'IND'),
('OFF004', 4, 'Palo Alto', 'Tesla Drive', 789, 'USA'),
('OFF005', 5, 'Toronto', 'Shopify Road', 300, 'CAN');

-- EmployeeBadging
INSERT INTO EmloyeeBadging (Employee, Office, BadgeIn, BadgeOut) VALUES
(1, 'OFF001', '2024-06-01 08:00:00', '2024-06-01 17:00:00'),
(2, 'OFF002', '2024-06-01 09:00:00', NULL),
(3, 'OFF003', '2024-06-01 10:00:00', '2024-06-01 18:00:00'),
(4, 'OFF004', '2024-06-01 07:00:00', '2024-06-01 15:00:00'),
(5, 'OFF005', '2024-06-01 08:30:00', NULL), 
(1, 'OFF001', '2024-06-02 08:00:00', NULL),
(6, 'OFF001', '2023-06-02 08:00:00', NULL);

-- Report
INSERT INTO Report (Id, Name, Description) VALUES
(1, 'Annual Report', 'Annual performance'),
(2, 'Quarterly Report', 'Quarterly performance'),
(3, 'Diversity Report', 'Gender diversity in roles');

-- User
INSERT INTO User (Id, Name, Email, Password) VALUES
(1, 'Auditor A', 'A@test.com', '123'),
(2, 'Auditor B', 'B@test.com', '456'),
(3, 'Auditor C', 'C@test.com', '789');

-- UserReport`
INSERT INTO UserReport (ReportId, UserId, Date) VALUES
(1, 1, '2024-12-01 10:00:00'),
(2, 2, '2024-12-02 11:00:00'),
(3, 3, '2024-12-03 09:00:00');

