for N in 0 1 2 3 4 5
do
    for DISTANCE in 0 1 2 3 4 5 6 7 8 9
    do
    	until [ -e ../Resultats/distance/output_"$N"."$DISTANCE"mm.root ]
    	do
		./SCOPSim output_"$N"."$DISTANCE"mm 1000 vrml.mac OFF S1Distance="$N"."$DISTANCE"
		mv ../Resultats/output_"$N"."$DISTANCE"mm.root ../Resultats/distance/
	done
    done
done
