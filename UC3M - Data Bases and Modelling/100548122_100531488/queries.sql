-- 1
SELECT Name, Email, Gender
FROM EMPLOYEE;

-- 2
SELECT *
FROM COMPANY
WHERE nStocks is not null AND nStocks != 0;

-- 3
SELECT C.Name, COUNT(CC.Country) AS Num_Countries
FROM COMPANYCOUNTRY CC, COMPANY C
WHERE CC.Company = C.Id
GROUP BY CC.Company
ORDER BY C.Name;

-- 4
SELECT Country, Count(Company) AS Num_Companies
FROM COMPANYCOUNTRY
GROUP BY Country
HAVING Count(Company) > 0
ORDER BY Count(Company) DESC;

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
	AND E.Name LIKE 'Maria%';

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
FROM EmployeeDepartment ED INNER JOIN EmployeeRole ER ON ED.Employee = ER.Employee AND ED.Employee = '1' -- in replacement of ID '12345678' (substitute)
ORDER BY Department_Date DESC, Role_Date DESC;

-- 9
SELECT R.ID, R.Name, R.Description, UR.UserId, UR.Date
FROM Report R, UserReport UR
WHERE UR.ReportID = R.ID
ORDER BY UR.Date DESC;

-- 10
SELECT E.Name, E.Email, EB.employee, E.fullRemote
FROM Employee E LEFT JOIN EmloyeeBadging EB ON E.id = EB.employee AND YEAR(EB.badgeIn) = 2024
WHERE E.fullRemote = FALSE AND EB.employee IS NULL;

-- 11 
SELECT c.Name AS CompanyName, Ceo.Id AS CEOId, Ceo.NetWealth AS CEONetWealth, 
	(c.nStocks * c.stockValue) AS CompanyNetWealth
FROM Company c, Ceo  
WHERE c.CEO = ceo.Id AND c.nStocks IS NOT NULL AND c.stockValue IS NOT NULL
ORDER BY CompanyNetWealth DESC, c.Name ASC;

-- 12
SELECT e.Gender, r.Name AS Role, YEAR(CURDATE()) - er.RoleStartingYear AS ExperienceYears, 
	AVG(er.Salary) AS AverageSalary
FROM Employee e,EmployeeRole er, Role r,  EmployeeDepartment ed,  Department d, Company c  
WHERE e.Id = er.Employee AND er.AssignedRole = r.Id AND e.Id = ed.Employee AND 
	ed.Department = d.Id AND d.Company = c.Id AND c.Name = 'Netflix'
GROUP BY e.Gender, r.Name, ExperienceYears;


