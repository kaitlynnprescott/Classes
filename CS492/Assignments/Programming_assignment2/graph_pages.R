rm(list=ls())

LRUpre <- c(103972, 96374, 94148, 92945, 102813)

FIFOpre <- c(106533, 102004, 107567, 120698, 171487)

CLOCKpre <- c(104076, 96391, 94681, 94419, 171487)

LRUd <- c(189438, 140637, 116581, 104094, 99207)

FIFOd <- c(190759, 148927, 128419, 123269, 133434)

CLOCKd <- c(189473, 140689, 116827, 105927, 115515)

yrange <- range(0, 200000)
png(file = "prepage_algos.jpg")

plot(LRUpre, type = "o", col= "firebrick", ylim = yrange, axes = FALSE, ann = FALSE)
axis(1, at=1:5, lab=c("1", "2", "4", "8", "16"))
axis(2, las=1, at=10000*0:yrange[2], cex.axis = 0.5)
box()
lines(FIFOpre, type = "o", col = "cornflowerblue")
lines(CLOCKpre, type = "o", col = "forestgreen")
title(main = "Prepaging Algorithm Results", col.main="magenta4", font.main=4)
title(xlab = "Page Size", col.lab="turquoise4")
title(ylab = "Page Swaps", col.lab="turquoise4")

legend(1, yrange[2], c("LRU", "FIFO", "Clock"), cex = 0.8, col = c("firebrick", "cornflowerblue", "forestgreen"), pch=21:22, lty=1:2)

dev.off()

png(file = "demand_algos.jpg")

plot(LRUd, type = "o", col= "firebrick", ylim = yrange, axes = FALSE, ann = FALSE)
axis(1, at=1:5, lab=c("1", "2", "4", "8", "16"))
axis(2, las=1, at=10000*0:yrange[2], cex.axis = 0.5)
box()
lines(FIFOd, type = "o", col = "cornflowerblue")
lines(CLOCKd, type = "o", col = "forestgreen")
title(main = "Demand Paging Algorithm Results", col.main="magenta4", font.main=4)
title(xlab = "Page Size", col.lab="turquoise4")
title(ylab = "Page Swaps", col.lab="turquoise4")

legend(1, 30000, c("LRU", "FIFO", "Clock"), cex = 0.8, col = c("firebrick", "cornflowerblue", "forestgreen"), pch=21:22, lty=1:2)

dev.off()