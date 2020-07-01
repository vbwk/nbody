options(warn = -1)

library(ggplot2)
library(plotly)
library(htmlwidgets)

setwd("./data/")

load("sim.Rdata")

## trajectory plot
trajectory_plot = plot_ly(
	data = vdata, 
	x = ~x, y = ~y, z = ~z, 
	color = ~particle, 
	type = "scatter3d", 
	mode = "lines", 
	line = list(width = 1, alpha = 0.4), 
	showlegend = F) %>%
	layout(paper_bgcolor='#111111')

saveWidget(trajectory_plot, file = "../graphics/trajectory_plot.html") 

