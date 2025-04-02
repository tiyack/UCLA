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
(5, 'Shopify', 5, 300000, 45.75),
(6, 'EY', 1, NULL, NULL); 

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

-- Office
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

