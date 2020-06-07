setwd("./data/")
## read data
position = read.csv("../outfiles/position.csv", header = F)
velocity = read.csv("../outfiles/velocity.csv", header = F)
time = read.csv("../outfiles/time.csv", header = F)
meta = read.delim("../outfiles/meta.txt", header = F)

## extract simulation parameters
DT = as.numeric(as.character(meta[2,1]))
TT = as.numeric(as.character(meta[3,1]))
NT = TT / DT

## extract system parameters
system_name = as.character(meta[4,1])
N = as.numeric(as.character(meta[5,1]))
K = as.numeric(as.character(meta[6,1]))
IC = as.character(meta[7,1])
M_values = as.numeric(as.character(meta[8:(7+N),1]))
K_values = as.numeric(as.character(meta[(8+N):(7+N+K),1]))

## build dataset:

## create time indicator
time_indicator = NULL
for (i in 1:NT) {
	time_indicator = c(time_indicator, rep(time$V1[i], N)) 
}

vdata = data.frame(time = time_indicator)

## create mass indicator 
mass_labels = NULL
for (i in 1:N) {
	mass_labels[i] = paste("m", i, sep = "")
}

mass_indicator = rep(mass_labels, NT)

vdata$particle = mass_indicator

## add mass values
vdata$mass = rep(M_values, NT)

# merge position and velocity data
vdata[ , 4:6] = position
vdata[ , 7:9] = velocity

## rename columns
names(vdata)[4:9] = c("x", "y", "z", "vx", "vy", "vz")

## compute momentum data
vdata$px = vdata$mass * vdata$vx
vdata$py = vdata$mass * vdata$vy
vdata$pz = vdata$mass * vdata$vz

## compute energy data [pend]
vdata$ke = 0.5 * vdata$mass * 
	((vdata$vx)**2 + (vdata$vy)**2 + (vdata$vz)**2)
vdata$pe = vdata$mass * 9.81 * vdata$z
vdata$te = vdata$ke + vdata$pe

## make sub-sampled dataset
sampling_rate = TT 

sub_vdata = vdata[seq(1, nrow(position), sampling_rate), ]

if (N > 1) {
	for (i in 2:N) {
		extra_sub_vdata = vdata[seq(i, nrow(position), 
					    sampling_rate), ]
		sub_vdata = rbind(sub_vdata, extra_sub_vdata)
	}
}

## make horizontal dataset [reshape]
hdata = reshape(vdata, direction = "wide", idvar = "time", 
		timevar = "particle", v.names = 
		c("mass", "x", "y", "z", "vx", "vy", "vz", 
		"px", "py", "pz", "ke", "pe", "te")) 

## save data
save(DT, TT, NT, N, K, IC, M_values, K_values, vdata, 
     sub_vdata, hdata, file = "simulation.Rdata")

#write.csv(hdata, "hdata.csv")
write.csv(vdata, "vdata.csv")
write.csv(sub_vdata, "sub_vdata.csv")
