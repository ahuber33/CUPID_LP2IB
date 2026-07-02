for N in 0
do
    for thickness in 45 46 47 48 49 50 51 52 53 54 55 56 57 58 59 60 61 62 63 64 65 66 67 68 69 70 71 72 73 74 75 76 77 78 79 80 81 82 83 84 85
    do
    	until [ -e ../Resultats/coating_thickness/output_Si_SiN_"$thickness"mm.root ]
    	do
		./SCOPSim output_Si_SiN_"$thickness"mm 10000 vrml.mac OFF LDMat=Silicon LDCoatRINDEX=1.97 LDCoatThickness="$thickness"
		mv ../Resultats/output_Si_SiN_"$thickness"mm.root  ../Resultats/coating_thickness/
	done
	until [ -e ../Resultats/coating_thickness/output_Ge_SiO_"$thickness"mm.root ]
    	do
		./SCOPSim output_Ge_SiO_"$thickness"mm 10000 vrml.mac OFF LDMat=Germanium LDCoatRINDEX=2.48 LDCoatThickness="$thickness"
		mv ../Resultats/output_Ge_SiO_"$thickness"mm.root  ../Resultats/coating_thickness/
	done
    done
done
