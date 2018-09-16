#pie chart
slices = c(3, 2, 1, 3, 2)
labels = c("(0.0-2.0) ", "(2.0-4.0) ", "(4.0-6.0) ", "(6.0-8.0) ", "(8.0-10.0) ")
percents = round(slices/sum(slices)*100)
labels <- paste(labels, percents)
labels <- paste(labels, "%", sep = "")
pie(slices, labels = labels, col = rainbow(length(slices)), main = "Pie chart, Y-Coordinates")