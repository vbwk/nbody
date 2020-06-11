options(warn = -1)

setwd("./data/")

## read data
position = read.csv("../outfiles/position.csv", header = F)
velocity = read.csv("../outfiles/velocity.csv", header = F)
time = read.csv("../outfiles/time.csv", header = F)
meta = read.delim("../outfiles/meta.txt", header = F)

## extract simulation parameters
system_name = as.character(meta[1, 1])
time_step = as.numeric(as.character(meta[2, 1]))
run_time = as.numeric(as.character(meta[3, 1]))
num_time_steps = run_time / time_step

## extract system parameters
initial_conditions = as.character(meta[4, 1])
num_particles = as.numeric(as.character(meta[5, 1]))
num_constraints = as.numeric(as.character(meta[6, 1]))
mass_values = as.numeric(as.character(meta[7:(6 + num_particles), 1]))
constraint_values = as.numeric(as.character(meta[(7 + num_particles):
	(6 + num_particles + num_constraints), 1]))

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

# merge position and velocity data
vdata[ , 4:6] = position
vdata[ , 7:9] = velocity

## rename columns
names(vdata)[4:9] = c("x", "y", "z", "vx", "vy", "vz")

## compute momentum data
vdata$px = vdata$mass * vdata$vx
vdata$py = vdata$mass * vdata$vy
vdata$pz = vdata$mass * vdata$vz

### compute energy data [pend]
#vdata$ke = 0.5 * vdata$mass * 
#	((vdata$vx)**2 + (vdata$vy)**2 + (vdata$vz)**2)
#vdata$pe = vdata$mass * 9.81 * vdata$z
#vdata$te = vdata$ke + vdata$pe

## make sub-sampled dataset
sampling_rate = run_time 

sub_vdata = vdata[seq(1, nrow(position), sampling_rate), ]

if (num_particles > 1) {
	for (i in 2:num_particles) {
		extra_sub_vdata = vdata[seq(i, nrow(position), 
					    sampling_rate), ]
		sub_vdata = rbind(sub_vdata, extra_sub_vdata)
	}
}

## make horizontal dataset [reshape]
hdata = reshape(vdata, 
		direction = "wide", 
		idvar = "time", 
		timevar = "particle", 
		v.names = c("mass", "x", "y", "z", 
			    "vx", "vy", "vz", 
			    "px", "py", "pz")) 

## save data
save(time_step, run_time, num_time_steps, num_particles, 
     num_constraints, initial_conditions, mass_values, 
     constraint_values, vdata, sub_vdata, hdata, 
     file = "simulation.Rdata")

write.csv(vdata, "trajectories.csv")
#write.csv(hdata, "hdata.csv")
