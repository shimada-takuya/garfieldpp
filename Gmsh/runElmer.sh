#gmsh grid solver


gmsh wire_tpc.geo -3 -optimize -order 2 -format msh2
#gmsh wire_tpc.geo -3 -optimize -order 2
ElmerGrid 14 2 wire_tpc.msh -autoclean
#ElmerGrid 14 2 wire_tpc.msh -autoclean
ElmerSolver wire_tpc.sif
