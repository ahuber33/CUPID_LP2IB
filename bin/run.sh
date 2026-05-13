for THICKNESS in 30 60 90 120 150 180
do
    for RINDEX in 1.0 1.5 2.0 2.5 3.0 3.5 4.0 4.5 5.0 5.5
    do
    	until [ -e ../Resultats/coating_Si/output_"$THICKNESS"nm_n="$RINDEX".root ]
    	do
		./OpSim output_"$THICKNESS"nm_n="$RINDEX" 1000 vrml.mac OFF LDCoatThickness="$THICKNESS" LDCoatRINDEX="$RINDEX" LDMat=Silicon
		mv ../Resultats/output_"$THICKNESS"nm_n="$RINDEX".root ../Resultats/coating_Si/
	done
    done
done
