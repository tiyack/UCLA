#Q1
heights <- c(67, 65, 60)
print(heights)

names <- c("Tiya", "Sanchita", "Simran")
print(names)

#this commands combines the 2 vectors giving us a matrix with 2 columns
cbind(heights, names)
class(cbind(heights, names)) #which we can verify here

#Q2 - downloading the db
NCbirths <- read.csv(file = "births.csv")
head(NCbirths)

#Q3
find.package("maps")
library(maps)
map("state")

#Q4
weights <- NCbirths$weight #it looks like the weights are in ounces
weights_in_pounds <- weights / 16
weights_in_pounds[1:20]

#Q5
mean(weights_in_pounds)
tally(NCbirths$Habit, format = "percent")

#Q6
histogram(weights_in_pounds, breaks = 3)
histogram(weights_in_pounds, breaks = 20)
histogram(weights_in_pounds, breaks = 100)

#Q7
boxplot(NCbirths$Mage, NCbirths$Fage, names = c("Mother's Ages", "Father's Ages"))

#Q8
histogram(~ weight | Habit, data = NCbirths, layout = c(1, 2))

#Q9
dotPlot(weights_in_pounds, xlab = "Weight in pounds", nint = 20)

#Q10 creating a 2 way table between mothers smoking habts and 
prop.table(tally(~Habit | Premie, data = NCbirths), margin = 1)

#Q11
plot(NCbirths$weight ~ NCbirths$Mage, cex = 0.25, ylab = "Baby Weight (oz)", 
     xlab = "Mother Age", main = "Baby weight vs. Mother Age")
