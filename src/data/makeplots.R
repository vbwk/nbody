library(ggplot2)
library(plotly)
library(htmlwidgets)

setwd("./data/")

load("simulation.Rdata")

## static plot
static_plot = plot_ly(
	data = vdata, 
	x = ~x, y = ~y, z = ~z, 
        color = ~particle, 
        type = "scatter3d", 
        mode = "lines", 
        line = list(width = 1, alpha = 0.4), 
        showlegend = F) %>%
	layout(paper_bgcolor='#111111')

htmlwidgets::saveWidget(static_plot, file = "static_plot.html") 

animated_plot = plot_ly(
	data = sub_vdata,
	x = ~x, y = ~y, z = ~z, 
        color = ~particle, 
        type = "scatter3d", 
        mode = "lines", 
        line = list(width = 1, alpha = 0.4), 
        showlegend = F) %>%
	layout(paper_bgcolor='#111111') %>%
	
	add_trace(x = ~x, y = ~y, z = ~z, 
	color = ~particle, 
	type = "scatter3d", 
	mode = "markers", 
	marker = list(size = 10), 
	frame = ~time, 
	showlegend = T)

animated_plot = animated_plot %>%
	layout(paper_pgcolor='#111111')

animated_plot = animated_plot %>%
	animation_opts(frame = 20, transition = 0)

#x_range = list(nticks = 10, range = c(-5, 5))
#y_range = list(nticks = 10, range = c(-5, 5))
#z_range = list(nticks = 10, range = c(-5, 5))
#
#animated_plot = animated_plot %>%
#	layout(scene = list(xaxis = x_range,
#	       yaxis = y_range,
#	       zaxis = z_range),
#	       paper_bgcolor='#111111')

htmlwidgets::saveWidget(animated_plot, file = "animated_plot.html")

## energy plot
energy_plot = ggplot(data = vdata, aes(x = time, y = te)) +
	geom_line(size = 0.1) +
	facet_wrap(~particle) +
	theme_light()

ggsave(filename = "energy.png", plot = energy_plot, device = "png")
