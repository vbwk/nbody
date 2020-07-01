options(warn = -1)

setwd("./data/")

## read data
state_cartesian = read.csv("sim_data_cartesian.csv", header = F) 
#data_generalized = read.csv("sim_data_generalized.csv", header = F) 
time = read.csv("sim_timedata.csv", header = F) 
meta = read.delim("sim_metadata.txt", header = F)

## extract position and velocity data
position_cartesian = state_cartesian[seq(1, nrow(state_cartesian), 2), ]
velocity_cartesian = state_cartesian[seq(2, nrow(state_cartesian), 2), ]

## extract simulation parameters
system_name = as.character(meta[1, 1]) 
initial_conditions = as.character(meta[2, 1]) 
time_step = as.numeric(as.character(meta[3, 1]))
run_time = as.numeric(as.character(meta[4, 1]))
num_time_steps = run_time / time_step

## extract system parameters
num_particles = as.integer(as.character(meta[5, 1]))
num_hol_constraints = as.integer(as.character(meta[6, 1]))
num_semihol_constraints = as.integer(as.character(meta[7, 1]))
num_ineq_constraints = as.integer(as.character(meta[8, 1]))
mass_values = as.numeric(as.character(meta[9:(8 + num_particles), 1]))
#constraint_values = as.numeric(as.character(meta[(7 + num_particles):
	#(6 + num_particles + num_constraints), 1]))

## build dataset:

## create time indicator
time_indicator = NULL 
for (i in 1:num_time_steps) {
	time_indicator = c(time_indicator, 
			   rep(time$V1[i], num_particles)) 
}

vdata = data.frame(time = time_indicator)

## create particle indicator 
mass_labels = NULL
for (i in 1:num_particles) {
	mass_labels[i] = paste("m", i, sep = "")
}

particle_indicator = rep(mass_labels, num_time_steps)

vdata$particle = particle_indicator

## add mass values
vdata$mass = rep(mass_values, num_time_steps)

## merge cartesian state data
vdata[ , 4:6] = position_cartesian
vdata[ , 7:9] = velocity_cartesian

## rename columns
names(vdata)[4:9] = c("x", "y", "z", "dot_x", "dot_y", "dot_z")

## compute momentum data
vdata$p_x = vdata$mass * vdata$dot_x
vdata$p_y = vdata$mass * vdata$dot_y
vdata$p_z = vdata$mass * vdata$dot_z

## make horizontal dataset [reshape]
hdata = reshape(vdata, 
		direction = "wide", 
		idvar = "time", 
		timevar = "particle", 
		v.names = c("mass", "x", "y", "z", 
			    "dot_x", "dot_y", "dot_z", 
			    "p_x", "p_y", "p_z")) 

## save data
save(time_step, run_time, num_time_steps, num_particles, 
     initial_conditions, mass_values, vdata, hdata,
     file = "sim.Rdata")

#write.csv(vdata, "debug.csv")
