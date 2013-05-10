These guys will plot out the PMT and ELLIE positions from a root file.

To make a minimal root file to plot, try

rat quickgeometryfile.mac

It should make a file geometrydata.root.  To plot it with python, one can run 

python PlotPMTpos.py geometrydata.root

Or to do it directly in root,

root
.L PlotPMTpos.cc+
PlotPMTpos("geometrydata.root")


