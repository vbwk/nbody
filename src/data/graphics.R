options(warn = -1)

library(ggplot2)
library(plotly)
library(htmlwidgets)

setwd("./data/")

load("sim.Rdata")

vdata = vdata %>%
	mutate(KE = 0.5 * mass * (sqrt(vx^2 + vy^2 + vz^2))^2, 
	       PE = mass * 9.81 * y, 
	       ME = KE + PE)

plot_KE = ggplot(data = vdata, aes(x = time, y = KE, color = particle)) +
	geom_line() +
	theme_light()

plot_PE = ggplot(data = vdata, aes(x = time, y = PE, color = particle)) +
	geom_line() +
	theme_light()

plot_ME = ggplot(data = vdata, aes(x = time, y = ME, color = particle)) +
	geom_line() +
	theme_light()

total_energy = vdata %>%
	select(time, KE, PE, ME) %>%
	group_by(time) %>%
	summarise(totalKE = sum(KE), 
		  totalPE = sum(PE),
		  totalME = sum(ME))

plot_TE = ggplot(data = total_energy, 
		 aes(x = time, y = totalME)) +
	geom_line() +
	geom_line(aes(x = time, y = totalKE)) +
	geom_line(aes(x = time, y = totalPE)) +
	theme_light()


ggsave("../graphics/plot_KE.png", plot = plot_KE)
ggsave("../graphics/plot_PE.png", plot = plot_PE)
ggsave("../graphics/plot_ME.png", plot = plot_ME)
ggsave("../graphics/plot_TE.png", plot = plot_TE)

## trajectory plot
#trajectory_plot = plot_ly(
#	data = vdata, 
#	x = ~x, y = ~y, z = ~z, 
#	color = ~particle, 
#	type = "scatter3d", 
#	mode = "lines", 
#	line = list(width = 1, alpha = 0.4), 
#	showlegend = F) %>%
#	layout(paper_bgcolor='#111111')
#
#saveWidget(trajectory_plot, file = "../graphics/trajectory_plot.html") 

